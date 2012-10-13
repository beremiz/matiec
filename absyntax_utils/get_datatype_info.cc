/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2003-2012  Mario de Sousa (msousa@fe.up.pt)
 *  Copyright (C) 2007-2011  Laurent Bessard and Edouard Tisserant
 *  Copyright (C) 2012       Manuele Conti  (conti.ma@alice.it)
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

/* Determine the characteristics of a specific data type
 *  e.g., is it an enumeration, is it an array, is it ANY_INT, etc...
 *
 * The methods of this class may be passed either:
 *  - a data type declaration symbol_c, 
 *   OR
 *  - the name of a data type (identifier_c)
 *    In this case, we shall first serach for the basetype declaration using search_base_type_c, and then 
 *    run the normal process.
 */
#include "absyntax_utils.hh"

#include "../main.hh" // required for ERROR() and ERROR_MSG() macros.



#include <typeinfo>  // required for typeid






static search_base_type_c search_base_type;





bool get_datatype_info_c::is_type_equal(symbol_c *first_type, symbol_c *second_type) {
  if ((NULL == first_type) || (NULL == second_type))
      return false;
  if (typeid(* first_type) == typeid(invalid_type_name_c))
      return false;
  if (typeid(*second_type) == typeid(invalid_type_name_c))
      return false;
    
  if (get_datatype_info_c::is_ANY_ELEMENTARY(first_type)) {
      if (typeid(*first_type) == typeid(*second_type))
          return true;
  } else   /* ANY_DERIVED */
      return (first_type == second_type);

  return false;
}



bool get_datatype_info_c::is_type_valid(symbol_c *type) {
  if (NULL == type)
      return false;
  if (typeid(*type) == typeid(invalid_type_name_c))
      return false;

  return true;
}






bool get_datatype_info_c::is_sfc_initstep(symbol_c *type_symbol) {
  symbol_c *type_decl = search_base_type.get_basetype_decl(type_symbol); 
  if (typeid(*type_decl) == typeid(initial_step_c))                  {return true;}   /* INITIAL_STEP step_name ':' action_association_list END_STEP */  /* A pseudo data type! */
  return false;
}





bool get_datatype_info_c::is_sfc_step(symbol_c *type_symbol) {
  symbol_c *type_decl = search_base_type.get_basetype_decl(type_symbol); 
  if (typeid(*type_decl) == typeid(initial_step_c))                  {return true;}   /* INITIAL_STEP step_name ':' action_association_list END_STEP */  /* A pseudo data type! */
  if (typeid(*type_decl) == typeid(        step_c))                  {return true;}   /*         STEP step_name ':' action_association_list END_STEP */  /* A pseudo data type! */
  return false;
}




bool get_datatype_info_c::is_function_block(symbol_c *type_symbol) {
  symbol_c *type_decl = search_base_type.get_basetype_decl(type_symbol); 
  if (typeid(*type_decl) == typeid(function_block_declaration_c))    {return true;}   /*  FUNCTION_BLOCK derived_function_block_name io_OR_other_var_declarations function_block_body END_FUNCTION_BLOCK */
  return false;
}





bool get_datatype_info_c::is_subrange(symbol_c *type_symbol) {
  symbol_c *type_decl = search_base_type.get_basetype_decl(type_symbol); /* NOTE: will work correctly once we update the way search_base_type_c works, by adding a new search_effective_type:c */
  
  if (typeid(*type_decl) == typeid(subrange_type_declaration_c))     {return true;}   /*  subrange_type_name ':' subrange_spec_init */
  if (typeid(*type_decl) == typeid(subrange_spec_init_c))            {return true;}   /* subrange_specification ASSIGN signed_integer */
  if (typeid(*type_decl) == typeid(subrange_specification_c))        {return true;}   /*  integer_type_name '(' subrange')' */
    
  if (typeid(*type_decl) == typeid(subrange_c))                      {ERROR;}         /*  signed_integer DOTDOT signed_integer */
  return false;
}





bool get_datatype_info_c::is_enumerated(symbol_c *type_symbol) {
  symbol_c *type_decl = search_base_type.get_basetype_decl(type_symbol);
  
  if (typeid(*type_decl) == typeid(enumerated_type_declaration_c))   {return true;}   /*  enumerated_type_name ':' enumerated_spec_init */
  if (typeid(*type_decl) == typeid(enumerated_spec_init_c))          {return true;}   /* enumerated_specification ASSIGN enumerated_value */
  if (typeid(*type_decl) == typeid(enumerated_value_list_c))         {return true;}   /* enumerated_value_list ',' enumerated_value */        /* once we change the way we handle enums, this will probably become an ERROR! */
  
  if (typeid(*type_decl) == typeid(enumerated_value_c))              {ERROR;}         /* enumerated_type_name '#' identifier */
  return false;
}





bool get_datatype_info_c::is_array(symbol_c *type_symbol) {
  symbol_c *type_decl = search_base_type.get_basetype_decl(type_symbol);
  
  if (typeid(*type_decl) == typeid(array_type_declaration_c))        {return true;}   /*  identifier ':' array_spec_init */
  if (typeid(*type_decl) == typeid(array_spec_init_c))               {return true;}   /* array_specification [ASSIGN array_initialization} */
  if (typeid(*type_decl) == typeid(array_specification_c))           {return true;}   /* ARRAY '[' array_subrange_list ']' OF non_generic_type_name */
  
  if (typeid(*type_decl) == typeid(array_subrange_list_c))           {ERROR;}         /* array_subrange_list ',' subrange */
  if (typeid(*type_decl) == typeid(array_initial_elements_list_c))   {ERROR;}         /* array_initialization:  '[' array_initial_elements_list ']' */  /* array_initial_elements_list ',' array_initial_elements */
  if (typeid(*type_decl) == typeid(array_initial_elements_c))        {ERROR;}         /* integer '(' [array_initial_element] ')' */
  return false;
}





bool get_datatype_info_c::is_structure(symbol_c *type_symbol) {
  symbol_c *type_decl = search_base_type.get_basetype_decl(type_symbol);
  
  if (typeid(*type_decl) == typeid(structure_type_declaration_c))              {return true;}   /*  structure_type_name ':' structure_specification */
  if (typeid(*type_decl) == typeid(initialized_structure_c))                   {return true;}   /* structure_type_name ASSIGN structure_initialization */
  if (typeid(*type_decl) == typeid(structure_element_declaration_list_c))      {return true;}   /* structure_declaration:  STRUCT structure_element_declaration_list END_STRUCT */ /* structure_element_declaration_list structure_element_declaration ';' */
  
  if (typeid(*type_decl) == typeid(structure_element_declaration_c))           {ERROR;}         /*  structure_element_name ':' *_spec_init */
  if (typeid(*type_decl) == typeid(structure_element_initialization_list_c))   {ERROR;}         /* structure_initialization: '(' structure_element_initialization_list ')' */  /* structure_element_initialization_list ',' structure_element_initialization */
  if (typeid(*type_decl) == typeid(structure_element_initialization_c))        {ERROR;}         /*  structure_element_name ASSIGN value */
  return false;
}










bool get_datatype_info_c::is_ANY_ELEMENTARY(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_MAGNITUDE(type_symbol))                           {return true;}
  if (is_ANY_BIT      (type_symbol))                           {return true;}
  if (is_ANY_STRING   (type_symbol))                           {return true;}
  if (is_ANY_DATE     (type_symbol))                           {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_SAFEELEMENTARY(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_SAFEMAGNITUDE(type_symbol))                       {return true;}
  if (is_ANY_SAFEBIT      (type_symbol))                       {return true;}
  if (is_ANY_SAFESTRING   (type_symbol))                       {return true;}
  if (is_ANY_SAFEDATE     (type_symbol))                       {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_ELEMENTARY_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_ELEMENTARY    (type_symbol))                      {return true;}
  if (is_ANY_SAFEELEMENTARY(type_symbol))                      {return true;}
  return false;
}







bool get_datatype_info_c::is_ANY_MAGNITUDE(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_TIME(type_symbol))                                    {return true;}
  if (is_ANY_NUM(type_symbol))                                 {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_SAFEMAGNITUDE(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_SAFETIME(type_symbol))                                {return true;}
  if (is_ANY_SAFENUM(type_symbol))                             {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_MAGNITUDE_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_MAGNITUDE    (type_symbol))                       {return true;}
  if (is_ANY_SAFEMAGNITUDE(type_symbol))                       {return true;}
  return false;
}







bool get_datatype_info_c::is_ANY_signed_MAGNITUDE(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(time_type_name_c))        {return true;}
  if (is_ANY_signed_NUM(type_symbol))                          {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_signed_SAFEMAGNITUDE(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(safetime_type_name_c))    {return true;}
  return is_ANY_signed_SAFENUM(type_symbol);
}


bool get_datatype_info_c::is_ANY_signed_MAGNITUDE_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_signed_MAGNITUDE    (type_symbol))                {return true;}
  if (is_ANY_signed_SAFEMAGNITUDE(type_symbol))                {return true;}
  return false;
}







bool get_datatype_info_c::is_ANY_NUM(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_REAL(type_symbol))                                {return true;}
  if (is_ANY_INT (type_symbol))                                {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_SAFENUM(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_SAFEREAL(type_symbol))                            {return true;}
  if (is_ANY_SAFEINT (type_symbol))                            {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_NUM_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_NUM    (type_symbol))                             {return true;}
  if (is_ANY_SAFENUM(type_symbol))                             {return true;}
  return false;
}







bool get_datatype_info_c::is_ANY_signed_NUM(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_REAL      (type_symbol))                          {return true;}
  if (is_ANY_signed_INT(type_symbol))                          {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_signed_SAFENUM(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_SAFEREAL      (type_symbol))                      {return true;}
  if (is_ANY_signed_SAFEINT(type_symbol))                      {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_signed_NUM_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_signed_NUM    (type_symbol))                      {return true;}
  if (is_ANY_signed_SAFENUM(type_symbol))                      {return true;}
  return false;
}







bool get_datatype_info_c::is_ANY_INT(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_signed_INT  (type_symbol))                        {return true;}
  if (is_ANY_unsigned_INT(type_symbol))                        {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_SAFEINT(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_signed_SAFEINT  (type_symbol))                    {return true;}
  if (is_ANY_unsigned_SAFEINT(type_symbol))                    {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_INT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_INT    (type_symbol))                             {return true;}
  if (is_ANY_SAFEINT(type_symbol))                             {return true;}
  return false;
}






bool get_datatype_info_c::is_ANY_signed_INT(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(sint_type_name_c))        {return true;}
  if (typeid(*type_symbol) == typeid(int_type_name_c))         {return true;}
  if (typeid(*type_symbol) == typeid(dint_type_name_c))        {return true;}
  if (typeid(*type_symbol) == typeid(lint_type_name_c))        {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_signed_SAFEINT(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(safesint_type_name_c))    {return true;}
  if (typeid(*type_symbol) == typeid(safeint_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(safedint_type_name_c))    {return true;}
  if (typeid(*type_symbol) == typeid(safelint_type_name_c))    {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_signed_INT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_signed_INT    (type_symbol))                      {return true;}
  if (is_ANY_signed_SAFEINT(type_symbol))                      {return true;}
  return false;
}









bool get_datatype_info_c::is_ANY_unsigned_INT(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(usint_type_name_c))       {return true;}
  if (typeid(*type_symbol) == typeid(uint_type_name_c))        {return true;}
  if (typeid(*type_symbol) == typeid(udint_type_name_c))       {return true;}
  if (typeid(*type_symbol) == typeid(ulint_type_name_c))       {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_unsigned_SAFEINT(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(safeusint_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(safeuint_type_name_c))    {return true;}
  if (typeid(*type_symbol) == typeid(safeudint_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(safeulint_type_name_c))   {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_unsigned_INT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_unsigned_INT    (type_symbol))                    {return true;}
  if (is_ANY_unsigned_SAFEINT(type_symbol))                    {return true;}
  return false;
}








bool get_datatype_info_c::is_ANY_REAL(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(real_type_name_c))        {return true;}
  if (typeid(*type_symbol) == typeid(lreal_type_name_c))       {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_SAFEREAL(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(safereal_type_name_c))    {return true;}
  if (typeid(*type_symbol) == typeid(safelreal_type_name_c))   {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_REAL_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_REAL    (type_symbol))                            {return true;}
  if (is_ANY_SAFEREAL(type_symbol))                            {return true;}
  return false;
}








bool get_datatype_info_c::is_ANY_nBIT(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(byte_type_name_c))        {return true;}
  if (typeid(*type_symbol) == typeid(word_type_name_c))        {return true;}
  if (typeid(*type_symbol) == typeid(dword_type_name_c))       {return true;}
  if (typeid(*type_symbol) == typeid(lword_type_name_c))       {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_SAFEnBIT(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(safebyte_type_name_c))    {return true;}
  if (typeid(*type_symbol) == typeid(safeword_type_name_c))    {return true;}
  if (typeid(*type_symbol) == typeid(safedword_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(safelword_type_name_c))   {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_nBIT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_nBIT    (type_symbol))                            {return true;}
  if (is_ANY_SAFEnBIT(type_symbol))                            {return true;}
  return false;
}










bool get_datatype_info_c::is_BOOL(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(bool_type_name_c))        {return true;}
  return false;
}


bool get_datatype_info_c::is_SAFEBOOL(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(safebool_type_name_c))    {return true;}
  return false;
}


bool get_datatype_info_c::is_BOOL_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_BOOL    (type_symbol))                                {return true;}
  if (is_SAFEBOOL(type_symbol))                                {return true;}
  return false;
}









bool get_datatype_info_c::is_ANY_BIT(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_BOOL    (type_symbol))                                {return true;}
  if (is_ANY_nBIT(type_symbol))                                {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_SAFEBIT(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_SAFEBOOL    (type_symbol))                            {return true;}
  if (is_ANY_SAFEnBIT(type_symbol))                            {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_BIT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_BIT    (type_symbol))                             {return true;}
  if (is_ANY_SAFEBIT(type_symbol))                             {return true;}
  return false;
}








bool get_datatype_info_c::is_TIME(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(time_type_name_c))        {return true;}
  return false;
}


bool get_datatype_info_c::is_SAFETIME(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(safetime_type_name_c))    {return true;}
  return false;
}


bool get_datatype_info_c::is_TIME_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_TIME    (type_symbol))                                {return true;}
  if (is_SAFETIME(type_symbol))                                {return true;}
  return false;
}








bool get_datatype_info_c::is_ANY_DATE(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(date_type_name_c))        {return true;}
  if (typeid(*type_symbol) == typeid(tod_type_name_c))         {return true;}
  if (typeid(*type_symbol) == typeid(dt_type_name_c))          {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_SAFEDATE(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(safedate_type_name_c))    {return true;}
  if (typeid(*type_symbol) == typeid(safetod_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(safedt_type_name_c))      {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_DATE_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_DATE    (type_symbol))                            {return true;}
  if (is_ANY_SAFEDATE(type_symbol))                            {return true;}
  return false;
}











bool get_datatype_info_c::is_ANY_STRING(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(string_type_name_c))      {return true;}
  if (typeid(*type_symbol) == typeid(wstring_type_name_c))     {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_SAFESTRING(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (typeid(*type_symbol) == typeid(safestring_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safewstring_type_name_c)) {return true;}
  return false;
}


bool get_datatype_info_c::is_ANY_STRING_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL)                                     {return false;}
  if (is_ANY_STRING    (type_symbol))                          {return true;}
  if (is_ANY_SAFESTRING(type_symbol))                          {return true;}
  return false;
}







/* Can't we do away with this?? */
bool get_datatype_info_c::is_ANY_REAL_literal(symbol_c *type_symbol) {
  if (type_symbol == NULL)                              {return true;} /* Please make sure things will work correctly before changing this to false!! */
  if (typeid(*type_symbol) == typeid(real_c))           {return true;}
  if (typeid(*type_symbol) == typeid(neg_real_c))       {return true;}
  return false;
}

/* Can't we do away with this?? */
bool get_datatype_info_c::is_ANY_INT_literal(symbol_c *type_symbol) {
  if (type_symbol == NULL)                              {return true;} /* Please make sure things will work correctly before changing this to false!! */
  if (typeid(*type_symbol) == typeid(integer_c))        {return true;}
  if (typeid(*type_symbol) == typeid(neg_integer_c))    {return true;}
  if (typeid(*type_symbol) == typeid(binary_integer_c)) {return true;}
  if (typeid(*type_symbol) == typeid(octal_integer_c))  {return true;}
  if (typeid(*type_symbol) == typeid(hex_integer_c))    {return true;}
  return false;
}

