/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2009-2012  Mario de Sousa (msousa@fe.up.pt)
 *  Copyright (C) 2012       Manuele Conti  (conti.ma@alice.it)
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

#ifndef _HELPER_FUNCTIONS_HH_
#define _HELPER_FUNCTIONS_HH_

#include "../absyntax/visitor.hh"
#include <typeinfo>

#define is_type(type_name_symbol, type_name_class)  ((type_name_symbol == NULL) ? false : (typeid(*type_name_symbol) == typeid(type_name_class)))
#define sizeoftype(symbol) get_sizeof_datatype_c::getsize(symbol)

/* Widening Primitive Conversion */
struct widen_entry {
	symbol_c *left;
	symbol_c *right;
	symbol_c *result;
};
/*
 * 2.5.1.5.6 Functions of time data types
 * Table 30 - page 64
 */
extern const struct widen_entry widen_ADD_table[];
extern const struct widen_entry widen_SUB_table[];
extern const struct widen_entry widen_MUL_table[];
extern const struct widen_entry widen_DIV_table[];

/* Search for a datatype inside a candidate_datatypes list.
 * Returns: position of datatype in the list, or -1 if not found.
 */
int search_in_datatype_list(symbol_c *datatype, std::vector <symbol_c *> candidate_datatypes);

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

#if 0
bool is_nonneg_literal_integer_type (symbol_c *type_symbol);
bool is_literal_integer_type        (symbol_c *type_symbol);
bool is_literal_real_type           (symbol_c *type_symbol);
bool is_literal_bool_type           (symbol_c *type_symbol);

/* Determine the common data type between two data types.
 * If no common data type found, return NULL.
 *
 * If data types are identical, return the first (any would do...).
 * If any of the data types is a literal, we confirm that
 *   the literal uses less bits than the fixed size data type.
 *   e.g. BYTE and 1024 returns NULL
 *        BYTE and 255  returns BYTE
 *
 * If two literals, then return the literal that requires more bits...
 */
symbol_c *common_type(symbol_c *first_type, symbol_c *second_type);
bool is_valid_assignment(symbol_c *var_type, symbol_c *value_type);
bool is_compatible_type(symbol_c *first_type, symbol_c *second_type);
#endif

bool is_type_equal(symbol_c *first_type, symbol_c *second_type);

// typedef bool (*helper_function_t) (symbol_c *type_symbol);  /* a pointer to a function! */



#endif /* _HELPER_FUNCTIONS_HH_ */
