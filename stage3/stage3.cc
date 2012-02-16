/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2009-2012  Mario de Sousa (msousa@fe.up.pt)
 *  Copyright (C) 2007-2011  Laurent Bessard and Edouard Tisserant
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

#include "stage3.hh"

#include "flow_control_analysis.hh"
#include "fill_candidate_datatypes.hh"
#include "narrow_candidate_datatypes.hh"
#include "print_datatypes_error.hh"


static int flow_control_analysis(symbol_c *tree_root){
  flow_control_analysis_c flow_control_analysis(tree_root);
  tree_root->accept(flow_control_analysis);
  return 0;
}

/* Type safety analysis assumes that flow control analysis has already been completed,
 * so be sure to call flow_control_analysis() before calling this function
 */
static int type_safety(symbol_c *tree_root){
	fill_candidate_datatypes_c fill_candidate_datatypes(tree_root);
	tree_root->accept(fill_candidate_datatypes);
	narrow_candidate_datatypes_c narrow_candidate_datatypes(tree_root);
	tree_root->accept(narrow_candidate_datatypes);
 	print_datatypes_error_c print_datatypes_error(tree_root);
	tree_root->accept(print_datatypes_error);
	if (print_datatypes_error.get_error_found())
		return -1;
	return 0;
}



int stage3(symbol_c *tree_root){
	flow_control_analysis(tree_root);
	return type_safety(tree_root);
}
