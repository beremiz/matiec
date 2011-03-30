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


/*
 * Function call parameter iterator.
 *
 * This is part of the 4th stage that generates
 * a c++ source program equivalent to the IL and ST
 * code.
 */


#include "../absyntax/visitor.hh"



/* given a function_body_c, iterate through each
 * function/FB call in that code.
 */

class function_call_iterator_c : public iterator_visitor_c {

  private:
    symbol_c *start_symbol;
    int next_fcall, fcall_count;
    symbol_c *current_fcall_name;
    symbol_c *current_finvocation;

  public:
    /* initialise the iterator object.
     * We must be given a reference to the function declaration
     * that will be analysed...
     */
    function_call_iterator_c(symbol_c *symbol);

    /* Skip to the next function call. After object creation,
     * the object references _before_ the first, so
     * this function must be called once to get the object to
     * reference the first function call...
     *
     * Returns the function_invocation_c!
     */
    symbol_c *next(void);

    /* Returns the name of the currently referenced function invocation */
    identifier_c *fname(void);

  private:
  /***************************************/
  /* B.3 - Language ST (Structured Text) */
  /***************************************/
  /***********************/
  /* B 3.1 - Expressions */
  /***********************/
    void *visit(function_invocation_c *symbol);
  
  /****************************************/
  /* B.2 - Language IL (Instruction List) */
  /****************************************/
  /***********************************/
  /* B 2.1 Instructions and Operands */
  /***********************************/
  
  /* | function_name [il_operand_list] */
  // SYM_REF2(il_function_call_c, function_name, il_operand_list)
    void *visit(il_function_call_c *symbol);
  
  /* | function_name '(' eol_list [il_param_list] ')' */
  // SYM_REF2(il_formal_funct_call_c, function_name, il_param_list)
  void *visit(il_formal_funct_call_c *symbol);

}; // class function_call_iterator_c 




