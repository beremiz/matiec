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

/* Verify whether the semantic rules of data type compatibility are being followed.
 *
 * For example:
 */

#include "../absyntax_utils/absyntax_utils.hh"

class visit_expression_type_c: public search_constant_type_c {

  private:
    search_varfb_instance_type_c *search_varfb_instance_type;
    search_base_type_c search_base_type;

    /* When calling a function block, we must first find it's type,
     * by searching through the declarations of the variables currently
     * in scope.
     * This class does just that...
     * A new bject instance is instantiated whenever we start checking semantics
     * for a function block type declaration, or a program declaration.
     * This object instance will then later be called while the
     * function block's or the program's body is being handled.
     *
     * Note that functions cannot contain calls to function blocks,
     * so we do not create an object instance when handling
     * a function declaration.
     */
//     search_var_instance_decl_c *search_var_instance_decl;
    
     /* This variable was created to pass information from
      * visit_expression_type_c::visit(case_statement_c *symbol) function to
      * visit_expression_type_c::visit(case_list_c *symbol) function.
      */
      symbol_c *case_expression_type;
  
    /* In IL code, once we find a type mismatch error, it is best to
     * ignore any further errors until the end of the logicl operation,
     * i.e. until the next LD.
     * However, we cannot clear the il_error flag on all LD operations,
     * as these may also be used within parenthesis. LD operations
     * within parenthesis may not clear the error flag.
     * We therefore need a counter to know how deep inside a parenthesis 
     * structure we are.
     */
    int  il_parenthesis_level;
    bool il_error;
    bool error_found;

    /* the current data type of the data stored in the IL stack, i.e. the default variable */
    symbol_c *il_default_variable_type;
    /* the current IL operand being analysed - its symbol and its data type */
    symbol_c *il_operand_type;
    symbol_c *il_operand;


  public:
    visit_expression_type_c(symbol_c *ignore);
    virtual ~visit_expression_type_c(void);

    bool get_error_found(void);

    typedef struct {
      symbol_c *value;
      symbol_c *type;
    } value_and_type_t; 

    /* A helper function... */
    bool is_ANY_ELEMENTARY_type         (symbol_c *type_symbol);
    bool is_ANY_SAFEELEMENTARY_type     (symbol_c *type_symbol);
    bool is_ANY_ELEMENTARY_compatible   (symbol_c *type_symbol);

    bool is_ANY_MAGNITUDE_type          (symbol_c *type_symbol);
    bool is_ANY_SAFEMAGNITUDE_type      (symbol_c *type_symbol);
    bool is_ANY_MAGNITUDE_compatible    (symbol_c *type_symbol);

    bool is_ANY_DATE_type               (symbol_c *type_symbol);
    bool is_ANY_SAFEDATE_type           (symbol_c *type_symbol);
    bool is_ANY_DATE_compatible         (symbol_c *type_symbol);

    bool is_ANY_STRING_type             (symbol_c *type_symbol);
    bool is_ANY_SAFESTRING_type         (symbol_c *type_symbol);
    bool is_ANY_STRING_compatible       (symbol_c *type_symbol);   

    bool is_ANY_INT_type                (symbol_c *type_symbol);
    bool is_ANY_SAFEINT_type            (symbol_c *type_symbol);
    bool is_ANY_INT_compatible          (symbol_c *type_symbol);

    bool is_ANY_REAL_type               (symbol_c *type_symbol);
    bool is_ANY_SAFEREAL_type           (symbol_c *type_symbol);
    bool is_ANY_REAL_compatible         (symbol_c *type_symbol);

    bool is_ANY_NUM_type                (symbol_c *type_symbol);
    bool is_ANY_SAFENUM_type            (symbol_c *type_symbol);
    bool is_ANY_NUM_compatible          (symbol_c *type_symbol);

    bool is_ANY_BIT_type                (symbol_c *type_symbol);
    bool is_ANY_SAFEBIT_type            (symbol_c *type_symbol);
    bool is_ANY_BIT_compatible          (symbol_c *type_symbol);

    bool is_BOOL_type                   (symbol_c *type_symbol);
    bool is_SAFEBOOL_type               (symbol_c *type_symbol);
    bool is_ANY_BOOL_compatible         (symbol_c *type_symbol);
    
    bool is_nonneg_literal_integer_type (symbol_c *type_symbol);
    bool is_literal_integer_type        (symbol_c *type_symbol);
    bool is_literal_real_type           (symbol_c *type_symbol);
    bool is_literal_bool_type           (symbol_c *type_symbol);

    /* Determine the common data type between two data types.
     * If no common data type found, return NULL.
     *
     * If data types are identical, return the first (any would do...).
     * If any of the datat types is a literal, we confirm that 
     *   the literal uses less bits than the fixed size data type.
     *   e.g. BYTE and 1024 returns NULL
     *        BYTE and 255  returns BYTE
     *
     * If two literals, then return the literal that requires more bits...
     */
    symbol_c *common_type__(symbol_c *first_type, symbol_c *second_type);
    /* Determine the common data type between two data types.
     * Unlike the common_type__() function, we stop the compiler with an ERROR
     *  if no common data type is found.
     */
    symbol_c *common_type(symbol_c *first_type, symbol_c *second_type);
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
    bool is_valid_assignment(symbol_c *var_type, symbol_c *value_type);

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
    bool is_compatible_type(symbol_c *first_type, symbol_c *second_type);

    void compute_input_operatores(symbol_c *symbol, const char *input_operator);
    void check_formal_parameter(symbol_c *call_param_name, symbol_c *call_param_type, symbol_c *f_decl);

    /* check the semantics of a FB or Function non-formal call */
    /* e.g. foo(1, 2, 3, 4);  */
    void check_nonformal_call(symbol_c *f_call, symbol_c *f_decl, bool use_il_defvar = false);
    /* check the semantics of a FB or Function formal call */
    /* e.g. foo(IN1 := 1, OUT1 =>x, EN := true);  */
    void check_formal_call(symbol_c *f_call, symbol_c *f_decl);


    void *compute_standard_function_default(function_invocation_c *st_symbol, il_formal_funct_call_c *il_symbol);
    void *compute_standard_function_il(il_function_call_c *symbol, symbol_c *param_data_type);


    /* A helper function... */
    typedef bool (visit_expression_type_c::*is_data_type_t)(symbol_c *type_symbol);  /* a pointer to a function! */
//    symbol_c *compute_boolean_expression(symbol_c *left_exp, symbol_c *right_exp, is_data_type_t is_data_type);
//    symbol_c *compute_numeric_expression(symbol_c *left_exp, symbol_c *right_exp, is_data_type_t is_data_type);
//    symbol_c *compute_expression(symbol_c *left_exp, symbol_c *right_exp, is_data_type_t is_data_type);
    symbol_c *compute_expression(symbol_c *left_type, symbol_c *right_type, is_data_type_t is_data_type,
                                 symbol_c *left_expr=NULL, symbol_c *right_expr=NULL);


    /* a helper function... */
    symbol_c *base_type(symbol_c *symbol);

    /* a helper function... */
    void *verify_null(symbol_c *symbol);

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

    /****************************************/
    /* B.2 - Language IL (Instruction List) */
    /****************************************/
    /***********************************/
    /* B 2.1 Instructions and Operands */
    /***********************************/
    // void *visit(instruction_list_c *symbol);
    void *visit(il_simple_operation_c *symbol);
    void *visit(il_function_call_c *symbol);
    void *visit(il_expression_c *symbol);
//     void *visit(il_jump_operation_c *symbol);
    void *visit(il_fb_call_c *symbol);
    void *visit(il_formal_funct_call_c *symbol);
    /*
    void *visit(il_operand_list_c *symbol);
    void *visit(simple_instr_list_c *symbol);
    void *visit(il_param_list_c *symbol);
    void *visit(il_param_assignment_c *symbol);
    void *visit(il_param_out_assignment_c *symbol);
    */

    /*******************/
    /* B 2.2 Operators */
    /*******************/
    void *visit(LD_operator_c *symbol);
    void *visit(LDN_operator_c *symbol);
    void *visit(ST_operator_c *symbol);
    void *visit(STN_operator_c *symbol);
    void *visit(NOT_operator_c *symbol);
    void *visit(S_operator_c *symbol);
    void *visit(R_operator_c *symbol);
    void *visit(S1_operator_c *symbol);
    void *visit(R1_operator_c *symbol);
    void *visit(CLK_operator_c *symbol);
    void *visit(CU_operator_c *symbol);
    void *visit(CD_operator_c *symbol);
    void *visit(PV_operator_c *symbol);
    void *visit(IN_operator_c *symbol);
    void *visit(PT_operator_c *symbol);
    void *visit(AND_operator_c *symbol);
    void *visit(OR_operator_c *symbol);
    void *visit(XOR_operator_c *symbol);
    void *visit(ANDN_operator_c *symbol);
    void *visit(ORN_operator_c *symbol);
    void *visit(XORN_operator_c *symbol);
    void *visit(ADD_operator_c *symbol);
    void *visit(SUB_operator_c *symbol);
    void *visit(MUL_operator_c *symbol);
    void *visit(DIV_operator_c *symbol);
    void *visit(MOD_operator_c *symbol);
    void *visit(GT_operator_c *symbol);
    void *visit(GE_operator_c *symbol);
    void *visit(EQ_operator_c *symbol);
    void *visit(LT_operator_c *symbol);
    void *visit(LE_operator_c *symbol);
    void *visit(NE_operator_c *symbol);
    void *visit(CAL_operator_c *symbol);
    void *visit(CALC_operator_c *symbol);
    void *visit(CALCN_operator_c *symbol);
    void *visit(RET_operator_c *symbol);
    void *visit(RETC_operator_c *symbol);
    void *visit(RETCN_operator_c *symbol);
    void *visit(JMP_operator_c *symbol);
    void *visit(JMPC_operator_c *symbol);
    void *visit(JMPCN_operator_c *symbol);
    /* Symbol class handled together with function call checks */
    // void *visit(il_assign_operator_c *symbol, variable_name);
    /* Symbol class handled together with function call checks */
    // void *visit(il_assign_operator_c *symbol, option, variable_name);



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

    /*********************************/
    /* B 3.2.1 Assignment Statements */
    /*********************************/
    void *visit(assignment_statement_c *symbol);

    /*****************************************/
    /* B 3.2.2 Subprogram Control Statements */
    /*****************************************/
    void *visit(fb_invocation_c *symbol);

    /********************************/
    /* B 3.2.3 Selection Statements */
    /********************************/
 
    void *visit(if_statement_c *symbol);    
//     void *visit(elseif_statement_list_c *symbol);
    void *visit(elseif_statement_c *symbol);
    void *visit(case_statement_c *symbol);
//     void *visit(case_element_list_c *symbol);
//     void *visit(case_element_c *symbol);   
   void *visit(case_list_c *symbol);
    
    /********************************/
    /* B 3.2.4 Iteration Statements */
    /********************************/
    
    void *visit(for_statement_c *symbol);
    void *visit(while_statement_c *symbol);
    void *visit(repeat_statement_c *symbol);
    

//TODO: delete this functions. Why are they needed?
void *visit(program_declaration_c *symbol);
void *visit(function_declaration_c *symbol);
void *visit(function_block_declaration_c *symbol);

}; // visit_expression_type_c

