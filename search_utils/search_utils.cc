/*
 * (c) 2009 Mario de Sousa
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


/*
 * This is the main stage 3a file.
 *
 * In stage 3a some helpful symbol tables are instanciated and populated.
 * These symbol tables wll then be used by stage3b and atage4 code generators.
 */






// #include <stdio.h>  /* required for NULL */
#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <list>
#include <strings.h>

#include "../util/symtable.hh"
#include "../util/dsymtable.hh"
#include "../absyntax/visitor.hh"



//#define DEBUG
#ifdef DEBUG
#define TRACE(classname) printf("\n____%s____\n",classname);
#else
#define TRACE(classname)
#endif

#define ERROR error_exit(__FILE__,__LINE__)
/* function defined in main.cc */
extern void error_exit(const char *file_name, int line_no);





/* A symbol table with all globally declared functions... */
function_declaration_c null_symbol1(NULL,NULL,NULL,NULL);
dsymtable_c<function_declaration_c *, &null_symbol1> function_symtable;

/* A symbol table with all globally declared functions block types... */
function_block_declaration_c null_symbol2(NULL,NULL,NULL);
symtable_c<function_block_declaration_c *, &null_symbol2> function_block_type_symtable;

/* A symbol table with all globally declared program types... */
program_declaration_c null_symbol3(NULL,NULL,NULL);
symtable_c<program_declaration_c *, &null_symbol3> program_type_symtable;

/* A symbol table with all user declared type definitions... */
/* Note that function block types and program types have their
 * own symbol tables, so do not get placed in this symbol table!
 */
symbol_c null_symbol4;
symtable_c<symbol_c *, &null_symbol4> type_symtable;



/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

/*
#include "spec_init_separator.cc"
#include "function_param_iterator.cc"
#include "function_call_iterator.cc"
#include "function_call_param_iterator.cc"
#include "type_initial_value.cc"
#include "search_fb_instance_decl.cc"
#include "search_fb_typedecl.cc"
#include "search_base_type.cc"
#include "search_var_instance_decl.cc"
#include "decompose_var_instance_name.cc"
#include "search_varfb_instance_type.cc"
#include "search_constant_type.cc"
#include "search_expression_type.cc"

#include "generate_c_base.cc"
#include "generate_c_typedecl.cc"
#include "generate_c_sfcdecl.cc"
#include "generate_c_vardecl.cc"
#include "generate_c_configbody.cc"
#include "generate_location_list.cc"
#include "generate_var_list.cc"
*/

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


class populate_symtables_c: public iterator_visitor_c {

  public:
    populate_symtables_c(void) {};
    virtual ~populate_symtables_c(void) {}


  public:

/*************************/
/* B.1 - Common elements */
/*************************/
/*******************************************/
/* B 1.1 - Letters, digits and identifiers */
/*******************************************/
/*********************/
/* B 1.2 - Constants */
/*********************/
/******************************/
/* B 1.2.1 - Numeric Literals */
/******************************/
/*******************************/
/* B.1.2.2   Character Strings */
/*******************************/
/***************************/
/* B 1.2.3 - Time Literals */
/***************************/
/************************/
/* B 1.2.3.1 - Duration */
/************************/
/************************************/
/* B 1.2.3.2 - Time of day and Date */
/************************************/
/**********************/
/* B.1.3 - Data types */
/**********************/
/***********************************/
/* B 1.3.1 - Elementary Data Types */
/***********************************/
/********************************/
/* B.1.3.2 - Generic data types */
/********************************/
/********************************/
/* B 1.3.3 - Derived data types */
/********************************/

/*  subrange_type_name ':' subrange_spec_init */
void *visit(subrange_type_declaration_c *symbol) {
  TRACE("subrange_type_declaration_c");  
  type_symtable.insert(symbol->subrange_type_name, symbol->subrange_spec_init);
  return NULL;
}


/*  enumerated_type_name ':' enumerated_spec_init */
void *visit(enumerated_type_declaration_c *symbol) {
  TRACE("enumerated_type_declaration_c");
  type_symtable.insert(symbol->enumerated_type_name, symbol->enumerated_spec_init);
  return NULL;
}


/*  identifier ':' array_spec_init */
void *visit(array_type_declaration_c *symbol) {
  TRACE("array_type_declaration_c");
  type_symtable.insert(symbol->identifier, symbol->array_spec_init);
  return NULL;
}


/*  simple_type_name ':' simple_spec_init */
void *visit(simple_type_declaration_c *symbol) {
  TRACE("simple_type_declaration_c");
  type_symtable.insert(symbol->simple_type_name, symbol->simple_spec_init);
  return NULL;
}


/*  structure_type_name ':' structure_specification */
void *visit(structure_type_declaration_c *symbol) {
  TRACE("structure_type_declaration_c");
  type_symtable.insert(symbol->structure_type_name, symbol->structure_specification);
  return NULL;
}



/*********************/
/* B 1.4 - Variables */
/*********************/
/********************************************/
/* B.1.4.1   Directly Represented Variables */
/********************************************/
/*************************************/
/* B.1.4.2   Multi-element Variables */
/*************************************/
/******************************************/
/* B 1.4.3 - Declaration & Initialisation */
/******************************************/
/**************************************/
/* B.1.5 - Program organization units */
/**************************************/
/***********************/
/* B 1.5.1 - Functions */
/***********************/
public:
/*   FUNCTION derived_function_name ':' elementary_type_name io_OR_function_var_declarations_list function_body END_FUNCTION */
/* | FUNCTION derived_function_name ':' derived_type_name io_OR_function_var_declarations_list function_body END_FUNCTION */
void *visit(function_declaration_c *symbol) {
  TRACE("function_declaration_c");
  function_symtable.insert(symbol->derived_function_name, symbol);

  /* symbol->derived_function_name->accept(*this);  */ /* Function name */
  /* symbol->type_name->accept(*this);              */ /* return data type */
  /* symbol->var_declarations_list->accept(*this);  */ /* Function parameters and variables */
  /* symbol->function_body->accept(*this);          */ /* Function body */
  return NULL;
}


/*****************************/
/* B 1.5.2 - Function Blocks */
/*****************************/
public:
/*  FUNCTION_BLOCK derived_function_block_name io_OR_other_var_declarations function_block_body END_FUNCTION_BLOCK */
//SYM_REF4(function_block_declaration_c, fblock_name, var_declarations, fblock_body, unused)
void *visit(function_block_declaration_c *symbol) {
  TRACE("function_block_declaration_c");
  function_block_type_symtable.insert(symbol->fblock_name, symbol);
/*
  symbol->fblock_name->accept(*this);
  symbol->var_declarations->accept(*this);
  symbol->fblock_body->accept(*this);
*/
  return NULL;
}


/**********************/
/* B 1.5.3 - Programs */
/**********************/
public:
/*  PROGRAM program_type_name program_var_declarations_list function_block_body END_PROGRAM */
//SYM_REF4(program_declaration_c, program_type_name, var_declarations, function_block_body, unused)
void *visit(program_declaration_c *symbol) {
  TRACE("program_declaration_c");
  program_type_symtable.insert(symbol->program_type_name, symbol);
/*
  symbol->program_type_name->accept(*this);
  symbol->var_declarations->accept(*this);
  symbol->function_block_body->accept(*this);
*/
  return NULL;
}

}; /* populate_symtables_c */





void search_utils_init(symbol_c *tree_root) {
  populate_symtables_c populate_symbols;

  tree_root->accept(populate_symbols);
}
