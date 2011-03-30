/*
 * (c) 2003 Mario de Sousa
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
 * FINAL DRAFT - IEC 61131-3, 2nd Ed. (2001-12-10)
 *
 */

/* Returns the function block declaration symbol
 * of a specific function block type.
 */

#include "absyntax_utils.hh"


search_fb_typedecl_c::search_fb_typedecl_c(symbol_c *search_scope) {
  this->search_scope = search_scope;
}

symbol_c *search_fb_typedecl_c::get_decl(symbol_c *fb_type_name) {
  this->search_name = fb_type_name;
  return (symbol_c *)search_scope->accept(*this);
}
/**************************************/
/* B.1.5 - Program organization units */
/**************************************/

/*****************************/
/* B 1.5.2 - Function Blocks */
/*****************************/
void *search_fb_typedecl_c::visit(function_block_declaration_c *symbol) {
  if (compare_identifiers(symbol->fblock_name, search_name) == 0)
    return symbol;
  return NULL;
}

/**********************/
/* B 1.5.3 - Programs */
/**********************/
void *search_fb_typedecl_c::visit(program_declaration_c *symbol) {
  if (compare_identifiers(symbol->program_type_name, search_name) == 0)
    return symbol;
  return NULL;
}

