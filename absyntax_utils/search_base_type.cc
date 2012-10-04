/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2003-2012  Mario de Sousa (msousa@fe.up.pt)
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

/* Determine the data type on which another data type is based on.
 * If a new default initial value is given, we DO NOT consider it a
 * new base class, and continue looking further!
 *
 * E.g. TYPE new_int_t : INT; END_TYPE;
 *      TYPE new_int2_t : INT = 2; END_TYPE;
 *      TYPE new_subr_t : INT (4..5); END_TYPE;
 *
 *    new_int_t is really an INT!!
 *    new_int2_t is also really an INT!!
 *    new_subr_t is also really an INT!!
 *
 * Note that a FB declaration is also considered a base type, as
 * we may have FB instances declared of a specific FB type.
 */
#include "absyntax_utils.hh"
#include "../main.hh" // required for ERROR() and ERROR_MSG() macros.



search_base_type_c::search_base_type_c(void) {current_type_name = NULL;}




symbol_c *search_base_type_c::get_basetype_decl(symbol_c *symbol) {
  if (NULL == symbol)
    return NULL;
  
  return (symbol_c *)symbol->accept(*this);
}

symbol_c *search_base_type_c::get_basetype_id  (symbol_c *symbol) {
  if (NULL == symbol)
    return NULL;
  
  current_type_name = NULL; /* just to be on the safe side... */
  symbol->accept(*this);
  return (symbol_c *)current_type_name;
}


/* Note by MJS: The following two functions definately do not belong in this class!! Maybe create a new utility class?
 * I will need to clean this up when the opportunity arises!
 */

bool search_base_type_c::type_is_subrange(symbol_c* type_decl) {
  this->is_subrange = false;
  type_decl->accept(*this);
  return this->is_subrange;
}

bool search_base_type_c::type_is_enumerated(symbol_c* type_decl) {
  this->is_enumerated = false;
  type_decl->accept(*this);
  return this->is_enumerated;
}


/*************************/
/* B.1 - Common elements */
/*************************/

/*******************************************/
/* B 1.1 - Letters, digits and identifiers */
/*******************************************/
void *search_base_type_c::visit(identifier_c *type_name) {
  symbol_c *type_decl;

  this->current_type_name = type_name;
  
  /* look up the type declaration... */
  type_decl = type_symtable.find_value(type_name);
  if (type_decl != type_symtable.end_value())
    return type_decl->accept(*this);
    
  type_decl = function_block_type_symtable.find_value(type_name);
  if (type_decl != function_block_type_symtable.end_value())
    return type_decl->accept(*this);
  
  /* Type declaration not found!! */
    ERROR;
    
  return NULL;
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
void *search_base_type_c::visit(real_c *symbol)                   {return (void *)symbol;}
void *search_base_type_c::visit(neg_real_c *symbol)               {return (void *)symbol;}
void *search_base_type_c::visit(integer_c *symbol)                {return (void *)symbol;}
void *search_base_type_c::visit(neg_integer_c *symbol)            {return (void *)symbol;}
void *search_base_type_c::visit(binary_integer_c *symbol)         {return (void *)symbol;}
void *search_base_type_c::visit(octal_integer_c *symbol)          {return (void *)symbol;}
void *search_base_type_c::visit(hex_integer_c *symbol)            {return (void *)symbol;}
void *search_base_type_c::visit(boolean_true_c *symbol)           {return (void *)symbol;}
void *search_base_type_c::visit(boolean_false_c *symbol)          {return (void *)symbol;}


/***********************************/
/* B 1.3.1 - Elementary Data Types */
/***********************************/
void *search_base_type_c::visit(time_type_name_c *symbol)         {return (void *)symbol;}
void *search_base_type_c::visit(bool_type_name_c *symbol)         {return (void *)symbol;}
void *search_base_type_c::visit(sint_type_name_c *symbol)         {return (void *)symbol;}
void *search_base_type_c::visit(int_type_name_c *symbol)          {return (void *)symbol;}
void *search_base_type_c::visit(dint_type_name_c *symbol)         {return (void *)symbol;}
void *search_base_type_c::visit(lint_type_name_c *symbol)         {return (void *)symbol;}
void *search_base_type_c::visit(usint_type_name_c *symbol)        {return (void *)symbol;}
void *search_base_type_c::visit(uint_type_name_c *symbol)         {return (void *)symbol;}
void *search_base_type_c::visit(udint_type_name_c *symbol)        {return (void *)symbol;}
void *search_base_type_c::visit(ulint_type_name_c *symbol)        {return (void *)symbol;}
void *search_base_type_c::visit(real_type_name_c *symbol)         {return (void *)symbol;}
void *search_base_type_c::visit(lreal_type_name_c *symbol)        {return (void *)symbol;}
void *search_base_type_c::visit(date_type_name_c *symbol)         {return (void *)symbol;}
void *search_base_type_c::visit(tod_type_name_c *symbol)          {return (void *)symbol;}
void *search_base_type_c::visit(dt_type_name_c *symbol)           {return (void *)symbol;}
void *search_base_type_c::visit(byte_type_name_c *symbol)         {return (void *)symbol;}
void *search_base_type_c::visit(word_type_name_c *symbol)         {return (void *)symbol;}
void *search_base_type_c::visit(dword_type_name_c *symbol)        {return (void *)symbol;}
void *search_base_type_c::visit(lword_type_name_c *symbol)        {return (void *)symbol;}
void *search_base_type_c::visit(string_type_name_c *symbol)       {return (void *)symbol;}
void *search_base_type_c::visit(wstring_type_name_c *symbol)      {return (void *)symbol;}


/******************************************************/
/* Extensions to the base standard as defined in      */
/* "Safety Software Technical Specification,          */
/*  Part 1: Concepts and Function Blocks,             */
/*  Version 1.0 – Official Release"                   */
/* by PLCopen - Technical Committee 5 - 2006-01-31    */
/******************************************************/

void *search_base_type_c::visit(safetime_type_name_c *symbol)     {return (void *)symbol;}
void *search_base_type_c::visit(safebool_type_name_c *symbol)     {return (void *)symbol;}
void *search_base_type_c::visit(safesint_type_name_c *symbol)     {return (void *)symbol;}
void *search_base_type_c::visit(safeint_type_name_c *symbol)      {return (void *)symbol;}
void *search_base_type_c::visit(safedint_type_name_c *symbol)     {return (void *)symbol;}
void *search_base_type_c::visit(safelint_type_name_c *symbol)     {return (void *)symbol;}
void *search_base_type_c::visit(safeusint_type_name_c *symbol)    {return (void *)symbol;}
void *search_base_type_c::visit(safeuint_type_name_c *symbol)     {return (void *)symbol;}
void *search_base_type_c::visit(safeudint_type_name_c *symbol)    {return (void *)symbol;}
void *search_base_type_c::visit(safeulint_type_name_c *symbol)    {return (void *)symbol;}
void *search_base_type_c::visit(safereal_type_name_c *symbol)     {return (void *)symbol;}
void *search_base_type_c::visit(safelreal_type_name_c *symbol)    {return (void *)symbol;}
void *search_base_type_c::visit(safedate_type_name_c *symbol)     {return (void *)symbol;}
void *search_base_type_c::visit(safetod_type_name_c *symbol)      {return (void *)symbol;}
void *search_base_type_c::visit(safedt_type_name_c *symbol)       {return (void *)symbol;}
void *search_base_type_c::visit(safebyte_type_name_c *symbol)     {return (void *)symbol;}
void *search_base_type_c::visit(safeword_type_name_c *symbol)     {return (void *)symbol;}
void *search_base_type_c::visit(safedword_type_name_c *symbol)    {return (void *)symbol;}
void *search_base_type_c::visit(safelword_type_name_c *symbol)    {return (void *)symbol;}
void *search_base_type_c::visit(safestring_type_name_c *symbol)   {return (void *)symbol;}
void *search_base_type_c::visit(safewstring_type_name_c *symbol)  {return (void *)symbol;}

/********************************/
/* B 1.3.3 - Derived data types */
/********************************/
/*  simple_type_name ':' simple_spec_init */
void *search_base_type_c::visit(simple_type_declaration_c *symbol) {
  return symbol->simple_spec_init->accept(*this);
}
/* simple_specification ASSIGN constant */
void *search_base_type_c::visit(simple_spec_init_c *symbol) {
  return symbol->simple_specification->accept(*this);
}

/*  subrange_type_name ':' subrange_spec_init */
void *search_base_type_c::visit(subrange_type_declaration_c *symbol) {
  return symbol->subrange_spec_init->accept(*this);
}

/* subrange_specification ASSIGN signed_integer */
void *search_base_type_c::visit(subrange_spec_init_c *symbol) {
  this->is_subrange = true;
  return symbol->subrange_specification->accept(*this);
}

/*  integer_type_name '(' subrange')' */
void *search_base_type_c::visit(subrange_specification_c *symbol) {
  return symbol->integer_type_name->accept(*this);
}

/*  signed_integer DOTDOT signed_integer */
void *search_base_type_c::visit(subrange_c *symbol)                                     {ERROR; return NULL;} /* should never get called... */

/*  enumerated_type_name ':' enumerated_spec_init */
void *search_base_type_c::visit(enumerated_type_declaration_c *symbol) {
  this->current_type_name = symbol->enumerated_type_name;
  return symbol->enumerated_spec_init->accept(*this);
}

/* enumerated_specification ASSIGN enumerated_value */
void *search_base_type_c::visit(enumerated_spec_init_c *symbol) {
  this->is_enumerated = true;
  return symbol->enumerated_specification->accept(*this);
}

/* helper symbol for enumerated_specification->enumerated_spec_init */
/* enumerated_value_list ',' enumerated_value */
void *search_base_type_c::visit(enumerated_value_list_c *symbol) {
  this->is_enumerated = true;
  return (void *)symbol;
}

/* enumerated_type_name '#' identifier */
// SYM_REF2(enumerated_value_c, type, value)
void *search_base_type_c::visit(enumerated_value_c *symbol)                             {ERROR; return NULL;} /* should never get called... */

/*  identifier ':' array_spec_init */
void *search_base_type_c::visit(array_type_declaration_c *symbol) {
  this->current_type_name = symbol->identifier;
  return symbol->array_spec_init->accept(*this);
}

/* array_specification [ASSIGN array_initialization} */
/* array_initialization may be NULL ! */
void *search_base_type_c::visit(array_spec_init_c *symbol) {
  /* Note that the 'array_specification' may be either an identifier of a previsously defined array type, 
   * or an array_specification_c, so we can not stop here and simply return a array_spec_init_c, 
   * especially if we are looking for the base class!
   */  
  return symbol->array_specification->accept(*this);
}

/* ARRAY '[' array_subrange_list ']' OF non_generic_type_name */
void *search_base_type_c::visit(array_specification_c *symbol)                          {return (void *)symbol;}

/* helper symbol for array_specification */
/* array_subrange_list ',' subrange */
void *search_base_type_c::visit(array_subrange_list_c *symbol)                          {ERROR; return NULL;} /* should never get called... */

/* array_initialization:  '[' array_initial_elements_list ']' */
/* helper symbol for array_initialization */
/* array_initial_elements_list ',' array_initial_elements */
void *search_base_type_c::visit(array_initial_elements_list_c *symbol)                  {ERROR; return NULL;} /* should never get called... */

/* integer '(' [array_initial_element] ')' */
/* array_initial_element may be NULL ! */
void *search_base_type_c::visit(array_initial_elements_c *symbol)                       {ERROR; return NULL;} /* should never get called... */

/*  structure_type_name ':' structure_specification */
/* NOTE: structure_specification will point to either a
 *       initialized_structure_c
 *       OR A
 *       structure_element_declaration_list_c
 */
void *search_base_type_c::visit(structure_type_declaration_c *symbol)  {
  this->current_type_name = symbol->structure_type_name;
  return symbol->structure_specification->accept(*this);
}

/*  var1_list ':' structure_type_name */
void *search_base_type_c::visit(structured_var_declaration_c *symbol) {
	return symbol;
}

/* structure_type_name ASSIGN structure_initialization */
/* structure_initialization may be NULL ! */
void *search_base_type_c::visit(initialized_structure_c *symbol)	{
  return symbol->structure_type_name->accept(*this);
}

/* helper symbol for structure_declaration */
/* structure_declaration:  STRUCT structure_element_declaration_list END_STRUCT */
/* structure_element_declaration_list structure_element_declaration ';' */
void *search_base_type_c::visit(structure_element_declaration_list_c *symbol)           {return (void *)symbol;}

/*  structure_element_name ':' *_spec_init */
void *search_base_type_c::visit(structure_element_declaration_c *symbol)                {ERROR; return NULL;} /* should never get called... */

/* helper symbol for structure_initialization */
/* structure_initialization: '(' structure_element_initialization_list ')' */
/* structure_element_initialization_list ',' structure_element_initialization */
void *search_base_type_c::visit(structure_element_initialization_list_c *symbol)        {ERROR; return NULL;} /* should never get called... */

/*  structure_element_name ASSIGN value */
void *search_base_type_c::visit(structure_element_initialization_c *symbol)             {ERROR; return NULL;} /* should never get called... */

/*  string_type_name ':' elementary_string_type_name string_type_declaration_size string_type_declaration_init */
/*
SYM_REF4(string_type_declaration_c,	string_type_name,
					elementary_string_type_name,
					string_type_declaration_size,
					string_type_declaration_init) // may be == NULL!
*/
void *search_base_type_c::visit(string_type_declaration_c *symbol)	                {return (void *)symbol;}

  

/*****************************/
/* B 1.5.2 - Function Blocks */
/*****************************/
/*  FUNCTION_BLOCK derived_function_block_name io_OR_other_var_declarations function_block_body END_FUNCTION_BLOCK */
// SYM_REF3(function_block_declaration_c, fblock_name, var_declarations, fblock_body)
void *search_base_type_c::visit(function_block_declaration_c *symbol)                   {return (void *)symbol;}



/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/
/* INITIAL_STEP step_name ':' action_association_list END_STEP */
// SYM_REF2(initial_step_c, step_name, action_association_list)
void *search_base_type_c::visit(initial_step_c *symbol) {
  this->current_type_name = NULL; /* this pseudo data type does not have a type name! */
  return (void *)symbol;
}

/* STEP step_name ':' action_association_list END_STEP */
// SYM_REF2(step_c, step_name, action_association_list)
void *search_base_type_c::visit(step_c *symbol) {
  this->current_type_name = NULL; /* this pseudo data type does not have a type name! */
  return (void *)symbol;
}

