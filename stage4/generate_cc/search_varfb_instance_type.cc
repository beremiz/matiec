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



/* Determine the data type of a variable.
 * The variable may be a simple variable, a function block instance, a
 * struture element within a data structured type (a struct or a fb), or
 * an array element.
 * A mixture of array element of a structure element of a structure element
 * of a .... is also suported!
 *
 * A reference to the relevant base type __definition__ is returned.
 * This means that if we find that the variable is of type MY_INT,
 * which was previously declared to be
 * TYPE MY_INT: INT := 9;
 * this class wil return INT, and __not__ MY_INT !!
 *
 *
 *  example:
 *    window.points[1].coordinate.x
 *    window.points[1].colour
 *    etc... ARE ALLOWED!
 *
 * This class must be passed the scope within which the
 * variable was declared, and the variable name...
 */
class search_varfb_instance_type_c: public search_base_type_c {
  private:
    search_var_instance_decl_c search_var_instance_decl;
    decompose_var_instance_name_c *decompose_var_instance_name;
    symbol_c *current_structelement_name;

  public:
    search_varfb_instance_type_c(symbol_c *search_scope): search_var_instance_decl(search_scope) {
      this->decompose_var_instance_name = NULL;
      this->current_structelement_name = NULL;
    }


    symbol_c *get_type(symbol_c *variable_name) {
      this->current_structelement_name = NULL;
      this->decompose_var_instance_name = new decompose_var_instance_name_c(variable_name);
      if (NULL == decompose_var_instance_name) ERROR;

      /* find the part of the variable name that will appear in the
       * variable declaration, for e.g., in window.point.x, this would be
       * window!
       */
      symbol_c *var_name_part = decompose_var_instance_name->next_part();
      if (NULL == var_name_part) ERROR;

      /* Now we try to find the variable instance declaration, to determine its type... */
      symbol_c *var_decl = search_var_instance_decl.get_decl(var_name_part);
      if (NULL == var_decl) {
        /* variable instance declaration not found! */
 	return NULL;
      }

      /* if it is a struct or function block, we must search the type
       * of the struct or function block member.
       * This is done by this class visiting the var_decl.
       * This class, while visiting, will recursively call
       * decompose_var_instance_name->get_next() when and if required...
       */
      symbol_c *res = (symbol_c *)var_decl->accept(*this);
      if (NULL == res) ERROR;

      /* make sure that we have decomposed all strcuture elements of the variable name */
      symbol_c *var_name = decompose_var_instance_name->next_part();
      if (NULL != var_name) ERROR;

      return res;
    }

  private:
    /* a helper function... */
    void *visit_list(list_c *list)	{
      if (NULL == current_structelement_name) ERROR;

      for(int i = 0; i < list->n; i++) {
        void *res = list->elements[i]->accept(*this);
        if (res != NULL)
          return res;
      }
      /* not found! */
      return NULL;
    }

    /* a helper function... */
    void *base_type(symbol_c *symbol)	{
        search_base_type_c search_base_type;
	return symbol->accept(search_base_type);
    }


  private:
    /* We override the base class' visitor to identifier_c.
     * This is so because the base class does not consider a function block
     * to be a type, unlike this class that allows a variable instance
     * of a function block type...
     */
    void *visit(identifier_c *type_name) {
      /* look up the type declaration... */
      symbol_c *fb_decl = function_block_type_symtable.find_value(type_name);
      if (fb_decl != function_block_type_symtable.end_value())
        /* Type declaration found!! */
	return fb_decl->accept(*this);

      /* No. It is not a function block, so we let
       * the base class take care of it...
       */
      return search_base_type_c::visit(type_name);
    }

/********************************/
/* B 1.3.3 - Derived data types */
/********************************/
/*  structure_type_name ':' structure_specification */
    void *visit(structure_type_declaration_c *symbol) {
      return symbol->structure_specification->accept(*this);
      /* NOTE: structure_specification will point to either a
       *       initialized_structure_c
       *       OR A
       *       structure_element_declaration_list_c
       */
    }

/* structure_type_name ASSIGN structure_initialization */
/* structure_initialization may be NULL ! */
// SYM_REF2(initialized_structure_c, structure_type_name, structure_initialization)
    void *visit(initialized_structure_c *symbol)	{
      /* make sure that we have decomposed all strcuture elements of the variable name */
      symbol_c *var_name = decompose_var_instance_name->next_part();
      if (NULL == var_name) {
        /* this is it... !
	  * No need to look any further...
	 */
	/* NOTE: we could simply do a
	 *   return (void *)symbol;
	 *       nevertheless, note that this search_varfb_instance_type_c
	 *       class inherits from the search_base_type_c class,
	 *       which means that it will usually return the base type,
	 *       and not the derived type (*). If we are to be consistent,
	 *       we should guarantee that we always return the base type.
	 *       To do this we could use
	 *   return (void *)symbol->accept(*this);
	 *       since this class inherits from the search_base_type_c.
	 *       However, in this case we don't want it to follow
	 *       the structs as this search_varfb_instance_type_c does.
	 *       We therefore have to create a new search_base_type_c
	 *       instance to search through this type without going
	 *       through the structs...
	 */
        return base_type(symbol->structure_type_name);
      }

      /* now search the structure declaration */
      current_structelement_name = var_name;
      /* recursively find out the data type of var_name... */
      return symbol->structure_type_name->accept(*this);
    }

/* helper symbol for structure_declaration */
/* structure_declaration:  STRUCT structure_element_declaration_list END_STRUCT */
/* structure_element_declaration_list structure_element_declaration ';' */
    void *visit(structure_element_declaration_list_c *symbol)	{return visit_list(symbol);}

/*  structure_element_name ':' spec_init */
    void *visit(structure_element_declaration_c *symbol) {
      if (NULL == current_structelement_name) ERROR;

      if (compare_identifiers(symbol->structure_element_name, current_structelement_name) == 0)
        return symbol->spec_init->accept(*this);

      return NULL;
    }

/* helper symbol for structure_initialization */
/* structure_initialization: '(' structure_element_initialization_list ')' */
/* structure_element_initialization_list ',' structure_element_initialization */
    void *visit(structure_element_initialization_list_c *symbol) {ERROR; return NULL;} /* should never get called... */
/*  structure_element_name ASSIGN value */
    void *visit(structure_element_initialization_c *symbol) {ERROR; return NULL;} /* should never get called... */



/**************************************/
/* B.1.5 - Program organization units */
/**************************************/
/*****************************/
/* B 1.5.2 - Function Blocks */
/*****************************/
/*  FUNCTION_BLOCK derived_function_block_name io_OR_other_var_declarations function_block_body END_FUNCTION_BLOCK */
// SYM_REF4(function_block_declaration_c, fblock_name, var_declarations, fblock_body, unused)
    void *visit(function_block_declaration_c *symbol) {
      /* make sure that we have decomposed all strcuture elements of the variable name */

      symbol_c *var_name = decompose_var_instance_name->next_part();
      if (NULL == var_name) {
        /* this is it... !
	 * No need to look any further...
	 * Note also that, unlike for the struct types, a function block may
	 * not be defined based on another (i.e. no inheritance is allowed),
	 * so this function block is already the most base type.
	 * We simply return it.
	 */
	return (void *)symbol;
      }

      /* now search the function block declaration for the variable... */
      search_var_instance_decl_c search_decl(symbol);
      symbol_c *var_decl = search_decl.get_decl(var_name);
      if (NULL == var_decl) {
        /* variable instance declaration not found! */
 	return NULL;
      }

      /* We have found the declaration.
       * Should we look any further?
       */
      var_name = decompose_var_instance_name->next_part();
      if (NULL == var_name) {
        /* this is it... ! */
	return base_type(var_decl);
      }

      current_structelement_name = var_name;
      /* recursively find out the data type of var_name... */
      return symbol->var_declarations->accept(*this);
    }

};





