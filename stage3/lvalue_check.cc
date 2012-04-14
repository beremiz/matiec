/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2009-2012  Mario de Sousa (msousa@fe.up.pt)
 *  Copyright (C) 2012       Manuele Conti  (conti.ma@alice.it)
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


#include "lvalue_check.hh"

#define FIRST_(symbol1, symbol2) (((symbol1)->first_order < (symbol2)->first_order)   ? (symbol1) : (symbol2))
#define  LAST_(symbol1, symbol2) (((symbol1)->last_order  > (symbol2)->last_order)    ? (symbol1) : (symbol2))

#define STAGE3_ERROR(error_level, symbol1, symbol2, ...) {                                                                  \
  if (current_display_error_level >= error_level) {                                                                         \
    fprintf(stderr, "%s:%d-%d..%d-%d: error: ",                                                                             \
            FIRST_(symbol1,symbol2)->first_file, FIRST_(symbol1,symbol2)->first_line, FIRST_(symbol1,symbol2)->first_column,\
                                                 LAST_(symbol1,symbol2) ->last_line,  LAST_(symbol1,symbol2) ->last_column);\
    fprintf(stderr, __VA_ARGS__);                                                                                           \
    fprintf(stderr, "\n");                                                                                                  \
    error_found = true;                                                                                                     \
  }                                                                                                                         \
}


#define STAGE3_WARNING(symbol1, symbol2, ...) {                                                                             \
    fprintf(stderr, "%s:%d-%d..%d-%d: warning: ",                                                                           \
            FIRST_(symbol1,symbol2)->first_file, FIRST_(symbol1,symbol2)->first_line, FIRST_(symbol1,symbol2)->first_column,\
                                                 LAST_(symbol1,symbol2) ->last_line,  LAST_(symbol1,symbol2) ->last_column);\
    fprintf(stderr, __VA_ARGS__);                                                                                           \
    fprintf(stderr, "\n");                                                                                                  \
    warning_found = true;                                                                                                   \
}


lvalue_check_c::lvalue_check_c(symbol_c *ignore) {
	error_found = false;
}

lvalue_check_c::~lvalue_check_c(void) {
}

int lvalue_check_c::get_error_found() {
	return error_found;
}

/* No writing to iterator variables (used in FOR loops) inside the loop itself */
void lvalue_check_c::check_for_controlvar_assignment(symbolic_variable_c * lvalue) {
	for (unsigned int i = 0; i < control_variables.size(); i++) {
		symbolic_variable_c *cvar = (symbolic_variable_c *)control_variables[i];
		if (strcasecmp(((identifier_c *)lvalue->var_name)->value, ((identifier_c *)cvar->var_name)->value) == 0) {
			STAGE3_ERROR(0, lvalue, lvalue, "Assignment to FOR control variable are not be allowed.");
			break;
		}
	}
}

/* fb_instance.var := ...  is not valid if var is output (not input ??) variable */
void lvalue_check_c::check_output_assignment(symbolic_variable_c * lvalue) {
	symbol_c *type_id = search_varfb_instance_type->get_basetype_id(lvalue->var_name);
	if (NULL != type_id) {
		function_block_declaration_c *fb_decl = function_block_type_symtable.find_value(type_id);
		if (function_block_type_symtable.end_value() != fb_decl) {
			search_var_instance_decl_c   search_var_instance_decl(fb_decl);
			structured_variable_c * str_var = (structured_variable_c *)lvalue;
			unsigned int vartype = search_var_instance_decl.get_vartype(str_var->field_selector);
			if (vartype == search_var_instance_decl_c::output_vt)
				STAGE3_ERROR(0, lvalue, lvalue, "Assignment to FB output field variable are not be allowed.");
		}
	}
}

/*  No writing to CONSTANTs */
void lvalue_check_c::check_constant_assignment(symbolic_variable_c *lvalue) {
	unsigned int option = search_var_instance_decl->get_option(lvalue->var_name);
	if (option == search_var_instance_decl_c::constant_opt) {
		STAGE3_ERROR(0, lvalue, lvalue, "Assignment to CONSTANT variables are not be allowed.");
	}
}

/* function_name(45)  will check whether the first parameter of the function is not an output variable. */
/* function_name(var_name)  will check whether var_name is lvalue if the first parameter of the function is an output variable. */
void lvalue_check_c::check_function_call_parameter(function_invocation_c *f_call) {
	function_declaration_c *f_decl;
	identifier_c *param_name;
	symbol_c *call_param_value;

	if (NULL == f_call)
		return;
	/* We use called_function_declaration and for this reason LVALUE
	 * check must be run after DATA TYPE check
	 */
	if (NULL == f_call->called_function_declaration)
		ERROR;
	f_decl = (function_declaration_c *)f_call->called_function_declaration;
	search_constant_type_c search_constant_type;
	function_call_param_iterator_c fcp_iterator(f_call);
	function_param_iterator_c       fp_iterator(f_decl);
	do {
		param_name = fp_iterator.next();
		if(param_name == NULL) return;
	} while ((strcmp(param_name->value, "EN")  == 0) || (strcmp(param_name->value, "ENO") == 0));
	while((call_param_value = fcp_iterator.next_nf()) != NULL) {
		if (search_constant_type.is_constant_value(call_param_value)) {
			if (function_param_iterator_c::direction_out == fp_iterator.param_direction())
				STAGE3_ERROR(0, call_param_value, call_param_value, "Assignment Constant value to Output parameter are not be allowed.");
		}
		param_name = fp_iterator.next();
	}
}



/**************************************/
/* B 1.5 - Program organisation units */
/**************************************/
/***********************/
/* B 1.5.1 - Functions */
/***********************/
void *lvalue_check_c::visit(function_declaration_c *symbol) {
	search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
	search_var_instance_decl = new search_var_instance_decl_c(symbol);
	symbol->function_body->accept(*this);
	delete search_varfb_instance_type;
	delete search_var_instance_decl;
	search_varfb_instance_type = NULL;
	search_var_instance_decl = NULL;
	return NULL;
}

/*****************************/
/* B 1.5.2 - Function blocks */
/*****************************/
void *lvalue_check_c::visit(function_block_declaration_c *symbol) {
	search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
	search_var_instance_decl = new search_var_instance_decl_c(symbol);
	symbol->fblock_body->accept(*this);
	delete search_varfb_instance_type;
	delete search_var_instance_decl;
	search_varfb_instance_type = NULL;
	search_var_instance_decl = NULL;
	return NULL;
}

/**********************/
/* B 1.5.3 - Programs */
/**********************/
void *lvalue_check_c::visit(program_declaration_c *symbol) {
	search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
	search_var_instance_decl = new search_var_instance_decl_c(symbol);
	symbol->function_block_body->accept(*this);
	delete search_varfb_instance_type;
	delete search_var_instance_decl;
	search_varfb_instance_type = NULL;
	search_var_instance_decl = NULL;
	return NULL;
}

/***************************************/
/* B.3 - Language ST (Structured Text) */
/***************************************/
/***********************/
/* B 3.1 - Expressions */
/***********************/
void *lvalue_check_c::visit(function_invocation_c *symbol) {
	check_function_call_parameter(symbol);
	return NULL;
}

/*********************************/
/* B 3.2.1 Assignment Statements */
/*********************************/
void *lvalue_check_c::visit(assignment_statement_c *symbol) {
	symbolic_variable_c *lvalue;

	lvalue = (symbolic_variable_c *)symbol->l_exp;
	check_for_controlvar_assignment(lvalue);
	check_output_assignment(lvalue);
	check_constant_assignment(lvalue);
	/* We call visit r_exp to check function_call */
	symbol->r_exp->accept(*this);
	return NULL;
}

/********************************/
/* B 3.2.4 Iteration Statements */
/********************************/
void *lvalue_check_c::visit(for_statement_c *symbol) {
	control_variables.push_back(symbol->control_variable);
	symbol->statement_list->accept(*this);
	control_variables.pop_back();
	return NULL;
}







