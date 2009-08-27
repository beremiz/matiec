/*
 * (c) 2003 Mario de Sousa
 *
 * Offered to the public under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * This code is made available on the understanding that it will not be
 * used in safety-critical situations without a full and competent review.
 */

/*
 * An IEC 61131-3 IL and ST compiler.
 *
 * Based on the
 * FINAL DRAFT - IEC 61131-3, 2nd Ed. (2001-12-10)
 *
 */

/* Determine the data type of a specific constant or variable.
 * A reference to the relevant type definition is returned.
 *
 * For example:
 *       22          -> returns reference to a int_type_name_c object.
 *       22.2        -> returns reference to a real_type_name_c object.
 *       LREAL#22.2  -> returns reference to a lreal_type_name_c object.
 *       etc...
 */


#include "search_constant_type.hh"

#define ERROR error_exit(__FILE__,__LINE__)
/* function defined in main.cc */
extern void error_exit(const char *file_name, int line_no);

symbol_c *search_constant_type_c::get_type(symbol_c *constant) {
  return (symbol_c *)constant->accept(*this);
}


/*********************/
/* B 1.2 - Constants */
/*********************/

/******************************/
/* B 1.2.1 - Numeric Literals */
/******************************/
/* Numeric literals without any explicit type cast have unknown data type, 
  * so we continue considering them as their own basic data types until
  * they can be resolved (for example, when using '30+x' where 'x' is a LINT variable, the
  * numeric literal '30' must then be considered a LINT so the ADD function may be called
  * with all inputs of the same data type.
  * If 'x' were a SINT, then the '30' would have to be a SINT too!
  */
void *search_constant_type_c::visit(real_c *symbol)           {return (void *)symbol;}
void *search_constant_type_c::visit(integer_c *symbol)        {return (void *)symbol;}
void *search_constant_type_c::visit(binary_integer_c *symbol) {return (void *)symbol;}
void *search_constant_type_c::visit(octal_integer_c *symbol)  {return (void *)symbol;}
void *search_constant_type_c::visit(hex_integer_c *symbol)    {return (void *)symbol;}

void *search_constant_type_c::visit(integer_literal_c *symbol)
  {return (void *)((symbol->type!=NULL)?symbol->type:symbol->value->accept(*this));}
void *search_constant_type_c::visit(real_literal_c *symbol)
  {return (void *)((symbol->type!=NULL)?symbol->type:symbol->value->accept(*this));}
void *search_constant_type_c::visit(bit_string_literal_c *symbol)
  {return (void *)((symbol->type!=NULL)?symbol->type:symbol->value->accept(*this));}
void *search_constant_type_c::visit(boolean_literal_c *symbol)
  {return (void *)((symbol->type!=NULL)?symbol->type:symbol->value->accept(*this));}

void *search_constant_type_c::visit(boolean_true_c *symbol)   {return (void *)symbol;}
void *search_constant_type_c::visit(boolean_false_c *symbol)  {return (void *)symbol;}


/*******************************/
/* B.1.2.2   Character Strings */
/*******************************/
void *search_constant_type_c::visit(double_byte_character_string_c *symbol) {return (void *)&wstring_type_name;}
void *search_constant_type_c::visit(single_byte_character_string_c *symbol) {return (void *)&string_type_name;}

/***************************/
/* B 1.2.3 - Time Literals */
/***************************/
/************************/
/* B 1.2.3.1 - Duration */
/************************/
void *search_constant_type_c::visit(neg_time_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
void *search_constant_type_c::visit(duration_c *symbol) {return (void *)&time_type_name;}
void *search_constant_type_c::visit(fixed_point_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
void *search_constant_type_c::visit(days_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
void *search_constant_type_c::visit(hours_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
void *search_constant_type_c::visit(minutes_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
void *search_constant_type_c::visit(seconds_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
void *search_constant_type_c::visit(milliseconds_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */

/************************************/
/* B 1.2.3.2 - Time of day and Date */
/************************************/
void *search_constant_type_c::visit(time_of_day_c *symbol) {return (void *)&tod_type_name;}
void *search_constant_type_c::visit(daytime_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
void *search_constant_type_c::visit(date_c *symbol) {return (void *)&date_type_name;}
void *search_constant_type_c::visit(date_literal_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
void *search_constant_type_c::visit(date_and_time_c *symbol) {return (void *)&dt_type_name;}

real_type_name_c     search_constant_type_c::real_type_name;
sint_type_name_c     search_constant_type_c::sint_type_name;
lint_type_name_c     search_constant_type_c::lint_type_name;
dint_type_name_c     search_constant_type_c::dint_type_name;
date_type_name_c     search_constant_type_c::date_type_name;
dword_type_name_c    search_constant_type_c::dword_type_name;
dt_type_name_c       search_constant_type_c::dt_type_name;
tod_type_name_c      search_constant_type_c::tod_type_name;
udint_type_name_c    search_constant_type_c::udint_type_name;
word_type_name_c     search_constant_type_c::word_type_name;
wstring_type_name_c  search_constant_type_c::wstring_type_name;
string_type_name_c   search_constant_type_c::string_type_name;
lword_type_name_c    search_constant_type_c::lword_type_name;
uint_type_name_c     search_constant_type_c::uint_type_name;
lreal_type_name_c    search_constant_type_c::lreal_type_name;
byte_type_name_c     search_constant_type_c::byte_type_name;
usint_type_name_c    search_constant_type_c::usint_type_name;
ulint_type_name_c    search_constant_type_c::ulint_type_name;
bool_type_name_c     search_constant_type_c::bool_type_name;
time_type_name_c     search_constant_type_c::time_type_name;
int_type_name_c      search_constant_type_c::int_type_name;

/*
constant_real_type_name_c     search_constant_type_c::constant_real_type_name;
constant_int_type_name_c      search_constant_type_c::constant_int_type_name;
*/
/* temporarily here until we remove the st_code_gen.c and il_code_gen.c files... */
/* It should then move to search_expression_type_c                               */
integer_c search_constant_type_c::integer("1");
