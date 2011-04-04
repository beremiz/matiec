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

/* Determine the data type of an ST expression.
 * A reference to the relevant type definition is returned.
 *
 * For example:
 *       2 + 3       -> returns reference to a int_type_name_c object.
 *       22.2 - 5    -> returns reference to a real_type_name_c object.
 *       etc...
 */

class search_expression_type_c: public search_constant_type_c {

  private:
    search_varfb_instance_type_c *search_varfb_instance_type;
    search_base_type_c search_base_type;


  public:
    search_expression_type_c(symbol_c *search_scope);
    virtual ~search_expression_type_c(void);

    /* A helper function... */
    bool is_bool_type(symbol_c *type_symbol);
    bool is_time_type(symbol_c *type_symbol);
    bool is_string_type(symbol_c *type_symbol);
    bool is_literal_integer_type(symbol_c *type_symbol);
    bool is_integer_type(symbol_c *type_symbol);
    bool is_literal_real_type(symbol_c *type_symbol);
    bool is_real_type(symbol_c *type_symbol);
    bool is_num_type(symbol_c *type_symbol);
    bool is_nbinary_type(symbol_c *type_symbol);
    bool is_binary_type(symbol_c *type_symbol);

    bool is_same_type(symbol_c *first_type, symbol_c *second_type);
    symbol_c* common_type(symbol_c *first_type, symbol_c *second_type);

    /*
    #include "search_type_code.c"
    */
    void *compute_standard_function_default(function_invocation_c *st_symbol, il_formal_funct_call_c *il_symbol);
    void *compute_standard_function_il(il_function_call_c *symbol, symbol_c *param_data_type);



    /*static bool_type_name_c bool_type_name;*/

    /* A helper function... */
    void *compute_boolean_expression(symbol_c *left_type, symbol_c *right_type);

    /* A helper function... */
    void *compute_numeric_expression(symbol_c *left_type, symbol_c *right_type);

    /* a helper function... */
    symbol_c *base_type(symbol_c *symbol);

    /*********************/
    /* B 1.4 - Variables */
    /*********************/
    
    void *visit(symbolic_variable_c *symbol);

    /********************************************/
    /* B 1.4.1 - Directly Represented Variables */
    /********************************************/
    void *visit(direct_variable_c *symbol);

    /*************************************/
    /* B 1.4.2 - Multi-element variables */
    /*************************************/
 
    void *visit(array_variable_c *symbol);
    void *visit(structured_variable_c *symbol);

    /***************************************/
    /* B.3 - Language ST (Structured Text) */
    /***************************************/
    /***********************/
    /* B 3.1 - Expressions */
    /***********************/
    void *visit(or_expression_c *symbol);
    void *visit(xor_expression_c *symbol);
    void *visit(and_expression_c *symbol);
    void *visit(equ_expression_c *symbol);
    void *visit(notequ_expression_c *symbol);
    void *visit(lt_expression_c *symbol);
    void *visit(gt_expression_c *symbol);
    void *visit(le_expression_c *symbol);
    void *visit(ge_expression_c *symbol);
    
    void *visit(add_expression_c *symbol);
    void *visit(sub_expression_c *symbol);
    void *visit(mul_expression_c *symbol);
    void *visit(div_expression_c *symbol);
    void *visit(mod_expression_c *symbol);
    void *visit(power_expression_c *symbol);
    void *visit(neg_expression_c *symbol);
    void *visit(not_expression_c *symbol);
    void *visit(function_invocation_c *symbol);


    static integer_c integer;

}; // search_expression_type_c



