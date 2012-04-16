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
    error_count++;                                                                                                     \
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
	error_count = 0;
}

lvalue_check_c::~lvalue_check_c(void) {
}

int lvalue_check_c::get_error_count() {
	return error_count;
}


#include <strings.h>
/* No writing to iterator variables (used in FOR loops) inside the loop itself */
void lvalue_check_c::check_assignment_to_controlvar(symbol_c *lvalue) {
	for (unsigned int i = 0; i < control_variables.size(); i++) {
		symbolic_variable_c *cvar = (symbolic_variable_c *)control_variables[i];
		if (strcasecmp(((identifier_c *)((symbolic_variable_c *)lvalue)->var_name)->value, ((identifier_c *)((symbolic_variable_c *)cvar)->var_name)->value) == 0) {
			STAGE3_ERROR(0, lvalue, lvalue, "Assignment to FOR control variable are not be allowed.");
			break;
		}
	}
}


/* fb_instance.var := ...  is not valid if var is output variable */
/* NOTE, if a fb_instance1.fb_instance2.fb_instance3.var is used, we must iteratively check that none of the 
 *       FB records are declared as OUTPUT variables!!  
 *       This is the reason why we have the while() loop in this function!
 */
void lvalue_check_c::check_assignment_to_output(symbol_c *lvalue) {
	decompose_var_instance_name_c decompose_lvalue(lvalue);
	search_base_type_c            search_base_type;

	symbol_c *struct_elem = decompose_lvalue.next_part();
	symbol_c *type_decl   = search_var_instance_decl->get_decl(struct_elem);
	// symbol_c *type_id  = spec_init_sperator_c::get_spec(type_decl); /* this is not required! search_base_type_c can handle spec_init symbols! */
	symbol_c *basetype_id = search_base_type.get_basetype_id(/*type_id*/ type_decl);
	/* If we can not determine the data type of the element, then the code must have a data type semantic error.
	 * This will have been caught by the data type semantic verifier, so we do not bother with this anymore!
	 */
	if (NULL == basetype_id) return;

	/* Determine if the record/structure element is of a FB type. */
	/* NOTE: If the structure element is not a FB type, then we can quit this check.
	 *       Remember that the standard does not allow a STRUCT data type to have elements that are FB instances!
	 *       Similarly, arrays of FB instances is also not allowed.
	 *       So, as soon as we find one record/structure element that is not a FB, no other record/structure element
	 *       will be of FB type, which means we can quit this check!
	 */
	function_block_declaration_c *fb_decl = function_block_type_symtable.find_value(basetype_id);
	if (function_block_type_symtable.end_value() == fb_decl) return;

	while (NULL != (struct_elem = decompose_lvalue.next_part())) {
		search_var_instance_decl_c   fb_search_var_instance_decl(fb_decl);
		if (search_var_instance_decl_c::output_vt == fb_search_var_instance_decl.get_vartype(struct_elem)) {
			STAGE3_ERROR(0, struct_elem, struct_elem, "Assignment to FB output variable is not allowed.");
			return; /* no need to carry on checking once the first error is found! */
		}

		/* prepare for any possible further record/structure elements */
		type_decl   = fb_search_var_instance_decl.get_decl(struct_elem);
		basetype_id = search_base_type.get_basetype_id(type_decl);
		if (NULL == basetype_id) return; /* same comment as above... */
		fb_decl = function_block_type_symtable.find_value(basetype_id);
		if (function_block_type_symtable.end_value() == fb_decl) return; /* same comment as above... */
	}
}


/*  No writing to CONSTANTs */
void lvalue_check_c::check_assignment_to_constant(symbol_c *lvalue) {
	unsigned int option = search_var_instance_decl->get_option(lvalue);
	if (option == search_var_instance_decl_c::constant_opt) {
		STAGE3_ERROR(0, lvalue, lvalue, "Assignment to CONSTANT variables is not be allowed.");
	}
}


/*  No assigning values to expressions. */
void lvalue_check_c::check_assignment_to_expression(symbol_c *lvalue) {
	/* TODO: check whether the lvalue is an expresion! */
	/* This may occur in function invocations, when passing values (possibly an expression) to one 
	 * of the function's OUTPUT or IN_OUT parameters.
	 */
}



void lvalue_check_c::verify_is_lvalue(symbol_c *lvalue) {
	check_assignment_to_expression(lvalue);
	check_assignment_to_controlvar(lvalue);
	check_assignment_to_output(lvalue);
	check_assignment_to_constant(lvalue);
}




/* check whether all values passed to OUT or IN_OUT parameters are legal lvalues. */
void lvalue_check_c::check_nonformal_call(symbol_c *f_call, symbol_c *f_decl) {
  /* TODO */
}

  
/* check whether all values passed to OUT or IN_OUT parameters are legal lvalues. */
void lvalue_check_c::check_formal_call(symbol_c *f_call, symbol_c *f_decl) {
	/* if data type semantic verification was unable to determine which function is being called,
	 * then it does not make sense to go ahead and check for lvalues to unknown parameters.
	 * We simply bug out!
	 */
	if (NULL == f_decl) return;
	
	symbol_c *call_param_name;
	function_param_iterator_c       fp_iterator(f_decl);
	function_call_param_iterator_c fcp_iterator(f_call);

	/* Iterating through the formal parameters of the function call */
	while((call_param_name = fcp_iterator.next_f()) != NULL) {

		/* Obtaining the value being passed in the function call */
		symbol_c *call_param_value = fcp_iterator.get_current_value();
		if (NULL == call_param_value) ERROR;

		/* Find the corresponding parameter in function declaration, and it's direction (IN, OUT, IN_OUT) */
		identifier_c *param_name = fp_iterator.search(call_param_name);
		function_param_iterator_c::param_direction_t param_direction = fp_iterator.param_direction();
		
		/* We only check if 'call_param_value' is a valid lvalue if the value is being passed
		 * to a valid paramater of the function being called, and that parameter is either OUT or IN_OUT.
		 */
		if ((param_name != NULL) && ((function_param_iterator_c::direction_out == param_direction) || (function_param_iterator_c::direction_inout == param_direction))) {
			verify_is_lvalue(call_param_value);
		}
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
// SYM_REF3(function_invocation_c, function_name, formal_param_list, nonformal_param_list, symbol_c *called_function_declaration; int extensible_param_count; std::vector <symbol_c *> candidate_functions;)
void *lvalue_check_c::visit(function_invocation_c *symbol) {
	if (NULL != symbol->formal_param_list   )  check_formal_call   (symbol, symbol->called_function_declaration);
	if (NULL != symbol->nonformal_param_list)  check_nonformal_call(symbol, symbol->called_function_declaration);
	return NULL;
}

/*********************************/
/* B 3.2.1 Assignment Statements */
/*********************************/
void *lvalue_check_c::visit(assignment_statement_c *symbol) {
	verify_is_lvalue(symbol->l_exp);
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







