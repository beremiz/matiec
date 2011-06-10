/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2009-2011  Mario de Sousa (msousa@fe.up.pt)
 *  Copyright (C) 2007-2011  Laurent Bessard and Edouard Tisserant
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This code is made available on the understanding that it will not be
 * used in safety-critical situations without a full and competent review.
 */

/*
 * An IEC 61131-3 compiler.
 *
 * Based on the
 * FINAL DRAFT - IEC 61131-3, 2nd Ed. (2001-12-10)
 *
 */


/* Verify whether the semantic rules of data type compatibility are being followed.
 *
 * For example:
 */

#include "visit_expression_type.hh"
#include <typeinfo>
#include <list>
#include <string>
#include <string.h>
#include <strings.h>


#define FIRST_(symbol1, symbol2) (((symbol1)->first_order < (symbol2)->first_order)   ? (symbol1) : (symbol2))
#define  LAST_(symbol1, symbol2) (((symbol1)->last_order  > (symbol2)->last_order)    ? (symbol1) : (symbol2))

#define STAGE3_ERROR(symbol1, symbol2, msg) {                                          \
    fprintf(stderr, "%s:%d-%d..%d-%d: error : %s\n",                                   \
           FIRST_(symbol1,symbol2)->first_file, FIRST_(symbol1,symbol2)->first_line, FIRST_(symbol1,symbol2)->first_column, \
                                                LAST_(symbol1,symbol2) ->last_line,  LAST_(symbol1,symbol2) ->last_column,  \
           msg);                                                                       \
    il_error = true;                                                                   \
    error_found = true;                                                                \
  }


/* set to 1 to see debug info during execution */
static int debug = 0;


void *visit_expression_type_c::visit(program_declaration_c *symbol) {
  search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
  symbol->var_declarations->accept(*this);
  if (debug) printf("checking semantics in body of program %s\n", ((token_c *)(symbol->program_type_name))->value);
  il_parenthesis_level = 0;
  il_error = false;
  il_default_variable_type = NULL;
  symbol->function_block_body->accept(*this);
  il_default_variable_type = NULL;
  delete search_varfb_instance_type;
  search_varfb_instance_type = NULL;
  return NULL;
}

void *visit_expression_type_c::visit(function_declaration_c *symbol) {
  search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
  symbol->var_declarations_list->accept(*this);
  if (debug) printf("checking semantics in body of function %s\n", ((token_c *)(symbol->derived_function_name))->value);
  il_parenthesis_level = 0;
  il_error = false;
  il_default_variable_type = NULL;
  symbol->function_body->accept(*this);
  il_default_variable_type = NULL;
  delete search_varfb_instance_type;
  search_varfb_instance_type = NULL;
  return NULL;
}

void *visit_expression_type_c::visit(function_block_declaration_c *symbol) {
  search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
  symbol->var_declarations->accept(*this);
  if (debug) printf("checking semantics in body of FB %s\n", ((token_c *)(symbol->fblock_name))->value);
  il_parenthesis_level = 0;
  il_error = false;
  il_default_variable_type = NULL;
  symbol->fblock_body->accept(*this);
  il_default_variable_type = NULL;
  delete search_varfb_instance_type;
  search_varfb_instance_type = NULL;
  return NULL;
}









visit_expression_type_c::visit_expression_type_c(symbol_c *ignore) {
  error_found = false;
}

visit_expression_type_c::~visit_expression_type_c(void) {
}

bool visit_expression_type_c::get_error_found(void) {
  return error_found;
}



/* NOTE on data type handling and literals...
 * ==========================================
 *
 * Literals that are explicitly type cast 
 *   e.g.:   BYTE#42
 *           INT#65
 *           TIME#45h23m
 *               etc...
 *  are NOT considered literals in the following code.
 *  Since they are type cast, and their data type is fixed and well known,
 *  they are treated as a variable of that data type (except when determining lvalues)
 *  In other words, when calling search_constant_type_c on these constants, it returns
 *  a xxxxx_type_name_c, and not one of the xxxx_literal_c ! 
 *
 *  When the following code handles a literal, it is really a literal of unknown data type.
 *    e.g.   42, may be considered an int, a byte, a word, etc... 
 *
 * NOTE: type_symbol == NULL is valid!
 *       This will occur, for example, when and undefined/undeclared symbolic_variable is used in the program.
 *       This will not be of any type, so we always return false.
 */

/* A helper function... */
bool visit_expression_type_c::is_ANY_ELEMENTARY_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  return is_ANY_MAGNITUDE_type(type_symbol)
      || is_ANY_BIT_type      (type_symbol)
      || is_ANY_STRING_type   (type_symbol)
      || is_ANY_DATE_type     (type_symbol);
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_SAFEELEMENTARY_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  return is_ANY_SAFEMAGNITUDE_type(type_symbol)
      || is_ANY_SAFEBIT_type      (type_symbol)
      || is_ANY_SAFESTRING_type   (type_symbol)
      || is_ANY_SAFEDATE_type     (type_symbol);
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_ELEMENTARY_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  /* NOTE: doing 
   *          return is_ANY_SAFEELEMENTARY_type() || is_ANY_ELEMENTARY_type()
   *       is incorrect, as the literals would never be considered compatible...
   */
  return is_ANY_MAGNITUDE_compatible(type_symbol)
      || is_ANY_BIT_compatible      (type_symbol)
      || is_ANY_STRING_compatible   (type_symbol)
      || is_ANY_DATE_compatible     (type_symbol);
}


/* A helper function... */
bool visit_expression_type_c::is_ANY_MAGNITUDE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(time_type_name_c)) {return true;}
  return is_ANY_NUM_type(type_symbol);
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_SAFEMAGNITUDE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safetime_type_name_c)) {return true;}
  return is_ANY_SAFENUM_type(type_symbol);
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_MAGNITUDE_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_MAGNITUDE_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEMAGNITUDE_type(type_symbol))              {return true;}

  return is_ANY_NUM_compatible(type_symbol);
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_NUM_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_type(type_symbol))                       {return true;}
  if (is_ANY_INT_type(type_symbol))                        {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_SAFENUM_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  return is_ANY_SAFEREAL_type(type_symbol) 
      || is_ANY_SAFEINT_type (type_symbol);
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_NUM_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_compatible(type_symbol))                       {return true;}
  if (is_ANY_INT_compatible(type_symbol))                        {return true;}
  return false;  
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_DATE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(date_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(tod_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(dt_type_name_c))   {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_SAFEDATE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safedate_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safetod_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safedt_type_name_c))   {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_DATE_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_DATE_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEDATE_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_STRING_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(string_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(wstring_type_name_c)) {return true;}
// TODO literal_string ???
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_SAFESTRING_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safestring_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safewstring_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_STRING_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_STRING_type    (type_symbol))              {return true;}
  if (is_ANY_SAFESTRING_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_INT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(sint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(int_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(dint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(lint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(usint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(uint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(udint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(ulint_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_SAFEINT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safesint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safeint_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(safedint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safelint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safeusint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safeuint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safeudint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safeulint_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_INT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_INT_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEINT_type(type_symbol))              {return true;}
  if (is_literal_integer_type(type_symbol))          {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_REAL_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(real_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(lreal_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_SAFEREAL_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safereal_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safelreal_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_REAL_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEREAL_type(type_symbol))              {return true;}
  if (is_literal_real_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_BIT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(bool_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(byte_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(word_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(dword_type_name_c))    {return true;}
  if (typeid(*type_symbol) == typeid(lword_type_name_c))    {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_SAFEBIT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safebool_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(safebyte_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(safeword_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(safedword_type_name_c))    {return true;}
  if (typeid(*type_symbol) == typeid(safelword_type_name_c))    {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_BIT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_BIT_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEBIT_type(type_symbol))              {return true;}
  if (is_nonneg_literal_integer_type(type_symbol))   {return true;}
  if (is_literal_bool_type(type_symbol))             {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_BOOL_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(bool_type_name_c))      {return true;}
  return false;
}

/* A helper function... */
bool visit_expression_type_c::is_SAFEBOOL_type(symbol_c *type_symbol){
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safebool_type_name_c))  {return true;}
  return false;  
}

/* A helper function... */
bool visit_expression_type_c::is_ANY_BOOL_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_BOOL_type    (type_symbol))              {return true;}
  if (is_SAFEBOOL_type(type_symbol))              {return true;}
  if (is_literal_bool_type(type_symbol))              {return true;}
  return false;
}


#define is_type(type_name_symbol, type_name_class)  (typeid(*type_name_symbol) == typeid(type_name_class))


#define sizeoftype(symbol) get_sizeof_datatype_c::getsize(symbol)


/* A helper function... */
bool visit_expression_type_c::is_literal_integer_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(neg_integer_c))        {return true;}
  return is_nonneg_literal_integer_type(type_symbol);
}


/* A helper function... */
bool visit_expression_type_c::is_nonneg_literal_integer_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(integer_c))        {return true;}
  if (typeid(*type_symbol) == typeid(binary_integer_c)) {return true;}
  if (typeid(*type_symbol) == typeid(octal_integer_c))  {return true;}
  if (typeid(*type_symbol) == typeid(hex_integer_c))    {return true;}
  return false;
}


/* A helper function... */
bool visit_expression_type_c::is_literal_real_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(real_c))     {return true;}
  if (typeid(*type_symbol) == typeid(neg_real_c)) {return true;}
  return false;
}


/* A helper function... */
bool visit_expression_type_c::is_literal_bool_type(symbol_c *type_symbol) {
  bool_type_name_c bool_t;

  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(boolean_true_c))    {return true;}
  if (typeid(*type_symbol) == typeid(boolean_false_c))   {return true;}
  if (is_nonneg_literal_integer_type(type_symbol))
    if (sizeoftype(&bool_t) >= sizeoftype(type_symbol))  {return true;}
  return false;
}

/* Determine the common data type between two data types.
 * If no common data type found, return NULL.
 *
 * If data types are identical, return the first (actually any would do...).
 * If any of the data types is a literal, we confirm that 
 *   the literal uses less bits than the fixed size data type.
 *   e.g. BYTE and 1024 returns NULL
 *        BYTE and 255  returns BYTE
 *
 * If two literals, then return the literal that requires more bits...
 */

symbol_c *visit_expression_type_c::common_type__(symbol_c *first_type, symbol_c *second_type) {
  if (first_type == NULL && second_type == NULL) {return NULL;}
  if (first_type == NULL)  {return second_type;}
  if (second_type == NULL) {return first_type;}

  if (is_literal_integer_type(first_type) && is_literal_integer_type(second_type))
    {return ((sizeoftype(first_type) > sizeoftype(second_type))? first_type:second_type);}

  if (is_literal_real_type(first_type) && is_literal_real_type(second_type))
    {return ((sizeoftype(first_type) > sizeoftype(second_type))? first_type:second_type);}

  if (is_literal_bool_type(first_type) && is_literal_bool_type(second_type))
    {return first_type;}

  /* The following check can only be made after the is_literal_XXXX checks */
  /* When two literals of the same type, with identical typeid's are checked,
   * we must return the one that occupies more bits... This is done above.
   */
  if (typeid(*first_type) == typeid(*second_type)) {return first_type;}

  /* NOTE Although a BOOL is also an ANY_BIT, we must check it explicitly since some
   *       literal bool values are not literal integers...
   */ 
  if (is_BOOL_type(first_type)        && is_literal_bool_type(second_type))    {return first_type;}
  if (is_BOOL_type(second_type)       && is_literal_bool_type(first_type))     {return second_type;}

  if (is_SAFEBOOL_type(first_type)    && is_literal_bool_type(second_type))    {return first_type;}
  if (is_SAFEBOOL_type(second_type)   && is_literal_bool_type(first_type))     {return second_type;}

  if (is_SAFEBOOL_type(first_type)    && is_BOOL_type(second_type))            {return second_type;}
  if (is_SAFEBOOL_type(second_type)   && is_BOOL_type(first_type))             {return first_type;}

  if (is_ANY_BIT_type(first_type)     && is_nonneg_literal_integer_type(second_type))
    {return ((sizeoftype(first_type)  >= sizeoftype(second_type))? first_type :NULL);}
  if (is_ANY_BIT_type(second_type)    && is_nonneg_literal_integer_type(first_type))
    {return ((sizeoftype(second_type) >= sizeoftype(first_type)) ? second_type:NULL);}

  if (is_ANY_SAFEBIT_type(first_type)     && is_nonneg_literal_integer_type(second_type))
    {return ((sizeoftype(first_type)  >= sizeoftype(second_type))? first_type :NULL);}
  if (is_ANY_SAFEBIT_type(second_type)    && is_nonneg_literal_integer_type(first_type))
    {return ((sizeoftype(second_type) >= sizeoftype(first_type)) ? second_type:NULL);}

  if  (is_ANY_SAFEBIT_type(first_type)    && is_ANY_BIT_type(second_type))
    {return ((sizeoftype(first_type) == sizeoftype(second_type))? second_type:NULL);}
  if  (is_ANY_SAFEBIT_type(second_type)   && is_ANY_BIT_type(first_type))
    {return ((sizeoftype(first_type) == sizeoftype(second_type))? first_type :NULL);}

  if (is_ANY_INT_type(first_type)     && is_literal_integer_type(second_type))
    {return ((sizeoftype(first_type)  >= sizeoftype(second_type))? first_type :NULL);}
  if (is_ANY_INT_type(second_type)    && is_literal_integer_type(first_type))
    {return ((sizeoftype(second_type) >= sizeoftype(first_type)) ? second_type:NULL);}

  if (is_ANY_SAFEINT_type(first_type)     && is_literal_integer_type(second_type))
    {return ((sizeoftype(first_type)  >= sizeoftype(second_type))? first_type :NULL);}
  if (is_ANY_SAFEINT_type(second_type)    && is_literal_integer_type(first_type))
    {return ((sizeoftype(second_type) >= sizeoftype(first_type)) ? second_type:NULL);}

  if  (is_ANY_SAFEINT_type(first_type)    && is_ANY_INT_type(second_type))
    {return ((sizeoftype(first_type) == sizeoftype(second_type))? second_type:NULL);}
  if  (is_ANY_SAFEINT_type(second_type)   && is_ANY_INT_type(first_type))
    {return ((sizeoftype(first_type) == sizeoftype(second_type))? first_type :NULL);}

  if (is_ANY_REAL_type(first_type)    && is_literal_real_type(second_type))
    {return ((sizeoftype(first_type)  >= sizeoftype(second_type))? first_type :NULL);}
  if (is_ANY_REAL_type(second_type)   && is_literal_real_type(first_type))
    {return ((sizeoftype(second_type) >= sizeoftype(first_type)) ? second_type:NULL);}

  if (is_ANY_SAFEREAL_type(first_type)    && is_literal_real_type(second_type))
    {return ((sizeoftype(first_type)  >= sizeoftype(second_type))? first_type :NULL);}
  if (is_ANY_SAFEREAL_type(second_type)   && is_literal_real_type(first_type))
    {return ((sizeoftype(second_type) >= sizeoftype(first_type)) ? second_type:NULL);}

  if  (is_ANY_SAFEREAL_type(first_type)    && is_ANY_REAL_type(second_type))
    {return ((sizeoftype(first_type) == sizeoftype(second_type))? second_type:NULL);}
  if  (is_ANY_SAFEREAL_type(second_type)   && is_ANY_REAL_type(first_type))
    {return ((sizeoftype(first_type) == sizeoftype(second_type))? first_type :NULL);}

  /* the Time and Date types... */
  if (is_type(first_type,  safetime_type_name_c) && is_type(second_type, time_type_name_c))  {return second_type;}
  if (is_type(second_type, safetime_type_name_c) && is_type( first_type, time_type_name_c))  {return  first_type;}

  if (is_type(first_type,  safedate_type_name_c) && is_type(second_type, date_type_name_c))  {return second_type;}
  if (is_type(second_type, safedate_type_name_c) && is_type( first_type, date_type_name_c))  {return  first_type;}

  if (is_type(first_type,  safedt_type_name_c)   && is_type(second_type, dt_type_name_c))    {return second_type;}
  if (is_type(second_type, safedt_type_name_c)   && is_type( first_type, dt_type_name_c))    {return  first_type;}

  if (is_type(first_type,  safetod_type_name_c)  && is_type(second_type, tod_type_name_c))   {return second_type;}
  if (is_type(second_type, safetod_type_name_c)  && is_type( first_type, tod_type_name_c))   {return  first_type;}

  /* no common type */
  return NULL;
}

/* Determine the common data type between two data types.
 * Unlike the common_type__() function, we stop the compiler with an ERROR
 *  if no common data type is found.
 */
symbol_c *visit_expression_type_c::common_type(symbol_c *first_type, symbol_c *second_type) {
/*  
  symbol_c *res = common_type__(first_type, second_type);
  if (NULL == res) ERROR;
  return res;
*/
  return common_type__(first_type, second_type);
}


/* Return TRUE if the second (value) data type may be assigned to a variable of the first (variable) data type
 * such as: 
 *     var_type     value_type
 *    BOOL           BYTE#7     -> returns false
 *    INT            INT#7      -> returns true
 *    INT            7          -> returns true
 *    REAL           7.89       -> returns true
 *    REAL           7          -> returns true
 *    INT            7.89       -> returns false
 *    SAFEBOOL       BOOL#1     -> returns false   !!!
 *   etc...
 *
 * NOTE: It is assumed that the var_type is the data type of an lvalue
 */
bool visit_expression_type_c::is_valid_assignment(symbol_c *var_type, symbol_c *value_type) {
  if (var_type == NULL)   {/* STAGE3_ERROR(value_type, value_type, "Var_type   == NULL"); */ return false;}
  if (value_type == NULL) {/* STAGE3_ERROR(var_type,   var_type,   "Value_type == NULL"); */ return false;}

  symbol_c *common_type = common_type__(var_type, value_type);
  if (NULL == common_type)
    return false;
  return (typeid(*var_type) == typeid(*common_type));
}


/* Return TRUE if there is a common data type, otherwise return FALSE
 * i.e., return TRUE if both data types may be used simultaneously in an expression
 * such as:
 *    BOOL#0     AND BYTE#7  -> returns false
 *    0          AND BYTE#7  -> returns true
 *    INT#10     AND INT#7   -> returns true
 *    INT#10     AND 7       -> returns true
 *    REAL#34.3  AND 7.89    -> returns true
 *    REAL#34.3  AND 7       -> returns true
 *    INT#10     AND 7.89    -> returns false
 *    SAFEBOOL#0 AND BOOL#1  -> returns true   !!!
 *   etc...
 */
bool visit_expression_type_c::is_compatible_type(symbol_c *first_type, symbol_c *second_type) {
  if (first_type == NULL || second_type == NULL) {return false;}
  return (NULL != common_type__(first_type, second_type));
}



#define is_num_type      is_ANY_NUM_compatible
#define is_integer_type  is_ANY_INT_compatible
#define is_real_type     is_ANY_REAL_compatible
#define is_binary_type   is_ANY_BIT_compatible
 /* actually the ROR, ROL, SHL, and SHR function also accept boolean type! */
#define is_nbinary_type  is_ANY_BIT_compatible
#define compute_standard_function_default visit_expression_type_c::compute_standard_function_default
#define compute_standard_function_il visit_expression_type_c::compute_standard_function_il
#define search_expression_type_c visit_expression_type_c
#define search(x) search_f(x)
#define next() next_nf()
//     #define search_constant_type_c::constant_int_type_name  search_expression_type_c::integer
#define constant_int_type_name  integer
#define is_same_type is_compatible_type
#include "../absyntax_utils/search_type_code.c"
#undef is_same_type
#undef constant_int_type_name
//     #undef search_constant_type_c::constant_int_type_name
#undef next
#undef search
#undef compute_standard_function_default
#undef compute_standard_function_il
#undef search_expression_type_c
#undef is_real_type
#undef is_binary_type
#undef is_nbinary_type
#undef is_integer_type
#undef is_num_type






/* A helper function... */
/*
symbol_c *visit_expression_type_c::compute_boolean_expression(symbol_c *left_type, symbol_c *right_type,
                                                              is_data_type_t is_data_type) {
*/
symbol_c *visit_expression_type_c::compute_expression(symbol_c *left_type,      symbol_c *right_type,     is_data_type_t is_data_type,
						      symbol_c *left_expr, symbol_c *right_expr) {
  bool error = false;

  if (!(this->*is_data_type)(left_type)) {
    if (debug) printf("visit_expression_type_c::compute_expression(): invalid left_type\n");
    if (left_expr != NULL)
      STAGE3_ERROR(left_expr, left_expr, "Invalid data type of operand, or of data resulting from previous IL instructions.");
    error = true;
  }
  if (!(this->*is_data_type)(right_type)) {
    if (debug) printf("visit_expression_type_c::compute_expression(): invalid right_type\n");
    if (right_expr != NULL)
      STAGE3_ERROR(right_expr, right_expr, "Invalid data type of operand.");
    error = true;
  }
  if (!is_compatible_type(left_type, right_type)) {
    if (debug) printf("visit_expression_type_c::compute_expression(): left_type & right_type are incompatible\n");
    if ((left_expr != NULL) && (right_expr != NULL))
      STAGE3_ERROR(left_expr, right_expr, "Type mismatch between operands.");
    error = true;
  }

  if (error)
    return NULL;
  else
    return common_type(left_type, right_type);
}


# if 0
/* A helper function... */
symbol_c *visit_expression_type_c::compute_numeric_expression(symbol_c *left_type, symbol_c *right_type,
                                                              is_data_type_t is_data_type) {
  bool error = false;

  if (!(this->*is_data_type)(left_type)) {
    STAGE3_ERROR(left_type, right_type, "Invalid data type of left operand.");
    error = true;
  }
  if (!(this->*is_data_type)(right_type)) {
    STAGE3_ERROR(left_type, right_type, "Invalid data type of right operand.");
    error = true;
  }
  if (!is_compatible_type(left_type, right_type)) {
    STAGE3_ERROR(left_type, right_type, "Type mismatch between operands.");
    error = true;
  }

/*
  if (is_literal_integer_type(left_type) || is_literal_real_type(left_type)) {
    return right_type;
  } else {
    return left_type;
  }
*/

  if (error)
    return NULL;
  else
    return common_type(left_type, right_type);

  /* humour the compiler... */
/*
  return NULL;
*/
}
#endif





/* A helper function... */
/* check the semantics of a FB or Function non-formal call */
/* e.g. foo(1, 2, 3, 4);  */
void visit_expression_type_c::check_nonformal_call(symbol_c *f_call, symbol_c *f_decl, bool use_il_defvar) {
  symbol_c *call_param_value, *call_param_type, *param_type;
  identifier_c *param_name;
  function_param_iterator_c       fp_iterator(f_decl);
  function_call_param_iterator_c fcp_iterator(f_call);

  /* if use_il_defvar, then the first parameter for the call comes from the il_default_variable */
  if (use_il_defvar) {
    /* The first parameter of the function corresponds to the il_default_variable_type of the function call */
    do {
      param_name = fp_iterator.next();
      if(param_name == NULL) break;
      /*  The EN and ENO parameters are default parameters.
       *  In the non-formal invocation of a function there can be no assignment of
       * values to these parameters. Therefore, we ignore the parameters declared
       * in the function.
       */
    } while ((strcmp(param_name->value, "EN") == 0) || (strcmp(param_name->value, "ENO") == 0));
    /* If the function does not have any parameters (param_name == NULL)
     * then we cannot compare its type with the il_default_variable_type.
     */
    if(param_name != NULL) {
      param_type = fp_iterator.param_type();
      if(!is_valid_assignment(param_type, il_default_variable_type)) 
        STAGE3_ERROR(f_call, f_call, "In function/FB call, first parameter has invalid data type.");
    }
  } // if (use_il_defvar)

  /* Iterating through the non-formal parameters of the function call */
  while((call_param_value = fcp_iterator.next_nf()) != NULL) {
    /* Obtaining the type of the current parameter in the function call */
    call_param_type = base_type((symbol_c*)call_param_value->accept(*this));
    if (call_param_type == NULL) STAGE3_ERROR(call_param_value, call_param_value, "Could not determine data type of value being passed in function/FB call.");;

    /* Iterate to the next parameter of the function being called.
     * Get the name of that parameter, and ignore if EN or ENO.
     */
    do {
      param_name = fp_iterator.next();
      /* If there is no parameter declared with that name */
      if(param_name == NULL) {STAGE3_ERROR(f_call, f_call, "Too many parameters in function/FB call."); break;}
    } while ((strcmp(param_name->value, "EN") == 0) || (strcmp(param_name->value, "ENO") == 0));

    if(param_name != NULL) {
      /* Get the parameter type */
      param_type = fp_iterator.param_type();
      /* If the declared parameter and the parameter from the function call do no have the same type */
      if(!is_valid_assignment(param_type, call_param_type)) STAGE3_ERROR(call_param_value, call_param_value, "Type mismatch in function/FB call parameter.");
    }
  }
}

void visit_expression_type_c::compute_input_operatores(symbol_c *symbol, const char *input_operator){
  symbol_c *call_param_type;
  symbol_c *fb_decl = il_operand_type;
    /* The following should never occur. The function block must be defined, 
     * and the FB type being called MUST be in the symtable... 
     * This was all already checked at stage 2!
     */
  if (NULL == fb_decl){ 
    STAGE3_ERROR(symbol, symbol, "Parameter operator needs an instance of a function block operand.");
    ERROR;
  }

   /* Iterating through the formal parameters of the function call */
  identifier_c call_param_name(input_operator);

  /* Obtaining the type of the value being passed in the function call */
  call_param_type = il_default_variable_type;
  if (call_param_type == NULL) {
    STAGE3_ERROR(&call_param_name, &call_param_name, "Could not determine data type of value being passed in function/FB call.");
    /* The data value being passed is possibly any enumerated type value.
     * We do not yet handle semantic verification of enumerated types.
     */
    ERROR;
  }
  call_param_type = base_type(call_param_type);
  if (call_param_type == NULL) STAGE3_ERROR(&call_param_name, &call_param_name, "Could not determine data type of value being passed in function/FB call.");
  

  check_formal_parameter(&call_param_name, call_param_type, fb_decl);
//   return NULL;
}

void visit_expression_type_c::check_formal_parameter(symbol_c *call_param_name, symbol_c *call_param_type, symbol_c *f_decl) {
  symbol_c *param_type;
  identifier_c *param_name;
  function_param_iterator_c       fp_iterator(f_decl);
 
  /* Find the corresponding parameter of the function being called */
  param_name = fp_iterator.search(call_param_name);
  if(param_name == NULL) {
    STAGE3_ERROR(call_param_name, call_param_name, "Invalid parameter in function/FB call.");
  } else {
    /* Get the parameter type */
    param_type = fp_iterator.param_type();
    /* If the declared parameter and the parameter from the function call have the same type */
    if(!is_valid_assignment(param_type, call_param_type)) STAGE3_ERROR(call_param_name, call_param_name, "Type mismatch function/FB call parameter.");
  }
}


/* A helper function... */
/* check the semantics of a FB or Function formal call */
/* e.g. foo(IN1 := 1, OUT1 =>x, EN := true);  */
void visit_expression_type_c::check_formal_call(symbol_c *f_call, symbol_c *f_decl) {
  symbol_c *call_param_value, *call_param_type, *call_param_name, *param_type;
  symbol_c *verify_duplicate_param;
  identifier_c *param_name;
  function_param_iterator_c       fp_iterator(f_decl);
  function_call_param_iterator_c fcp_iterator(f_call);

  /* Iterating through the formal parameters of the function call */
  while((call_param_name = fcp_iterator.next_f()) != NULL) {
        
    /* Obtaining the value being passed in the function call */
    call_param_value = fcp_iterator.get_current_value();
    /* the following should never occur. If it does, then we have a bug in our code... */
    if (NULL == call_param_value) ERROR;

    /* Checking if there are duplicated parameter values */
    verify_duplicate_param = fcp_iterator.search_f(call_param_name);
    if(verify_duplicate_param != call_param_value){
      STAGE3_ERROR(call_param_name, verify_duplicate_param, "Duplicated parameter values.");
    }   

    /* Obtaining the type of the value being passed in the function call */
    call_param_type = (symbol_c*)call_param_value->accept(*this);
    if (call_param_type == NULL) {
      STAGE3_ERROR(call_param_name, call_param_value, "Could not determine data type of value being passed in function/FB call.");
      /* The data value being passed is possibly any enumerated type value.
       * We do not yet handle semantic verification of enumerated types.
       */
      ERROR;
    }
    call_param_type = base_type(call_param_type);
    if (call_param_type == NULL) STAGE3_ERROR(call_param_name, call_param_value, "Could not determine data type of value being passed in function/FB call.");

    /* Find the corresponding parameter of the function being called */
    param_name = fp_iterator.search(call_param_name);
    if(param_name == NULL) {
      STAGE3_ERROR(call_param_name, call_param_name, "Invalid parameter in function/FB call.");
    } else {
      /* Get the parameter type */
      param_type = fp_iterator.param_type();
      /* If the declared parameter and the parameter from the function call have the same type */
      if(!is_valid_assignment(param_type, call_param_type)) STAGE3_ERROR(call_param_name, call_param_value, "Type mismatch function/FB call parameter.");
    }
  }
}




/* a helper function... */
symbol_c *visit_expression_type_c::base_type(symbol_c *symbol) {
  /* NOTE: symbol == NULL is valid. It will occur when, for e.g., an undefined/undeclared symbolic_variable is used
   *       in the code.
   */
  if (symbol == NULL) return NULL;
  return (symbol_c *)symbol->accept(search_base_type);
}


/* a helper function... */
void *visit_expression_type_c::verify_null(symbol_c *symbol){
  if(il_default_variable_type == NULL){
    STAGE3_ERROR(symbol, symbol, "Missing LD instruction (or equivalent) before this instruction.");
  }
  if(il_operand_type == NULL){
    STAGE3_ERROR(symbol, symbol, "This instruction requires an operand.");
  }
  return NULL;
}


/********************************/
/* B 1.3.3 - Derived data types */
/********************************/
void *visit_expression_type_c::visit(data_type_declaration_c *symbol) {
  // TODO !!!
  /* for the moment we must return NULL so semantic analysis of remaining code is not interrupted! */
  return NULL;
}


/*********************/
/* B 1.4 - Variables */
/*********************/

void *visit_expression_type_c::visit(symbolic_variable_c *symbol) {
  return search_varfb_instance_type->get_type(symbol);
}

/********************************************/
/* B 1.4.1 - Directly Represented Variables */
/********************************************/
void *visit_expression_type_c::visit(direct_variable_c *symbol) {
  switch (symbol->value[2]) {
    case 'X': // bit - 1 bit
      return (void *)&bool_type_name;
    case 'B': // byte - 8 bits
      return (void *)&byte_type_name;
    case 'W': // word - 16 bits
      return (void *)&word_type_name;
    case 'D': // double word - 32 bits
      return (void *)&dword_type_name;
    case 'L': // long word - 64 bits
      return (void *)&lword_type_name;
    default:  // if none of the above, then the empty string was used <=> boolean 
      return (void *)&bool_type_name;
   }
}

/*************************************/
/* B 1.4.2 - Multi-element variables */
/*************************************/
void *visit_expression_type_c::visit(array_variable_c *symbol) {
  return search_varfb_instance_type->get_type(symbol);
}

void *visit_expression_type_c::visit(structured_variable_c *symbol) {
  return search_varfb_instance_type->get_type(symbol);
}



/********************************/
/* B 1.7 Configuration elements */
/********************************/
void *visit_expression_type_c::visit(configuration_declaration_c *symbol) {
  // TODO !!!
  /* for the moment we must return NULL so semantic analysis of remaining code is not interrupted! */
  return NULL;
}


/****************************************/
/* B.2 - Language IL (Instruction List) */
/****************************************/
/***********************************/
/* B 2.1 Instructions and Operands */
/***********************************/
/*| instruction_list il_instruction */
/* The visitor of the base class search_visitor_c will handle calling each instruction in the list.
 * We do not need to do anything here...
 */
// void *visit_expression_type_c::visit(instruction_list_c *symbol)

/* | label ':' [il_incomplete_instruction] eol_list */
//SYM_REF2(il_instruction_c, label, il_instruction)
// void *visit_expression_type_c::visit(il_instruction_c *symbol);


/* | il_simple_operator [il_operand] */
// SYM_REF2(il_simple_operation_c, il_simple_operator, il_operand)
void *visit_expression_type_c::visit(il_simple_operation_c *symbol) {
  if (il_error)
    return NULL;

  /* determine the data type of the operand */
  il_operand = symbol->il_operand;
  if (symbol->il_operand != NULL){
    il_operand_type = base_type((symbol_c *)symbol->il_operand->accept(*this));
  } else {
    il_operand_type = NULL;
  }
  /* recursive call to see whether data types are compatible */
  symbol->il_simple_operator->accept(*this);

  il_operand_type = NULL;
  il_operand = NULL;
  return NULL;
}

// | function_name [il_operand_list] */
//SYM_REF2(il_function_call_c, function_name, il_operand_list)
void *visit_expression_type_c::visit(il_function_call_c *symbol) {
  if (il_error)
    return NULL;

  /* First find the declaration of the function being called! */
  function_declaration_c *f_decl = function_symtable.find_value(symbol->function_name);

  symbol_c *return_data_type = NULL;

  if (f_decl == function_symtable.end_value()) {
    function_type_t current_function_type = get_function_type((identifier_c *)symbol->function_name);
    if (current_function_type == function_none) ERROR;
    /*  This code is for the functions that the user did not declare and that are
     * part of the IL or ST languagem (built-in functions).
     *  For now we won't do the semantics analysis for that kind of functions.
    */
    /*  
    return_data_type = (symbol_c *)search_expression_type->compute_standard_function_default(NULL, symbol);
    if (NULL == return_data_type) ERROR;

    function_call_param_iterator_c fcp_iterator(symbol);

    int nb_param = 0;
    if (symbol->il_param_list != NULL)
      nb_param += ((list_c *)symbol->il_param_list)->n;

    identifier_c en_param_name("EN");*/
    /* Get the value from EN param */
    /*symbol_c *EN_param_value = fcp_iterator.search(&en_param_name);
    if (EN_param_value == NULL)
      EN_param_value = (symbol_c*)(new boolean_literal_c((symbol_c*)(new bool_type_name_c()), new boolean_true_c()));
    else
      nb_param --;
    ADD_PARAM_LIST(EN_param_value, (symbol_c*)(new bool_type_name_c()), function_param_iterator_c::direction_in)

    identifier_c eno_param_name("EN0");*/
    /* Get the value from ENO param */
    /*symbol_c *ENO_param_value = fcp_iterator.search(&eno_param_name);
    if (ENO_param_value != NULL)
      nb_param --;
    ADD_PARAM_LIST(ENO_param_value, (symbol_c*)(new bool_type_name_c()), function_param_iterator_c::direction_out)
    
    #include "st_code_gen.c"
    */
  } else {
    /* determine the base data type returned by the function being called... */
    return_data_type = base_type(f_decl->type_name);
    /* If the following occurs, then we must have some big bug in the syntax parser (stage 2)... */
    if (NULL == return_data_type) ERROR;

    /* check semantics of data passed in the function call... */
    check_nonformal_call(symbol, f_decl, true);

    /* set the new ddata type of the default variable for the following verifications... */
    il_default_variable_type = return_data_type;
  }
  return NULL;
}


/* | il_expr_operator '(' [il_operand] eol_list [simple_instr_list] ')' */
// SYM_REF3(il_expression_c, il_expr_operator, il_operand, simple_instr_list);
void *visit_expression_type_c::visit(il_expression_c *symbol) {
  if (il_error)
    return NULL;

  symbol_c *il_default_variable_type_back = il_default_variable_type;

  il_parenthesis_level++;

  if(symbol->il_operand != NULL) {
     il_default_variable_type = base_type((symbol_c *)symbol->il_operand->accept(*this));
  } else {
     il_default_variable_type = NULL;
  }

  if(symbol->simple_instr_list != NULL) {
    symbol->simple_instr_list->accept(*this);
  }

  il_parenthesis_level--;
  if (il_parenthesis_level < 0) ERROR;

  il_operand = symbol->simple_instr_list;
  il_operand_type = il_default_variable_type;
  il_default_variable_type = il_default_variable_type_back;

  /* Now check the if the data type semantics of operation are correct,
   * but only if no previous error has been found...
   */
  if (!il_error)
    symbol->il_expr_operator->accept(*this);

  il_operand_type = NULL;
  il_operand = NULL;
  return NULL;
}


#if 0
/*  il_jump_operator label */
SYM_REF2(il_jump_operation_c, il_jump_operator, label)
void *visit_expression_type_c::visit(il_jump_operation_c *symbol);
#endif


/*   il_call_operator prev_declared_fb_name
 * | il_call_operator prev_declared_fb_name '(' ')'
 * | il_call_operator prev_declared_fb_name '(' eol_list ')'
 * | il_call_operator prev_declared_fb_name '(' il_operand_list ')'
 * | il_call_operator prev_declared_fb_name '(' eol_list il_param_list ')'
 */
/* SYM_REF4(il_fb_call_c, il_call_operator, fb_name, il_operand_list, il_param_list) */
void *visit_expression_type_c::visit(il_fb_call_c *symbol) {
  if (il_error)
    return NULL;

  /* first check whether the il_default_variable is of the correct type
   * for the CAL / CALC / CALCN operator being used...
   */
  symbol->il_call_operator->accept(*this);

  /* Now check the FB call itself... */

  /* First we find the declaration of the FB type of the FB instance being called... */
  /* e.g.  Function_block foo_fb_type
   *         ...
   *       End_Function_Block
   *
   *       Program test
   *         var fb1 : foo_fb_type; end_var
   *         fb1(...)
   *       End_Program
   *
   *    search_varfb_instance_type->get_type( identifier_c("fb1") )
   *    in the scope of Program 'test'
   *    will return the fb declaration of foo_fb_type !!
   */
#if 0
  symbol_c *fb_decl_symbol = search_varfb_instance_type->get_type(symbol->fb_name);
    /* The following should never occur. The function block must be defined, 
     * and the FB type being called MUST be in the symtable... 
     * This was all already checked at stage 2!
     */
  if (NULL == fb_decl_symbol) ERROR;

  function_block_declaration_c *fb_decl = dynamic_cast<function_block_declaration_c *>(fb_decl_symbol);
    /* should never occur. ... */
  if (NULL == fb_decl) ERROR;
#endif
  symbol_c *fb_decl = search_varfb_instance_type->get_type(symbol->fb_name);
    /* The following should never occur. The function block must be defined, 
     * and the FB type being called MUST be in the symtable... 
     * This was all already checked at stage 2!
     */
  if (NULL == fb_decl) ERROR;

  /* now check the semantics of the fb call... */
  /* If the syntax parser is working correctly, exactly one of the 
   * following two symbols will be NULL, while the other is != NULL.
   */
  if (NULL != symbol->il_operand_list)  check_nonformal_call(symbol, fb_decl);
  if (NULL != symbol->il_param_list)    check_formal_call   (symbol, fb_decl);

  return NULL;
}



/* | function_name '(' eol_list [il_param_list] ')' */
/* SYM_REF2(il_formal_funct_call_c, function_name, il_param_list) */
void *visit_expression_type_c::visit(il_formal_funct_call_c *symbol) {
  if (il_error)
    return NULL;

  function_declaration_c *f_decl = function_symtable.find_value(symbol->function_name);

  symbol_c *return_data_type = NULL;

  if (f_decl == function_symtable.end_value()) {
    function_type_t current_function_type = get_function_type((identifier_c *)symbol->function_name);
    if (current_function_type == function_none) ERROR;
    
    /*  This code is for the functions that the user did not declare and that are
     * part of the IL or ST languagem (built-in functions).
     *  For now we won't do the semantics analysis for that kind of functions.
    */
    #if 0
    return_data_type = (symbol_c *)search_expression_type->compute_standard_function_default(NULL, symbol);
    if (NULL == return_data_type) ERROR;
    
    function_call_param_iterator_c fcp_iterator(symbol);
    
    int nb_param = 0;
    if (symbol->il_param_list != NULL)
      nb_param += ((list_c *)symbol->il_param_list)->n;
    
    identifier_c en_param_name("EN");
    /* Get the value from EN param */
    symbol_c *EN_param_value = fcp_iterator.search(&en_param_name);
    if (EN_param_value == NULL)
      EN_param_value = (symbol_c*)(new boolean_literal_c((symbol_c*)(new bool_type_name_c()), new boolean_true_c()));
    else
      nb_param --;
    ADD_PARAM_LIST(EN_param_value, (symbol_c*)(new bool_type_name_c()), function_param_iterator_c::direction_in)
    
    identifier_c eno_param_name("EN0");
    /* Get the value from ENO param */
    symbol_c *ENO_param_value = fcp_iterator.search(&eno_param_name);
    if (ENO_param_value != NULL)
      nb_param --;
    ADD_PARAM_LIST(ENO_param_value, (symbol_c*)(new bool_type_name_c()), function_param_iterator_c::direction_out)
    
    #include "st_code_gen.c"
    #endif
  } else {
    /* determine the base data type returned by the function being called... */
    return_data_type = base_type(f_decl->type_name);
    /* the following should never occur. If it does, then we have a bug in the syntax parser (stage 2)... */
    if (NULL == return_data_type) ERROR;

    /* check semantics of data passed in the function call... */
    check_formal_call(symbol, f_decl);

    /* the data type of the data returned by the function, and stored in the il default variable... */
    il_default_variable_type = return_data_type;
  }
  return NULL;
}


#if 0
/* | il_operand_list ',' il_operand */
SYM_LIST(il_operand_list_c)
void *visit_expression_type_c::visit(il_operand_list_c *symbol);

/* | simple_instr_list il_simple_instruction */
SYM_LIST(simple_instr_list_c)
void *visit_expression_type_c::visit(simple_instr_list_c *symbol);

/* | il_initial_param_list il_param_instruction */
SYM_LIST(il_param_list_c)
void *visit_expression_type_c::visit(il_param_list_c *symbol);

/*  il_assign_operator il_operand
 * | il_assign_operator '(' eol_list simple_instr_list ')'
 */
SYM_REF3(il_param_assignment_c, il_assign_operator, il_operand, simple_instr_list)
void *visit_expression_type_c::visit(il_param_assignment_c *symbol);
/*  il_assign_out_operator variable */
SYM_REF2(il_param_out_assignment_c, il_assign_out_operator, variable)
void *visit_expression_type_c::visit(il_param_out_assignment_c *symbol);

#endif


/*******************/
/* B 2.2 Operators */
/*******************/

//SYM_REF0(LD_operator_c)
void *visit_expression_type_c::visit(LD_operator_c *symbol) {
  if (0 == il_parenthesis_level)
    il_error = false;

  if(il_operand_type == NULL)
      STAGE3_ERROR(symbol, symbol, "LD operator requires an operand.");
  il_default_variable_type = il_operand_type;
  return NULL;
}

// SYM_REF0(LDN_operator_c)
void *visit_expression_type_c::visit(LDN_operator_c *symbol) {
  if(il_operand_type == NULL)
      STAGE3_ERROR(symbol, symbol, "LDN operator requires an operand.");
  if(!is_ANY_BIT_compatible(il_operand_type))
      STAGE3_ERROR(symbol, il_operand, "invalid data type of LDN operand, should be of type ANY_BIT.");
  il_default_variable_type = il_operand_type;
  return NULL;
}

// SYM_REF0(ST_operator_c)
void *visit_expression_type_c::visit(ST_operator_c *symbol) {
  verify_null(symbol);

  if(!is_valid_assignment(il_operand_type, il_default_variable_type))
    STAGE3_ERROR(symbol, symbol, "Type mismatch in ST operation.");
  /* TODO: check whether il_operand_type is an LVALUE !! */
  /* data type of il_default_variable_type is unchanged... */
  // il_default_variable_type = il_default_variable_type;
  return NULL;
}

// SYM_REF0(STN_operator_c)
 void *visit_expression_type_c::visit(STN_operator_c *symbol) {
  verify_null(symbol);
  if(!is_valid_assignment(il_operand_type, il_default_variable_type))
    STAGE3_ERROR(symbol, symbol, "Type mismatch in ST operation.");
  /* TODO: check whether il_operand_type is an LVALUE !! */
  if(!is_ANY_BIT_compatible(il_default_variable_type))
      STAGE3_ERROR(symbol, symbol, "invalid data type of il_default_variable for STN operand, should be of type ANY_BIT.");
  if(!is_ANY_BIT_compatible(il_operand_type))
      STAGE3_ERROR(symbol, il_operand, "invalid data type of STN operand, should be of type ANY_BIT.");
  /* data type of il_default_variable_type is unchanged... */
  // il_default_variable_type = il_default_variable_type;
  return NULL;
}

//SYM_REF0(NOT_operator_c)
void *visit_expression_type_c::visit(NOT_operator_c *symbol) {
  if(il_operand_type != NULL){
    STAGE3_ERROR(symbol, il_operand, "NOT operator may not have an operand.");
    return NULL;
  }
  if(il_default_variable_type == NULL) {
    STAGE3_ERROR(symbol, symbol, "Il default variable should not be NULL.");
    return NULL;
  }
  if(!is_ANY_BIT_compatible(il_default_variable_type)) {
    STAGE3_ERROR(symbol, symbol, "Il default variable should be of type ANY_BIT.");
    return NULL;
  }
  /* data type of il_default_variable_type is unchanged... */
  // il_default_variable_type = il_default_variable_type;
  return NULL;
}

// SYM_REF0(S_operator_c)
void *visit_expression_type_c::visit(S_operator_c *symbol) {
  verify_null(symbol);
  if (!is_BOOL_type(il_default_variable_type)) {STAGE3_ERROR(symbol, symbol, "IL default variable should be BOOL type.");}
  if (!is_BOOL_type(il_operand_type)) {STAGE3_ERROR(symbol, il_operand, "operator S requires operand of type BOOL.");}
  /* TODO: check whether il_operand_type is an LVALUE !! */
  /* data type of il_default_variable_type is unchanged... */
  // il_default_variable_type = il_default_variable_type;
  return NULL;
}

// SYM_REF0(R_operator_c)
void *visit_expression_type_c::visit(R_operator_c *symbol) {
  verify_null(symbol);
  if (!is_BOOL_type(il_default_variable_type)) {STAGE3_ERROR(symbol, symbol, "IL default variable should be BOOL type.");}
  if (!is_BOOL_type(il_operand_type)) {STAGE3_ERROR(symbol, il_operand, "operator R requires operand of type BOOL.");}
  /* TODO: check whether il_operand_type is an LVALUE !! */
  /* data type of il_default_variable_type is unchanged... */
  // il_default_variable_type = il_default_variable_type;
  return NULL;
}


// SYM_REF0(S1_operator_c)
void *visit_expression_type_c::visit(S1_operator_c *symbol){
  compute_input_operatores(symbol, "S1");
  return NULL;
}

// SYM_REF0(R1_operator_c)
void *visit_expression_type_c::visit(R1_operator_c *symbol) {
  compute_input_operatores(symbol, "R1");
  return NULL;
}

// SYM_REF0(CLK_operator_c)
void *visit_expression_type_c::visit(CLK_operator_c *symbol) {
  compute_input_operatores(symbol, "CLK");
  return NULL;
}

// SYM_REF0(CU_operator_c)
void *visit_expression_type_c::visit(CU_operator_c *symbol) {
  compute_input_operatores(symbol, "CU");
  return NULL;
}

// SYM_REF0(CD_operator_c)
void *visit_expression_type_c::visit(CD_operator_c *symbol) {
  compute_input_operatores(symbol, "CD");
  return NULL;
}

// SYM_REF0(PV_operator_c)
void *visit_expression_type_c::visit(PV_operator_c *symbol) {
  compute_input_operatores(symbol, "PV");
  return NULL;
}

// SYM_REF0(IN_operator_c)
void *visit_expression_type_c::visit(IN_operator_c *symbol) {
  compute_input_operatores(symbol, "IN");
  return NULL;
}

// SYM_REF0(PT_operator_c)
void *visit_expression_type_c::visit(PT_operator_c *symbol) {
  compute_input_operatores(symbol, "PT");
  return NULL;
}

//SYM_REF0(AND_operator_c)
void *visit_expression_type_c::visit(AND_operator_c *symbol) {
  verify_null(symbol);
  il_default_variable_type = compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_BIT_compatible,
                                                symbol                  , il_operand);
  return NULL;
}

//SYM_REF0(OR_operator_c)
void *visit_expression_type_c::visit(OR_operator_c *symbol) {
  verify_null(symbol);
  il_default_variable_type = compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_BIT_compatible,
                                                symbol                  , il_operand);
  return NULL;
}

//SYM_REF0(XOR_operator_c)
void *visit_expression_type_c::visit(XOR_operator_c *symbol) {
  verify_null(symbol);
  il_default_variable_type = compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_BIT_compatible,
                                                symbol                  , il_operand);
  return NULL;
}

// SYM_REF0(ANDN_operator_c)
void *visit_expression_type_c::visit(ANDN_operator_c *symbol) {
  verify_null(symbol);
  il_default_variable_type = compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_BIT_compatible,
                                                symbol                  , il_operand);
  return NULL;
}

// SYM_REF0(ORN_operator_c)
void *visit_expression_type_c::visit(ORN_operator_c *symbol) {
  verify_null(symbol);
  il_default_variable_type = compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_BIT_compatible,
                                                symbol                  , il_operand);
  return NULL;
}

// SYM_REF0(XORN_operator_c)
void *visit_expression_type_c::visit(XORN_operator_c *symbol) {
  verify_null(symbol);
  il_default_variable_type = compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_BIT_compatible,
                                                symbol                  , il_operand);
  return NULL;
}

// SYM_REF0(ADD_operator_c)
void *visit_expression_type_c::visit(ADD_operator_c *symbol) {
  verify_null(symbol);
  symbol_c *left_type  = il_default_variable_type;
  symbol_c *right_type = il_operand_type;

/* The following is not required, it is already handled by compute_expression() ... */
/*
  if      (is_type(left_type, time_type_name_c) && is_type(right_type, time_type_name_c))
    il_default_variable_type = &time_type_name;
*/

  if      (is_type(left_type, tod_type_name_c)      && is_type(right_type, time_type_name_c))
    il_default_variable_type = &tod_type_name;
  else if (is_type(left_type, safetod_type_name_c)  && is_type(right_type, time_type_name_c))
    il_default_variable_type = &tod_type_name;
  else if (is_type(left_type, tod_type_name_c)      && is_type(right_type, safetime_type_name_c))
    il_default_variable_type = &tod_type_name;
  else if (is_type(left_type, safetod_type_name_c)  && is_type(right_type, safetime_type_name_c))
    il_default_variable_type = &safetod_type_name;

  else if (is_type(left_type, dt_type_name_c)       && is_type(right_type, time_type_name_c))
    il_default_variable_type = &dt_type_name;
  else if (is_type(left_type, safedt_type_name_c)   && is_type(right_type, time_type_name_c))
    il_default_variable_type = &dt_type_name;
  else if (is_type(left_type, dt_type_name_c)       && is_type(right_type, safetime_type_name_c))
    il_default_variable_type = &dt_type_name;
  else if (is_type(left_type, safedt_type_name_c)   && is_type(right_type, safetime_type_name_c))
    il_default_variable_type = &safedt_type_name;

  else il_default_variable_type = compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_MAGNITUDE_compatible,
                                                     symbol                  , il_operand);
  return NULL;
}

// SYM_REF0(SUB_operator_c)
void *visit_expression_type_c::visit(SUB_operator_c *symbol) {
  verify_null(symbol);
  symbol_c *left_type = il_default_variable_type;
  symbol_c *right_type = il_operand_type;;

/* The following is not required, it is already handled by compute_expression() ... */
/*
  if      (typeid(*left_type) == typeid(time_type_name_c) && typeid(*right_type) == typeid(time_type_name_c))
    il_default_variable_type = &time_type_name;
*/

  if      (is_type(left_type, tod_type_name_c)       && is_type(right_type, time_type_name_c))
    il_default_variable_type = &tod_type_name;
  else if (is_type(left_type, safetod_type_name_c)   && is_type(right_type, time_type_name_c))
    il_default_variable_type = &tod_type_name;
  else if (is_type(left_type, tod_type_name_c)       && is_type(right_type, safetime_type_name_c))
    il_default_variable_type = &tod_type_name;
  else if (is_type(left_type, safetod_type_name_c)   && is_type(right_type, safetime_type_name_c))
    il_default_variable_type = &safetod_type_name;

  else if (is_type(left_type, dt_type_name_c)       && is_type(right_type, time_type_name_c))
    il_default_variable_type = &dt_type_name;
  else if (is_type(left_type, safedt_type_name_c)   && is_type(right_type, time_type_name_c))
    il_default_variable_type = &dt_type_name;
  else if (is_type(left_type, dt_type_name_c)       && is_type(right_type, safetime_type_name_c))
    il_default_variable_type = &dt_type_name;
  else if (is_type(left_type, safedt_type_name_c)   && is_type(right_type, safetime_type_name_c))
    il_default_variable_type = &safedt_type_name;

  else if (is_type(left_type, date_type_name_c)     && is_type(right_type, date_type_name_c))
    il_default_variable_type = &time_type_name;
  else if (is_type(left_type, safedate_type_name_c) && is_type(right_type, date_type_name_c))
    il_default_variable_type = &time_type_name;
  else if (is_type(left_type, date_type_name_c)     && is_type(right_type, safedate_type_name_c))
    il_default_variable_type = &time_type_name;
  else if (is_type(left_type, safedate_type_name_c) && is_type(right_type, safedate_type_name_c))
    il_default_variable_type = &safetime_type_name;

  else if (is_type(left_type, tod_type_name_c)      && is_type(right_type, tod_type_name_c))
    il_default_variable_type = &time_type_name;
  else if (is_type(left_type, safetod_type_name_c)  && is_type(right_type, tod_type_name_c))
    il_default_variable_type = &time_type_name;
  else if (is_type(left_type, tod_type_name_c)      && is_type(right_type, safetod_type_name_c))
    il_default_variable_type = &time_type_name;
  else if (is_type(left_type, safetod_type_name_c)  && is_type(right_type, safetod_type_name_c))
    il_default_variable_type = &safetime_type_name;

  else if (is_type(left_type, dt_type_name_c)       && is_type(right_type, dt_type_name_c))
    il_default_variable_type = &time_type_name;
  else if (is_type(left_type, safedt_type_name_c)   && is_type(right_type, dt_type_name_c))
    il_default_variable_type = &time_type_name;
  else if (is_type(left_type, dt_type_name_c)       && is_type(right_type, safedt_type_name_c))
    il_default_variable_type = &time_type_name;
  else if (is_type(left_type, safedt_type_name_c)   && is_type(right_type, safedt_type_name_c))
    il_default_variable_type = &safetime_type_name;

  else il_default_variable_type = compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_MAGNITUDE_compatible,
                                                     symbol                  , il_operand);
  return NULL;
}

// SYM_REF0(MUL_operator_c)
void *visit_expression_type_c::visit(MUL_operator_c *symbol) {
  verify_null(symbol);
  symbol_c *left_type = il_default_variable_type;
  symbol_c *right_type = il_operand_type;

  if      (is_type(left_type, time_type_name_c)     && is_ANY_NUM_compatible(right_type))
    il_default_variable_type = &time_type_name;
  else if (is_type(left_type, safetime_type_name_c) && is_ANY_NUM_type(right_type))
    il_default_variable_type = &time_type_name;
  else if (is_type(left_type, safetime_type_name_c) && is_ANY_SAFENUM_type(right_type))
    il_default_variable_type = &safetime_type_name;
  /* Since we have already checked for ANY_NUM_type and ANY_SAFENUM_type in the previous lines,
   * this next line is really only to check for integers/reals of undefined type on 'right_type'... 
   */
  else if (is_type(left_type, safetime_type_name_c) && is_ANY_NUM_compatible(right_type))
    il_default_variable_type = &safetime_type_name;

  else il_default_variable_type = compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_NUM_compatible,
                                                     symbol                  , il_operand);
  return NULL;
}

// SYM_REF0(DIV_operator_c)
void *visit_expression_type_c::visit(DIV_operator_c *symbol) {
  verify_null(symbol);
  symbol_c *left_type = il_default_variable_type;
  symbol_c *right_type = il_operand_type;

  if      (is_type(left_type, time_type_name_c)     && is_ANY_NUM_compatible(right_type))
    il_default_variable_type = &time_type_name;
  else if (is_type(left_type, safetime_type_name_c) && is_ANY_NUM_type(right_type))
    il_default_variable_type = &time_type_name;
  else if (is_type(left_type, safetime_type_name_c) && is_ANY_SAFENUM_type(right_type))
    il_default_variable_type = &safetime_type_name;
  /* Since we have already checked for ANY_NUM_type and ANY_SAFENUM_type in the previous lines,
   * this next line is really only to check for integers/reals of undefined type on 'right_type'... 
   */
  else if (is_type(left_type, safetime_type_name_c) && is_ANY_NUM_compatible(right_type))
    il_default_variable_type = &safetime_type_name;

  else il_default_variable_type = compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_NUM_compatible,
                                                     symbol                  , il_operand);
  return NULL;
}

// SYM_REF0(MOD_operator_c)
void *visit_expression_type_c::visit(MOD_operator_c *symbol) {
  verify_null(symbol);
  il_default_variable_type = compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_INT_compatible); 
  return NULL;
}

// SYM_REF0(GT_operator_c)
void *visit_expression_type_c::visit(GT_operator_c *symbol) {
  verify_null(symbol);
  compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_ELEMENTARY_compatible,
                     symbol                  , il_operand);
  il_default_variable_type = &search_expression_type_c::bool_type_name;
  return NULL;
}

//SYM_REF0(GE_operator_c)
void *visit_expression_type_c::visit(GE_operator_c *symbol) {
  verify_null(symbol);
  compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_ELEMENTARY_compatible,
                     symbol                  , il_operand);
  il_default_variable_type = &search_expression_type_c::bool_type_name;
  return NULL;
}

//SYM_REF0(EQ_operator_c)
void *visit_expression_type_c::visit(EQ_operator_c *symbol) {
  verify_null(symbol);
  compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_ELEMENTARY_compatible,
                     symbol                  , il_operand);
  il_default_variable_type = &search_expression_type_c::bool_type_name;
  return NULL;
}

//SYM_REF0(LT_operator_c)
void *visit_expression_type_c::visit(LT_operator_c *symbol) {
  verify_null(symbol);
  compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_ELEMENTARY_compatible,
                     symbol                  , il_operand);
  il_default_variable_type = &search_expression_type_c::bool_type_name;
  return NULL;
}

//SYM_REF0(LE_operator_c)
void *visit_expression_type_c::visit(LE_operator_c *symbol) {
  verify_null(symbol);
  compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_ELEMENTARY_compatible,
                     symbol                  , il_operand);
  il_default_variable_type = &search_expression_type_c::bool_type_name;
  return NULL;
}

//SYM_REF0(NE_operator_c)
void *visit_expression_type_c::visit(NE_operator_c *symbol) {
  verify_null(symbol);
  compute_expression(il_default_variable_type, il_operand_type, &visit_expression_type_c::is_ANY_ELEMENTARY_compatible,
                     symbol                  , il_operand);
  il_default_variable_type = &search_expression_type_c::bool_type_name;
  return NULL;
}

// SYM_REF0(CAL_operator_c)
void *visit_expression_type_c::visit(CAL_operator_c *symbol) {
  return NULL;
}

// SYM_REF0(CALC_operator_c)
void *visit_expression_type_c::visit(CALC_operator_c *symbol) {
  if(il_default_variable_type == NULL)
    STAGE3_ERROR(symbol, symbol, "CALC: il default variable should not be NULL.");
  if (!is_BOOL_type(il_default_variable_type))
    STAGE3_ERROR(symbol, symbol, "CALC operator requires il_default_variable to be of type BOOL.");
  return NULL;
}

// SYM_REF0(CALCN_operator_c)
void *visit_expression_type_c::visit(CALCN_operator_c *symbol) {
  if(il_default_variable_type == NULL)
    STAGE3_ERROR(symbol, symbol, "CALCN: il_default_variable should not be NULL.");
  if (!is_BOOL_type(il_default_variable_type))
    STAGE3_ERROR(symbol, symbol, "CALCN operator requires il_default_variable to be of type BOOL.");
  return NULL;
}

// SYM_REF0(RET_operator_c)
void *visit_expression_type_c::visit(RET_operator_c *symbol) {
  return NULL;
}

// SYM_REF0(RETC_operator_c)
void *visit_expression_type_c::visit(RETC_operator_c *symbol) {
  if(il_default_variable_type == NULL)
    STAGE3_ERROR(symbol, symbol, "RETC: il default variable should not be NULL.");
  if (!is_BOOL_type(il_default_variable_type))
    STAGE3_ERROR(symbol, symbol, "RETC operator requires il_default_variable to be of type BOOL.");
  return NULL;
}

// SYM_REF0(RETCN_operator_c)
void *visit_expression_type_c::visit(RETCN_operator_c *symbol) {
  if(il_default_variable_type == NULL)
    STAGE3_ERROR(symbol, symbol, "RETCN: il_default_variable should not be NULL.");
  if (!is_BOOL_type(il_default_variable_type))
    STAGE3_ERROR(symbol, symbol, "RETCN operator requires il_default_variable to be of type BOOL.");
  return NULL;
}

// SYM_REF0(JMP_operator_c)
void *visit_expression_type_c::visit(JMP_operator_c *symbol){
  return NULL;
}

// SYM_REF0(JMPC_operator_c)
void *visit_expression_type_c::visit(JMPC_operator_c *symbol) {
  if(il_default_variable_type == NULL)
    STAGE3_ERROR(symbol, symbol, "JMPC: il default variable should not be NULL.");
  if (!is_BOOL_type(il_default_variable_type))
    STAGE3_ERROR(symbol, symbol, "JMPC operator requires il_default_variable to be of type BOOL.");
  return NULL;
}

// SYM_REF0(JMPCN_operator_c)
void *visit_expression_type_c::visit(JMPCN_operator_c *symbol) {
  if(il_default_variable_type == NULL)
    STAGE3_ERROR(symbol, symbol, "JMPCN: il_default_variable should not be NULL.");
  if (!is_BOOL_type(il_default_variable_type))
    STAGE3_ERROR(symbol, symbol, "JMPCN operator requires il_default_variable to be of type BOOL.");
  return NULL;
}

/* Symbol class handled together with function call checks */
/*  any_identifier ASSIGN */
// SYM_REF1(il_assign_operator_c, variable_name)
// void *visit_expression_type_c::visit(il_assign_operator_c *symbol, variable_name);

/* Symbol class handled together with function call checks */
/*| [NOT] any_identifier SENDTO */
// SYM_REF2(il_assign_out_operator_c, option, variable_name)
// void *visit_expression_type_c::visit(il_assign_operator_c *symbol, option, variable_name);





/***************************************/
/* B.3 - Language ST (Structured Text) */
/***************************************/
/***********************/
/* B 3.1 - Expressions */
/***********************/

void *visit_expression_type_c::visit(or_expression_c *symbol) {
  symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  return compute_expression(left_type, right_type, &visit_expression_type_c::is_ANY_BIT_compatible);
}


void *visit_expression_type_c::visit(xor_expression_c *symbol) {
  symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  return compute_expression(left_type, right_type, &visit_expression_type_c::is_ANY_BIT_compatible);
}


void *visit_expression_type_c::visit(and_expression_c *symbol) {
  symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  return compute_expression(left_type, right_type, &visit_expression_type_c::is_ANY_BIT_compatible);
}


void *visit_expression_type_c::visit(equ_expression_c *symbol) {
  symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  compute_expression(left_type, right_type, &visit_expression_type_c::is_ANY_ELEMENTARY_compatible);
  return &search_expression_type_c::bool_type_name;
}


void *visit_expression_type_c::visit(notequ_expression_c *symbol)  {
  symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  compute_expression(left_type, right_type, &visit_expression_type_c::is_ANY_ELEMENTARY_compatible);
  return &search_expression_type_c::bool_type_name;
}


void *visit_expression_type_c::visit(lt_expression_c *symbol) {
  symbol_c *left_type  = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  compute_expression(left_type, right_type, &visit_expression_type_c::is_ANY_ELEMENTARY_compatible);
  return &search_expression_type_c::bool_type_name;
}


void *visit_expression_type_c::visit(gt_expression_c *symbol) {
  symbol_c *left_type  = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  compute_expression(left_type, right_type, &visit_expression_type_c::is_ANY_ELEMENTARY_compatible);
  return &search_expression_type_c::bool_type_name;
}


void *visit_expression_type_c::visit(le_expression_c *symbol) {
  symbol_c *left_type  = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  compute_expression(left_type, right_type, &visit_expression_type_c::is_ANY_ELEMENTARY_compatible);
  return &search_expression_type_c::bool_type_name;
}


void *visit_expression_type_c::visit(ge_expression_c *symbol) {
  symbol_c *left_type  = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  compute_expression(left_type, right_type, &visit_expression_type_c::is_ANY_ELEMENTARY_compatible);
  return &search_expression_type_c::bool_type_name;
}


void *visit_expression_type_c::visit(add_expression_c *symbol) {
  symbol_c *left_type  = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));

/* The following is already checked in compute_expression */
/*
  if (is_type(left_type, time_type_name_c) && is_type(right_type, time_type_name_c)) 
    return (void *)&time_type_name;
*/

  if (is_type(left_type, tod_type_name_c)      && is_type(right_type, time_type_name_c)) 
    return (void *)&tod_type_name;
  if (is_type(left_type, safetod_type_name_c)  && is_type(right_type, time_type_name_c)) 
    return (void *)&tod_type_name;
  if (is_type(left_type, tod_type_name_c)      && is_type(right_type, safetime_type_name_c)) 
    return (void *)&tod_type_name;
  if (is_type(left_type, safetod_type_name_c)  && is_type(right_type, safetime_type_name_c)) 
    return (void *)&safetod_type_name;

  if (is_type(left_type, dt_type_name_c)       && is_type(right_type, time_type_name_c)) 
    return (void *)&dt_type_name;
  if (is_type(left_type, safedt_type_name_c)   && is_type(right_type, time_type_name_c)) 
    return (void *)&dt_type_name;
  if (is_type(left_type, dt_type_name_c)       && is_type(right_type, safetime_type_name_c)) 
    return (void *)&dt_type_name;
  if (is_type(left_type, safedt_type_name_c)   && is_type(right_type, safetime_type_name_c)) 
    return (void *)&safedt_type_name;

  return compute_expression(left_type, right_type, &visit_expression_type_c::is_ANY_MAGNITUDE_compatible);
}


void *visit_expression_type_c::visit(sub_expression_c *symbol) {
  symbol_c *left_type  = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));

/* The following is already checked in compute_expression */
/*
  if (is_type(left_type, time_type_name_c) && is_type(right_type, time_type_name_c))
    return (void *)&time_type_name;
*/

  if (is_type(left_type, tod_type_name_c)     && is_type(right_type, time_type_name_c))
    return (void *)&tod_type_name;
  if (is_type(left_type, safetod_type_name_c) && is_type(right_type, time_type_name_c))
    return (void *)&tod_type_name;
  if (is_type(left_type, tod_type_name_c)     && is_type(right_type, safetime_type_name_c))
    return (void *)&tod_type_name;
  if (is_type(left_type, safetod_type_name_c) && is_type(right_type, safetime_type_name_c))
    return (void *)&safetod_type_name;

  if (is_type(left_type, dt_type_name_c)     && is_type(right_type, time_type_name_c))
    return (void *)&dt_type_name;
  if (is_type(left_type, safedt_type_name_c) && is_type(right_type, time_type_name_c))
    return (void *)&dt_type_name;
  if (is_type(left_type, dt_type_name_c)     && is_type(right_type, safetime_type_name_c))
    return (void *)&dt_type_name;
  if (is_type(left_type, safedt_type_name_c) && is_type(right_type, safetime_type_name_c))
    return (void *)&safedt_type_name;

  if (is_type(left_type, tod_type_name_c)     && is_type(right_type, tod_type_name_c))
    return (void *)&time_type_name;
  if (is_type(left_type, safetod_type_name_c) && is_type(right_type, tod_type_name_c))
    return (void *)&time_type_name;
  if (is_type(left_type, tod_type_name_c)     && is_type(right_type, safetod_type_name_c))
    return (void *)&time_type_name;
  if (is_type(left_type, safetod_type_name_c) && is_type(right_type, safetod_type_name_c))
    return (void *)&safetime_type_name;

  if (is_type(left_type, date_type_name_c)     && is_type(right_type, date_type_name_c))
    return (void *)&time_type_name;
  if (is_type(left_type, safedate_type_name_c) && is_type(right_type, date_type_name_c))
    return (void *)&time_type_name;
  if (is_type(left_type, date_type_name_c)     && is_type(right_type, safedate_type_name_c))
    return (void *)&time_type_name;
  if (is_type(left_type, safedate_type_name_c) && is_type(right_type, safedate_type_name_c))
    return (void *)&safetime_type_name;

  if (is_type(left_type, dt_type_name_c)     && is_type(right_type, dt_type_name_c))
    return (void *)&time_type_name;
  if (is_type(left_type, safedt_type_name_c) && is_type(right_type, dt_type_name_c))
    return (void *)&time_type_name;
  if (is_type(left_type, dt_type_name_c)     && is_type(right_type, safedt_type_name_c))
    return (void *)&time_type_name;
  if (is_type(left_type, safedt_type_name_c) && is_type(right_type, safedt_type_name_c))
    return (void *)&safetime_type_name;

  return compute_expression(left_type, right_type, &visit_expression_type_c::is_ANY_MAGNITUDE_compatible);
}


void *visit_expression_type_c::visit(mul_expression_c *symbol) {
  symbol_c *left_type  = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));

  if (is_type(left_type, time_type_name_c)     && is_ANY_NUM_compatible(right_type)) 
    return (void *)&time_type_name;
  if (is_type(left_type, safetime_type_name_c) && is_ANY_NUM_type(right_type)) 
    return (void *)&time_type_name;
  if (is_type(left_type, safetime_type_name_c) && is_ANY_SAFENUM_type(right_type)) 
    return (void *)&safetime_type_name;
  /* Since we have already checked for ANY_NUM_type and ANY_SAFENUM_type in the previous lines,
   * this next line is really only to check for integers/reals of undefined type on 'right_type'... 
   */
  if (is_type(left_type, safetime_type_name_c) && is_ANY_NUM_compatible(right_type)) 
    return (void *)&safetime_type_name;

  return compute_expression(left_type, right_type, &visit_expression_type_c::is_ANY_NUM_compatible);
}


void *visit_expression_type_c::visit(div_expression_c *symbol) {
  symbol_c *left_type  = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));

  if (is_type(left_type, time_type_name_c)     && is_ANY_NUM_compatible(right_type)) 
    return (void *)&time_type_name;
  if (is_type(left_type, safetime_type_name_c) && is_ANY_NUM_type(right_type)) 
    return (void *)&time_type_name;
  if (is_type(left_type, safetime_type_name_c) && is_ANY_SAFENUM_type(right_type)) 
    return (void *)&safetime_type_name;
  /* Since we have already checked for ANY_NUM_type and ANY_SAFENUM_type in the previous lines,
   * this next line is really only to check for integers/reals of undefined type on 'right_type'... 
   */
  if (is_type(left_type, safetime_type_name_c) && is_ANY_NUM_compatible(right_type)) 
    return (void *)&safetime_type_name;

  return compute_expression(left_type, right_type, &visit_expression_type_c::is_ANY_NUM_compatible);
}


void *visit_expression_type_c::visit(mod_expression_c *symbol) {
  symbol_c *left_type  = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  return compute_expression(left_type, right_type, &visit_expression_type_c::is_ANY_INT_compatible);
}


void *visit_expression_type_c::visit(power_expression_c *symbol) {
  symbol_c *left_type  = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  if (!is_ANY_REAL_compatible(left_type))
    STAGE3_ERROR(symbol->l_exp, symbol->l_exp, "first operand of ** operator has invalid data type, should be of type ANY_REAL.");
  if (!is_ANY_NUM_compatible(right_type))
    STAGE3_ERROR(symbol->r_exp, symbol->r_exp, "second operand of ** operator has invalid data type, should be of type ANY_NUM.");

  return (void *)left_type;
}


void *visit_expression_type_c::visit(neg_expression_c *symbol) {
  symbol_c *exp_type = base_type((symbol_c *)symbol->exp->accept(*this));
  if (!is_ANY_MAGNITUDE_compatible(exp_type))
    STAGE3_ERROR(symbol, symbol, "operand of negate expression '-' has invalid data type, should be of type ANY_MAGNITUDE.");

  return exp_type;
}


void *visit_expression_type_c::visit(not_expression_c *symbol) {
  symbol_c *type = base_type((symbol_c *)symbol->exp->accept(*this));
  return compute_expression(type, type, &visit_expression_type_c::is_ANY_BIT_compatible);
}


void *visit_expression_type_c::visit(function_invocation_c *symbol) {
  function_declaration_c *f_decl = function_symtable.find_value(symbol->function_name);
  if (f_decl == function_symtable.end_value()) {
    /* TODO: the following code is for standard library functions. We do not yet support this... */
    void *res = compute_standard_function_default(symbol);
    if (res != NULL) return res;
    ERROR;
  }

  /* now check the semantics of the function call... */
  /* If the syntax parser is working correctly, exactly one of the 
   * following two symbols will be NULL, while the other is != NULL.
   */
  if (symbol->   formal_param_list != NULL) check_formal_call   (symbol, f_decl);
  if (symbol->nonformal_param_list != NULL) check_nonformal_call(symbol, f_decl);

  return base_type(f_decl->type_name);
}

/********************/
/* B 3.2 Statements */
/********************/
// SYM_LIST(statement_list_c)
/* The visitor of the base class search_visitor_c will handle calling each instruction in the list.
 * We do not need to do anything here...
 */
// void *visit_expression_type_c::visit(statement_list_c *symbol)


/*********************************/
/* B 3.2.1 Assignment Statements */
/*********************************/

void *visit_expression_type_c::visit(assignment_statement_c *symbol) {
  symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));

  if (debug) {
    printf("visit_expression_type_c::visit(assignment_statement_c) called. Checking --->");  
    symbolic_variable_c *hi = dynamic_cast<symbolic_variable_c *>(symbol->l_exp);  
    if (hi != NULL) {
      identifier_c *hi1 = dynamic_cast<identifier_c *>(hi->var_name);  
      if (hi1 != NULL) printf(hi1->value);
    }
    printf(" := ");
    hex_integer_c *hi2 = dynamic_cast<hex_integer_c *>(symbol->r_exp);  
    if (hi2 != NULL) printf(hi2->value);
    printf("\n");
  } // if (debug)
  
  if (!is_valid_assignment(left_type, right_type))  {
     STAGE3_ERROR(symbol, symbol, "data type mismatch in assignment statement!\n");
  }
  return NULL;
}



/*****************************************/
/* B 3.2.2 Subprogram Control Statements */
/*****************************************/

/*  RETURN */
// SYM_REF0(return_statement_c)


/* fb_name '(' [param_assignment_list] ')' */
/* param_assignment_list -> may be NULL ! */
// SYM_REF3(fb_invocation_c, fb_name, formal_param_list, nonformal_param_list)
void *visit_expression_type_c::visit(fb_invocation_c *symbol) {
  symbol_c *fb_decl = search_varfb_instance_type->get_type(symbol->fb_name);
    /* The following should never occur. The function block must be defined, 
     * and the FB type being called MUST be in the symtable... 
     * This was all already checked at stage 2!
     */
  if (NULL == fb_decl) ERROR;

  /* now check the semantics of the fb call... */
  /* If the syntax parser is working correctly, exactly one of the 
   * following two symbols will be NULL, while the other is != NULL.
   */
  if (symbol->   formal_param_list != NULL) check_formal_call   (symbol, fb_decl);
  if (symbol->nonformal_param_list != NULL) check_nonformal_call(symbol, fb_decl);

  return NULL;
}


#if 0
/* helper symbol for fb_invocation */
/* param_assignment_list ',' param_assignment */
SYM_LIST(param_assignment_list_c)

/*  variable_name ASSIGN expression */
SYM_REF2(input_variable_param_assignment_c, variable_name, expression)

/* [NOT] variable_name '=>' variable */
SYM_REF3(output_variable_param_assignment_c, not_param, variable_name, variable)

/* helper CLASS for output_variable_param_assignment */
SYM_REF0(not_paramassign_c)
#endif

/********************************/
/* B 3.2.3 Selection Statements */
/********************************/

/* IF expression THEN statement_list elseif_statement_list ELSE statement_list END_IF */
// SYM_REF4(if_statement_c, expression, statement_list, elseif_statement_list, else_statement_list)
void *visit_expression_type_c::visit(if_statement_c *symbol) {
  symbol_c *expr_type = base_type((symbol_c*)symbol->expression->accept(*this));
  if (!is_BOOL_type(expr_type)) STAGE3_ERROR(symbol->expression,symbol->expression,"IF conditional expression is not of boolean type.");
  if (NULL != symbol->statement_list)
    symbol->statement_list->accept(*this); 
  if (NULL != symbol->elseif_statement_list)  
    symbol->elseif_statement_list->accept(*this);
  if (NULL != symbol->else_statement_list)  
    symbol->else_statement_list->accept(*this);  
  return NULL;
}

/* helper symbol for if_statement */
// SYM_LIST(elseif_statement_list_c)
// void *visit_expression_type_c::visit(elseif_statement_list_c *symbol) { }

/* helper symbol for elseif_statement_list */
/* ELSIF expression THEN statement_list    */
// SYM_REF2(elseif_statement_c, expression, statement_list)
void *visit_expression_type_c::visit(elseif_statement_c *symbol) {
  symbol_c *elseif_expr_type = base_type((symbol_c*)symbol->expression->accept(*this));
  if(!is_BOOL_type(elseif_expr_type)) STAGE3_ERROR(symbol->expression,symbol->expression,"ELSIF conditional expression is not of boolean type.");
  if (NULL != symbol->statement_list)
    symbol->statement_list->accept(*this); 
  return NULL;
}


/* CASE expression OF case_element_list ELSE statement_list END_CASE */
// SYM_REF3(case_statement_c, expression, case_element_list, statement_list)
void *visit_expression_type_c::visit(case_statement_c *symbol) {
  case_expression_type = base_type((symbol_c*)symbol->expression->accept(*this));
  if (NULL != case_expression_type) {
    if (NULL != symbol->case_element_list)
      symbol->case_element_list->accept(*this);
  }
  if (NULL != symbol->statement_list)
    symbol->statement_list->accept(*this);
  return NULL;
}

#if 0
/* helper symbol for case_statement */
// SYM_LIST(case_element_list_c)
// void *visit_expression_type_c::visit(case_element_list_c *symbol);

/*  case_list ':' statement_list */
// SYM_REF2(case_element_c, case_list, statement_list)
void *visit_expression_type_c::visit(case_element_c *symbol);  
#endif

// SYM_LIST(case_list_c)
void *visit_expression_type_c::visit(case_list_c *symbol) {
  symbol_c *element_type;
  for(int i = 0; i < symbol->n; i++) {
    element_type = (symbol_c *)symbol->elements[i]->accept(*this);
    if (NULL == element_type) {
      STAGE3_ERROR(symbol->elements[i], symbol->elements[i], "Case list element has undefined data type.");
    } else {
      element_type = base_type(element_type);
      if (NULL != element_type){
        /* The CASE value is only used for comparison (and not assingment), so we only check for compatibility! */ 
        if (!is_compatible_type(case_expression_type, element_type))
          STAGE3_ERROR(symbol->elements[i], symbol->elements[i], "Invalid data type of case list element.");
      }
    }
  }
  return NULL;
}

/********************************/
/* B 3.2.4 Iteration Statements */
/********************************/

/*  FOR control_variable ASSIGN expression TO expression [BY expression] DO statement_list END_FOR */
// SYM_REF5(for_statement_c, control_variable, beg_expression, end_expression, by_expression, statement_list)
void *visit_expression_type_c::visit(for_statement_c *symbol) {
  symbol_c *var_type = (symbol_c*)symbol->control_variable->accept(*this);
  if (NULL == var_type) ERROR;
  var_type = base_type(var_type);
  if (NULL == var_type) ERROR;
  // ASSIGN
  symbol_c *beg_expr_type = base_type((symbol_c*)symbol->beg_expression->accept(*this));
  if (NULL != beg_expr_type) {
    /* The BEG value is assigned to the variable, so we check for assignment validity! */ 
    if(!is_valid_assignment(var_type, beg_expr_type)) 
      STAGE3_ERROR(symbol->beg_expression, symbol->beg_expression, "Data type mismatch between control variable and initial value.");
  }
  // TO
  symbol_c *end_expr_type = base_type((symbol_c*)symbol->end_expression->accept(*this));
  if (NULL != end_expr_type) { 
    /* The TO value is only used for comparison, so we only check for compatibility! */ 
    if(!is_compatible_type(var_type, end_expr_type)) 
      STAGE3_ERROR(symbol->end_expression, symbol->end_expression, "Data type mismatch between control variable and final value.");
  }
  // BY
  if(symbol->by_expression != NULL) {
    symbol_c *by_expr_type = base_type((symbol_c*)symbol->by_expression->accept(*this));
    if (NULL != end_expr_type) {   
      /* The BY value is used in an expression (add, sub, ...), so we only check for compatibility! */ 
      if(!is_compatible_type(var_type, by_expr_type)) 
        STAGE3_ERROR(symbol->by_expression, symbol->by_expression, "Data type mismatch between control variable and BY value.");
    }
  }
  // DO
  if (NULL != symbol->statement_list)
    symbol->statement_list->accept(*this); 
  return NULL;
}


/*  WHILE expression DO statement_list END_WHILE */
// SYM_REF2(while_statement_c, expression, statement_list)
void *visit_expression_type_c::visit(while_statement_c *symbol) {
  symbol_c *expr_type = base_type((symbol_c*)symbol->expression->accept(*this));
  if (NULL != expr_type) {
    if(!is_BOOL_type(expr_type)) 
      STAGE3_ERROR(symbol->expression,symbol->expression,"WHILE conditional expression is not of boolean type.");
  }
 
  if (NULL != symbol->statement_list)
    symbol->statement_list->accept(*this); 
  return NULL;
}

/*  REPEAT statement_list UNTIL expression END_REPEAT */
// SYM_REF2(repeat_statement_c, statement_list, expression)
void *visit_expression_type_c::visit(repeat_statement_c *symbol) {
  if (NULL != symbol->statement_list)
    symbol->statement_list->accept(*this); 
 
  symbol_c *expr_type = base_type((symbol_c*)symbol->expression->accept(*this));
  if (NULL != expr_type) {
    if(!is_BOOL_type(expr_type)) 
      STAGE3_ERROR(symbol->expression,symbol->expression,"REPEAT conditional expression is not of boolean type.");
  }
  return NULL;
}

/*  EXIT */
// SYM_REF0(exit_statement_c)



