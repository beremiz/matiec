/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2009-2012  Mario de Sousa (msousa@fe.up.pt)
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

/* Determine the data type of an constant expression.
 * A reference to the relevant type definition is returned.
 *
 * For example:
 *       2 + 3       -> returns reference 
 *       22.2 - 5    -> returns reference
 *       etc...
 */

#include <vector>
#include "../absyntax_utils/absyntax_utils.hh"



class constant_folding_c : public iterator_visitor_c {
    search_varfb_instance_type_c *search_varfb_instance_type;
    search_base_type_c search_base_type;
    int error_count;
    bool warning_found;
    int current_display_error_level;

public:
	constant_folding_c(symbol_c *symbol = NULL);
	virtual ~constant_folding_c(void);
	int get_error_count();

private:
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
};

