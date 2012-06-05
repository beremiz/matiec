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


/* Determine the value of an ST expression.
 * Filling in all symbols the correct value.
 *
 * For example:
 *       2 + 3         -> returns constant_value_integer = 5
 *       22.2 - 5.0    -> returns constant_value_real    = 17.2
 *       etc...
 */

#include "constant_folding.hh"
#include <typeinfo>
#include <limits>
#include <math.h> /* required for pow function */

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



#define DO_OPER(dtype)\
    (NULL != symbol->r_exp->const_value_##dtype ) && \
    (NULL != symbol->l_exp->const_value_##dtype )


#define CHECK_OVERFLOW_SUM(a, b, type)\
	((((std::numeric_limits< type >::max() - a) < (b)) ? 1 : 0) || \
	 (((std::numeric_limits< type >::min() + a) > (b)) ? 1 : 0))

#define CHECK_OVERFLOW_SUB(a, b, type)\
	((((std::numeric_limits< type >::max() - a) < (-b)) ? 1 : 0) || \
	 (((std::numeric_limits< type >::min() + a) > (-b)) ? 1 : 0))





constant_folding_c::constant_folding_c(symbol_c *symbol) {
    error_count = 0;
    current_display_error_level = 0;
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
	double *real_value;

	real_value = (double *)malloc(sizeof(double));
	sscanf(symbol->value, "%lf", real_value);
	symbol->const_value_real = real_value;

	return NULL;
}

void *constant_folding_c::visit(integer_c *symbol) {
	int64_t *integer_value;

	integer_value = (int64_t *)malloc(sizeof(int64_t));
	*integer_value = extract_integer_value(symbol);
	symbol->const_value_integer = integer_value;

	return NULL;
}

void *constant_folding_c::visit(neg_real_c *symbol) {
	double *real_value;

	real_value = (double *)malloc(sizeof(double));
	symbol->exp->accept(*this);
	if (NULL == symbol->exp->const_value_real)
		ERROR;
	*real_value = - *(symbol->exp->const_value_real);
	symbol->const_value_real = real_value;

	return NULL;
}

void *constant_folding_c::visit(neg_integer_c *symbol) {
	int64_t *integer_value;

	integer_value = (int64_t *)malloc(sizeof(int64_t));
	*integer_value = extract_integer_value(symbol);
	symbol->const_value_integer = integer_value;

	return NULL;
}

void *constant_folding_c::visit(binary_integer_c *symbol) {

	return NULL;
}

void *constant_folding_c::visit(octal_integer_c *symbol) {

	return NULL;
}

void *constant_folding_c::visit(hex_integer_c *symbol) {
	int64_t *integer_value;

	integer_value = (int64_t *)malloc(sizeof(int64_t));
	*integer_value = extract_hex_value(symbol);

	return NULL;
}

void *constant_folding_c::visit(integer_literal_c *symbol) {
	int64_t *integer_value;

	symbol->value->accept(*this);
	if (NULL == symbol->value->const_value_integer) ERROR;
	*(symbol->const_value_integer) = *(symbol->value->const_value_integer);
	integer_value = (int64_t *)malloc(sizeof(int64_t));

	return NULL;
}

void *constant_folding_c::visit(real_literal_c *symbol) {
	double *real_value;

	real_value = (double *)malloc(sizeof(double));
	symbol->value->accept(*this);
	if (NULL == symbol->value->const_value_real)
		ERROR;
	*real_value = *(symbol->value->const_value_real);
	symbol->const_value_real = real_value;

	return NULL;
}

void *constant_folding_c::visit(bit_string_literal_c *symbol) {

	return NULL;
}

void *constant_folding_c::visit(boolean_literal_c *symbol) {
	symbol->value->accept(*this);
	if (NULL == symbol->value->const_value_bool) ERROR;
	symbol->const_value_bool = (bool *)malloc(sizeof(bool));
	*(symbol->const_value_bool) = *(symbol->value->const_value_bool);

	return NULL;
}

void *constant_folding_c::visit(boolean_true_c *symbol) {
	symbol->const_value_bool = (bool *)malloc(sizeof(bool));
	*(symbol->const_value_bool) = true;

	return NULL;
}

void *constant_folding_c::visit(boolean_false_c *symbol) {
	symbol->const_value_bool = (bool *)malloc(sizeof(bool));
	*(symbol->const_value_bool) = false;

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
	if (DO_OPER(bool)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_bool) || *(symbol->r_exp->const_value_bool);
	}
	if (DO_OPER(integer)) {
		symbol->const_value_integer = (int64_t*) malloc(sizeof(int64_t));
		*(symbol->const_value_integer) = *(symbol->l_exp->const_value_integer) | *(symbol->r_exp->const_value_integer);
	}

	return NULL;
}

void *constant_folding_c::visit(xor_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if (DO_OPER(integer)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_integer) ^ *(symbol->r_exp->const_value_integer);
	}

	return NULL;
}

void *constant_folding_c::visit(and_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if (DO_OPER(bool)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_bool) && *(symbol->r_exp->const_value_bool);
	}
	if (DO_OPER(integer)) {
		symbol->const_value_integer = (int64_t*) malloc(sizeof(int64_t));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_integer) & *(symbol->r_exp->const_value_integer);
	}

	return NULL;
}

void *constant_folding_c::visit(equ_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if (DO_OPER(bool)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_bool) == *(symbol->r_exp->const_value_bool);
	}
	if (DO_OPER(integer)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_integer) == *(symbol->r_exp->const_value_integer);
	}
	if (DO_OPER(real)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_real) == *(symbol->r_exp->const_value_real);
	}

	return NULL;
}

void *constant_folding_c::visit(notequ_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if (DO_OPER(bool)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_bool) != *(symbol->r_exp->const_value_bool);
	}
	if (DO_OPER(integer)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_integer) != *(symbol->r_exp->const_value_integer);
	}
	if (DO_OPER(real)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_real) != *(symbol->r_exp->const_value_real);
	}

	return NULL;
}

void *constant_folding_c::visit(lt_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if (DO_OPER(integer)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_integer) < *(symbol->r_exp->const_value_integer);
	}
	if (DO_OPER(real)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_real) < *(symbol->r_exp->const_value_real);
	}

	return NULL;
}

void *constant_folding_c::visit(gt_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if (DO_OPER(integer)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_integer) > *(symbol->r_exp->const_value_integer);
	}
	if (DO_OPER(real)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_real) > *(symbol->r_exp->const_value_real);
	}

	return NULL;
}

void *constant_folding_c::visit(le_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if (DO_OPER(integer)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_integer) <= *(symbol->r_exp->const_value_integer);
	}
	if (DO_OPER(real)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_real) <= *(symbol->r_exp->const_value_real);
	}

	return NULL;
}

void *constant_folding_c::visit(ge_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if (DO_OPER(integer)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_integer) >= *(symbol->r_exp->const_value_integer);
	}
	if (DO_OPER(real)) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = *(symbol->l_exp->const_value_real) >= *(symbol->r_exp->const_value_real);
	}

	return NULL;
}

void *constant_folding_c::visit(add_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if (DO_OPER(integer)) {
		if (CHECK_OVERFLOW_SUM(*(symbol->l_exp->const_value_integer), *(symbol->r_exp->const_value_integer), int64_t))
			STAGE3_ERROR(0, symbol, symbol, "Overflow in constant expression.");
		symbol->const_value_integer = (int64_t*) malloc(sizeof(int64_t));
		*(symbol->const_value_integer) = *(symbol->l_exp->const_value_integer) + *(symbol->r_exp->const_value_integer);
	}
	if (DO_OPER(real)) {
		if (CHECK_OVERFLOW_SUM(*(symbol->l_exp->const_value_real), *(symbol->r_exp->const_value_real), double))
			STAGE3_ERROR(0, symbol, symbol, "Overflow in constant expression.");
		symbol->const_value_real = (double*) malloc(sizeof(double));
		*(symbol->const_value_real) = *(symbol->l_exp->const_value_real) + *(symbol->r_exp->const_value_real);
	}

	return NULL;
}

void *constant_folding_c::visit(sub_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if (DO_OPER(integer)) {
		if (CHECK_OVERFLOW_SUB(*(symbol->l_exp->const_value_integer), *(symbol->r_exp->const_value_integer), int64_t))
			STAGE3_ERROR(0, symbol, symbol, "Overflow in constant expression.");
		symbol->const_value_integer = (int64_t*) malloc(sizeof(int64_t));
		*(symbol->const_value_integer) = *(symbol->l_exp->const_value_integer) - *(symbol->r_exp->const_value_integer);
	}
	if (DO_OPER(real)) {
		if (CHECK_OVERFLOW_SUB(*(symbol->l_exp->const_value_real), *(symbol->r_exp->const_value_real), double))
			STAGE3_ERROR(0, symbol, symbol, "Overflow in constant expression.");
		symbol->const_value_real = (double*) malloc(sizeof(double));
		*(symbol->const_value_real) = *(symbol->l_exp->const_value_real) - *(symbol->r_exp->const_value_real);
	}

	return NULL;
}

void *constant_folding_c::visit(mul_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if (DO_OPER(integer)) {
		symbol->const_value_integer = (int64_t*) malloc(sizeof(int64_t));
		if ((*(symbol->l_exp->const_value_integer) == 0) ||
			(*(symbol->r_exp->const_value_integer) == 0)) {
			*(symbol->const_value_integer) = 0;
			return NULL;
		}

		*(symbol->const_value_integer) = *(symbol->l_exp->const_value_integer) * *(symbol->r_exp->const_value_integer);
	}
	if (DO_OPER(real)) {
		symbol->const_value_real = (double*) malloc(sizeof(double));
		*(symbol->const_value_real) = *(symbol->l_exp->const_value_real) * *(symbol->r_exp->const_value_real);
	}

	return NULL;
}

void *constant_folding_c::visit(div_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if (DO_OPER(integer)) {
		if (*(symbol->r_exp->const_value_integer) == 0)
			STAGE3_ERROR(0, symbol, symbol, "Division by zero in constant expression.");
		symbol->const_value_integer = (int64_t*) malloc(sizeof(int64_t));
		*(symbol->const_value_integer) = *(symbol->l_exp->const_value_integer) / *(symbol->r_exp->const_value_integer);
	}
	if (DO_OPER(real)) {
		if (*(symbol->r_exp->const_value_real) == 0)
			STAGE3_ERROR(0, symbol, symbol, "Division by zero in constant expression.");
		symbol->const_value_real = (double*) malloc(sizeof(double));
		*(symbol->const_value_real) = *(symbol->l_exp->const_value_real) / *(symbol->r_exp->const_value_real);
	}

	return NULL;
}

void *constant_folding_c::visit(mod_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if (DO_OPER(integer)) {
		if (*(symbol->r_exp->const_value_integer) == 0)
			STAGE3_ERROR(0, symbol, symbol, "Division by zero in constant expression.");
		symbol->const_value_integer = (int64_t*) malloc(sizeof(int64_t));
		*(symbol->const_value_integer) = *(symbol->l_exp->const_value_integer) % *(symbol->r_exp->const_value_integer);
	}

	return NULL;
}

void *constant_folding_c::visit(power_expression_c *symbol) {
	symbol->l_exp->accept(*this);
	symbol->r_exp->accept(*this);
	if ((NULL != symbol->l_exp->const_value_real) && (NULL != symbol->r_exp->const_value_integer)) {
		symbol->const_value_real = (double*) malloc(sizeof(double));
		*(symbol->const_value_real) = pow(*(symbol->l_exp->const_value_real), *(symbol->r_exp->const_value_integer));
	}

	return NULL;
}
void *constant_folding_c::visit(neg_expression_c *symbol) {
	symbol->exp->accept(*this);
	if (NULL != symbol->exp->const_value_integer) {
		symbol->const_value_integer = (int64_t*) malloc(sizeof(int64_t));
		*(symbol->const_value_integer) = - *(symbol->exp->const_value_integer);
	}
	if (NULL != symbol->exp->const_value_real) {
		symbol->const_value_real = (double*) malloc(sizeof(double));
		*(symbol->const_value_real) = - *(symbol->exp->const_value_real);
	}
	return NULL;
}

void *constant_folding_c::visit(not_expression_c *symbol) {
	symbol->exp->accept(*this);
	if (NULL != symbol->exp->const_value_bool) {
		symbol->const_value_bool = (bool*) malloc(sizeof(bool));
		*(symbol->const_value_bool) = !*(symbol->exp->const_value_bool);
	}

	return NULL;
}



