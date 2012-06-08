/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2003-2011  Mario de Sousa (msousa@fe.up.pt)
 *  Copyright (C) 2012       Manuele Conti (conti.ma@alice.it)
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


/* Do constant folding...
 *
 * I.e., Determine the value of all expressions in which only constant values (i.e. literals) are used.
 * The (constant) result of each operation is stored (annotated) in the respective operation symbol 
 * (e.g.: add_expression_c) in the abstract syntax tree,
 *
 * For example:
 *       2 + 3         -> the constant value '5'    is stored in the add_expression_c symbol.
 *       22.2 - 5.0    -> the constant value '17.2' is stored in the add_expression_c symbol.
 *       etc...
 *
 *
 * NOTE 1 that some operations and constants can have multiple data types. For example,
 *        1 AND 0
 *      may be either a BOOL, BYTE, WORD or LWORD.
 *
 *      The same happens with 
 *        1 + 2
 *      which may be signed (e.g. INT) or unsigned (UINT)
 *
 *      For the above reason, instead of storing a single constant value, we actually store 4:
 *        - bool
 *        - uint64
 *        -  int64
 *        - real64
 *
 *      Additionally, since the result of an operation may result in an overflow, we actually
 *      store the result inside a struct (defined in absyntax.hh)
 *
 *             ** During stage 3 (semantic analysis/checking) we will be doing constant folding.
 *              * That algorithm will anotate the abstract syntax tree with the result of operations
 *              * on literals (i.e. 44 + 55 will store the result 99).
 *              * Since the same source code (e.g. 1 + 0) may actually be a BOOL or an ANY_INT,
 *              * or an ANY_BIT, we need to handle all possibilities, and determine the result of the
 *              * operation assuming each type.
 *              * For this reason, we have one entry for each possible type, with some expressions
 *              * having more than one entry filled in!
 *              **
 *             typedef enum { cs_undefined,   // not defined --> const_value is not valid!
 *                            cs_const_value, // const value is valid
 *                            cs_overflow     // result produced overflow or underflow --> const_value is not valid!
 *                          } const_status_t;
 *    
 *             typedef struct {
 *                 const_status_t status;
 *                 real64_t       value; 
 *             } const_value_real64_t;
 *             const_value_real64_t *const_value_real64; // when NULL --> UNDEFINED
 *             
 *             typedef struct {
 *                 const_status_t status;
 *                 int64_t        value; 
 *             } const_value_int64_t;
 *             const_value_int64_t *const_value_int64; // when NULL --> UNDEFINED
 *             
 *             typedef struct {
 *                 const_status_t status;
 *                 uint64_t       value; 
 *             } const_value_uint64_t;
 *             const_value_uint64_t *const_value_uint64; // when NULL --> UNDEFINED
 *             
 *             typedef struct {
 *                 const_status_t status;
 *                 bool           value; 
 *             } const_value_bool_t;
 *             const_value_bool_t *const_value_bool; // when NULL --> UNDEFINED
 *
 *
 *
 * NOTE 2 
 *    This file does not print out any error messages!
 *    We cannot really print out error messages when we find an overflow. Since each operation
 *    (symbol in the absract syntax tree for that operation) will have up to 4 constant results,
 *    it may happen that some of them overflow, while other do not.
 *    We must wait for data type checking to determine the exact data type of each expression
 *    before we can decide whether or not we should print out an overflow error message.
 *
 *    For this reason, this visitor merely annotates the abstract syntax tree, and leaves the
 `    actuall printing of errors for the print_datatype_errors_c class!
 */

#include "constant_folding.hh"
#include <typeinfo>
#include <limits>
#include <math.h> /* required for pow function */
#include <stdlib.h> /* required for malloc() */




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












#define NEW_CVALUE(dtype, symbol) \
 (symbol->const_value_##dtype) = new(symbol_c::const_value_##dtype##_t); \
 if ((symbol->const_value_##dtype) == NULL) ERROR; \
 (symbol->const_value_##dtype)->status = symbol_c::cs_undefined;

#define SET_CVALUE(dtype, symbol, new_value)  ((symbol)->const_value_##dtype->value) = new_value; ((symbol)->const_value_##dtype->status) = symbol_c::cs_const_value;  
#define GET_CVALUE(dtype, symbol)             ((symbol)->const_value_##dtype->value) 
#define SET_OVFLOW(dtype, symbol)             ((symbol)->const_value_##dtype->status) = symbol_c::cs_overflow
    /* The following test is correct in the presence of a NULL pointer, as the logical evaluation will be suspended as soon as the first condition is false! */
#define VALID_CVALUE(dtype, symbol)           ((NULL != (symbol)->const_value_##dtype) && (symbol_c::cs_const_value == (symbol)->const_value_##dtype->status))
#define ISZERO_CVALUE(dtype, symbol)          ((VALID_CVALUE(dtype, symbol)) && (GET_CVALUE(dtype, symbol) == 0))
#define DO_BIN_OPER(dtype, oper)\
	if (VALID_CVALUE(dtype, symbol->r_exp) && VALID_CVALUE(dtype, symbol->l_exp)) {                                \
		NEW_CVALUE(dtype, symbol);                                                                             \
		SET_CVALUE(dtype, symbol, GET_CVALUE(dtype, symbol->l_exp) oper GET_CVALUE(dtype, symbol->r_exp));     \
	}





constant_folding_c::constant_folding_c(symbol_c *symbol) {
    error_count = 0;
    warning_found = false;
    current_display_error_level = 0;
    
    /* check whether the platform on which the compiler is being run implements IEC 559 floating point data types. */
    symbol_c null_symbol;
    if (! (std::numeric_limits<real64_t>::is_iec559) )
        STAGE3_WARNING(&null_symbol, &null_symbol, "The platform running the compiler does not implement IEC 559 floating point numbers. "
                                                   "Any error and/or warning messages related to overflow/underflow of the result of operations on REAL/LREAL literals "
                                                   " (i.e. constant folding) may themselves be erroneous, although are most probably correct.");
}


constant_folding_c::~constant_folding_c(void) {
}


int constant_folding_c::get_error_count() {
	return error_count;
}


/*********************/
/* B 1.2 - Constants */
/*********************/
/******************************/
/* B 1.2.1 - Numeric Literals */
/******************************/
void *constant_folding_c::visit(real_c *symbol) {
	NEW_CVALUE(real64, symbol);
	SET_CVALUE(real64, symbol, extract_real_value(symbol));
	return NULL;
}


void *constant_folding_c::visit(integer_c *symbol) {
	NEW_CVALUE( int64, symbol);
	SET_CVALUE( int64, symbol, extract_integer_value(symbol));
	NEW_CVALUE(uint64, symbol);
	SET_CVALUE(uint64, symbol, extract_integer_value(symbol));
	return NULL;
}


void *constant_folding_c::visit(neg_real_c *symbol) {
	symbol->exp->accept(*this);
	if (!VALID_CVALUE(real64, symbol->exp))
		return NULL;
	NEW_CVALUE(real64, symbol);
	SET_CVALUE(real64, symbol, - GET_CVALUE( real64, symbol->exp));
	return NULL;
}

/* | '-' integer	{$$ = new neg_integer_c($2, locloc(@$));} */
void *constant_folding_c::visit(neg_integer_c *symbol) {
	symbol->exp->accept(*this);
	if (VALID_CVALUE(int64, symbol->exp)) {
		NEW_CVALUE( int64, symbol);
		SET_CVALUE( int64, symbol, - GET_CVALUE( int64, symbol->exp));
	}
	return NULL;
}


void *constant_folding_c::visit(binary_integer_c *symbol) {
	return NULL;
}


void *constant_folding_c::visit(octal_integer_c *symbol) {
	return NULL;
}


void *constant_folding_c::visit(hex_integer_c *symbol) {
	NEW_CVALUE( int64, symbol);
	SET_CVALUE( int64, symbol, extract_hex_value(symbol));
	NEW_CVALUE(uint64, symbol);
	SET_CVALUE(uint64, symbol, extract_hex_value(symbol));
	return NULL;
}


/*
integer_literal:
  integer_type_name '#' signed_integer	{$$ = new integer_literal_c($1, $3, locloc(@$));}
| integer_type_name '#' binary_integer	{$$ = new integer_literal_c($1, $3, locloc(@$));}
| integer_type_name '#' octal_integer	{$$ = new integer_literal_c($1, $3, locloc(@$));}
| integer_type_name '#' hex_integer	{$$ = new integer_literal_c($1, $3, locloc(@$));}
*/
// SYM_REF2(integer_literal_c, type, value)
void *constant_folding_c::visit(integer_literal_c *symbol) {
	symbol->value->accept(*this);
	if (VALID_CVALUE( int64, symbol->value)) {
		NEW_CVALUE( int64, symbol);
		SET_CVALUE( int64, symbol, GET_CVALUE( int64, symbol->value));
	}
	if (VALID_CVALUE(uint64, symbol->value)) {
		NEW_CVALUE(uint64, symbol);
		SET_CVALUE(uint64, symbol, GET_CVALUE(uint64, symbol->value));
	}
	return NULL;
}


void *constant_folding_c::visit(real_literal_c *symbol) {
	symbol->value->accept(*this);
	if (VALID_CVALUE(real64, symbol->value)) {
		NEW_CVALUE(real64, symbol);
		SET_CVALUE(real64, symbol,  GET_CVALUE(real64, symbol->value));
	}
	return NULL;
}


void *constant_folding_c::visit(bit_string_literal_c *symbol) {
	return NULL;
}


void *constant_folding_c::visit(boolean_literal_c *symbol) {
	symbol->value->accept(*this);
	if (VALID_CVALUE(bool, symbol->value)) {
		NEW_CVALUE(bool, symbol);
		SET_CVALUE(bool, symbol,  GET_CVALUE(  bool, symbol->value));
	}
	return NULL;
}


void *constant_folding_c::visit(boolean_true_c *symbol) {
	NEW_CVALUE(bool, symbol);
	SET_CVALUE(bool, symbol, true);
	return NULL;
}


void *constant_folding_c::visit(boolean_false_c *symbol) {
	NEW_CVALUE(bool, symbol);
	SET_CVALUE(bool, symbol, false);
	return NULL;
}


/***************************************/
/* B.3 - Language ST (Structured Text) */
/***************************************/
/***********************/
/* B 3.1 - Expressions */
/***********************/
void *constant_folding_c::visit(or_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	DO_BIN_OPER(bool,   ||);
	DO_BIN_OPER(uint64, | );
	return NULL;
}


void *constant_folding_c::visit(xor_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	DO_BIN_OPER(bool,   ^);
	DO_BIN_OPER(uint64, ^);
	return NULL;
}


void *constant_folding_c::visit(and_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	DO_BIN_OPER(bool,   &&);
	DO_BIN_OPER(uint64, & );
	return NULL;
}


void *constant_folding_c::visit(equ_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	DO_BIN_OPER(bool,   ==);
	DO_BIN_OPER(uint64, ==);
	DO_BIN_OPER( int64, ==);
	DO_BIN_OPER(real64, ==);
	return NULL;
}


void *constant_folding_c::visit(notequ_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	DO_BIN_OPER(bool,   !=);
	DO_BIN_OPER(uint64, !=);
	DO_BIN_OPER( int64, !=);
	DO_BIN_OPER(real64, !=);
	return NULL;
}


void *constant_folding_c::visit(lt_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	DO_BIN_OPER(bool,   <);
	DO_BIN_OPER(uint64, <);
	DO_BIN_OPER( int64, <);
	DO_BIN_OPER(real64, <);
	return NULL;
}


void *constant_folding_c::visit(gt_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	DO_BIN_OPER(bool,   >);
	DO_BIN_OPER(uint64, >);
	DO_BIN_OPER( int64, >);
	DO_BIN_OPER(real64, >);
	return NULL;
}


void *constant_folding_c::visit(le_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	DO_BIN_OPER(bool,   <=);
	DO_BIN_OPER(uint64, <=);
	DO_BIN_OPER( int64, <=);
	DO_BIN_OPER(real64, <=);
	return NULL;
}


void *constant_folding_c::visit(ge_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	DO_BIN_OPER(bool,   >=);
	DO_BIN_OPER(uint64, >=);
	DO_BIN_OPER( int64, >=);
	DO_BIN_OPER(real64, >=);
	return NULL;
}


#define CHECK_OVERFLOW_SUM(dtype)\
	if (VALID_CVALUE(dtype, symbol))                                                                                                             \
		if ((((std::numeric_limits< dtype##_t >::max() - GET_CVALUE(dtype, symbol->l_exp)) < (GET_CVALUE(dtype, symbol->r_exp))) ? 1 : 0) || \
		    (((std::numeric_limits< dtype##_t >::min() + GET_CVALUE(dtype, symbol->l_exp)) > (GET_CVALUE(dtype, symbol->r_exp))) ? 1 : 0))   \
			SET_OVFLOW(dtype, symbol);
#define CHECK_OVERFLOW_real64  \
	if (VALID_CVALUE(real64, symbol))                                                                                                            \
        	/* NaN => underflow, overflow, number is a higher precision format, is a complex number (IEEE standard) */                           \
		 if (isnan(GET_CVALUE(real64, symbol)))                                                                                              \
			SET_OVFLOW(real64, symbol);
void *constant_folding_c::visit(add_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	DO_BIN_OPER(uint64, +);
	DO_BIN_OPER( int64, +);
	DO_BIN_OPER(real64, +);
	CHECK_OVERFLOW_SUM(uint64);
	CHECK_OVERFLOW_SUM( int64);
	CHECK_OVERFLOW_real64;
	return NULL;
}


#define CHECK_OVERFLOW_SUB(dtype)\
	if (VALID_CVALUE(dtype, symbol))                                                                                                             \
		if ((((std::numeric_limits< dtype##_t >::max() - GET_CVALUE(dtype, symbol->l_exp)) < (-GET_CVALUE(dtype, symbol->r_exp))) ? 1 : 0) || \
		    (((std::numeric_limits< dtype##_t >::min() + GET_CVALUE(dtype, symbol->l_exp)) > (-GET_CVALUE(dtype, symbol->r_exp))) ? 1 : 0))   \
			SET_OVFLOW(dtype, symbol);
void *constant_folding_c::visit(sub_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	DO_BIN_OPER(uint64, -);
	DO_BIN_OPER( int64, -);
	DO_BIN_OPER(real64, -);
	CHECK_OVERFLOW_SUB(uint64);
	CHECK_OVERFLOW_SUB( int64);
	CHECK_OVERFLOW_real64;
	return NULL;
}


/* TODO!!! */
#define CHECK_OVERFLOW_MUL(dtype)\
	if (VALID_CVALUE(dtype, symbol))                                                                                                             \
		if (false)                                                                                                                                   \
			SET_OVFLOW(dtype, symbol);
void *constant_folding_c::visit(mul_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	DO_BIN_OPER(uint64, *);
	DO_BIN_OPER( int64, *);
	DO_BIN_OPER(real64, *);
	CHECK_OVERFLOW_MUL(uint64);
	CHECK_OVERFLOW_MUL( int64);
	CHECK_OVERFLOW_real64;
	return NULL;
}



/* TODO!!! */
#define CHECK_OVERFLOW_DIV(dtype)\
	if (VALID_CVALUE(dtype, symbol))                                                                                                             \
		if (false)                                                                                                                                   \
			SET_OVFLOW(dtype, symbol);
void *constant_folding_c::visit(div_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if (ISZERO_CVALUE(uint64, symbol->r_exp))  {NEW_CVALUE(uint64, symbol); SET_OVFLOW(uint64, symbol);} else {DO_BIN_OPER(uint64, /); CHECK_OVERFLOW_DIV(uint64)};
	if (ISZERO_CVALUE( int64, symbol->r_exp))  {NEW_CVALUE( int64, symbol); SET_OVFLOW( int64, symbol);} else {DO_BIN_OPER( int64, /); CHECK_OVERFLOW_DIV( int64)};
	if (ISZERO_CVALUE(real64, symbol->r_exp))  {NEW_CVALUE(real64, symbol); SET_OVFLOW(real64, symbol);} else {DO_BIN_OPER(real64, /); CHECK_OVERFLOW_real64;};
	return NULL;
}


/* TODO!!! */
#define CHECK_OVERFLOW_MOD(dtype)\
	if (VALID_CVALUE(dtype, symbol))                                                                                                             \
		if (false)                                                                                                                                   \
			SET_OVFLOW(dtype, symbol);
void *constant_folding_c::visit(mod_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if (ISZERO_CVALUE(uint64, symbol->r_exp))  {NEW_CVALUE(uint64, symbol); SET_OVFLOW(uint64, symbol);} else {DO_BIN_OPER(uint64, %); CHECK_OVERFLOW_MOD(uint64)};
	if (ISZERO_CVALUE( int64, symbol->r_exp))  {NEW_CVALUE( int64, symbol); SET_OVFLOW( int64, symbol);} else {DO_BIN_OPER( int64, %); CHECK_OVERFLOW_MOD( int64)};
	return NULL;
}


void *constant_folding_c::visit(power_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	/* NOTE: If the const_value in symbol->r_exp is within the limits of both int64 and uint64, then we do both operations.
	 *       That is OK, as the result should be identicial (we do create an unnecessary CVALUE variable, but who cares?).
	 *       If only one is valid, then that is the oper we will do!
	 */
	if (VALID_CVALUE(real64, symbol->l_exp) && VALID_CVALUE( int64, symbol->r_exp)) {
		NEW_CVALUE(real64, symbol);
		SET_CVALUE(real64, symbol, pow(GET_CVALUE(real64, symbol->l_exp), GET_CVALUE( int64, symbol->r_exp)));
	}
	if (VALID_CVALUE(real64, symbol->l_exp) && VALID_CVALUE(uint64, symbol->r_exp)) {
		NEW_CVALUE(real64, symbol);
		SET_CVALUE(real64, symbol, pow(GET_CVALUE(real64, symbol->l_exp), GET_CVALUE(uint64, symbol->r_exp)));
	}
	CHECK_OVERFLOW_real64;
	return NULL;
}


/* TODO!!! */
#define CHECK_OVERFLOW_NEG(dtype)\
	if (VALID_CVALUE(dtype, symbol))                                                                                                             \
		if (false)                                                                                                                                   \
			SET_OVFLOW(dtype, symbol);
void *constant_folding_c::visit(neg_expression_c *symbol) {
	symbol->exp->accept(*this);
	if (VALID_CVALUE( int64, symbol->exp)) {
		NEW_CVALUE( int64, symbol);
		SET_CVALUE( int64, symbol, - GET_CVALUE( int64, symbol->exp));
	}
	if (VALID_CVALUE(real64, symbol->exp)) {
		NEW_CVALUE(real64, symbol);
		SET_CVALUE(real64, symbol, - GET_CVALUE(real64, symbol->exp));
	}
	CHECK_OVERFLOW_NEG( int64);
	CHECK_OVERFLOW_real64;
	return NULL;
}



void *constant_folding_c::visit(not_expression_c *symbol) {
	symbol->exp->accept(*this);
	if (VALID_CVALUE(  bool, symbol->exp)) {
		NEW_CVALUE(  bool, symbol);
		SET_CVALUE(  bool, symbol,  ! GET_CVALUE(  bool, symbol->exp));
	}
	if (VALID_CVALUE(uint64, symbol->exp)) {
		NEW_CVALUE(uint64, symbol);
		SET_CVALUE(uint64, symbol,  ~ GET_CVALUE(uint64, symbol->exp));
	}
	return NULL;
}


