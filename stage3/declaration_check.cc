/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2003-2012  Mario de Sousa (msousa@fe.up.pt)
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


/* Declaration sequence is a source code part needed to declare variables.
 * There are some checks we need to do before start with other analysis:
 *
 *   - Check external option redefinition.
 *   - Check external data type redefinition.
 *   - Check initial values consistently with the data types of the variables/data types being declared.
 *   - Check whether a function block uses a CONSTANT qualifier as described in 2.5.2.1.
 *
 */


#include "declaration_check.hh"
#include "datatype_functions.hh"

#define FIRST_(symbol1, symbol2) (((symbol1)->first_order < (symbol2)->first_order)   ? (symbol1) : (symbol2))
#define  LAST_(symbol1, symbol2) (((symbol1)->last_order  > (symbol2)->last_order)    ? (symbol1) : (symbol2))

#define STAGE3_ERROR(error_level, symbol1, symbol2, ...) {                                                                  \
  if (current_display_error_level >= error_level) {                                                                         \
    fprintf(stderr, "%s:%d-%d..%d-%d: error: ",                                                                             \
            FIRST_(symbol1,symbol2)->first_file, FIRST_(symbol1,symbol2)->first_line, FIRST_(symbol1,symbol2)->first_column,\
                                                 LAST_(symbol1,symbol2) ->last_line,  LAST_(symbol1,symbol2) ->last_column);\
    fprintf(stderr, __VA_ARGS__);                                                                                           \
    fprintf(stderr, "\n");                                                                                                  \
    error_count++;                                                                                                     \
  }                                                                                                                         \
}


#define STAGE3_WARNING(symbol1, symbol2, ...) {                                                                             \
    fprintf(stderr, "%s:%d-%d..%d-%d: warning: ",                                                                           \
            FIRST_(symbol1,symbol2)->first_file, FIRST_(symbol1,symbol2)->first_line, FIRST_(symbol1,symbol2)->first_column,\
                                                 LAST_(symbol1,symbol2) ->last_line,  LAST_(symbol1,symbol2) ->last_column);\
    fprintf(stderr, __VA_ARGS__);                                                                                           \
    fprintf(stderr, "\n");                                                                                                  \
    warning_found = true;                                                                                                   \
}


declaration_check_c::declaration_check_c(symbol_c *ignore) {
  current_display_error_level = 0;
  current_pou_decl = NULL;
  current_resource_decl = NULL;
  error_count = 0;
}

declaration_check_c::~declaration_check_c(void) {

}

int declaration_check_c::get_error_count() {
  return error_count;
}

void declaration_check_c::check_global_decl(symbol_c *p_decl) {
  if (NULL == current_pou_decl) ERROR;
  
  search_var_instance_decl_c search_var_instance_pou_glo_decl(current_pou_decl);
  search_var_instance_decl_c search_var_instance_res_glo_decl(current_resource_decl);
  search_var_instance_decl_c search_var_instance_ext_decl(p_decl);
  function_param_iterator_c  fpi(p_decl);
  
  symbol_c *var_name;
  while((var_name = fpi.next()) != NULL) {
    if (fpi.param_direction() == function_param_iterator_c::direction_extref) {
      /* found an external reference parameter. */
      symbol_c *ext_decl = search_var_instance_ext_decl.get_decl(var_name);
      
      // NOTE: Must check the POU first, and RESOURCE second!
      symbol_c                                       *glo_decl =  search_var_instance_res_glo_decl.get_decl(var_name);           
      search_var_instance_decl_c *search_var_instance_glo_decl = &search_var_instance_res_glo_decl;
      if (NULL == glo_decl) {
        glo_decl                     =  search_var_instance_pou_glo_decl.get_decl(var_name);
        search_var_instance_glo_decl = &search_var_instance_pou_glo_decl;
      }
      
      if (NULL == glo_decl) {
        STAGE3_ERROR(0, ext_decl, ext_decl, "Declaration error. The external variable does not match with any global variable.");
        continue;
      }
      
      /* Check whether variable's constness (CONSTANT) is compatible.
       *        VAR_GLOBAL is contant     => VAR_EXTERNAL must also be CONSTANT
       *        VAR_GLOBAL is not contant => VAR_EXTERNAL may be CONSTANT, or not!
       */
      search_var_instance_decl_c::opt_t ext_opt = search_var_instance_ext_decl. get_option(var_name);
      search_var_instance_decl_c::opt_t glo_opt = search_var_instance_glo_decl->get_option(var_name);
      if ((glo_opt == search_var_instance_decl_c::constant_opt) && (ext_opt != search_var_instance_decl_c::constant_opt))
        STAGE3_ERROR(0, glo_decl, glo_decl, "Declaration error. The external variable must be declared as constant, as it maps to a constant global variable.");

      /* TODO: Check redefinition data type.
       *       We need a new class (like search_base_type class) to get type id by variable declaration.
       *  symbol_c *glo_type = ????;
       *  symbol_c *ext_type = fpi.param_type();
       */
      /* For the moment, we will just use search_base_type_c instead... */
      symbol_c *glo_type = search_base_type_c::get_basetype_decl(glo_decl);
      symbol_c *ext_type = search_base_type_c::get_basetype_decl(ext_decl);
      if (! get_datatype_info_c::is_type_equal(glo_type, ext_type))
        STAGE3_ERROR(0, ext_decl, ext_decl, "Declaration error.  Data type mismatch between external and global variable declarations.");
    }
  }
}



/*****************************/
/* B 1.5.2 - Function Blocks */
/*****************************/
/*  FUNCTION_BLOCK derived_function_block_name io_OR_other_var_declarations function_block_body END_FUNCTION_BLOCK */
// SYM_REF3(function_block_declaration_c, fblock_name, var_declarations, fblock_body)
void *declaration_check_c::visit(function_block_declaration_c *symbol) {
  /* The following two lines of code are only valid for v3 of IEC 61131-3, that allows VAR_GLOBAL declarations inside FBs!
   * current_pou_decl = symbol;  
   * current_resource_decl = NULL;  
   */
  /* check if any FB declared as a VAR has any incompatible VAR_EXTERNAL declarations */
  if (NULL != symbol->var_declarations)
    symbol->var_declarations->accept(*this);
  return NULL;
}

/******************************************/
/* B 1.5.3 - Declaration & Initialisation */
/******************************************/
/*  PROGRAM program_type_name program_var_declarations_list function_block_body END_PROGRAM */
// SYM_REF3(program_declaration_c, program_type_name, var_declarations, function_block_body)
void *declaration_check_c::visit(program_declaration_c *symbol) {
  /* The following two lines of code are only valid for v3 of IEC 61131-3, that allows VAR_GLOBAL declarations inside PROGRAMs!
   * current_pou_decl = symbol;  
   * current_resource_decl = NULL;  
   */
  /* check if any FB declared as a VAR has any incompatible VAR_EXTERNAL declarations */
  if (NULL != symbol->var_declarations)
    symbol->var_declarations->accept(*this);
  return NULL;
}

/********************************/
/* B 1.7 Configuration elements */
/********************************/
/*
 * CONFIGURATION configuration_name
 *    optional_global_var_declarations
 *    (resource_declaration_list | single_resource_declaration)
 *    optional_access_declarations
 *    optional_instance_specific_initializations
 * END_CONFIGURATION
 */
//SYM_REF5(configuration_declaration_c, configuration_name, global_var_declarations, resource_declarations, access_declarations, instance_specific_initializations)
void *declaration_check_c::visit(configuration_declaration_c *symbol) {
  current_pou_decl = symbol;
  /* check if any FB declared as a VAR has any incompatible VAR_EXTERNAL declarations */
  if (NULL != symbol->resource_declarations)
    symbol->resource_declarations->accept(*this);
  current_pou_decl = NULL;
  return NULL;
}

/*
RESOURCE resource_name ON resource_type_name
   optional_global_var_declarations
   single_resource_declaration
END_RESOURCE
*/
/* enumvalue_symtable is filled in by enum_declaration_check_c, during stage3 semantic verification, with a list of all enumerated constants declared inside this POU */
// SYM_REF4(resource_declaration_c, resource_name, resource_type_name, global_var_declarations, resource_declaration, enumvalue_symtable_t enumvalue_symtable;)
void *declaration_check_c::visit(resource_declaration_c *symbol) {
  current_resource_decl = symbol;
  /* check if any FB declared as a VAR has any incompatible VAR_EXTERNAL declarations */
  symbol->resource_declaration->accept(*this);
  current_resource_decl = NULL;  
  return NULL;
}

/*  PROGRAM [RETAIN | NON_RETAIN] program_name [WITH task_name] ':' program_type_name ['(' prog_conf_elements ')'] */
void *declaration_check_c::visit(program_configuration_c *symbol) {
  symbol_c *p_decl = program_type_symtable.find_value(symbol->program_type_name);
  if (p_decl == program_type_symtable.end_value())
    p_decl = function_block_type_symtable.find_value(symbol->program_type_name);
  /* stage1_2 guarantees that we are sure to find a declaration in FB or Program symtable. */
  if (p_decl == function_block_type_symtable.end_value())
    ERROR;
  check_global_decl(p_decl);
  return NULL;
}

