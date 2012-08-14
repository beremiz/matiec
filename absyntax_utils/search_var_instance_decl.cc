/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2003-2011  Mario de Sousa (msousa@fe.up.pt)
 *  Copyright (C) 2007-2011  Laurent Bessard and Edouard Tisserant
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

/* Determine the data type of a specific variable instance, including
 * function block instances.
 * A reference to the relevant variable declaration is returned.
 * The variable instance may NOT be a member of a structure of a member
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
#include "absyntax_utils.hh"


search_var_instance_decl_c::search_var_instance_decl_c(symbol_c *search_scope) {
  this->current_vartype = none_vt;
  this->search_scope = search_scope;
  this->search_name = NULL;
  this->current_type_decl = NULL;
}

symbol_c *search_var_instance_decl_c::get_decl(symbol_c *variable_instance_name) {
  this->current_vartype = none_vt;
  this->search_name = variable_instance_name;
  return (symbol_c *)search_scope->accept(*this);
}

unsigned int search_var_instance_decl_c::get_vartype(void) {
  return current_vartype;
}

/***************************/
/* B 0 - Programming Model */
/***************************/
void *search_var_instance_decl_c::visit(library_c *symbol) {
  /* we do not want to search multiple declaration scopes,
   * so we do not visit all the functions, function blocks, etc...
   */
  return NULL;
}



/******************************************/
/* B 1.4.3 - Declaration & Initialization */
/******************************************/

/* edge -> The F_EDGE or R_EDGE directive */
// SYM_REF2(edge_declaration_c, edge, var1_list)
// TODO

void *search_var_instance_decl_c::visit(input_declarations_c *symbol) {
  current_vartype = input_vt;
  void *res = symbol->input_declaration_list->accept(*this);
  if (res == NULL) {
    current_vartype = none_vt;
  }
  return res;
}

/* VAR_OUTPUT [RETAIN | NON_RETAIN] var_init_decl_list END_VAR */
/* option -> may be NULL ! */
void *search_var_instance_decl_c::visit(output_declarations_c *symbol) {
  current_vartype = output_vt;
  void *res = symbol->var_init_decl_list->accept(*this);
  if (res == NULL) {
    current_vartype = none_vt;
  }
  return res;
}

/*  VAR_IN_OUT var_declaration_list END_VAR */
void *search_var_instance_decl_c::visit(input_output_declarations_c *symbol) {
  current_vartype = inoutput_vt;
  void *res = symbol->var_declaration_list->accept(*this);
  if (res == NULL) {
    current_vartype = none_vt;
  }
  return res;
}

/* ENO : BOOL */
void *search_var_instance_decl_c::visit(eno_param_declaration_c *symbol) {
  if (compare_identifiers(symbol->name, search_name) == 0)
    return symbol->type;
  return NULL;
}


/* VAR [CONSTANT] var_init_decl_list END_VAR */
/* option -> may be NULL ! */
/* helper symbol for input_declarations */
void *search_var_instance_decl_c::visit(var_declarations_c *symbol) {
  current_vartype = private_vt;
  void *res = symbol->var_init_decl_list->accept(*this);
  if (res == NULL) {
    current_vartype = none_vt;
  }
  return res;
}

/*  VAR RETAIN var_init_decl_list END_VAR */
void *search_var_instance_decl_c::visit(retentive_var_declarations_c *symbol) {
  current_vartype = private_vt;
  void *res = symbol->var_init_decl_list->accept(*this);
  if (res == NULL) {
    current_vartype = none_vt;
  }
  return res;
}

/*  VAR [CONSTANT|RETAIN|NON_RETAIN] located_var_decl_list END_VAR */
/* option -> may be NULL ! */
//SYM_REF2(located_var_declarations_c, option, located_var_decl_list)
void *search_var_instance_decl_c::visit(located_var_declarations_c *symbol) {
  current_vartype = located_vt;
  void *res = symbol->located_var_decl_list->accept(*this);
  if (res == NULL) {
    current_vartype = none_vt;
  }
  return res;
}

/*| VAR_EXTERNAL [CONSTANT] external_declaration_list END_VAR */
/* option -> may be NULL ! */
//SYM_REF2(external_var_declarations_c, option, external_declaration_list)
void *search_var_instance_decl_c::visit(external_var_declarations_c *symbol) {
  current_vartype = external_vt;
  void *res = symbol->external_declaration_list->accept(*this);
  if (res == NULL) {
    current_vartype = none_vt;
  }
  return res;
}

/*| VAR_GLOBAL [CONSTANT|RETAIN] global_var_decl_list END_VAR */
/* option -> may be NULL ! */
//SYM_REF2(global_var_declarations_c, option, global_var_decl_list)
void *search_var_instance_decl_c::visit(global_var_declarations_c *symbol) {
  current_vartype = global_vt;
  void *res = symbol->global_var_decl_list->accept(*this);
  if (res == NULL) {
    current_vartype = none_vt;
  }
  return res;
}

/* var1_list is one of the following...
 *    simple_spec_init_c *
 *    subrange_spec_init_c *
 *    enumerated_spec_init_c *
 */
// SYM_REF2(var1_init_decl_c, var1_list, spec_init)
void *search_var_instance_decl_c::visit(var1_init_decl_c *symbol) {
  current_type_decl = symbol->spec_init;
  return symbol->var1_list->accept(*this);
}

/* var1_list ',' variable_name */
// SYM_LIST(var1_list_c)
void *search_var_instance_decl_c::visit(var1_list_c *symbol) {
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
void *search_var_instance_decl_c::visit(fb_name_decl_c *symbol) {
  current_type_decl = symbol->function_block_type_name;
  return symbol->fb_name_list->accept(*this);
}

/* name_list ',' fb_name */
void *search_var_instance_decl_c::visit(fb_name_list_c *symbol) {
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
void *search_var_instance_decl_c::visit(array_var_init_decl_c *symbol) {
  current_type_decl = symbol->array_spec_init;
  return symbol->var1_list->accept(*this);
}

/*  var1_list ':' initialized_structure */
// SYM_REF2(structured_var_init_decl_c, var1_list, initialized_structure)
void *search_var_instance_decl_c::visit(structured_var_init_decl_c *symbol) {
  current_type_decl = symbol->initialized_structure;
  return symbol->var1_list->accept(*this);
}

/*  var1_list ':' array_specification */
// SYM_REF2(array_var_declaration_c, var1_list, array_specification)
void *search_var_instance_decl_c::visit(array_var_declaration_c *symbol) {
  current_type_decl = symbol->array_specification;
  return symbol->var1_list->accept(*this);
}

/*  var1_list ':' structure_type_name */
// SYM_REF2(structured_var_declaration_c, var1_list, structure_type_name)
void *search_var_instance_decl_c::visit(structured_var_declaration_c *symbol) {
  current_type_decl = symbol;
  return symbol->var1_list->accept(*this);
}

/*  [variable_name] location ':' located_var_spec_init */
/* variable_name -> may be NULL ! */
// SYM_REF4(located_var_decl_c, variable_name, location, located_var_spec_init, unused)
// TODO!!

/*  global_var_name ':' (simple_specification|subrange_specification|enumerated_specification|array_specification|prev_declared_structure_type_name|function_block_type_name */
// SYM_REF2(external_declaration_c, global_var_name, specification)
void *search_var_instance_decl_c::visit(external_declaration_c *symbol) {
  if (compare_identifiers(symbol->global_var_name, search_name) == 0)
      return symbol->specification;
  return NULL;
}

/*| global_var_spec ':' [located_var_spec_init|function_block_type_name] */
/* type_specification ->may be NULL ! */
// SYM_REF2(global_var_decl_c, global_var_spec, type_specification)
void *search_var_instance_decl_c::visit(global_var_decl_c *symbol) {
  if (symbol->type_specification != NULL) {
    current_type_decl = symbol->type_specification;
    return symbol->global_var_spec->accept(*this);
  }
  else
    return NULL;
}

/*| global_var_name location */
//SYM_REF2(global_var_spec_c, global_var_name, location)
void *search_var_instance_decl_c::visit(global_var_spec_c *symbol) {
  if (symbol->global_var_name != NULL && compare_identifiers(symbol->global_var_name, search_name) == 0)
      return current_type_decl;
  else
    return symbol->location->accept(*this);
}

/*| global_var_list ',' global_var_name */
//SYM_LIST(global_var_list_c)
void *search_var_instance_decl_c::visit(global_var_list_c *symbol) {
  list_c *list = symbol;
  for(int i = 0; i < list->n; i++) {
    if (compare_identifiers(list->elements[i], search_name) == 0)
      /* by now, current_type_decl should be != NULL */
      return current_type_decl;
  }
  return NULL;
}

/*  [variable_name] location ':' located_var_spec_init */
/* variable_name -> may be NULL ! */
//SYM_REF4(located_var_decl_c, variable_name, location, located_var_spec_init, unused)
void *search_var_instance_decl_c::visit(located_var_decl_c *symbol) {
  if (symbol->variable_name != NULL && compare_identifiers(symbol->variable_name, search_name) == 0)
    return symbol->located_var_spec_init;
  else {
    current_type_decl = symbol->located_var_spec_init;
    return symbol->location->accept(*this);
  }
}

/*| global_var_spec ':' [located_var_spec_init|function_block_type_name] */
/* type_specification ->may be NULL ! */
// SYM_REF2(global_var_decl_c, global_var_spec, type_specification)
// TODO!!

/*  AT direct_variable */
// SYM_REF2(location_c, direct_variable, unused)
void *search_var_instance_decl_c::visit(location_c *symbol) {
  if (compare_identifiers(symbol->direct_variable, search_name) == 0)
    return current_type_decl;
  else
    return NULL;
}
        
/*| global_var_list ',' global_var_name */
// SYM_LIST(global_var_list_c)
// TODO!!

/*  var1_list ':' single_byte_string_spec */
// SYM_REF2(single_byte_string_var_declaration_c, var1_list, single_byte_string_spec)
void *search_var_instance_decl_c::visit(single_byte_string_var_declaration_c *symbol) {
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
void *search_var_instance_decl_c::visit(double_byte_string_var_declaration_c *symbol) {
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
void *search_var_instance_decl_c::visit(function_declaration_c *symbol) {
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
void *search_var_instance_decl_c::visit(function_block_declaration_c *symbol) {
  /* no need to search through all the body, so we only
   * visit the variable declarations...!
   */
  return symbol->var_declarations->accept(*this);
}

/**********************/
/* B 1.5.3 - Programs */
/**********************/
void *search_var_instance_decl_c::visit(program_declaration_c *symbol) {
  /* no need to search through all the body, so we only
   * visit the variable declarations...!
   */
  return symbol->var_declarations->accept(*this);
}


/********************************/
/* B 1.7 Configuration elements */
/********************************/

/*
CONFIGURATION configuration_name
   optional_global_var_declarations
   (resource_declaration_list | single_resource_declaration)
   optional_access_declarations
   optional_instance_specific_initializations
END_CONFIGURATION
*/
/*
SYM_REF6(configuration_declaration_c, configuration_name, global_var_declarations, resource_declarations, access_declarations, instance_specific_initializations, unused)
*/
void *search_var_instance_decl_c::visit(configuration_declaration_c *symbol) {
  /* no need to search through all the configuration, so we only
   * visit the global variable declarations...!
   */
  if (symbol->global_var_declarations != NULL)
    return symbol->global_var_declarations->accept(*this);
  else
    return NULL;
}

/*
RESOURCE resource_name ON resource_type_name
   optional_global_var_declarations
   single_resource_declaration
END_RESOURCE
*/
// SYM_REF4(resource_declaration_c, resource_name, resource_type_name, global_var_declarations, resource_declaration)
void *search_var_instance_decl_c::visit(resource_declaration_c *symbol) {
  /* no need to search through all the resource, so we only
   * visit the global variable declarations...!
   */
  if (symbol->global_var_declarations != NULL)
    return symbol->global_var_declarations->accept(*this);
  else
    return NULL;
}

/* task_configuration_list program_configuration_list */
// SYM_REF2(single_resource_declaration_c, task_configuration_list, program_configuration_list)
void *search_var_instance_decl_c::visit(single_resource_declaration_c *symbol) {
  /* no need to search through all the resource,
   * and there is no global variable declarations...!
   */
  return NULL;
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



};
#endif
