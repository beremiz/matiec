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

/* Determine the data type of a specific variable instance, including
 * function block instances.
 * A reference to the relevant variable declaration is returned.
 * The variable instance may NOT be a member of a structure of a memeber
 * of a structure of an element of an array of ...
 *
 * example:
 *    window.points[1].coordinate.x
 *    window.points[1].colour
 *    etc... ARE NOT ALLOWED!
 *
 * This class must only be passed the name of the variable that will appear
 * in the variable declaration. In the above examples, this would be
 *   'window' !!
 *
 *
 * If you need to pass a complete name of a variable instance (such as
 * 'window.points[1].coordinate.x') use the search_varfb_instance_type_c instead!
 */
/* Note that current_type_decl that this class returns may reference the
 * name of a type, or the type declaration itself!
 * For an example of the first, consider a variable declared as ...
 * x : AAA;
 * where the AAA type is previously declared as whatever.
 * For an example of the second, consider a variable declared as ...
 * x : array of int [10];  ---->  is allowed
 *
 * If it is the first, we will return a reference to the name, if the second
 * we return a reference to the declaration!!
 */
class search_var_instance_decl_c: public search_visitor_c {

  private:
    symbol_c *search_scope;
    symbol_c *search_name;
    symbol_c *current_type_decl;

  public:
    search_var_instance_decl_c(symbol_c *search_scope) {
      this->search_scope = search_scope;
      this->search_name = NULL;
      this->current_type_decl = NULL;
    }

    symbol_c *get_decl(symbol_c *variable_instance_name) {
      this->search_name = variable_instance_name;
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
/* edge -> The F_EDGE or R_EDGE directive */
// SYM_REF2(edge_declaration_c, edge, var1_list)
// TODO

/* var1_list is one of the following...
 *    simple_spec_init_c *
 *    subrange_spec_init_c *
 *    enumerated_spec_init_c *
 */
// SYM_REF2(var1_init_decl_c, var1_list, spec_init)
    void *visit(var1_init_decl_c *symbol) {
      current_type_decl = symbol->spec_init;
      return symbol->var1_list->accept(*this);
    }

/* var1_list ',' variable_name */
// SYM_LIST(var1_list_c)
    void *visit(var1_list_c *symbol) {
      list_c *list = symbol;
      for(int i = 0; i < list->n; i++) {
        if (compare_identifiers(list->elements[i], search_name) == 0)
	  /* by now, current_type_decl should be != NULL */
          return current_type_decl;
      }
      return NULL;
    }

/* name_list ':' function_block_type_name ASSIGN structure_initialization */
/* structure_initialization -> may be NULL ! */
    void *visit(fb_name_decl_c *symbol) {
      current_type_decl = symbol->function_block_type_name;
      return symbol->fb_name_list->accept(*this);
    }

/* name_list ',' fb_name */
    void *visit(fb_name_list_c *symbol) {
      list_c *list = symbol;
      for(int i = 0; i < list->n; i++) {
        if (compare_identifiers(list->elements[i], search_name) == 0)
	  /* by now, current_fb_declaration should be != NULL */
          return current_type_decl;
      }
      return NULL;
    }

/* var1_list ':' array_spec_init */
// SYM_REF2(array_var_init_decl_c, var1_list, array_spec_init)
    void *visit(array_var_init_decl_c *symbol) {
      current_type_decl = symbol->array_spec_init;
      return symbol->var1_list->accept(*this);
    }

/*  var1_list ':' initialized_structure */
// SYM_REF2(structured_var_init_decl_c, var1_list, initialized_structure)
    void *visit(structured_var_init_decl_c *symbol) {
      current_type_decl = symbol->initialized_structure;
      return symbol->var1_list->accept(*this);
    }

/*  var1_list ':' array_specification */
// SYM_REF2(array_var_declaration_c, var1_list, array_specification)
    void *visit(array_var_declaration_c *symbol) {
      current_type_decl = symbol->array_specification;
      return symbol->var1_list->accept(*this);
    }

/*  var1_list ':' structure_type_name */
// SYM_REF2(structured_var_declaration_c, var1_list, structure_type_name)
    void *visit(structured_var_declaration_c *symbol) {
      current_type_decl = symbol->structure_type_name;
      return symbol->var1_list->accept(*this);
    }

/*  [variable_name] location ':' located_var_spec_init */
/* variable_name -> may be NULL ! */
// SYM_REF4(located_var_decl_c, variable_name, location, located_var_spec_init, unused)
// TODO!!

/*  global_var_name ':' (simple_specification|subrange_specification|enumerated_specification|array_specification|prev_declared_structure_type_name|function_block_type_name */
// SYM_REF2(external_declaration_c, global_var_name, specification)
    void *visit(external_declaration_c *symbol) {
      if (compare_identifiers(symbol->global_var_name, search_name) == 0)
          return symbol->specification;
      return NULL;
    }

/*| global_var_spec ':' [located_var_spec_init|function_block_type_name] */
/* type_specification ->may be NULL ! */
// SYM_REF2(global_var_decl_c, global_var_spec, type_specification)
// TODO!!

/*| global_var_name location */
// SYM_REF2(global_var_spec_c, global_var_name, location)
// TODO!!

/*  AT direct_variable */
// SYM_REF2(location_c, direct_variable, unused)
// TODO!!

/*| global_var_list ',' global_var_name */
// SYM_LIST(global_var_list_c)
// TODO!!

/*  var1_list ':' single_byte_string_spec */
// SYM_REF2(single_byte_string_var_declaration_c, var1_list, single_byte_string_spec)
    void *visit(single_byte_string_var_declaration_c *symbol) {
      current_type_decl = symbol->single_byte_string_spec;
      return symbol->var1_list->accept(*this);
    }

/*  STRING ['[' integer ']'] [ASSIGN single_byte_character_string] */
/* integer ->may be NULL ! */
/* single_byte_character_string ->may be NULL ! */
// SYM_REF2(single_byte_string_spec_c, integer, single_byte_character_string)
// TODO!!

/*  var1_list ':' double_byte_string_spec */
// SYM_REF2(double_byte_string_var_declaration_c, var1_list, double_byte_string_spec)
    void *visit(double_byte_string_var_declaration_c *symbol) {
      current_type_decl = symbol->double_byte_string_spec;
      return symbol->var1_list->accept(*this);
    }

/*  WSTRING ['[' integer ']'] [ASSIGN double_byte_character_string] */
/* integer ->may be NULL ! */
/* double_byte_character_string ->may be NULL ! */
// SYM_REF2(double_byte_string_spec_c, integer, double_byte_character_string)
// TODO!!

/*  variable_name incompl_location ':' var_spec */
// SYM_REF4(incompl_located_var_decl_c, variable_name, incompl_location, var_spec, unused)
// TODO!!

/*  AT incompl_location_token */
// SYM_TOKEN(incompl_location_c)
// TODO!!


/**************************************/
/* B.1.5 - Program organization units */
/**************************************/
/***********************/
/* B 1.5.1 - Functions */
/***********************/
// SYM_REF4(function_declaration_c, derived_function_name, type_name, var_declarations_list, function_body)
    void *visit(function_declaration_c *symbol) {
      /* functions have a variable named after themselves, to store
       * the variable that will be returned!!
       */
      if (compare_identifiers(symbol->derived_function_name, search_name) == 0)
          return symbol->type_name;

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


#if 0
/*********************/
/* B 1.4 - Variables */
/*********************/
SYM_REF2(symbolic_variable_c, var_name, unused)

/********************************************/
/* B.1.4.1   Directly Represented Variables */
/********************************************/
SYM_TOKEN(direct_variable_c)

/*************************************/
/* B.1.4.2   Multi-element Variables */
/*************************************/
/*  subscripted_variable '[' subscript_list ']' */
SYM_REF2(array_variable_c, subscripted_variable, subscript_list)

/* subscript_list ',' subscript */
SYM_LIST(subscript_list_c)

/*  record_variable '.' field_selector */
/*  WARNING: input and/or output variables of function blocks
 *           may be accessed as fields of a tructured variable!
 *           Code handling a structured_variable_c must take
 *           this into account!
 */
SYM_REF2(structured_variable_c, record_variable, field_selector)


#endif
};





