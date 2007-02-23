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


/*
 * This is one of the versions available for the 4th stage.
 *
 * This 4th stage generates a c++ source program equivalent
 * to the IL and ST code.
 */






// #include <stdio.h>  /* required for NULL */
#include <string>
#include <iostream>
#include <typeinfo>

#include "../../util/symtable.hh"
#include "../../util/dsymtable.hh"
#include "../../absyntax/visitor.hh"

#include "../stage4.hh"








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
function_block_declaration_c null_symbol2(NULL,NULL,NULL,NULL);
symtable_c<function_block_declaration_c *, &null_symbol2> function_block_type_symtable;

/* A symbol table with all globally declared program types... */
program_declaration_c null_symbol3(NULL,NULL,NULL,NULL);
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


/* returns 0 if the names are equal!! */
/* NOTE: it must ignore case!! */
static int compare_identifiers(symbol_c *ident1, symbol_c *ident2) {

  identifier_c *name1 = dynamic_cast<identifier_c *>(ident1);
  identifier_c *name2 = dynamic_cast<identifier_c *>(ident2);

  if ((name1 == NULL) || (name2 == NULL))
    /* invalid identifiers... */
    return -1;

  if (strcasecmp(name1->value, name2->value) == 0)
    return 0;

  /* identifiers do not match! */
  return 1;
}


/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

/* Unlike Programs and Configurations which get mapped onto C++ classes,
 * Function Blocks are mapped onto a C structure containing the variables, and
 * a C function containing the code in the FB's body. This is to allow direct allocation
 * of a FB variable (which is really an instance of the C data structure) to
 * a member of a union variable (note that classes with constructors cannot
 * be mebers of a union), which is done in IL when loading a FB onto IL's
 * default variable.
 *
 * So as not to clash the names of the C data structure and the C function,
 * the C structure is given a name identical to that of the FB name, whereas
 * the name of the function is the FB name with a constant string appended.
 * The value of that constant string which is appended is defined in the following
 * constant.
 * In order not to clash with any variable in the IL and ST source codem the
 * following constant should contain a double underscore, which is not allowed
 * in IL and ST.
 *
 * e.g.:  FUNTION_BLOCK TEST
 * is mapped onto a TEST data structure, and a TEST_body__ function.
 */

#define FB_FUNCTION_SUFFIX "_body__"

/* The FB body function is passed as the only parameter a pointer to the FB data
 * structure instance. The name of this parameter is given by the following cosntant.
 * In order not to clash with any variable in the IL and ST source codem the
 * following constant should contain a double underscore, which is not allowed
 * in IL and ST.
 *
 * e.g.: the body of FUNTION_BLOCK TEST
 * is mapped onto the C function
 *  TEST_body__(TEST *data__)
 */

#define FB_FUNCTION_PARAM "data__"


/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


#include "spec_init_separator.cc"
#include "function_param_iterator.cc"
#include "function_call_iterator.cc"
#include "function_call_param_iterator.cc"
#include "type_initial_value.cc"
#include "search_fb_instance_decl.cc"
#include "search_base_type.cc"
#include "search_var_instance_decl.cc"
#include "decompose_var_instance_name.cc"
#include "search_varfb_instance_type.cc"
#include "search_constant_type.cc"
#include "search_expression_type.cc"

#include "generate_cc_base.cc"
#include "generate_cc_sfcdecl.cc"
#include "generate_cc_typedecl.cc"
#include "generate_cc_vardecl.cc"
#include "generate_cc_configbody.cc"

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

/* Generate a name for a temporary variable.
 * Each new name generated is appended a different number,
 * starting off from 0.
 * After calling reset(), the names will start off again from 0.
 */
#define VAR_LEADER "__"
#define TEMP_VAR VAR_LEADER "TMP_"
#define SOURCE_VAR VAR_LEADER "SRC_"

#include "generate_cc_tempvardecl.cc"

#include "generate_cc_st.cc"
#include "generate_cc_il.cc"

#include "generate_cc.hh"



/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

/* A helper class that knows how to generate code for both the IL and ST languages... */
class generate_cc_SFC_IL_ST_c: public null_visitor_c {
  private:
    stage4out_c *s4o_ptr;
    symbol_c *scope;
    const char *variable_prefix;

  public:
    generate_cc_SFC_IL_ST_c(stage4out_c *s4o_ptr, symbol_c *scope, const char *variable_prefix = NULL);
    /*********************************************/
    /* B.1.6  Sequential function chart elements */
    /*********************************************/
    
    /*| sequential_function_chart sfc_network*/
    void *visit(sequential_function_chart_c * symbol);
    
    /****************************************/
    /* B.2 - Language IL (Instruction List) */
    /****************************************/
    
    /***********************************/
    /* B 2.1 Instructions and Operands */
    /***********************************/
    /*| instruction_list il_instruction */
    void *visit(instruction_list_c *symbol);
    
    /* Remainder implemented in generate_cc_il_c... */
    
    /***************************************/
    /* B.3 - Language ST (Structured Text) */
    /***************************************/
    /***********************/
    /* B 3.1 - Expressions */
    /***********************/
    /* Implemented in generate_cc_st_c */
    
    /********************/
    /* B 3.2 Statements */
    /********************/
    void *visit(statement_list_c *symbol);

/* Remainder implemented in generate_cc_st_c... */
};

#include "generate_cc_sfc.cc"

generate_cc_SFC_IL_ST_c::generate_cc_SFC_IL_ST_c(stage4out_c *s4o_ptr, symbol_c *scope, const char *variable_prefix) {
  if (NULL == scope) ERROR;
  this->s4o_ptr = s4o_ptr;
  this->scope = scope;
  this->variable_prefix = variable_prefix;
}

void *generate_cc_SFC_IL_ST_c::visit(sequential_function_chart_c * symbol) {
  generate_cc_sfc_c generate_cc_sfc(s4o_ptr, scope, variable_prefix);
  generate_cc_sfc.generate(symbol);
  return NULL;
}

void *generate_cc_SFC_IL_ST_c::visit(instruction_list_c *symbol) {
  generate_cc_il_c generate_cc_il(s4o_ptr, scope, variable_prefix);
  generate_cc_il.generate(symbol);
  return NULL;
}

void *generate_cc_SFC_IL_ST_c::visit(statement_list_c *symbol) {
  generate_cc_st_c generate_cc_st(s4o_ptr, scope, variable_prefix);
  generate_cc_st.generate(symbol);
  return NULL;
}




/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


class generate_cc_c: public generate_cc_typedecl_c {

  public:
    generate_cc_c(stage4out_c *s4o_ptr)
      : generate_cc_typedecl_c(s4o_ptr) {};
    virtual ~generate_cc_c(void) {}


  public:
/***************************/
/* B 0 - Programming Model */
/***************************/
void *visit(library_c *symbol) {
  TRACE("library_c");

  /* Insert the header... */
  s4o.print("/*******************************************/\n");
  s4o.print("/*     FILE GENERATED BY iec2cc            */\n");
  s4o.print("/* Editing this file is not recommended... */\n");
  s4o.print("/*******************************************/\n");
  s4o.print("\n\n\n\n\n");
  s4o.print("#include \"plciec.h\"\n");
  s4o.print("\n\n\n\n\n");

  /* now do the actual code... */
  print_list(symbol);
  s4o.print("\n\n");

  /* Finish off with the main() */
  s4o.print("#include \"plciec.cc\"\n");
  s4o.print("\n\n");

  // function_symtable.print();
  return NULL;
}

/*************************/
/* B.1 - Common elements */
/*************************/
/*******************************************/
/* B 1.1 - Letters, digits and identifiers */
/*******************************************/
  /* done in base class(es) */

/*********************/
/* B 1.2 - Constants */
/*********************/
  /* originally empty... */

/******************************/
/* B 1.2.1 - Numeric Literals */
/******************************/
  /* done in base class(es) */

/*******************************/
/* B.1.2.2   Character Strings */
/*******************************/
  /* done in base class(es) */

/***************************/
/* B 1.2.3 - Time Literals */
/***************************/
/************************/
/* B 1.2.3.1 - Duration */
/************************/
  /* done in base class(es) */

/************************************/
/* B 1.2.3.2 - Time of day and Date */
/************************************/
  /* done in base class(es) */

/**********************/
/* B.1.3 - Data types */
/**********************/
/***********************************/
/* B 1.3.1 - Elementary Data Types */
/***********************************/
  /* done in base class(es) */

/********************************/
/* B.1.3.2 - Generic data types */
/********************************/
  /* originally empty... */

/********************************/
/* B 1.3.3 - Derived data types */
/********************************/
  /* done in base class(es) */

/*********************/
/* B 1.4 - Variables */
/*********************/
  /* done in base class(es) */

/********************************************/
/* B.1.4.1   Directly Represented Variables */
/********************************************/
  /* done in base class(es) */

/*************************************/
/* B.1.4.2   Multi-element Variables */
/*************************************/
  /* done in base class(es) */

/******************************************/
/* B 1.4.3 - Declaration & Initialisation */
/******************************************/
  /* done in base class(es) */

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
  generate_cc_vardecl_c *vardecl;
  TRACE("function_declaration_c");

  /* start off by adding this declaration to the global
   * function declaration symbol table...
   */
  function_symtable.insert(symbol->derived_function_name, symbol);

  /* (A) Function declaration... */
  /* (A.1) Function return type */
  s4o.print("// FUNCTION\n");
  symbol->type_name->accept(*this); /* return type */
  s4o.print(" ");
  /* (A.2) Function name */
  symbol->derived_function_name->accept(*this);
  s4o.print("(");

  /* (A.3) Function parameters */
  s4o.indent_right();
  vardecl = new generate_cc_vardecl_c(&s4o,
  				      generate_cc_vardecl_c::finterface_vf,
  				      generate_cc_vardecl_c::input_vt |
				      generate_cc_vardecl_c::output_vt |
				      generate_cc_vardecl_c::inoutput_vt);
  vardecl->print(symbol->var_declarations_list);
  delete vardecl;
  s4o.indent_left();

  s4o.print(")\n" + s4o.indent_spaces + "{\n");

  /* (B) Function local variable declaration */
    /* (B.1) Variables declared in ST source code */
  s4o.indent_right();
  vardecl = new generate_cc_vardecl_c(&s4o, generate_cc_vardecl_c::localinit_vf, generate_cc_vardecl_c::private_vt);
  vardecl->print(symbol->var_declarations_list);
  delete vardecl;

    /* (B.2) Temporary variable for function's return value */
  /* It will have the same name as the function itself! */
  s4o.print(s4o.indent_spaces);
  symbol->type_name->accept(*this); /* return type */
  s4o.print(" ");
  symbol->derived_function_name->accept(*this);
  s4o.print(" = ");
  {
    /* get the default value of this variable's type */
    symbol_c *default_value = (symbol_c *)symbol->type_name->accept(*type_initial_value_c::instance());
    if (default_value == NULL) ERROR;
    default_value->accept(*this);
  }
  s4o.print(";\n\n");

  /* (C) Function body */
  generate_cc_SFC_IL_ST_c generate_cc_code(&s4o, symbol);
  symbol->function_body->accept(generate_cc_code);
  s4o.print(s4o.indent_spaces + "return ");
  symbol->derived_function_name->accept(*this);
  s4o.print(";\n");
  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "}\n\n\n");

  return NULL;
}


/* The remaining var_declarations_list_c, function_var_decls_c
 * and var2_init_decl_list_c are handled in the generate_cc_vardecl_c class
 */


/*****************************/
/* B 1.5.2 - Function Blocks */
/*****************************/
public:
/*  FUNCTION_BLOCK derived_function_block_name io_OR_other_var_declarations function_block_body END_FUNCTION_BLOCK */
//SYM_REF4(function_block_declaration_c, fblock_name, var_declarations, fblock_body, unused)
void *visit(function_block_declaration_c *symbol) {
  generate_cc_vardecl_c *vardecl;
  TRACE("function_block_declaration_c");

  /* start off by adding this declaration to the global
   * function block declaration symbol table...
   */
  function_block_type_symtable.insert(symbol->fblock_name, symbol);

  /* (A) Function Block data structure declaration... */
  /* (A.1) Data structure declaration */
  s4o.print("// FUNCTION_BLOCK ");
  symbol->fblock_name->accept(*this);
  s4o.print("\n// Data part\n");
  s4o.print("typedef struct {\n");
  s4o.indent_right();
  /* (A.2) Public variables: i.e. the function parameters... */
  s4o.print(s4o.indent_spaces + "// FB Interface - IN, OUT, IN_OUT variables\n");
  vardecl = new generate_cc_vardecl_c(&s4o,
  				      generate_cc_vardecl_c::local_vf,
  				      generate_cc_vardecl_c::input_vt |
  				      generate_cc_vardecl_c::output_vt |
  				      generate_cc_vardecl_c::inoutput_vt);
  vardecl->print(symbol->var_declarations);
  delete vardecl;
  s4o.print("\n");
  /* (A.3) Private internal variables */
  s4o.print(s4o.indent_spaces + "// FB private variables - TEMP, private and located variables\n");
  vardecl = new generate_cc_vardecl_c(&s4o,
  				      generate_cc_vardecl_c::local_vf,
				      generate_cc_vardecl_c::temp_vt |
  				      generate_cc_vardecl_c::private_vt |
  				      generate_cc_vardecl_c::located_vt);
  vardecl->print(symbol->var_declarations);
  delete vardecl;
  s4o.print("\n");

  /* (A.4) Function Block data structure type name. */
  s4o.indent_left();
  s4o.print("} ");
  symbol->fblock_name->accept(*this);
  s4o.print(";\n\n");


  /* (B) Function with FB body */
  /* (B.1) Function declaration */
  s4o.print("// Code part\n");
  /* function interface */
  s4o.print("void ");
  symbol->fblock_name->accept(*this);
  s4o.print(FB_FUNCTION_SUFFIX);
  s4o.print("(");
  /* first and only parameter is a pointer to the data */
  symbol->fblock_name->accept(*this);
  s4o.print(" *");
  s4o.print(FB_FUNCTION_PARAM);
  s4o.print(") {\n");
  s4o.indent_right();

  /* (B.2) Initialize TEMP variables */
  /* function body */
  s4o.print(s4o.indent_spaces + "// Initialise TEMP variables\n");
  vardecl = new generate_cc_vardecl_c(&s4o,
  				      generate_cc_vardecl_c::init_vf,
				      generate_cc_vardecl_c::temp_vt);
  vardecl->print(symbol->var_declarations, NULL,  FB_FUNCTION_PARAM"->");
  delete vardecl;
  s4o.print("\n");

  /* (B.3) Function code */
  generate_cc_SFC_IL_ST_c generate_cc_code(&s4o, symbol, FB_FUNCTION_PARAM"->");
  symbol->fblock_body->accept(generate_cc_code);
  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "} // ");
  symbol->fblock_name->accept(*this);
  s4o.print(FB_FUNCTION_SUFFIX);
  s4o.print(s4o.indent_spaces + "() \n\n");

  s4o.indent_left();
  s4o.print("\n\n\n\n");

  return NULL;
}


/* The remaining temp_var_decls_c, temp_var_decls_list_c
 * and non_retentive_var_decls_c are handled in the generate_cc_vardecl_c class
 */


/**********************/
/* B 1.5.3 - Programs */
/**********************/



public:
/*  PROGRAM program_type_name program_var_declarations_list function_block_body END_PROGRAM */
//SYM_REF4(program_declaration_c, program_type_name, var_declarations, function_block_body, unused)
void *visit(program_declaration_c *symbol) {
  generate_cc_vardecl_c *vardecl;
  TRACE("program_declaration_c");

  /* start off by adding this declaration to the global
   * program declaration symbol table...
   */
  program_type_symtable.insert(symbol->program_type_name, symbol);

  /* (A) Program data structure declaration... */
  /* (A.1) Data structure declaration */
  s4o.print("// PROGRAM ");
  symbol->program_type_name->accept(*this);
  s4o.print("\n// Data part\n");
  s4o.print("typedef struct {\n");
  s4o.indent_right();

  /* (A.2) Public variables: i.e. the program parameters... */
  s4o.print(s4o.indent_spaces + "// PROGRAM Interface - IN, OUT, IN_OUT variables\n");
  vardecl = new generate_cc_vardecl_c(&s4o,
  				      generate_cc_vardecl_c::local_vf,
  				      generate_cc_vardecl_c::input_vt |
  				      generate_cc_vardecl_c::output_vt |
  				      generate_cc_vardecl_c::inoutput_vt);
  vardecl->print(symbol->var_declarations);
  delete vardecl;
  s4o.print("\n");
  /* (A.3) Private internal variables */
  s4o.print(s4o.indent_spaces + "// PROGRAM private variables - TEMP, private and located variables\n");
  vardecl = new generate_cc_vardecl_c(&s4o,
                generate_cc_vardecl_c::local_vf,
                generate_cc_vardecl_c::temp_vt |
                generate_cc_vardecl_c::private_vt |
                generate_cc_vardecl_c::located_vt |
                generate_cc_vardecl_c::external_vt);
  vardecl->print(symbol->var_declarations);
  delete vardecl;
  s4o.print("\n");

  /* (A.4) Generate private internal variables for SFC*/
  generate_cc_sfcdecl_c generate_cc_sfcdecl(&s4o);
  symbol->function_block_body->accept(generate_cc_sfcdecl);

  /* (A.5) Program data structure type name. */
  s4o.indent_left();
  s4o.print("} ");
  symbol->program_type_name->accept(*this);
  s4o.print(";\n\n");

  /* (B) Function with PROGRAM body */
  /* (B.1) Function declaration */
  s4o.print("// Code part\n");
  /* function interface */
  s4o.print("void ");
  symbol->program_type_name->accept(*this);
  s4o.print(FB_FUNCTION_SUFFIX);
  s4o.print("(");
  /* first and only parameter is a pointer to the data */
  symbol->program_type_name->accept(*this);
  s4o.print(" *");
  s4o.print(FB_FUNCTION_PARAM);
  s4o.print(") {\n");
  s4o.indent_right();

  /* (B.2) Initialize TEMP variables */
  /* function body */
  s4o.print(s4o.indent_spaces + "// Initialise TEMP variables\n");
  vardecl = new generate_cc_vardecl_c(&s4o,
  				      generate_cc_vardecl_c::init_vf,
				      generate_cc_vardecl_c::temp_vt);
  vardecl->print(symbol->var_declarations, NULL,  FB_FUNCTION_PARAM"->");
  delete vardecl;
  s4o.print("\n");

  /* (B.3) Function code */
  generate_cc_SFC_IL_ST_c generate_cc_code(&s4o, symbol, FB_FUNCTION_PARAM"->");
  symbol->function_block_body->accept(generate_cc_code);
  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "} // ");
  symbol->program_type_name->accept(*this);
  s4o.print(FB_FUNCTION_SUFFIX);
  s4o.print(s4o.indent_spaces + "() \n\n");

  s4o.indent_left();
  s4o.print("\n\n\n\n");

  return NULL;
}


/* intermediate helper symbol for program_declaration_c */
/*  { io_var_declarations | other_var_declarations }   */
/*
 * NOTE: we re-use the var_declarations_list_c
 */

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/

/********************************/
/* B 1.7 Configuration elements */
/********************************/


public:
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
void *visit(configuration_declaration_c *symbol) {
  static int configuration_count = 0;
  generate_cc_vardecl_c *vardecl;
  TRACE("configuration_declaration_c");

  configuration_count++;
  if (configuration_count == 1) {
    /* the first configuration is the one we will use!! */
    s4o.print("#define __configuration_c ");
    symbol->configuration_name->accept(*this);
    s4o.print("\n" + s4o.indent_spaces);
  }

  /* (A) Class (__configuration) declaration... */
  /* (A.1) configuration name in comment */
  s4o.print("// CONFIGURATION\n" + s4o.indent_spaces);
  s4o.print("class ");
  symbol->configuration_name->accept(*this);
  s4o.print(" {\n");
  s4o.indent_right();

  /* (A.2) Global variables
   *    AND
   * (A.3) Programs in the Configuration
   */
  /* Programs types are mapped onto classes,
   * and programs are then instantiated inside the configuration
   * as objects of the appropriate class!
   */
  s4o.print(s4o.indent_spaces + "private:\n");
  s4o.indent_right();
  vardecl = new generate_cc_vardecl_c(&s4o,
  				      generate_cc_vardecl_c::local_vf,
  				      generate_cc_vardecl_c::global_vt |
				      generate_cc_vardecl_c::program_vt |
  				      generate_cc_vardecl_c::resource_vt);
  vardecl->print(symbol);
  delete vardecl;
  s4o.indent_left();
  s4o.print("\n");



  /* (B) Constructor */
  /* (B.1) Constructor name... */
  s4o.print(s4o.indent_spaces + "public:\n");
  s4o.indent_right();
  s4o.print(s4o.indent_spaces);
  symbol->configuration_name->accept(*this);
  s4o.print("(void)\n");

  /* (B.2) Member initializations... */
  s4o.indent_right();
  s4o.print(s4o.indent_spaces);
  vardecl = new generate_cc_vardecl_c(&s4o,
  				      generate_cc_vardecl_c::constructorinit_vf,
				      generate_cc_vardecl_c::program_vt |
  				      generate_cc_vardecl_c::global_vt |
  				      generate_cc_vardecl_c::resource_vt);
  vardecl->print(symbol);
  delete vardecl;

  /* (B.3) Constructor Body... */
  s4o.print("\n" + s4o.indent_spaces + "{}\n\n");
  s4o.indent_left();
  s4o.indent_left();

  /* (C) Public Function*/
  /* (C.1) Public Function declaration */
  s4o.print(s4o.indent_spaces + "public:\n");
  s4o.indent_right();
  s4o.print(s4o.indent_spaces + "void run(void) {\n");

  /* (C.2) Public Function body */
  /* Invoke each program in the configuration */
  s4o.indent_right();
  generate_cc_configbody_c *configbody = new generate_cc_configbody_c(&s4o);
  symbol->accept(*configbody);
  delete configbody;
  s4o.indent_left();

  /* (C.3) Close Public Function body */
  s4o.print(s4o.indent_spaces + "} /* f() */\n\n");
  s4o.indent_left();

  /* (D) Close the class declaration... */
  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "}; /* class ");
  symbol->configuration_name->accept(*this);
  s4o.print(" */\n\n\n");

  return NULL;
}







#if 0

/* helper symbol for configuration_declaration */
SYM_LIST(resource_declaration_list_c)

/*
RESOURCE resource_name ON resource_type_name
   optional_global_var_declarations
   single_resource_declaration
END_RESOURCE
*/
SYM_REF4(resource_declaration_c, resource_name, resource_type_name, global_var_declarations, resource_declaration)

/* task_configuration_list program_configuration_list */
SYM_REF2(single_resource_declaration_c, task_configuration_list, program_configuration_list)

/* helper symbol for single_resource_declaration */
SYM_LIST(task_configuration_list_c)

/* helper symbol for single_resource_declaration */
SYM_LIST(program_configuration_list_c)

/* helper symbol for
 *  - access_path
 *  - instance_specific_init
 */
SYM_LIST(any_fb_name_list_c)

/*  [resource_name '.'] global_var_name ['.' structure_element_name] */
SYM_REF4(global_var_reference_c, resource_name, global_var_name, structure_element_name, unused)

/*  prev_declared_program_name '.' symbolic_variable */
SYM_REF2(program_output_reference_c, program_name, symbolic_variable)

/*  TASK task_name task_initialization */
SYM_REF2(task_configuration_c, task_name, task_initialization)

/*  '(' [SINGLE ASSIGN data_source ','] [INTERVAL ASSIGN data_source ','] PRIORITY ASSIGN integer ')' */
SYM_REF4(task_initialization_c, single_data_source, interval_data_source, priority_data_source, unused)

/*  PROGRAM [RETAIN | NON_RETAIN] program_name [WITH task_name] ':' program_type_name ['(' prog_conf_elements ')'] */
SYM_REF6(program_configuration_c, retain_option, program_name, task_name, program_type_name, prog_conf_elements, unused)

/* prog_conf_elements ',' prog_conf_element */
SYM_LIST(prog_conf_elements_c)

/*  fb_name WITH task_name */
SYM_REF2(fb_task_c, fb_name, task_name)

/*  any_symbolic_variable ASSIGN prog_data_source */
SYM_REF2(prog_cnxn_assign_c, symbolic_variable, prog_data_source)

/* any_symbolic_variable SENDTO data_sink */
SYM_REF2(prog_cnxn_sendto_c, symbolic_variable, prog_data_source)

/* VAR_CONFIG instance_specific_init_list END_VAR_BOGUS */
SYM_REF2(instance_specific_initializations_c, instance_specific_init_list, unused)

/* helper symbol for instance_specific_initializations */
SYM_LIST(instance_specific_init_list_c)

/* resource_name '.' program_name '.' {fb_name '.'}
    ((variable_name [location] ':' located_var_spec_init) | (fb_name ':' fb_initialization))
*/
SYM_REF6(instance_specific_init_c, resource_name, program_name, any_fb_name_list, variable_name, location, initialization)

/* helper symbol for instance_specific_init */
/* function_block_type_name ':=' structure_initialization */
SYM_REF2(fb_initialization_c, function_block_type_name, structure_initialization)

#endif


}; /* generate_cc_c */



/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/




visitor_c *new_code_generator(stage4out_c *s4o)  {return new generate_cc_c(s4o);}
void delete_code_generator(visitor_c *code_generator) {delete code_generator;}


