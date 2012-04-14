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

#include <vector>
#include "../absyntax_utils/absyntax_utils.hh"
#include "datatype_functions.hh"

/*
 *  In this class we implemented all lvalue check.
 *  With lvalue check we mean all semantic error about
 *  assignment with wrong access
 */

class lvalue_check_c: public iterator_visitor_c {

  private:
	search_varfb_instance_type_c *search_varfb_instance_type;
	search_var_instance_decl_c *search_var_instance_decl;
    search_base_type_c search_base_type;
    int error_found;
    int current_display_error_level;
    std::vector <symbol_c *> control_variables;
    symbol_c *base_type(symbol_c *symbol);
    void check_for_controlvar_assignment(symbolic_variable_c *lvalue);
    void check_output_assignment(symbolic_variable_c *lvalue);
    void check_constant_assignment(symbolic_variable_c *lvalue);
    void check_function_call_parameter(function_invocation_c *f_call);


  public:
    lvalue_check_c(symbol_c *ignore);
    virtual ~lvalue_check_c(void);
    int get_error_found();

    /**************************************/
    /* B 1.5 - Program organisation units */
    /**************************************/
    /***********************/
    /* B 1.5.1 - Functions */
    /***********************/
    void *visit(function_declaration_c *symbol);

    /*****************************/
    /* B 1.5.2 - Function blocks */
    /*****************************/
    void *visit(function_block_declaration_c *symbol);

    /**********************/
    /* B 1.5.3 - Programs */
    /**********************/
    void *visit(program_declaration_c *symbol);

    /***************************************/
    /* B.3 - Language ST (Structured Text) */
    /***************************************/
    /***********************/
    /* B 3.1 - Expressions */
    /***********************/
    void *visit(function_invocation_c *symbol);

    /*********************************/
    /* B 3.2.1 Assignment Statements */
    /*********************************/
    void *visit(assignment_statement_c *symbol);

    /********************************/
    /* B 3.2.4 Iteration Statements */
    /********************************/
    void *visit(for_statement_c *symbol);

}; /* lvalue_check_c */







