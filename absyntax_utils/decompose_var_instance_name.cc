/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2003-2011  Mario de Sousa (msousa@fe.up.pt)
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


/* Decomposes a variable instance name into its constituents,
 * example:
 *    window.points[1].coordinate.x
 *
 *  will succesfully return
 *        - window
 *        - points
 *        - coordinate
 *        - x
 * on succesive calls to decompose_var_instance_name_c::next_part()
 */



#include "decompose_var_instance_name.hh"

decompose_var_instance_name_c::decompose_var_instance_name_c(symbol_c *variable_instance_name) {
  variable_name = variable_instance_name;
  next_variable_name = NULL;
  current_recursive_variable_name = NULL;
  previously_returned_variable_name = NULL;
}

symbol_c *decompose_var_instance_name_c::next_part(bool increment) {
  /* We must always start from the top!
   * See note in the structured_variable_c visitor
   * to understand why...
   */
  symbol_c *res = (symbol_c *)variable_name->accept(*this);
  if (increment)
    next_variable_name = current_recursive_variable_name;

  if (previously_returned_variable_name == res)
	  return NULL;
  if (increment)
    previously_returned_variable_name = res;
  return res;
}

/*************************/
/* B.1 - Common elements */
/*************************/
/*******************************************/
/* B 1.1 - Letters, digits and identifiers */
/*******************************************/
/* sometimes (e.g. FB calls) the name of the variable is stored directly in an identifier_c object */
void *decompose_var_instance_name_c::visit(identifier_c *symbol) {return (void *)symbol;}

/*********************/
/* B 1.4 - Variables */
/*********************/
void *decompose_var_instance_name_c::visit(symbolic_variable_c *symbol) {return (void *)(symbol->var_name);}

/********************************************/
/* B.1.4.1   Directly Represented Variables */
/********************************************/
void *decompose_var_instance_name_c::visit(direct_variable_c *symbol) {return (void *)symbol;}

/*************************************/
/* B.1.4.2   Multi-element Variables */
/*************************************/
/*  subscripted_variable '[' subscript_list ']' */
// SYM_REF2(array_variable_c, subscripted_variable, subscript_list)
void *decompose_var_instance_name_c::visit(array_variable_c *symbol) {
  /* NOTE: the subscripted_variable may itself be a structure!,
   * so we must recursevily visit!
   */
  return symbol->subscripted_variable->accept(*this);
}

/*  record_variable '.' field_selector */
/*  WARNING: input and/or output variables of function blocks
 *           may be accessed as fields of a tructured variable!
 *           Code handling a structured_variable_c must take
 *           this into account!
 */
//SYM_REF2(structured_variable_c, record_variable, field_selector)
void *decompose_var_instance_name_c::visit(structured_variable_c *symbol) {
  /* NOTE: The following code will not work, as structured_variable_c
   *       are grouped on the left, and not on the right!
   *
   *       example: window.origin.x
   *       will result in
   *       s1 = structured_variable_c("window, "origin");
   *       s2 = structured_variable_c(s1, "x");
   *       AND NOT
   *       s1 = structured_variable_c("origin", "x");
   *       s2 = structured_variable_c("window", s1);
   *
   *       as the following code assumes!!
   *
  current_variable_name = symbol->field_selector;
  return symbol->record_variable->accept(*this);
   */

  /* The correct code, is therefore more complex... */
  if (next_variable_name == symbol) {
    /* NOTE: field_selector is always an identifier_c,
     * so we do not have to recursevily visit it again...
     * return (void *)symbol->field_selector->accept(*this);  -> NOT REQUIRED!!
     */
	 return (void *)symbol->field_selector;
  }

  current_recursive_variable_name = symbol;
  return symbol->record_variable->accept(*this);
}




