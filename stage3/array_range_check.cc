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


/*
 * TODO:
 *   - Check subscript values fall within allowed range.
 *     For the checking of subscript values to work correctly, we would need to have constant folding working too:
 *     array_var[8 + 99] can not be checked without constant folding.
 *     However, even without constant folding range check may be usefull,
 *     and later changing it to use the values coming out of constant folding should not be very difficult.
 *
 */


#include "array_range_check.hh"

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


array_range_check_c::array_range_check_c(symbol_c *ignore) {
	error_count = 0;
	current_display_error_level = 0;
}

array_range_check_c::~array_range_check_c(void) {
}

int array_range_check_c::get_error_count() {
	return error_count;
}

void array_range_check_c::check_dimension_count(array_variable_c *symbol) {
	int dimension_count;
	symbol_c *var_decl;

	var_decl = search_varfb_instance_type->get_basetype_decl(symbol->subscripted_variable);
	array_dimension_iterator_c array_dimension_iterator(var_decl);
	for (dimension_count = 0; NULL != array_dimension_iterator.next(); dimension_count++);
	if (dimension_count != ((list_c *)symbol->subscript_list)->n)
		STAGE3_ERROR(0, symbol, symbol, "Number of dimensions does not match, Array have %d dimension(s)", dimension_count);
}

/*********************/
/* B 1.4 - Variables */
/*********************/
/*************************************/
/* B 1.4.2 - Multi-element variables */
/*************************************/
void *array_range_check_c::visit(array_variable_c *symbol) {
	check_dimension_count(symbol);
	return NULL;
}


/**************************************/
/* B 1.5 - Program organisation units */
/**************************************/
/***********************/
/* B 1.5.1 - Functions */
/***********************/
void *array_range_check_c::visit(function_declaration_c *symbol) {
	search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
	// search_var_instance_decl = new search_var_instance_decl_c(symbol);
	symbol->function_body->accept(*this);
	delete search_varfb_instance_type;
	// delete search_var_instance_decl;
	search_varfb_instance_type = NULL;
	// search_var_instance_decl = NULL;
	return NULL;
}

/*****************************/
/* B 1.5.2 - Function blocks */
/*****************************/
void *array_range_check_c::visit(function_block_declaration_c *symbol) {
	search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
	// search_var_instance_decl = new search_var_instance_decl_c(symbol);
	symbol->fblock_body->accept(*this);
	delete search_varfb_instance_type;
	// delete search_var_instance_decl;
	search_varfb_instance_type = NULL;
	// search_var_instance_decl = NULL;
	return NULL;
}

/**********************/
/* B 1.5.3 - Programs */
/**********************/
void *array_range_check_c::visit(program_declaration_c *symbol) {
	search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
	// search_var_instance_decl = new search_var_instance_decl_c(symbol);
	symbol->function_block_body->accept(*this);
	delete search_varfb_instance_type;
	// delete search_var_instance_decl;
	search_varfb_instance_type = NULL;
	// search_var_instance_decl = NULL;
	return NULL;
}



