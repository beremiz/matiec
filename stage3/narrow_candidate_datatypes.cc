/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2009-2012  Mario de Sousa (msousa@fe.up.pt)
 *  Copyright (C) 2012       Manuele Conti (manuele.conti@sirius-es.it)
 *  Copyright (C) 2012       Matteo Facchinetti (matteo.facchinetti@sirius-es.it)
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
 *  Narrow class select and store a data type from candidate data types list for all symbols
 */

#include "narrow_candidate_datatypes.hh"
#include "datatype_functions.hh"
#include <typeinfo>
#include <list>
#include <string>
#include <string.h>
#include <strings.h>


/* set to 1 to see debug info during execution */
static int debug = 0;

narrow_candidate_datatypes_c::narrow_candidate_datatypes_c(symbol_c *ignore) {
}

narrow_candidate_datatypes_c::~narrow_candidate_datatypes_c(void) {
}

bool narrow_candidate_datatypes_c::is_widening_compatible(symbol_c *left_type, symbol_c *right_type, symbol_c *result_type, const struct widen_entry widen_table[]) {
	for (int k = 0; NULL != widen_table[k].left;  k++) {
		if        ((typeid(*left_type)   == typeid(*widen_table[k].left))
		        && (typeid(*right_type)  == typeid(*widen_table[k].right))
				&& (typeid(*result_type) == typeid(*widen_table[k].result))) {
			return true;
		}
	}
	return false;
}

void narrow_candidate_datatypes_c::narrow_nonformal_call(symbol_c *f_call, symbol_c *f_decl, int *ext_parm_count) {
	symbol_c *call_param_value,  *param_type;
	identifier_c *param_name;
	function_param_iterator_c       fp_iterator(f_decl);
	function_call_param_iterator_c fcp_iterator(f_call);
	int extensible_parameter_highest_index = -1;
	unsigned int i;

	if (NULL != ext_parm_count) *ext_parm_count = -1;

	/* Iterating through the non-formal parameters of the function call */
	while((call_param_value = fcp_iterator.next_nf()) != NULL) {
		/* Obtaining the type of the value being passed in the function call */
		/* Iterate to the next parameter of the function being called.
		 * Get the name of that parameter, and ignore if EN or ENO.
		 */
		do {
			param_name = fp_iterator.next();
			/* If there is no other parameter declared, then we are passing too many parameters... */
			/* This error should have been caught in fill_candidate_datatypes_c, but may occur here again when we handle FB invocations! 
			 * In this case, we carry on analysing the code in order to be able to provide relevant error messages
			 * for that code too!
			 */
			if(param_name == NULL) break;
		} while ((strcmp(param_name->value, "EN") == 0) || (strcmp(param_name->value, "ENO") == 0));

		/* Set the desired datatype for this parameter, and call it recursively. */
		/* Note that if the call has more parameters than those declared in the function/FB declaration,
		 * we may be setting this to NULL!
		 */
		call_param_value->datatype = base_type(fp_iterator.param_type());
		if ((NULL != param_name) && (NULL == call_param_value->datatype)) ERROR;
		if ((NULL == param_name) && (NULL != call_param_value->datatype)) ERROR;
		call_param_value->accept(*this);

		if (NULL != param_name) 
			if (extensible_parameter_highest_index < fp_iterator.extensible_param_index())
				extensible_parameter_highest_index = fp_iterator.extensible_param_index();
	}
	/* In the case of a call to an extensible function, we store the highest index 
	 * of the extensible parameters this particular call uses, in the symbol_c object
	 * of the function call itself!
	 * In calls to non-extensible functions, this value will be set to -1.
	 * This information is later used in stage4 to correctly generate the
	 * output code.
	 */
	if ((NULL != ext_parm_count) && (extensible_parameter_highest_index >=0) /* if call to extensible function */)
		*ext_parm_count = 1 + extensible_parameter_highest_index - fp_iterator.first_extensible_param_index();
}



void narrow_candidate_datatypes_c::narrow_formal_call(symbol_c *f_call, symbol_c *f_decl, int *ext_parm_count) {
	symbol_c *call_param_value, *call_param_name, *param_type;
	symbol_c *verify_duplicate_param;
	identifier_c *param_name;
	function_param_iterator_c       fp_iterator(f_decl);
	function_call_param_iterator_c fcp_iterator(f_call);
	int extensible_parameter_highest_index = -1;
	identifier_c *extensible_parameter_name;
	unsigned int i;

	if (NULL != ext_parm_count) *ext_parm_count = -1;

	/* Iterating through the formal parameters of the function call */
	while((call_param_name = fcp_iterator.next_f()) != NULL) {

		/* Obtaining the value being passed in the function call */
		call_param_value = fcp_iterator.get_current_value();
		/* the following should never occur. If it does, then we have a bug in our code... */
		if (NULL == call_param_value) ERROR;

		/* Find the corresponding parameter in function declaration */
		param_name = fp_iterator.search(call_param_name);

		/* Set the desired datatype for this parameter, and call it recursively. */
		/* NOTE: When handling a FB call, this narrow_formal_call() may be called to analyse
		 *       an invalid FB call (call with parameters that do not exist on the FB declaration).
		 *       For this reason, the param_name may come out as NULL!
		 */
		call_param_value->datatype = base_type(fp_iterator.param_type());
		if ((NULL != param_name) && (NULL == call_param_value->datatype)) ERROR;
		if ((NULL == param_name) && (NULL != call_param_value->datatype)) ERROR;

		call_param_value->accept(*this);

		if (NULL != param_name) 
			if (extensible_parameter_highest_index < fp_iterator.extensible_param_index())
				extensible_parameter_highest_index = fp_iterator.extensible_param_index();
	}
	/* call is compatible! */

	/* In the case of a call to an extensible function, we store the highest index 
	 * of the extensible parameters this particular call uses, in the symbol_c object
	 * of the function call itself!
	 * In calls to non-extensible functions, this value will be set to -1.
	 * This information is later used in stage4 to correctly generate the
	 * output code.
	 */
	if ((NULL != ext_parm_count) && (extensible_parameter_highest_index >=0) /* if call to extensible function */)
		*ext_parm_count = 1 + extensible_parameter_highest_index - fp_iterator.first_extensible_param_index();
}



/* a helper function... */
symbol_c *narrow_candidate_datatypes_c::base_type(symbol_c *symbol) {
	/* NOTE: symbol == NULL is valid. It will occur when, for e.g., an undefined/undeclared symbolic_variable is used
	 *       in the code.
	 */
	if (symbol == NULL) return NULL;
	return (symbol_c *)symbol->accept(search_base_type);	
}

/*********************/
/* B 1.2 - Constants */
/*********************/

/**********************/
/* B 1.3 - Data types */
/**********************/
/********************************/
/* B 1.3.3 - Derived data types */
/********************************/
/*  signed_integer DOTDOT signed_integer */
// SYM_REF2(subrange_c, lower_limit, upper_limit)
void *narrow_candidate_datatypes_c::visit(subrange_c *symbol) {
	symbol->lower_limit->datatype = symbol->datatype;
	symbol->lower_limit->accept(*this);
	symbol->upper_limit->datatype = symbol->datatype;
	symbol->upper_limit->accept(*this);
	return NULL;
}


/*********************/
/* B 1.4 - Variables */
/*********************/

/********************************************/
/* B 1.4.1 - Directly Represented Variables */
/********************************************/

/*************************************/
/* B 1.4.2 - Multi-element variables */
/*************************************/
/*  subscripted_variable '[' subscript_list ']' */
// SYM_REF2(array_variable_c, subscripted_variable, subscript_list)
void *narrow_candidate_datatypes_c::visit(array_variable_c *symbol) {
	/* we need to check the data types of the expressions used for the subscripts... */
	symbol->subscript_list->accept(*this);
	return NULL;
}


/* subscript_list ',' subscript */
// SYM_LIST(subscript_list_c)
void *narrow_candidate_datatypes_c::visit(subscript_list_c *symbol) {
	for (int i = 0; i < symbol->n; i++) {
		for (unsigned int k = 0; k < symbol->elements[i]->candidate_datatypes.size(); k++) {
			if (is_ANY_INT_type(symbol->elements[i]->candidate_datatypes[k]))
				symbol->elements[i]->datatype = symbol->elements[i]->candidate_datatypes[k];
		}
		symbol->elements[i]->accept(*this);
	}
	return NULL;  
}



/************************************/
/* B 1.5 Program organization units */
/************************************/
/*********************/
/* B 1.5.1 Functions */
/*********************/
void *narrow_candidate_datatypes_c::visit(function_declaration_c *symbol) {
	search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
	if (debug) printf("Narrowing candidate data types list in body of function %s\n", ((token_c *)(symbol->derived_function_name))->value);
	prev_il_instruction = NULL;
	symbol->function_body->accept(*this);
	prev_il_instruction = NULL;
	delete search_varfb_instance_type;
	search_varfb_instance_type = NULL;
	return NULL;
}

/***************************/
/* B 1.5.2 Function blocks */
/***************************/
void *narrow_candidate_datatypes_c::visit(function_block_declaration_c *symbol) {
	search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
	if (debug) printf("Narrowing candidate data types list in body of FB %s\n", ((token_c *)(symbol->fblock_name))->value);
	prev_il_instruction = NULL;
	symbol->fblock_body->accept(*this);
	prev_il_instruction = NULL;
	delete search_varfb_instance_type;
	search_varfb_instance_type = NULL;
	return NULL;
}

/********************/
/* B 1.5.3 Programs */
/********************/
void *narrow_candidate_datatypes_c::visit(program_declaration_c *symbol) {
	search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
	if (debug) printf("Narrowing candidate data types list in body of program %s\n", ((token_c *)(symbol->program_type_name))->value);
	prev_il_instruction = NULL;
	symbol->function_block_body->accept(*this);
	prev_il_instruction = NULL;
	delete search_varfb_instance_type;
	search_varfb_instance_type = NULL;
	return NULL;
}


/********************************/
/* B 1.7 Configuration elements */
/********************************/
void *narrow_candidate_datatypes_c::visit(configuration_declaration_c *symbol) {
#if 0
	// TODO !!!
	/* for the moment we must return NULL so semantic analysis of remaining code is not interrupted! */
#endif
	return NULL;
}


/****************************************/
/* B.2 - Language IL (Instruction List) */
/****************************************/
/***********************************/
/* B 2.1 Instructions and Operands */
/***********************************/
// void *visit(instruction_list_c *symbol);
void *narrow_candidate_datatypes_c::visit(il_simple_operation_c *symbol) {
	il_operand = symbol->il_operand;
	if (NULL != symbol->il_operand) {
		symbol->il_operand->accept(*this);
	}
	/* recursive call to see whether data types are compatible */
	symbol->il_simple_operator->accept(*this);
	il_operand = NULL;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(il_function_call_c *symbol) {
	return NULL;
}

/* MJS: Manuele, could you please not delete the following 2 lines of comments. They help me understand where this class is used
 *     and when it is created by bison - syntax parse, and how it can show up in the abstract syntax tree.
 *
 *       Actually, it could be helpful if we could have all the similar comments already present in visit_expression_type_c
 *       in the 3 new classes fill/narrow/print candidate datatype 
 */
/* | il_expr_operator '(' [il_operand] eol_list [simple_instr_list] ')' */
// SYM_REF3(il_expression_c, il_expr_operator, il_operand, simple_instr_list);
void *narrow_candidate_datatypes_c::visit(il_expression_c *symbol) {
/* MJS: TODO... */
return NULL;
}

void *narrow_candidate_datatypes_c::visit(il_fb_call_c *symbol) {
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(il_formal_funct_call_c *symbol) {
	return NULL;
}


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
void *narrow_candidate_datatypes_c::visit(LD_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(LDN_operator_c *symbol) {
	if (symbol->candidate_datatypes.size() != 1)
		return NULL;
	symbol->datatype = symbol->candidate_datatypes[0];
	il_operand->datatype = symbol->datatype;
	il_operand->accept(*this);
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(ST_operator_c *symbol) {
	if (symbol->candidate_datatypes.size() != 1)
		return NULL;
	symbol->datatype = symbol->candidate_datatypes[0];
	il_operand->datatype = symbol->datatype;
	il_operand->accept(*this);
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(STN_operator_c *symbol) {
	if (symbol->candidate_datatypes.size() != 1)
		return NULL;
	symbol->datatype = symbol->candidate_datatypes[0];
	il_operand->datatype = symbol->datatype;
	il_operand->accept(*this);
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(NOT_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(S_operator_c *symbol) {
	if (symbol->candidate_datatypes.size() != 1)
		return NULL;
	symbol->datatype = symbol->candidate_datatypes[0];
	il_operand->datatype = symbol->datatype;
	il_operand->accept(*this);
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(R_operator_c *symbol) {
	if (symbol->candidate_datatypes.size() != 1)
		return NULL;
	symbol->datatype = symbol->candidate_datatypes[0];
	il_operand->datatype = symbol->datatype;
	il_operand->accept(*this);
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(S1_operator_c *symbol) {
	if (symbol->candidate_datatypes.size() != 1)
		return NULL;
	symbol->datatype = symbol->candidate_datatypes[0];
	il_operand->datatype = symbol->datatype;
	il_operand->accept(*this);
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(R1_operator_c *symbol) {
	if (symbol->candidate_datatypes.size() != 1)
		return NULL;
	symbol->datatype = symbol->candidate_datatypes[0];
	il_operand->datatype = symbol->datatype;
	il_operand->accept(*this);
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(CLK_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(CU_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(CD_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(PV_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(IN_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(PT_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(AND_operator_c *symbol) {
	if (symbol->candidate_datatypes.size() != 1)
		return NULL;
	symbol->datatype = symbol->candidate_datatypes[0];
	il_operand->datatype = symbol->datatype;
	il_operand->accept(*this);
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(OR_operator_c *symbol) {
	if (symbol->candidate_datatypes.size() != 1)
		return NULL;
	symbol->datatype = symbol->candidate_datatypes[0];
	il_operand->datatype = symbol->datatype;
	il_operand->accept(*this);
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(XOR_operator_c *symbol) {
	if (symbol->candidate_datatypes.size() != 1)
		return NULL;
	symbol->datatype = symbol->candidate_datatypes[0];
	il_operand->datatype = symbol->datatype;
	il_operand->accept(*this);
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(ANDN_operator_c *symbol) {
	if (symbol->candidate_datatypes.size() != 1)
		return NULL;
	symbol->datatype = symbol->candidate_datatypes[0];
	il_operand->datatype = symbol->datatype;
	il_operand->accept(*this);
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(ORN_operator_c *symbol) {
	if (symbol->candidate_datatypes.size() != 1)
		return NULL;
	symbol->datatype = symbol->candidate_datatypes[0];
	il_operand->datatype = symbol->datatype;
	il_operand->accept(*this);
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(XORN_operator_c *symbol) {
	if (symbol->candidate_datatypes.size() != 1)
		return NULL;
	symbol->datatype = symbol->candidate_datatypes[0];
	il_operand->datatype = symbol->datatype;
	il_operand->accept(*this);
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(ADD_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(SUB_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(MUL_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(DIV_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(MOD_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(GT_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(GE_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(EQ_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(LT_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(LE_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(NE_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(CAL_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(CALC_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(CALCN_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(RET_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(RETC_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(RETCN_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(JMP_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(JMPC_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(JMPCN_operator_c *symbol) {
	prev_il_instruction = symbol;
	return NULL;
}

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

void *narrow_candidate_datatypes_c::visit(or_expression_c *symbol) {
	symbol_c * selected_type = NULL;
	for(unsigned int i = 0; i < symbol->l_exp->candidate_datatypes.size(); i++) {
		for(unsigned int j = 0; j < symbol->r_exp->candidate_datatypes.size(); j++) {
			if (is_type_equal(symbol->l_exp->candidate_datatypes[i], symbol->r_exp->candidate_datatypes[j])) {
				selected_type = symbol->l_exp->candidate_datatypes[i];
				break;
			}
		}
	}

	if (NULL != selected_type) {
		symbol->l_exp->datatype = selected_type;
		symbol->l_exp->accept(*this);
		symbol->r_exp->datatype = selected_type;
		symbol->r_exp->accept(*this);
	}
	else
		ERROR;
	return NULL;
}


void *narrow_candidate_datatypes_c::visit(xor_expression_c *symbol) {
	symbol_c * selected_type = NULL;
	for(unsigned int i = 0; i < symbol->l_exp->candidate_datatypes.size(); i++) {
		for(unsigned int j = 0; j < symbol->r_exp->candidate_datatypes.size(); j++) {
			if (is_type_equal(symbol->l_exp->candidate_datatypes[i], symbol->r_exp->candidate_datatypes[j])) {
				selected_type = symbol->l_exp->candidate_datatypes[i];
				break;
			}
		}
	}

	if (NULL != selected_type) {
		symbol->l_exp->datatype = selected_type;
		symbol->l_exp->accept(*this);
		symbol->r_exp->datatype = selected_type;
		symbol->r_exp->accept(*this);
	}
	else
		ERROR;
	return NULL;
}


void *narrow_candidate_datatypes_c::visit(and_expression_c *symbol) {
	symbol_c * selected_type = NULL;
	for(unsigned int i = 0; i < symbol->l_exp->candidate_datatypes.size(); i++) {
		for(unsigned int j = 0; j < symbol->r_exp->candidate_datatypes.size(); j++) {
			if (typeid(*symbol->l_exp->candidate_datatypes[i]) == typeid(*symbol->r_exp->candidate_datatypes[j])) {
				selected_type = symbol->l_exp->candidate_datatypes[i];
				break;
			}
		}
	}

	if (NULL != selected_type) {
		symbol->l_exp->datatype = selected_type;
		symbol->l_exp->accept(*this);
		symbol->r_exp->datatype = selected_type;
		symbol->r_exp->accept(*this);
	}
	else
		ERROR;
	return NULL;
}


void *narrow_candidate_datatypes_c::visit(equ_expression_c *symbol) {
	/* Here symbol->datatype has already assigned to BOOL
	 * In conditional symbols like =, <>, =<, <, >, >= we have to set
	 * l_exp and r_exp expression matched with compatible type.
	 * Example:
	 * 		INT#14 = INT#81
	 * 		equ_expression_c symbol->datatype = BOOL from top visit
	 * 		symbol->l_exp->datatype => INT
	 * 		symbol->r_exp->datatype => INT
	 */
	symbol_c * selected_type = NULL;
	for(unsigned int i = 0; i < symbol->l_exp->candidate_datatypes.size(); i++) {
		for(unsigned int j = 0; j < symbol->r_exp->candidate_datatypes.size(); j++) {
			if (typeid(*symbol->l_exp->candidate_datatypes[i]) == typeid(*symbol->r_exp->candidate_datatypes[j])) {
				/*
				 * We do not need to check whether the type is an ANY_ELEMENTARY here.
				 * That was already done in fill_candidate_datatypes_c.
				 */
				selected_type = symbol->l_exp->candidate_datatypes[i];
				break;
			}
		}
	}

	if (NULL != selected_type) {
		symbol->l_exp->datatype = selected_type;
		symbol->l_exp->accept(*this);
		symbol->r_exp->datatype = selected_type;
		symbol->r_exp->accept(*this);
	}
	else
		ERROR;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(notequ_expression_c *symbol)  {
	symbol_c * selected_type = NULL;
	for(unsigned int i = 0; i < symbol->l_exp->candidate_datatypes.size(); i++) {
		for(unsigned int j = 0; j < symbol->r_exp->candidate_datatypes.size(); j++) {
			if (typeid(*symbol->l_exp->candidate_datatypes[i]) == typeid(*symbol->r_exp->candidate_datatypes[j])) {
				selected_type = symbol->l_exp->candidate_datatypes[i];
				break;
			}
		}
	}

	if (NULL != selected_type) {
		symbol->l_exp->datatype = selected_type;
		symbol->l_exp->accept(*this);
		symbol->r_exp->datatype = selected_type;
		symbol->r_exp->accept(*this);
	}
	else
		ERROR;
	return NULL;
}


void *narrow_candidate_datatypes_c::visit(lt_expression_c *symbol) {
	symbol_c * selected_type = NULL;
	for(unsigned int i = 0; i < symbol->l_exp->candidate_datatypes.size(); i++) {
		for(unsigned int j = 0; j < symbol->r_exp->candidate_datatypes.size(); j++) {
			if (typeid(*symbol->l_exp->candidate_datatypes[i]) == typeid(*symbol->r_exp->candidate_datatypes[j])
					&& is_ANY_ELEMENTARY_type(symbol->l_exp->candidate_datatypes[i])) {
				selected_type = symbol->l_exp->candidate_datatypes[i];
				break;
			}
		}
	}

	if (NULL != selected_type) {
		symbol->l_exp->datatype = selected_type;
		symbol->l_exp->accept(*this);
		symbol->r_exp->datatype = selected_type;
		symbol->r_exp->accept(*this);
	}
	else
		ERROR;
	return NULL;
}


void *narrow_candidate_datatypes_c::visit(gt_expression_c *symbol) {
	symbol_c * selected_type = NULL;
	for(unsigned int i = 0; i < symbol->l_exp->candidate_datatypes.size(); i++) {
		for(unsigned int j = 0; j < symbol->r_exp->candidate_datatypes.size(); j++) {
			if (typeid(*symbol->l_exp->candidate_datatypes[i]) == typeid(*symbol->r_exp->candidate_datatypes[j])
					&& is_ANY_ELEMENTARY_type(symbol->l_exp->candidate_datatypes[i])) {
				selected_type = symbol->l_exp->candidate_datatypes[i];
				break;
			}
		}
	}

	if (NULL != selected_type) {
		symbol->l_exp->datatype = selected_type;
		symbol->l_exp->accept(*this);
		symbol->r_exp->datatype = selected_type;
		symbol->r_exp->accept(*this);
	}
	else
		ERROR;
	return NULL;
}


void *narrow_candidate_datatypes_c::visit(le_expression_c *symbol) {
	symbol_c * selected_type = NULL;
	for(unsigned int i = 0; i < symbol->l_exp->candidate_datatypes.size(); i++) {
		for(unsigned int j = 0; j < symbol->r_exp->candidate_datatypes.size(); j++) {
			if (typeid(*symbol->l_exp->candidate_datatypes[i]) == typeid(*symbol->r_exp->candidate_datatypes[j])
					&& is_ANY_ELEMENTARY_type(symbol->l_exp->candidate_datatypes[i])) {
				selected_type = symbol->l_exp->candidate_datatypes[i];
				break;
			}
		}
	}

	if (NULL != selected_type) {
		symbol->l_exp->datatype = selected_type;
		symbol->l_exp->accept(*this);
		symbol->r_exp->datatype = selected_type;
		symbol->r_exp->accept(*this);
	}
	else
		ERROR;
	return NULL;
}


void *narrow_candidate_datatypes_c::visit(ge_expression_c *symbol) {
	symbol_c * selected_type = NULL;
	for(unsigned int i = 0; i < symbol->l_exp->candidate_datatypes.size(); i++) {
		for(unsigned int j = 0; j < symbol->r_exp->candidate_datatypes.size(); j++) {
			if (typeid(*symbol->l_exp->candidate_datatypes[i]) == typeid(*symbol->r_exp->candidate_datatypes[j])
					&& is_ANY_ELEMENTARY_type(symbol->l_exp->candidate_datatypes[i])) {
				selected_type = symbol->l_exp->candidate_datatypes[i];
				break;
			}
		}
	}

	if (NULL != selected_type) {
		symbol->l_exp->datatype = selected_type;
		symbol->l_exp->accept(*this);
		symbol->r_exp->datatype = selected_type;
		symbol->r_exp->accept(*this);
	}
	else
		ERROR;
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(add_expression_c *symbol) {
	int count = 0;

	if (is_ANY_NUM_compatible(symbol->datatype)) {
		symbol->l_exp->datatype = symbol->datatype;
		symbol->r_exp->datatype = symbol->datatype;
		count++;
	} else {
		/* TIME data type */
		for(unsigned int i = 0; i < symbol->l_exp->candidate_datatypes.size(); i++) {
			for(unsigned int j = 0; j < symbol->r_exp->candidate_datatypes.size(); j++) {
				/* test widening compatibility */
				if (is_widening_compatible(symbol->l_exp->candidate_datatypes[i],
						symbol->r_exp->candidate_datatypes[j],
						symbol->datatype, widen_ADD_table)) {
					symbol->l_exp->datatype = symbol->l_exp->candidate_datatypes[i];
					symbol->r_exp->datatype = symbol->r_exp->candidate_datatypes[j];
					count ++;
				}
			}
		}
	}
	if (count > 1)
		ERROR;
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	return NULL;
}



void *narrow_candidate_datatypes_c::visit(sub_expression_c *symbol) {
	int count = 0;

	if (is_ANY_NUM_compatible(symbol->datatype)) {
		symbol->l_exp->datatype = symbol->datatype;
		symbol->r_exp->datatype = symbol->datatype;
		count++;
	} else {
		/* TIME data type */
		for(unsigned int i = 0; i < symbol->l_exp->candidate_datatypes.size(); i++) {
			for(unsigned int j = 0; j < symbol->r_exp->candidate_datatypes.size(); j++) {
				/* test widening compatibility */
				if (is_widening_compatible(symbol->l_exp->candidate_datatypes[i],
						symbol->r_exp->candidate_datatypes[j],
						symbol->datatype, widen_SUB_table)) {
					symbol->l_exp->datatype = symbol->l_exp->candidate_datatypes[i];
					symbol->r_exp->datatype = symbol->r_exp->candidate_datatypes[j];
					count ++;
				}
			}
		}
	}
	if (count > 1)
		ERROR;
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(mul_expression_c *symbol) {
	int count = 0;

	if (is_ANY_NUM_compatible(symbol->datatype)) {
		symbol->l_exp->datatype = symbol->datatype;
		symbol->r_exp->datatype = symbol->datatype;
		count++;
	} else {
		/* TIME data type */
		for(unsigned int i = 0; i < symbol->l_exp->candidate_datatypes.size(); i++) {
			for(unsigned int j = 0; j < symbol->r_exp->candidate_datatypes.size(); j++) {
				/* test widening compatibility */
				if (is_widening_compatible(symbol->l_exp->candidate_datatypes[i],
						symbol->r_exp->candidate_datatypes[j],
						symbol->datatype, widen_MUL_table)) {
					symbol->l_exp->datatype = symbol->l_exp->candidate_datatypes[i];
					symbol->r_exp->datatype = symbol->r_exp->candidate_datatypes[j];
					count ++;
				}
			}
		}
	}
	if (count > 1)
		ERROR;
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(div_expression_c *symbol) {
	int count = 0;

	if (is_ANY_NUM_compatible(symbol->datatype)) {
		symbol->l_exp->datatype = symbol->datatype;
		symbol->r_exp->datatype = symbol->datatype;
		count++;
	} else {
		/* TIME data type */
		for(unsigned int i = 0; i < symbol->l_exp->candidate_datatypes.size(); i++) {
			for(unsigned int j = 0; j < symbol->r_exp->candidate_datatypes.size(); j++) {
				/* test widening compatibility */
				if (is_widening_compatible(symbol->l_exp->candidate_datatypes[i],
						symbol->r_exp->candidate_datatypes[j],
						symbol->datatype, widen_DIV_table)) {
					symbol->l_exp->datatype = symbol->l_exp->candidate_datatypes[i];
					symbol->r_exp->datatype = symbol->r_exp->candidate_datatypes[j];
					count ++;
				}
			}
		}
	}
	if (count > 1)
		ERROR;
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	return NULL;
}


void *narrow_candidate_datatypes_c::visit(mod_expression_c *symbol) {
	symbol->l_exp->datatype = symbol->datatype;
	symbol->l_exp->accept(*this);
	symbol->r_exp->datatype = symbol->datatype;
	symbol->r_exp->accept(*this);
	return NULL;
}


void *narrow_candidate_datatypes_c::visit(power_expression_c *symbol) {
	symbol->l_exp->datatype = symbol->datatype;
	symbol->l_exp->accept(*this);
	if (! symbol->r_exp->candidate_datatypes.size()){
		symbol->r_exp->datatype = symbol->r_exp->candidate_datatypes[0];
		symbol->r_exp->accept(*this);
	}
	return NULL;
}


void *narrow_candidate_datatypes_c::visit(neg_expression_c *symbol) {
	symbol->exp->datatype = symbol->datatype;
	symbol->exp->accept(*this);
	return NULL;
}


void *narrow_candidate_datatypes_c::visit(not_expression_c *symbol) {
	symbol->exp->datatype = symbol->datatype;
	symbol->exp->accept(*this);
	return NULL;
}


void *narrow_candidate_datatypes_c::visit(function_invocation_c *symbol) {
	int  ext_parm_count;

	/* set the called_function_declaration. */
	symbol->called_function_declaration = NULL;
	if (symbol->candidate_datatypes.size() == 1) {
		/* If only one possible called function, then that is the function to call!
		 * In this case we ignore the symbol->datatype value (that may even be NULL).
		 * This helps in identifying potential errors in the expressions used inside this function call
		 * even if there is a previous error, allowing us to make a more thorough analysis of the semantics
		 * of the ST code, and providing as many relevant error messages as possible!
		 * If symbol->datatype isn't NULL, then this chosen function should be returning the required datatype,
		 * otherwise we have a bug in our stage3 code!
		 */
		symbol->called_function_declaration = symbol->candidate_functions[0];
		if ((NULL != symbol->datatype) && (!is_type_equal(symbol->candidate_datatypes[0], symbol->datatype)))
			ERROR;
	}
	else {
		/* set the called_function_declaration taking into account the datatype that we need to return */
		symbol->called_function_declaration = NULL;
		for(unsigned int i = 0; i < symbol->candidate_datatypes.size(); i++) {
			if (is_type_equal(symbol->candidate_datatypes[i], symbol->datatype)) {
				symbol->called_function_declaration = symbol->candidate_functions[i];
				break;
			}
		}
	}
	/* NOTE: If we can't figure out the declaration of the function being called, this is not 
	 *       necessarily an internal compiler error. It could be because the symbol->datatype is NULL
	 *       (because the ST code being analysed has an error _before_ this function invocation).
	 *       However, we don't just give, up, we carry on recursivly analysing the code, so as to be
	 *       able to print out any error messages related to underlying code that could be partially correct.
	 */
	/* if (NULL == symbol->called_function_declaration) ERROR; */
	
	if (NULL != symbol->nonformal_param_list)  narrow_nonformal_call(symbol, symbol->called_function_declaration, &ext_parm_count);
	if (NULL != symbol->   formal_param_list)     narrow_formal_call(symbol, symbol->called_function_declaration, &ext_parm_count);
	symbol->extensible_param_count = ext_parm_count;

	return NULL;
}

/********************/
/* B 3.2 Statements */
/********************/


/*********************************/
/* B 3.2.1 Assignment Statements */
/*********************************/

void *narrow_candidate_datatypes_c::visit(assignment_statement_c *symbol) {
	if (symbol->candidate_datatypes.size() != 1)
		return NULL;
	symbol->datatype = symbol->candidate_datatypes[0];
	symbol->l_exp->datatype = symbol->datatype;
	symbol->l_exp->accept(*this);
	symbol->r_exp->datatype = symbol->datatype;
	symbol->r_exp->accept(*this);
	return NULL;
}


/*****************************************/
/* B 3.2.2 Subprogram Control Statements */
/*****************************************/

void *narrow_candidate_datatypes_c::visit(fb_invocation_c *symbol) {
	/* Note: We do not use the symbol->called_fb_declaration value (set in fill_candidate_datatypes_c)
	 *       because we try to identify any other datatype errors in the expressions used in the 
	 *       parameters to the FB call (e.g.  fb_var(var1 * 56 + func(var * 43)) )
	 *       even it the call to the FB is invalid. 
	 *       This makes sense because it may be errors in those expressions which are
	 *       making this an invalid call, so it makes sense to point them out to the user!
	 */
	symbol_c *fb_decl = search_varfb_instance_type->get_basetype_decl(symbol->fb_name);

	/* Although a call to a non-declared FB is a semantic error, this is currently caught by stage 2! */
	if (NULL == fb_decl) ERROR;
	if (NULL != symbol->nonformal_param_list)  narrow_nonformal_call(symbol, fb_decl);
	if (NULL != symbol->   formal_param_list)     narrow_formal_call(symbol, fb_decl);

	return NULL;
}


/********************************/
/* B 3.2.3 Selection Statements */
/********************************/

void *narrow_candidate_datatypes_c::visit(if_statement_c *symbol) {
	for(unsigned int i = 0; i < symbol->expression->candidate_datatypes.size(); i++) {
		if (is_type(symbol->expression->candidate_datatypes[i], bool_type_name_c))
			symbol->expression->datatype = symbol->expression->candidate_datatypes[i];
	}
	symbol->expression->accept(*this);
	if (NULL != symbol->statement_list)
		symbol->statement_list->accept(*this);
	if (NULL != symbol->elseif_statement_list)
		symbol->elseif_statement_list->accept(*this);
	if (NULL != symbol->else_statement_list)
		symbol->else_statement_list->accept(*this);
	return NULL;
}


void *narrow_candidate_datatypes_c::visit(elseif_statement_c *symbol) {
	for (unsigned int i = 0; i < symbol->expression->candidate_datatypes.size(); i++) {
		if (is_type(symbol->expression->candidate_datatypes[i], bool_type_name_c))
			symbol->expression->datatype = symbol->expression->candidate_datatypes[i];
	}
	symbol->expression->accept(*this);
	if (NULL != symbol->statement_list)
		symbol->statement_list->accept(*this);
	return NULL;
}

/* CASE expression OF case_element_list ELSE statement_list END_CASE */
// SYM_REF3(case_statement_c, expression, case_element_list, statement_list)
void *narrow_candidate_datatypes_c::visit(case_statement_c *symbol) {
	for (unsigned int i = 0; i < symbol->expression->candidate_datatypes.size(); i++) {
		if ((is_ANY_INT_type(symbol->expression->candidate_datatypes[i]))
				 || (search_base_type.type_is_enumerated(symbol->expression->candidate_datatypes[i])))
			symbol->expression->datatype = symbol->expression->candidate_datatypes[i];
	}
	symbol->expression->accept(*this);
	if (NULL != symbol->statement_list)
		symbol->statement_list->accept(*this);
	if (NULL != symbol->case_element_list) {
		symbol->case_element_list->datatype = symbol->expression->datatype;
		symbol->case_element_list->accept(*this);
	}
	return NULL;
}

/* helper symbol for case_statement */
// SYM_LIST(case_element_list_c)
void *narrow_candidate_datatypes_c::visit(case_element_list_c *symbol) {
	for (int i = 0; i < symbol->n; i++) {
		symbol->elements[i]->datatype = symbol->datatype;
		symbol->elements[i]->accept(*this);
	}
	return NULL;
}

/*  case_list ':' statement_list */
// SYM_REF2(case_element_c, case_list, statement_list)
void *narrow_candidate_datatypes_c::visit(case_element_c *symbol) {
	symbol->case_list->datatype = symbol->datatype;
	symbol->case_list->accept(*this);
	symbol->statement_list->accept(*this);
	return NULL;
}

// SYM_LIST(case_list_c)
void *narrow_candidate_datatypes_c::visit(case_list_c *symbol) {
	for (int i = 0; i < symbol->n; i++) {
		for (unsigned int k = 0; k < symbol->elements[i]->candidate_datatypes.size(); k++) {
			if (is_type_equal(symbol->datatype, symbol->elements[i]->candidate_datatypes[k]))
				symbol->elements[i]->datatype = symbol->elements[i]->candidate_datatypes[k];
		}
		/* NOTE: this may be an integer, a subrange_c, or a enumerated value! */
		symbol->elements[i]->accept(*this);
	}
	return NULL;
}


/********************************/
/* B 3.2.4 Iteration Statements */
/********************************/
void *narrow_candidate_datatypes_c::visit(for_statement_c *symbol) {
	/* Control variable */
	for(unsigned int i = 0; i < symbol->control_variable->candidate_datatypes.size(); i++) {
		if (is_ANY_INT_type(symbol->control_variable->candidate_datatypes[i])) {
			symbol->control_variable->datatype = symbol->control_variable->candidate_datatypes[i];
		}
	}
	symbol->control_variable->accept(*this);
	/* BEG expression */
	for(unsigned int i = 0; i < symbol->beg_expression->candidate_datatypes.size(); i++) {
		if (is_type_equal(symbol->control_variable->datatype,symbol->beg_expression->candidate_datatypes[i]) &&
				is_ANY_INT_type(symbol->beg_expression->candidate_datatypes[i])) {
			symbol->beg_expression->datatype = symbol->beg_expression->candidate_datatypes[i];
		}
	}
	symbol->beg_expression->accept(*this);
	/* END expression */
	for(unsigned int i = 0; i < symbol->end_expression->candidate_datatypes.size(); i++) {
		if (is_type_equal(symbol->control_variable->datatype,symbol->end_expression->candidate_datatypes[i]) &&
				is_ANY_INT_type(symbol->end_expression->candidate_datatypes[i])) {
			symbol->end_expression->datatype = symbol->end_expression->candidate_datatypes[i];
		}
	}
	symbol->end_expression->accept(*this);
	/* BY expression */
	if (NULL != symbol->by_expression) {
		for(unsigned int i = 0; i < symbol->by_expression->candidate_datatypes.size(); i++) {
			if (is_type_equal(symbol->control_variable->datatype,symbol->by_expression->candidate_datatypes[i]) &&
					is_ANY_INT_type(symbol->by_expression->candidate_datatypes[i])) {
				symbol->by_expression->datatype = symbol->by_expression->candidate_datatypes[i];
			}
		}
		symbol->by_expression->accept(*this);
	}
	if (NULL != symbol->statement_list)
		symbol->statement_list->accept(*this);
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(while_statement_c *symbol) {
	for (unsigned int i = 0; i < symbol->expression->candidate_datatypes.size(); i++) {
		if(is_BOOL_type(symbol->expression->candidate_datatypes[i]))
			symbol->expression->datatype = symbol->expression->candidate_datatypes[i];
	}
	symbol->expression->accept(*this);
	if (NULL != symbol->statement_list)
		symbol->statement_list->accept(*this);
	return NULL;
}

void *narrow_candidate_datatypes_c::visit(repeat_statement_c *symbol) {
	for (unsigned int i = 0; i < symbol->expression->candidate_datatypes.size(); i++) {
		if(is_BOOL_type(symbol->expression->candidate_datatypes[i]))
			symbol->expression->datatype = symbol->expression->candidate_datatypes[i];
	}
	symbol->expression->accept(*this);
	if (NULL != symbol->statement_list)
		symbol->statement_list->accept(*this);
	return NULL;
}





