/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2009-2011  Mario de Sousa (msousa@fe.up.pt)
 *  Copyright (C) 2011-2012  Manuele Conti (manuele.conti@sirius-es.it)
 *  Copyright (C) 2011-2012  Matteo Facchinetti (matteo.facchinetti@sirius-es.it)
 *
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


#include "../absyntax_utils/absyntax_utils.hh"
#include "datatype_functions.hh"


class print_datatypes_error_c: public iterator_visitor_c {

  private:
    /* The level of detail that the user wants us to display error messages. */
//     #define error_level_default (1)
    #define error_level_default (1)
    #define error_level_nagging (4)
    unsigned int current_display_error_level;
    
    search_varfb_instance_type_c *search_varfb_instance_type;
    search_base_type_c search_base_type;
    /* When calling a function block, we must first find it's type,
     * by searching through the declarations of the variables currently
     * in scope.
     * This class does just that...
     * A new object instance is instantiated whenever we start checking semantics
     * for a function block type declaration, or a program declaration.
     * This object instance will then later be called while the
     * function block's or the program's body is being handled.
     *
     * Note that functions cannot contain calls to function blocks,
     * so we do not create an object instance when handling
     * a function declaration.
     */

    /* In IL code, once we find a type mismatch error, it is best to
     * ignore any further errors until the end of the logical operation,
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
    symbol_c *prev_il_instruction;
    /* the current IL operand being analyzed - its symbol and its data type */
    symbol_c *il_operand_type;
    symbol_c *il_operand;

    /* some helper functions... */
    symbol_c *base_type(symbol_c *symbol);
    void handle_function_invocation(symbol_c *fcall, generic_function_call_t fcall_data);
    void handle_implicit_il_fb_invocation(symbol_c *il_operator, const char *param_name, symbol_c *called_fb_declaration);  
    void *handle_conditional_flow_control_IL_instruction(symbol_c *symbol, const char *oper);
  
  public:
    print_datatypes_error_c(symbol_c *ignore);
    virtual ~print_datatypes_error_c(void);
    int get_error_found();


    /*********************/
    /* B 1.2 - Constants */
    /*********************/
    /******************************/
    /* B 1.2.1 - Numeric Literals */
    /******************************/
    void *visit(real_c *symbol);
    void *visit(integer_c *symbol);
    void *visit(neg_real_c *symbol);
    void *visit(neg_integer_c *symbol);
    void *visit(binary_integer_c *symbol);
    void *visit(octal_integer_c *symbol);
    void *visit(hex_integer_c *symbol);
    void *visit(integer_literal_c *symbol);
    void *visit(real_literal_c *symbol);
    void *visit(bit_string_literal_c *symbol);
    void *visit(boolean_literal_c *symbol);
    void *visit(boolean_true_c *symbol);
    void *visit(boolean_false_c *symbol);

    /*******************************/
    /* B.1.2.2   Character Strings */
    /*******************************/
    void *visit(double_byte_character_string_c *symbol);
    void *visit(single_byte_character_string_c *symbol);

    /***************************/
    /* B 1.2.3 - Time Literals */
    /***************************/
    /************************/
    /* B 1.2.3.1 - Duration */
    /************************/
    void *visit(duration_c *symbol);

    /************************************/
    /* B 1.2.3.2 - Time of day and Date */
    /************************************/
    void *visit(time_of_day_c *symbol);
    void *visit(date_c *symbol);
    void *visit(date_and_time_c *symbol);

    /**********************/
    /* B 1.3 - Data types */
    /**********************/
    /********************************/
    /* B 1.3.3 - Derived data types */
    /********************************/
    void *visit(data_type_declaration_c *symbol);
    void *visit(enumerated_value_c *symbol);

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

    /**************************************/
    /* B 1.5 - Program organization units */
    /**************************************/
    /***********************/
    /* B 1.5.1 - Functions */
    /***********************/
    void *visit(function_declaration_c *symbol);

    /*****************************/
    /* B 1.5.2 - Function blocks */
    /*****************************/
    void *visit(function_block_declaration_c *symbol);

    /**********************/
    /* B 1.5.3 - Programs */
    /**********************/
    void *visit(program_declaration_c *symbol);

    /********************************/
    /* B 1.7 Configuration elements */
    /********************************/
    void *visit(configuration_declaration_c *symbol);

    /****************************************/
    /* B.2 - Language IL (Instruction List) */
    /****************************************/
    /***********************************/
    /* B 2.1 Instructions and Operands */
    /***********************************/
//  void *visit(instruction_list_c *symbol);
    void *visit(il_instruction_c *symbol);
    void *visit(il_simple_operation_c *symbol);
    void *visit(il_function_call_c *symbol);
    void *visit(il_expression_c *symbol);
    void *visit(il_fb_call_c *symbol);
    void *visit(il_formal_funct_call_c *symbol);
//  void *visit(il_operand_list_c *symbol);
//  void *visit(simple_instr_list_c *symbol);
    void *visit(il_simple_instruction_c*symbol);
//  void *visit(il_param_list_c *symbol);
//  void *visit(il_param_assignment_c *symbol);
//  void *visit(il_param_out_assignment_c *symbol);

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
    // void *visit(case_list_c *symbol);

    /********************************/
    /* B 3.2.4 Iteration Statements */
    /********************************/
    void *visit(for_statement_c *symbol);
    void *visit(while_statement_c *symbol);
    void *visit(repeat_statement_c *symbol);

}; // print_datatypes_error_c







