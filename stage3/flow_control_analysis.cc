/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2012  Mario de Sousa (msousa@fe.up.pt)
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


/*
 *  Do flow control analysis of the IEC 61131-3 code.
 *
 *  We currently only do this for IL code.
 *  This class will annotate the abstract syntax tree, by filling in the
 *  prev_il_instruction variable in the il_instruction_c, so it points to
 *  the previous il_instruction_c object in the instruction list instruction_list_c.
 *
 *  The result will essentially be a linked list of il_instruction_c objects, each 
 *  pointing to the previous il_instruction_c object.
 *
 *  The reality is we will get several independent and isolated linked lists
 *  (actually, once we process labels correctly, this will become a graph):
 *  one for each block of IL code (e.g. inside a Function, FB or Program).
 *  Additionally, when the IL code has an expression (expression_c object), we will actually
 *  have one more isolated linked list for the IL code inside that expression.
 *
 *  e.g.
 *       line_1:   LD 1
 *       line_2:   ADD (42
 *       line_3:        ADD B
 *       line_4:        ADD C 
 *       line_5:       )
 *       line_6:   ADD D
 *       line_7:   ST  E
 * 
 *     will result in two independent linked lists:
 *       main list:  line_7 -> line_6 -> line2 -> line_1
 *       expr list:  lin4_4 -> line_3 -> (operand of line_2, i.e. '42')
 * 
 * 
 *     In the main list, each:
 *        line_x: IL_operation IL_operand
 *      is encoded as
 *          il_instruction_c(label, il_incomplete_instruction)
 *      these il_instruction_c objects will point back to the previous il_instruction_c object.
 *
 *     In the expr list, each 
 *        line_x:        IL_operation IL_operand
 *      is encoded as
 *          il_simple_instruction_c(il_simple_instruction)
 *      these il_simple_instruction_c objects will point back to the previous il_simple_instruction_c object,
 *      except the for the first il_simple_instruction_c object in the list, which will point back to
 *      the first il_operand (in the above example, '42'), or NULL is it does not exist.
 *          
 *
 * label:
 *   identifier_c  
 *   
 * il_incomplete_instruction:
 *   il_simple_operation   (il_simple_operation_c, il_function_call_c)
 * | il_expression         (il_expression_c)
 * | il_jump_operation     (il_jump_operation_c)
 * | il_fb_call            (il_fb_call_c)
 * | il_formal_funct_call  (il_formal_funct_call_c)
 * | il_return_operator    (RET_operator_c, RETC_operator_c, RETCN_operator_c)
 *  
 * 
 * il_expression_c(il_expr_operator, il_operand, simple_instr_list)
 * 
 * il_operand:
 *   variable            (symbolic_variable_c, direct_variable_c, array_variable_c, structured_variable_c)  
 * | enumerated_value    (enumerated_value_c)
 * | constant            (lots of literal classes _c)
 * 
 * simple_instr_list:
 *   list of il_simple_instruction
 * 
 * il_simple_instruction:
 *   il_simple_operation       (il_simple_operation_c, il_function_call_c)
 * | il_expression             (il_expression_c)
 * | il_formal_funct_call      (il_formal_funct_call_c)
 * 
 */

#include "flow_control_analysis.hh"



/* set to 1 to see debug info during execution */
static int debug = 0;

flow_control_analysis_c::flow_control_analysis_c(symbol_c *ignore) {
}

flow_control_analysis_c::~flow_control_analysis_c(void) {
}



/************************************/
/* B 1.5 Program organization units */
/************************************/
/*********************/
/* B 1.5.1 Functions */
/*********************/
void *flow_control_analysis_c::visit(function_declaration_c *symbol) {
	search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
	if (debug) printf("Doing flow control analysis in body of function %s\n", ((token_c *)(symbol->derived_function_name))->value);
	symbol->function_body->accept(*this);
	delete search_varfb_instance_type;
	search_varfb_instance_type = NULL;
	return NULL;
}

/***************************/
/* B 1.5.2 Function blocks */
/***************************/
void *flow_control_analysis_c::visit(function_block_declaration_c *symbol) {
	search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
	if (debug) printf("Doing flow control analysis in body of FB %s\n", ((token_c *)(symbol->fblock_name))->value);
	symbol->fblock_body->accept(*this);
	delete search_varfb_instance_type;
	search_varfb_instance_type = NULL;
	return NULL;
}

/********************/
/* B 1.5.3 Programs */
/********************/
void *flow_control_analysis_c::visit(program_declaration_c *symbol) {
	search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
	if (debug) printf("Doing flow control analysis in body of program %s\n", ((token_c *)(symbol->program_type_name))->value);
	symbol->function_block_body->accept(*this);
	delete search_varfb_instance_type;
	search_varfb_instance_type = NULL;
	return NULL;
}


/********************************/
/* B 1.7 Configuration elements */
/********************************/
void *flow_control_analysis_c::visit(configuration_declaration_c *symbol) {
	return NULL;
}


/****************************************/
/* B.2 - Language IL (Instruction List) */
/****************************************/
/***********************************/
/* B 2.1 Instructions and Operands */
/***********************************/

/*| instruction_list il_instruction */
// SYM_LIST(instruction_list_c)
void *flow_control_analysis_c::visit(instruction_list_c *symbol) {
	for(int i = 0; i < symbol->n; i++) {
		prev_il_instruction = NULL;
		if (i > 0) prev_il_instruction = symbol->elements[i-1];
		symbol->elements[i]->accept(*this);
	}
	return NULL;
}

/* | label ':' [il_incomplete_instruction] eol_list */
// SYM_REF2(il_instruction_c, label, il_instruction)
// void *visit(instruction_list_c *symbol);
void *flow_control_analysis_c::visit(il_instruction_c *symbol) {
	symbol->prev_il_instruction = prev_il_instruction;
	/* TODO: handle labels correctly!
	 *
	 *      Don't forget to handle multiple consecutive lables too!
	 *        label2:
	 *        label3:
	 *        label4:
	 *                LD I
	 */
	/* NOTE: the following recursive call will mess up the value in the
	 *       this->prev_il_instruction variable, so be sure not to use it
	 *       after the return of symbol->il_instruction->accept(*this);
	 */
	/* check if it is an il_expression_c, and if so, handle it correctly */
	if (NULL != symbol->il_instruction)
		symbol->il_instruction->accept(*this);
	return NULL;
}


#if 0
/* | function_name [il_operand_list] */
/* NOTE: The parameters 'called_function_declaration' and 'extensible_param_count' are used to pass data between the stage 3 and stage 4. */
// SYM_REF2(il_function_call_c, function_name, il_operand_list, symbol_c *called_function_declaration; int extensible_param_count;)
void *flow_control_analysis_c::visit(il_function_call_c *symbol) {
	return NULL;
}
#endif

/* | il_expr_operator '(' [il_operand] eol_list [simple_instr_list] ')' */
// SYM_REF3(il_expression_c, il_expr_operator, il_operand, simple_instr_list);
void *flow_control_analysis_c::visit(il_expression_c *symbol) {
	if(NULL == symbol->simple_instr_list) 
		/* nothing to do... */
		return NULL;
  
	prev_il_instruction = symbol->il_operand;
	symbol->simple_instr_list->accept(*this);
	return NULL;
}


#if 0
/*   il_call_operator prev_declared_fb_name
 * | il_call_operator prev_declared_fb_name '(' ')'
 * | il_call_operator prev_declared_fb_name '(' eol_list ')'
 * | il_call_operator prev_declared_fb_name '(' il_operand_list ')'
 * | il_call_operator prev_declared_fb_name '(' eol_list il_param_list ')'
 */
/* NOTE: The parameter 'called_fb_declaration'is used to pass data between stage 3 and stage4 (although currently it is not used in stage 4 */
// SYM_REF4(il_fb_call_c, il_call_operator, fb_name, il_operand_list, il_param_list, symbol_c *called_fb_declaration)
void *flow_control_analysis_c::visit(il_fb_call_c *symbol) {
	return NULL;
}


/* | function_name '(' eol_list [il_param_list] ')' */
/* NOTE: The parameter 'called_function_declaration' is used to pass data between the stage 3 and stage 4. */
// SYM_REF2(il_formal_funct_call_c, function_name, il_param_list, symbol_c *called_function_declaration; int extensible_param_count;)
void *flow_control_analysis_c::visit(il_formal_funct_call_c *symbol) {
	return NULL;
}
#endif


//  void *visit(il_operand_list_c *symbol);
void *flow_control_analysis_c::visit(simple_instr_list_c *symbol) {
	for(int i = 0; i < symbol->n; i++) {
		/* The prev_il_instruction for element[0] was set in visit(il_expression_c *) */
		if (i>0) prev_il_instruction = symbol->elements[i-1];
		symbol->elements[i]->accept(*this);
	}
	return NULL;
}


// SYM_REF1(il_simple_instruction_c, il_simple_instruction, symbol_c *prev_il_instruction;)
void *flow_control_analysis_c::visit(il_simple_instruction_c*symbol) {
	symbol->prev_il_instruction = prev_il_instruction;
	return NULL;
}


/*
    void *visit(il_param_list_c *symbol);
    void *visit(il_param_assignment_c *symbol);
    void *visit(il_param_out_assignment_c *symbol);
 */



