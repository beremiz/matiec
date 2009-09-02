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


/* Determine the data type of an ST expression.
 * A reference to the relevant type definition is returned.
 *
 * For example:
 *       2 + 3       -> returns reference to a int_type_name_c object.
 *       22.2 - 5    -> returns reference to a real_type_name_c object.
 *       etc...
 */



#include "absyntax_utils.hh"
#include <typeinfo>

search_expression_type_c::search_expression_type_c(symbol_c *search_scope) {
  search_varfb_instance_type = new search_varfb_instance_type_c(search_scope);
}

search_expression_type_c::~search_expression_type_c(void) {
  delete search_varfb_instance_type;
}

/* A helper function... */
bool search_expression_type_c::is_bool_type(symbol_c *type_symbol) {
  bool_type_name_c tt;
  if (type_symbol == NULL) {return true;}
  return (typeid(*type_symbol) == typeid(bool_type_name_c));
}

/* A helper function... */
bool search_expression_type_c::is_time_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return true;}
  if (typeid(*type_symbol) == typeid(time_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(date_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(tod_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(dt_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool search_expression_type_c::is_string_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return true;}
  if (typeid(*type_symbol) == typeid(string_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(wstring_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool search_expression_type_c::is_literal_integer_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return true;}
  if (typeid(*type_symbol) == typeid(integer_c))        {return true;}
  if (typeid(*type_symbol) == typeid(binary_integer_c)) {return true;}
  if (typeid(*type_symbol) == typeid(octal_integer_c))  {return true;}
  if (typeid(*type_symbol) == typeid(hex_integer_c))    {return true;}
  return false;
}

/* A helper function... */
bool search_expression_type_c::is_integer_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return true;}
  if (typeid(*type_symbol) == typeid(sint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(int_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(dint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(lint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(usint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(uint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(udint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(ulint_type_name_c)) {return true;}
  return is_literal_integer_type(type_symbol);
}

/* A helper function... */
bool search_expression_type_c::is_literal_real_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return true;}
  if (typeid(*type_symbol) == typeid(real_c)) {return true;}
  return false;
}

/* A helper function... */
bool search_expression_type_c::is_real_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return true;}
  if (typeid(*type_symbol) == typeid(real_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(lreal_type_name_c)) {return true;}
  return is_literal_real_type(type_symbol);
}

bool search_expression_type_c::is_num_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return true;}
  return is_real_type(type_symbol) || is_integer_type(type_symbol);
}

bool search_expression_type_c::is_nbinary_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return true;}
  if (typeid(*type_symbol) == typeid(byte_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(word_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(dword_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(lword_type_name_c)) {return true;}
  return is_literal_integer_type(type_symbol);
}

bool search_expression_type_c::is_binary_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return true;}
  if (typeid(*type_symbol) == typeid(bool_type_name_c)) {return true;}
  return is_nbinary_type(type_symbol);
}

bool search_expression_type_c::is_same_type(symbol_c *first_type, symbol_c *second_type) {
  if (first_type == NULL || second_type == NULL) {return true;}
  if (typeid(*first_type) == typeid(*second_type)) {return true;}
  if (is_integer_type(first_type) && is_literal_integer_type(second_type)) {return true;}
  if (is_literal_integer_type(first_type) && is_integer_type(second_type)) {return true;}
  if (is_binary_type(first_type) && is_literal_integer_type(second_type))  {return true;}
  if (is_literal_integer_type(first_type) && is_binary_type(second_type))  {return true;}
  if (is_real_type(first_type) && is_literal_real_type(second_type)) {return true;}
  if (is_literal_real_type(first_type) && is_real_type(second_type)) {return true;}
  return false;
}

symbol_c* search_expression_type_c::common_type(symbol_c *first_type, symbol_c *second_type) {
  if (first_type == NULL && second_type == NULL) {return NULL;}
  if (first_type == NULL) {return second_type;}
  if (second_type == NULL) {return first_type;}
  if (typeid(*first_type) == typeid(*second_type)) {return first_type;}
  if (is_integer_type(first_type) && is_literal_integer_type(second_type)) {return first_type;}
  if (is_literal_integer_type(first_type) && is_integer_type(second_type)) {return second_type;}
  if (is_binary_type(first_type) && is_literal_integer_type(second_type))  {return first_type;}
  if (is_literal_integer_type(first_type) && is_binary_type(second_type))  {return second_type;}
  if (is_real_type(first_type) && is_literal_real_type(second_type)) {return first_type;}
  if (is_literal_real_type(first_type) && is_real_type(second_type)) {return second_type;}
  return NULL;
}


integer_c search_expression_type_c::integer("1"); // what default value should we use here ???
#include "search_type_code.c"

/*static bool_type_name_c bool_type_name;*/

/* A helper function... */
void *search_expression_type_c::compute_boolean_expression(symbol_c *left_type, symbol_c *right_type) {
  if (!is_same_type(left_type, right_type))
    ERROR;
  if (!is_bool_type(left_type) && !is_binary_type(left_type))
    ERROR;
  if (is_literal_integer_type(left_type)) {return (void *)right_type;}
  else {return (void *)left_type;}
}

/* A helper function... */
void *search_expression_type_c::compute_numeric_expression(symbol_c *left_type, symbol_c *right_type) {
  if (!is_same_type(left_type, right_type))
    ERROR;
  if (!is_integer_type(left_type) && !is_real_type(left_type))
    ERROR;
  if (is_literal_integer_type(left_type) || is_literal_real_type(left_type)) {return (void *)right_type;}
  else {return (void *)left_type;}
  return NULL;
}

/* a helper function... */
symbol_c *search_expression_type_c::base_type(symbol_c *symbol) {
  return (symbol_c *)symbol->accept(search_base_type);
}

/*********************/
/* B 1.4 - Variables */
/*********************/

void *search_expression_type_c::visit(symbolic_variable_c *symbol) {
  symbol_c *res;
  
  /* Nope, now we assume it is a variable, and determine its type... */
  res = search_varfb_instance_type->get_type(symbol);
  if (NULL != res) return res;
  
  return NULL;
}

/********************************************/
/* B 1.4.1 - Directly Represented Variables */
/********************************************/
void *search_expression_type_c::visit(direct_variable_c *symbol) {
  symbol_c *res;
  
  /* Nope, now we assume it is a variable, and determine its type... */
  res = search_varfb_instance_type->get_type(symbol);
  if (NULL != res) return res;
  
  return NULL;
}

/*************************************/
/* B 1.4.2 - Multi-element variables */
/*************************************/

void *search_expression_type_c::visit(array_variable_c *symbol) {
  symbol_c *res;
  
  /* Nope, now we assume it is a variable, and determine its type... */
  res = search_varfb_instance_type->get_type(symbol);
  if (NULL != res) return res;
  
  return NULL;
}

void *search_expression_type_c::visit(structured_variable_c *symbol) {
  symbol_c *res;
  
  /* Nope, now we assume it is a variable, and determine its type... */
  res = search_varfb_instance_type->get_type(symbol);
  if (NULL != res) return res;
  
  return NULL;
}

/***************************************/
/* B.3 - Language ST (Structured Text) */
/***************************************/
/***********************/
/* B 3.1 - Expressions */
/***********************/
void *search_expression_type_c::visit(or_expression_c *symbol) {
  symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  return compute_boolean_expression(left_type, right_type);
}

void *search_expression_type_c::visit(xor_expression_c *symbol) {
  symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  return compute_boolean_expression(left_type, right_type);
}

void *search_expression_type_c::visit(and_expression_c *symbol) {
  symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  return compute_boolean_expression(left_type, right_type); 
}

void *search_expression_type_c::visit(equ_expression_c *symbol) {return (void *)&bool_type_name;}
void *search_expression_type_c::visit(notequ_expression_c *symbol) {return (void *)&bool_type_name;}
void *search_expression_type_c::visit(lt_expression_c *symbol) {return (void *)&bool_type_name;}
void *search_expression_type_c::visit(gt_expression_c *symbol) {return (void *)&bool_type_name;}
void *search_expression_type_c::visit(le_expression_c *symbol) {return (void *)&bool_type_name;}
void *search_expression_type_c::visit(ge_expression_c *symbol) {return (void *)&bool_type_name;}

void *search_expression_type_c::visit(add_expression_c *symbol) {
  symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  if (typeid(*left_type) == typeid(time_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) {return (void *)&time_type_name;}
  if (typeid(*left_type) == typeid(tod_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) {return (void *)&tod_type_name;}
  if (typeid(*left_type) == typeid(dt_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) {return (void *)&dt_type_name;}
  return compute_numeric_expression(left_type, right_type);
}

void *search_expression_type_c::visit(sub_expression_c *symbol) {
  symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  if (typeid(*left_type) == typeid(time_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) {return (void *)&time_type_name;}
  if (typeid(*left_type) == typeid(date_type_name_c) && typeid(*right_type) == typeid(date_type_name_c)) {return (void *)&time_type_name;}
  if (typeid(*left_type) == typeid(tod_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) {return (void *)&tod_type_name;}
  if (typeid(*left_type) == typeid(tod_type_name_c) && typeid(*right_type) == typeid(tod_type_name_c)) {return (void *)&time_type_name;}
  if (typeid(*left_type) == typeid(dt_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) {return (void *)&dt_type_name;}
  if (typeid(*left_type) == typeid(dt_type_name_c) && typeid(*right_type) == typeid(dt_type_name_c)) {return (void *)&time_type_name;}
  return compute_numeric_expression(left_type, right_type);
}

void *search_expression_type_c::visit(mul_expression_c *symbol) {
  symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  if (typeid(*left_type) == typeid(time_type_name_c) && is_num_type(right_type)) {
      return (void *)&time_type_name;
  }
  return compute_numeric_expression(left_type, right_type);
}

void *search_expression_type_c::visit(div_expression_c *symbol) {
  symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  if (typeid(*left_type) == typeid(time_type_name_c) && is_num_type(right_type)){
      return (void *)&time_type_name;
  }
  return compute_numeric_expression(left_type, right_type);
}

void *search_expression_type_c::visit(mod_expression_c *symbol) {
  symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  return compute_numeric_expression(left_type, right_type);
}

void *search_expression_type_c::visit(power_expression_c *symbol) {
  symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
  symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
  if (is_real_type(left_type) && is_num_type(right_type)) {
      return (void *)left_type;
  }
  ERROR;
  return NULL;
}

void *search_expression_type_c::visit(neg_expression_c *symbol) {
  symbol_c *exp_type = base_type((symbol_c *)symbol->exp->accept(*this));
  if (is_num_type(exp_type) || typeid(*exp_type) == typeid(time_type_name_c)){
      return (void *)exp_type;
  }
  ERROR;
  return NULL;
}

void *search_expression_type_c::visit(not_expression_c *symbol) {
  symbol_c *exp_type = base_type((symbol_c *)symbol->exp->accept(*this));
  return compute_boolean_expression(exp_type, exp_type);
}

void *search_expression_type_c::visit(function_invocation_c *symbol) {
  function_declaration_c *f_decl = function_symtable.find_value(symbol->function_name);
  if (f_decl == function_symtable.end_value()) {
    void *res = compute_standard_function_default(symbol);
    if (res == NULL)
       ERROR;
    return res;
  }
  return base_type(f_decl->type_name);
}

/*bool_type_name_c     search_expression_type_c::bool_type_name;*/

