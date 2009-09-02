/*
 * (c) 20099 Catarina da Costa Boucinha
 *
 * Offered to the public under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * This code is made available on the understanding that it will not be
 * used in safety-critical situations without a full and competent review.
 */

/*
 * An IEC 61131-3 IL and ST compiler.
 *
 * Based on the
 * FINAL DRAFT - IEC 61131-3, 2nd Ed. (2009-04-24)
 *
 */

#include "stage3.hh"

int type_safety(symbol_c *tree_root){
	visit_expression_type_c visit_expression_type(tree_root);

	(*tree_root).accept(visit_expression_type);

	return 0;
}

int stage3(symbol_c *tree_root){
	return type_safety(tree_root);
}
