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



#include "../absyntax/visitor.hh"



class decompose_var_instance_name_c: null_visitor_c {

  private:
    symbol_c *variable_name;
    symbol_c *next_variable_name;
    symbol_c *current_recursive_variable_name;
    symbol_c *previously_returned_variable_name;

  public:
    decompose_var_instance_name_c(symbol_c *variable_instance_name);

    symbol_c *next_part(void);

  private:
  /*************************/
  /* B.1 - Common elements */
  /*************************/
  /*******************************************/
  /* B 1.1 - Letters, digits and identifiers */
  /*******************************************/
    void *visit(identifier_c *symbol);

  /*********************/
  /* B 1.4 - Variables */
  /*********************/
    void *visit(symbolic_variable_c *symbol);

  /********************************************/
  /* B.1.4.1   Directly Represented Variables */
  /********************************************/
    void *visit(direct_variable_c *symbol);
  
  /*************************************/
  /* B.1.4.2   Multi-element Variables */
  /*************************************/
  /*  subscripted_variable '[' subscript_list ']' */
  // SYM_REF2(array_variable_c, subscripted_variable, subscript_list)
    void *visit(array_variable_c *symbol);
  
  /*  record_variable '.' field_selector */
  /*  WARNING: input and/or output variables of function blocks
   *           may be accessed as fields of a tructured variable!
   *           Code handling a structured_variable_c must take
   *           this into account!
   */
  //SYM_REF2(structured_variable_c, record_variable, field_selector)
    void *visit(structured_variable_c *symbol);

}; // decompose_var_instance_name_c




