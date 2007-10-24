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


/* Returns the function block type declaration
 * of a specific function block instance.
 */



/* Returns the type name of a specific function block
 * instance. This class will search the variable
 * declarations inside the scope given to it
 * searching for the declaration of the function
 * block instance.
 *
 * The class constructor must be given the search scope
 * (function, function block or program within which
 * the function block instance was declared).
 *
 * This class will search the tree from the root given to the
 * constructor. Another option would be to build a symbol table,
 * and search that instead. Building the symbol table would be done
 * while visiting the variable declaration objects in the parse
 * tree. Unfortuantely, generate_c_c does not visit these
 * objects, delegating it to another class. This means that
 * we would need another specialised class just to build the
 * symbol table. We might just as well have a specialised class
 * that searches the tree itself for the relevant info. This
 * class is exactly that...!
 */
class search_fb_instance_decl_c: public search_visitor_c {

  private:
    symbol_c *search_scope;

    symbol_c *search_name;
    symbol_c *current_fb_type_name;

  public:
    search_fb_instance_decl_c(symbol_c *search_scope) {
      this->search_scope = search_scope;
      this->current_fb_type_name = NULL;
    }

    symbol_c *get_type_name(symbol_c *fb_instance_name) {
      this->search_name = fb_instance_name;
      return (symbol_c *)search_scope->accept(*this);
    }

  public:
/***************************/
/* B 0 - Programming Model */
/***************************/
    void *visit(library_c *symbol) {
      /* we do not want to search multiple declaration scopes,
       * so we do not visit all the functions, fucntion blocks, etc...
       */
      return NULL;
    }

/******************************************/
/* B 1.4.3 - Declaration & Initialisation */
/******************************************/

/* name_list ':' function_block_type_name ASSIGN structure_initialization */
/* structure_initialization -> may be NULL ! */
    void *visit(fb_name_decl_c *symbol) {
      current_fb_type_name = symbol->function_block_type_name;
      return symbol->fb_name_list->accept(*this);
    }

/* name_list ',' fb_name */
    void *visit(fb_name_list_c *symbol) {
      list_c *list = symbol;
      for(int i = 0; i < list->n; i++) {
        if (compare_identifiers(list->elements[i], search_name) == 0)
	  /* by now, current_fb_declaration should be != NULL */
          return current_fb_type_name;
      }
      return NULL;
    }

/**************************************/
/* B.1.5 - Program organization units */
/**************************************/
/***********************/
/* B 1.5.1 - Functions */
/***********************/
    void *visit(function_declaration_c *symbol) {
      /* no need to search through all the body, so we only
       * visit the variable declarations...!
       */
      return symbol->var_declarations_list->accept(*this);
    }

/*****************************/
/* B 1.5.2 - Function Blocks */
/*****************************/
    void *visit(function_block_declaration_c *symbol) {
      /* no need to search through all the body, so we only
       * visit the variable declarations...!
       */
      return symbol->var_declarations->accept(*this);
    }

/**********************/
/* B 1.5.3 - Programs */
/**********************/
    void *visit(program_declaration_c *symbol) {
      /* no need to search through all the body, so we only
       * visit the variable declarations...!
       */
      return symbol->var_declarations->accept(*this);
    }
};




