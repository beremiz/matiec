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
#include <limits>  // required for std::numeric_limits<XXX>


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

#define GET_CVALUE(dtype, symbol)             ((symbol)->const_value_##dtype->value)
#define VALID_CVALUE(dtype, symbol)           ((NULL != (symbol)->const_value_##dtype) && (symbol_c::cs_const_value == (symbol)->const_value_##dtype->status))



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
		STAGE3_ERROR(0, symbol, symbol, "Number of subscripts/indexes does not match the number of subscripts/indexes in the array's declaration (array has %d indexes)", dimension_count);
}



void array_range_check_c::check_bounds(array_variable_c *symbol) {
  list_c *l; /* the subscript_list */
  symbol_c *var_decl;

  l = (list_c *)symbol->subscript_list;
  var_decl = search_varfb_instance_type->get_basetype_decl(symbol->subscripted_variable);
  array_dimension_iterator_c array_dimension_iterator(var_decl);
  for (int i =  0; i < l->n; i++) {
    subrange_c *dimension = array_dimension_iterator.next();
    /* mismatch between number of indexes/subscripts. This error will be caught in check_dimension_count() so we ignore it. */
    if (NULL == dimension) 
      return;
    
    if ( VALID_CVALUE( int64, l->elements[i]) && VALID_CVALUE( int64, dimension->lower_limit))
      if ( GET_CVALUE( int64, l->elements[i])   <  GET_CVALUE( int64, dimension->lower_limit))
      {STAGE3_ERROR(0, symbol, symbol, "Array access out of bounds."); continue;}

    if ( VALID_CVALUE( int64, l->elements[i]) && VALID_CVALUE( int64, dimension->upper_limit))
      if ( GET_CVALUE( int64, l->elements[i])   >  GET_CVALUE( int64, dimension->upper_limit))
      {STAGE3_ERROR(0, symbol, symbol, "Array access out of bounds."); continue;}

    if ( VALID_CVALUE(uint64, l->elements[i]) && VALID_CVALUE(uint64, dimension->lower_limit))
      if ( GET_CVALUE(uint64, l->elements[i])   <  GET_CVALUE(uint64, dimension->lower_limit))
      {STAGE3_ERROR(0, symbol, symbol, "Array access out of bounds."); continue;}

    if ( VALID_CVALUE(uint64, l->elements[i]) && VALID_CVALUE(uint64, dimension->upper_limit))
      if ( GET_CVALUE(uint64, l->elements[i])   >  GET_CVALUE(uint64, dimension->upper_limit))
      {STAGE3_ERROR(0, symbol, symbol, "Array access out of bounds."); continue;}
      
    /* TODO: what happens when one has a int64 cvalue, and another has a uint64 cvalue? */
  }
}









/*************************/
/* B.1 - Common elements */
/*************************/
/**********************/
/* B.1.3 - Data types */
/**********************/
/********************************/
/* B 1.3.3 - Derived data types */
/********************************/

/*  signed_integer DOTDOT signed_integer */
/* dimension will be filled in during stage 3 (array_range_check_c) with the number of elements in this subrange */
// SYM_REF2(subrange_c, lower_limit, upper_limit, unsigned long long int dimension)
void *array_range_check_c::visit(subrange_c *symbol) {
	unsigned long long int dimension = 0; // we use unsigned long long instead of uint64_t since it might just happen to be larger than uint64_t in the platform used for compiling this code!!

/* Determine the size of the array... */
	if        (VALID_CVALUE( int64, symbol->upper_limit) && VALID_CVALUE( int64, symbol->lower_limit)) {  
		// do the sums in such a way that no overflow is possible... even during intermediate steps used by compiler!
		// remember that the result (dimension) is unsigned, while the operands are signed!!
		// dimension = GET_CVALUE( int64, symbol->upper_limit) - VALID_CVALUE( int64, symbol->lower_limit);
		if (VALID_CVALUE( int64, symbol->lower_limit) >= 0) {
			dimension = GET_CVALUE( int64, symbol->upper_limit) - GET_CVALUE( int64, symbol->lower_limit);
		} else {
			dimension  = -GET_CVALUE( int64, symbol->lower_limit);
			dimension +=  GET_CVALUE( int64, symbol->upper_limit);     
		}
	} else if (VALID_CVALUE(uint64, symbol->upper_limit) && VALID_CVALUE(uint64, symbol->lower_limit)) {
		dimension = GET_CVALUE(uint64, symbol->upper_limit) - VALID_CVALUE(uint64, symbol->lower_limit); 
	} else if (VALID_CVALUE(uint64, symbol->upper_limit) && VALID_CVALUE( int64, symbol->lower_limit)) {
		if (VALID_CVALUE( int64, symbol->lower_limit) >= 0) {
			dimension = GET_CVALUE( int64, symbol->upper_limit) - GET_CVALUE( int64, symbol->lower_limit);
		} else {
		unsigned long long int lower_ull;
		lower_ull  = -GET_CVALUE( int64, symbol->lower_limit);
		dimension  =  GET_CVALUE( int64, symbol->upper_limit) + lower_ull;     
		/* TODO: check this overflow test, it does not seem to be working. I don't have to go now... Will check later. */
		if (dimension < lower_ull)
			STAGE3_ERROR(0, symbol, symbol, "Number of elements in array subrange exceeds maximum number of elements (%llu).", std::numeric_limits< unsigned long long int >::max());
		}
	} else ERROR;

	/* correct value for dimension is actually ---> dimension = upper_limit - lower_limit + 1
	 * Up to now, we have only determined dimension = upper_limit - lower_limit
	 * We must first check whether this last increment will cause an overflow!
	 */
	if (dimension == std::numeric_limits< unsigned long long int >::max())
		STAGE3_ERROR(0, symbol, symbol, "Number of elements in array subrange exceeds maximum number of elements (%llu).", std::numeric_limits< unsigned long long int >::max());
	
	/* correct value for dimension is actually ---> dimension = upper_limit - lower_limit + 1 */
	dimension++; 
	
	symbol->dimension = dimension;
	return NULL;
}


/*********************/
/* B 1.4 - Variables */
/*********************/
/*************************************/
/* B 1.4.2 - Multi-element variables */
/*************************************/
void *array_range_check_c::visit(array_variable_c *symbol) {
	check_dimension_count(symbol);
	check_bounds(symbol);
	return NULL;
}


/**************************************/
/* B 1.5 - Program organisation units */
/**************************************/
/***********************/
/* B 1.5.1 - Functions */
/***********************/
// SYM_REF4(function_declaration_c, derived_function_name, type_name, var_declarations_list, function_body)
void *array_range_check_c::visit(function_declaration_c *symbol) {
	symbol->var_declarations_list->accept(*this); // required for visiting subrange_c
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
// SYM_REF3(function_block_declaration_c, fblock_name, var_declarations, fblock_body)
void *array_range_check_c::visit(function_block_declaration_c *symbol) {
	symbol->var_declarations->accept(*this); // required for visiting subrange_c
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
// SYM_REF3(program_declaration_c, program_type_name, var_declarations, function_block_body)
void *array_range_check_c::visit(program_declaration_c *symbol) {
	symbol->var_declarations->accept(*this); // required for visiting subrange_c
	search_varfb_instance_type = new search_varfb_instance_type_c(symbol);
	// search_var_instance_decl = new search_var_instance_decl_c(symbol);
	symbol->function_block_body->accept(*this);
	delete search_varfb_instance_type;
	// delete search_var_instance_decl;
	search_varfb_instance_type = NULL;
	// search_var_instance_decl = NULL;
	return NULL;
}


