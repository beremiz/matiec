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
#include <sstream>
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

  token_c *name1 = dynamic_cast<token_c *>(ident1);
  token_c *name2 = dynamic_cast<token_c *>(ident2);
  
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

/* Idem as body, but for initializer FB function */
#define FB_INIT_SUFFIX "_init__"

/* Idem as body, but for run CONFIG and RESOURCE function */
#define FB_RUN_SUFFIX "_run__"

/* The FB body function is passed as the only parameter a pointer to the FB data
 * structure instance. The name of this parameter is given by the following constant.
 * In order not to clash with any variable in the IL and ST source codem the
 * following constant should contain a double underscore, which is not allowed
 * in IL and ST.
 *
 * e.g.: the body of FUNTION_BLOCK TEST
 * is mapped onto the C function
 *  TEST_body__(TEST *data__)
 */

#define FB_FUNCTION_PARAM "data__"


#define SFC_STEP_ACTION_PREFIX "__SFC_"

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
#include "generate_location_list.cc"

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

#define MILLISECOND 1000000
#define SECOND 1000 * MILLISECOND

/* A helper class that knows how to generate code for both the IL and ST languages... */
class calculate_time_c: public iterator_visitor_c {
  private:
    unsigned long time;
    float current_value;
  
  public:
    calculate_time_c(void){time = 0;};
    
    unsigned long get_time(void) {return time;};

    void *get_integer_value(token_c *token) {
      std::string str = "";
      for (unsigned int i = 0; i < strlen(token->value); i++)
        if (token->value[i] != '_')
          str += token->value[i];
      current_value = atof(str.c_str());
      return NULL;
    }

    void *get_float_value(token_c *token) {
      current_value = atof(token->value);
      return NULL;
    }

/******************************/
/* B 1.2.1 - Numeric Literals */
/******************************/

    void *visit(integer_c *symbol) {return get_integer_value(symbol);}
    
/************************/
/* B 1.2.3.1 - Duration */
/************************/
  
    /* SYM_REF2(duration_c, neg, interval) */
    void *visit(duration_c *symbol) {
      if (symbol->neg != NULL)
        ERROR;
      symbol->interval->accept(*this);
      return NULL;
    }
    
    /* SYM_TOKEN(fixed_point_c) */
    void *visit(fixed_point_c *symbol) {return get_float_value(symbol);}
    
    /* SYM_REF2(days_c, days, hours) */
    void *visit(days_c *symbol) {
      if (symbol->hours)
        symbol->hours->accept(*this);
      symbol->days->accept(*this);
      time += (unsigned long)(current_value * 24 * 3600 * SECOND);
      return NULL;
    }
    
    /* SYM_REF2(hours_c, hours, minutes) */
    void *visit(hours_c *symbol) {
      if (symbol->minutes)
        symbol->minutes->accept(*this);
      symbol->hours->accept(*this);
      time += (unsigned long)(current_value * 3600 * SECOND);
      return NULL;
    }
    
    /* SYM_REF2(minutes_c, minutes, seconds) */
    void *visit(minutes_c *symbol) {
      if (symbol->seconds)
        symbol->seconds->accept(*this);
      symbol->minutes->accept(*this);
      time += (unsigned long)(current_value * 60 * SECOND);
      return NULL;
    }
    
    /* SYM_REF2(seconds_c, seconds, milliseconds) */
    void *visit(seconds_c *symbol) {
      if (symbol->milliseconds)
        symbol->milliseconds->accept(*this);
      symbol->seconds->accept(*this);
      time += (unsigned long)(current_value * SECOND);
      return NULL;
    }
    
    /* SYM_REF2(milliseconds_c, milliseconds, unused) */
    void *visit(milliseconds_c *symbol) {
      symbol->milliseconds->accept(*this);
      time += (unsigned long)(current_value * MILLISECOND);
      return NULL;
    }
};

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class calculate_common_ticktime_c: public iterator_visitor_c {
  private:
    unsigned long common_ticktime;
    
  public:
    calculate_common_ticktime_c(void){common_ticktime = 0;}
    
    unsigned long euclide(unsigned long a, unsigned long b) {
      unsigned long c = a % b;
      if (c == 0)
        return b;
      else
        return euclide(b, c);
    }
    
    void update_ticktime(unsigned long time) {
      if (common_ticktime == 0)
        common_ticktime = time;
      else if (time > common_ticktime)
        common_ticktime = euclide(time, common_ticktime);
      else
        common_ticktime = euclide(common_ticktime, time);
    }

    unsigned long get_ticktime(void) {
      return common_ticktime;
    }

/*  TASK task_name task_initialization */
//SYM_REF2(task_configuration_c, task_name, task_initialization)  
    void *visit(task_initialization_c *symbol) {
      calculate_time_c calculate_time;
      unsigned long time = 0;
      if (symbol->interval_data_source != NULL) {
        symbol->interval_data_source->accept(calculate_time);
        time = calculate_time.get_time();
      }
      if (time > 0)
        update_ticktime(time);
      return NULL;
    }
};    

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


class generate_cc_pous_c: public generate_cc_typedecl_c {

  public:
    generate_cc_pous_c(stage4out_c *s4o_ptr)
      : generate_cc_typedecl_c(s4o_ptr) {};
    virtual ~generate_cc_pous_c(void) {}


  public:

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
  				      generate_cc_vardecl_c::located_vt |
  				      generate_cc_vardecl_c::external_vt);
  vardecl->print(symbol->var_declarations);
  delete vardecl;
  s4o.print("\n");

  /* (A.4) Function Block data structure type name. */
  s4o.indent_left();
  s4o.print("} ");
  symbol->fblock_name->accept(*this);
  s4o.print(";\n\n");


  /* (B) Constructor */
  /* (B.1) Constructor name... */
  s4o.print(s4o.indent_spaces + "void ");
  symbol->fblock_name->accept(*this);
  s4o.print(FB_INIT_SUFFIX);
  s4o.print("(");

  /* first and only parameter is a pointer to the data */
  symbol->fblock_name->accept(*this);
  s4o.print(" *");
  s4o.print(FB_FUNCTION_PARAM);
  s4o.print(") {\n");
  s4o.indent_right();

  /* (B.2) Member initializations... */
  s4o.print(s4o.indent_spaces);
  vardecl = new generate_cc_vardecl_c(&s4o,
  				      generate_cc_vardecl_c::constructorinit_vf,
  				      generate_cc_vardecl_c::input_vt |
  				      generate_cc_vardecl_c::output_vt |
  				      generate_cc_vardecl_c::inoutput_vt |
  				      generate_cc_vardecl_c::private_vt |
				        generate_cc_vardecl_c::located_vt |
				        generate_cc_vardecl_c::external_vt);
  vardecl->print(symbol->var_declarations, NULL,  FB_FUNCTION_PARAM"->");
  delete vardecl;
  s4o.indent_left();
  s4o.print("\n" + s4o.indent_spaces + "}\n\n");

  
  /* (C) Function with FB body */
  /* (C.1) Function declaration */
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

  /* (C.2) Initialize TEMP variables */
  /* function body */
  s4o.print(s4o.indent_spaces + "// Initialise TEMP variables\n");
  vardecl = new generate_cc_vardecl_c(&s4o,
  				      generate_cc_vardecl_c::init_vf,
				      generate_cc_vardecl_c::temp_vt);
  vardecl->print(symbol->var_declarations, NULL,  FB_FUNCTION_PARAM"->");
  delete vardecl;
  s4o.print("\n");

  /* (C.3) Function code */
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
  /* (A.4) Generate private internal variables for SFC */
  generate_cc_sfctables_c generate_cc_sfctables(&s4o);
  symbol->function_block_body->accept(generate_cc_sfctables);
  s4o.print("\n");

  /* (A.5) Program data structure type name. */
  s4o.indent_left();
  s4o.print("} ");
  symbol->program_type_name->accept(*this);
  s4o.print(";\n\n");

  /* (B) Constructor */
  /* (B.1) Constructor name... */
  s4o.print(s4o.indent_spaces + "void ");
  symbol->program_type_name->accept(*this);
  s4o.print(FB_INIT_SUFFIX);
  s4o.print("(");

  /* first and only parameter is a pointer to the data */
  symbol->program_type_name->accept(*this);
  s4o.print(" *");
  s4o.print(FB_FUNCTION_PARAM);
  s4o.print(") {\n");
  s4o.indent_right();

  /* (B.2) Member initializations... */
  s4o.print(s4o.indent_spaces);
  vardecl = new generate_cc_vardecl_c(&s4o,
  				      generate_cc_vardecl_c::constructorinit_vf,
  				      generate_cc_vardecl_c::input_vt |
  				      generate_cc_vardecl_c::output_vt |
  				      generate_cc_vardecl_c::inoutput_vt |
  				      generate_cc_vardecl_c::private_vt |
  				      generate_cc_vardecl_c::located_vt |
				      generate_cc_vardecl_c::external_vt);
  vardecl->print(symbol->var_declarations, NULL,  FB_FUNCTION_PARAM"->");
  delete vardecl;
  s4o.indent_left();
  s4o.print("\n" + s4o.indent_spaces + "}\n\n");

  /* (C) Function with PROGRAM body */
  /* (C.1) Step and Action definitions */
  generate_cc_sfcdecl_c generate_cc_sfcdecl(&s4o);
  symbol->function_block_body->accept(generate_cc_sfcdecl);

  /* (C.2) Function declaration */
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

  /* (C.3) Initialize TEMP variables */
  /* function body */
  s4o.print(s4o.indent_spaces + "// Initialise TEMP variables\n");
  vardecl = new generate_cc_vardecl_c(&s4o,
  				      generate_cc_vardecl_c::init_vf,
				      generate_cc_vardecl_c::temp_vt);
  vardecl->print(symbol->var_declarations, NULL,  FB_FUNCTION_PARAM"->");
  delete vardecl;
  s4o.print("\n");

  /* (C.4) Function code */
  generate_cc_SFC_IL_ST_c generate_cc_code(&s4o, symbol, FB_FUNCTION_PARAM"->");
  symbol->function_block_body->accept(generate_cc_code);
  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "} // ");
  symbol->program_type_name->accept(*this);
  s4o.print(FB_FUNCTION_SUFFIX);
  s4o.print(s4o.indent_spaces + "() \n\n");

  /* (C.5) Step and Action undefinitions */
  generate_cc_sfcundecl_c generate_cc_sfcundecl(&s4o);
  symbol->function_block_body->accept(generate_cc_sfcundecl);

  s4o.indent_left();
  s4o.print("\n\n\n\n");

  return NULL;
}

}; /* generate_cc_pous_c */

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_cc_config_c: public generate_cc_typedecl_c {

    public:
    generate_cc_config_c(stage4out_c *s4o_ptr)
      : generate_cc_typedecl_c(s4o_ptr) {};
    virtual ~generate_cc_config_c(void) {}

    typedef enum {
      initprotos_dt,
      initdeclare_dt,
      runprotos_dt,
      rundeclare_dt
    } declaretype_t;

    declaretype_t wanted_declaretype;

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
  generate_cc_vardecl_c *vardecl;
  
  /* Insert the header... */
  s4o.print("/*******************************************/\n");
  s4o.print("/*     FILE GENERATED BY iec2cc            */\n");
  s4o.print("/* Editing this file is not recommended... */\n");
  s4o.print("/*******************************************/\n\n");
  s4o.print("#include \"plciec.h\"\n\n");
  
  /* (A) configuration declaration... */
  /* (A.1) configuration name in comment */
  s4o.print("// CONFIGURATION ");
  symbol->configuration_name->accept(*this);
  s4o.print("\n");
  
  /* (A.2) Global variables */
  vardecl = new generate_cc_vardecl_c(&s4o,
  				      generate_cc_vardecl_c::local_vf,
  				      generate_cc_vardecl_c::global_vt);
  vardecl->print(symbol);
  delete vardecl;
  s4o.print("\n");

  /* (B) Initialisation Function */
  /* (B.1) Ressources initialisation protos... */
  wanted_declaretype = initprotos_dt;
  symbol->resource_declarations->accept(*this);
  s4o.print("\n");
  
  /* (B.2) Initialisation function name... */
  s4o.print(s4o.indent_spaces + "void config");
  s4o.print(FB_INIT_SUFFIX);
  s4o.print("(void) {\n");
  s4o.indent_right();
  
  /* (B.3) Global variables initializations... */
  s4o.print(s4o.indent_spaces);
  vardecl = new generate_cc_vardecl_c(&s4o,
  				      generate_cc_vardecl_c::constructorinit_vf,
  				      generate_cc_vardecl_c::global_vt);
  vardecl->print(symbol);
  delete vardecl;
  s4o.print("\n");
  
  /* (B.3) Resources initializations... */
  wanted_declaretype = initdeclare_dt;
  symbol->resource_declarations->accept(*this);
  
  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "}\n\n");


  /* (C) Run Function*/
  /* (C.1) Resources run functions protos... */
  wanted_declaretype = runprotos_dt;
  symbol->resource_declarations->accept(*this);
  s4o.print("\n");

  /* (C.2) Run function name... */
  s4o.print(s4o.indent_spaces + "void config");
  s4o.print(FB_RUN_SUFFIX);
  s4o.print("(int tick) {\n");
  s4o.indent_right();

  /* (C.3) Resources initializations... */
  wanted_declaretype = rundeclare_dt;
  symbol->resource_declarations->accept(*this);

  /* (C.3) Close Public Function body */
  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "}\n");

  return NULL;
}

void *visit(resource_declaration_c *symbol) {
  if (wanted_declaretype == initprotos_dt || wanted_declaretype == runprotos_dt) {
    s4o.print(s4o.indent_spaces + "void ");
    symbol->resource_name->accept(*this);
    if (wanted_declaretype == initprotos_dt) {
      s4o.print(FB_INIT_SUFFIX);
      s4o.print("(void);\n");
    }
    else {
      s4o.print(FB_RUN_SUFFIX);
      s4o.print("(int tick);\n");
    }
  }
  if (wanted_declaretype == initdeclare_dt || wanted_declaretype == rundeclare_dt) {
    s4o.print(s4o.indent_spaces);
    symbol->resource_name->accept(*this);
    if (wanted_declaretype == initdeclare_dt) {
      s4o.print(FB_INIT_SUFFIX);
      s4o.print("();\n");
    }
    else {
      s4o.print(FB_RUN_SUFFIX);
      s4o.print("(tick);\n");
    }
  }
  return NULL;
}

void *visit(single_resource_declaration_c *symbol) {
  if (wanted_declaretype == initprotos_dt || wanted_declaretype == runprotos_dt) {
    s4o.print(s4o.indent_spaces + "void RESOURCE");
    if (wanted_declaretype == initprotos_dt) {
      s4o.print(FB_INIT_SUFFIX);
      s4o.print("(void);\n");
    }
    else {
      s4o.print(FB_RUN_SUFFIX);
      s4o.print("(int tick);\n");
    }
  }
  if (wanted_declaretype == initdeclare_dt || wanted_declaretype == rundeclare_dt) {
    s4o.print(s4o.indent_spaces + "RESOURCE");
    if (wanted_declaretype == initdeclare_dt) {
      s4o.print(FB_INIT_SUFFIX);
      s4o.print("();\n");
    }
    else {
      s4o.print(FB_RUN_SUFFIX);
      s4o.print("(tick);\n");
    }
  }
  return NULL;
}

};

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


class generate_cc_resources_c: public generate_cc_typedecl_c {

  search_var_instance_decl_c *search_config_instance;
  search_var_instance_decl_c *search_resource_instance;

  private:
    /* The name of the resource curretnly being processed... */
    symbol_c *current_resource_name;
    symbol_c *current_global_vars;

  public:
    generate_cc_resources_c(stage4out_c *s4o_ptr, symbol_c *config_scope, symbol_c *resource_scope, unsigned long time)
      : generate_cc_typedecl_c(s4o_ptr) {
      search_config_instance = new search_var_instance_decl_c(config_scope);
      search_resource_instance = new search_var_instance_decl_c(resource_scope);
      common_ticktime = time;
      current_resource_name = NULL;
      current_global_vars = NULL;
    };
    virtual ~generate_cc_resources_c(void) {
      delete search_config_instance;
      delete search_resource_instance;
    }

    typedef enum {
      declare_dt,
      init_dt,
      run_dt
    } declaretype_t;

    declaretype_t wanted_declaretype;

    unsigned long common_ticktime;
    
    const char *current_program_name;

    typedef enum {
      assign_at,
      send_at
    } assigntype_t;

    assigntype_t wanted_assigntype;

/********************************/
/* B 1.7 Configuration elements */
/********************************/

/*
RESOURCE resource_name ON resource_type_name
   optional_global_var_declarations
   single_resource_declaration
END_RESOURCE
*/
// SYM_REF4(resource_declaration_c, resource_name, resource_type_name, global_var_declarations, resource_declaration)
    void *visit(resource_declaration_c *symbol) {
      current_resource_name = symbol->resource_name;
      current_global_vars = symbol->global_var_declarations;
      
      symbol->resource_declaration->accept(*this);
      
      current_resource_name = NULL;
      current_global_vars = NULL;
      return NULL;
    }

/* task_configuration_list program_configuration_list */
// SYM_REF2(single_resource_declaration_c, task_configuration_list, program_configuration_list)
    void *visit(single_resource_declaration_c *symbol) {
    	bool single_resource = current_resource_name == NULL;
      if (single_resource)
        current_resource_name = new identifier_c("RESOURCE");
      generate_cc_vardecl_c *vardecl;
      
      /* Insert the header... */
      s4o.print("/*******************************************/\n");
      s4o.print("/*     FILE GENERATED BY iec2cc            */\n");
      s4o.print("/* Editing this file is not recommended... */\n");
      s4o.print("/*******************************************/\n\n");
      s4o.print("#include \"plciec.h\"\n\n");
      
      /* (A) resource declaration... */
      /* (A.1) resource name in comment */
      s4o.print("// RESOURCE ");
      current_resource_name->accept(*this);
      s4o.print("\n");
       
      /* (A.2) POUs inclusion */
      s4o.print("#include \"POUS.c\"\n\n");
      
      /* (A.3) Global variables... */
      if (current_global_vars != NULL) {
        vardecl = new generate_cc_vardecl_c(&s4o,
                      generate_cc_vardecl_c::local_vf,
                      generate_cc_vardecl_c::global_vt);
        vardecl->print(current_global_vars);
        delete vardecl;
      }
      s4o.print("\n");
      
      /* (A.4) Resource programs declaration... */
      wanted_declaretype = declare_dt;
      symbol->program_configuration_list->accept(*this);
      s4o.print("\n");
      
      /* (B) resource initialisation function... */
      /* (B.1) initialisation function name... */
      s4o.print("void ");
      current_resource_name->accept(*this);
      s4o.print(FB_INIT_SUFFIX);
      s4o.print("(void) {\n");
      s4o.indent_right();
      
      /* (B.2) Global variables initialisations... */
      if (current_global_vars != NULL) {
        s4o.print(s4o.indent_spaces);
        vardecl = new generate_cc_vardecl_c(&s4o,
                      generate_cc_vardecl_c::constructorinit_vf,
                      generate_cc_vardecl_c::global_vt);
        vardecl->print(current_global_vars);
        delete vardecl;
      }
      s4o.print("\n");
      
      /* (B.3) Resource programs initialisations... */
      wanted_declaretype = init_dt;
      symbol->program_configuration_list->accept(*this);
      
      s4o.indent_left();
      s4o.print("}\n\n");
      
      /* (C) Resource run function... */
      /* (C.1) Run function name... */
      s4o.print("void ");
      current_resource_name->accept(*this);
      s4o.print(FB_RUN_SUFFIX);
      s4o.print("(int tick) {\n");
      s4o.indent_right();
      
      /* (C.2) Task management... */
      symbol->task_configuration_list->accept(*this);
      
      /* (C.3) Program run declaration... */
      wanted_declaretype = run_dt;
      symbol->program_configuration_list->accept(*this);
      
      s4o.indent_left();
      s4o.print("}\n\n");
      
      if (single_resource)
        delete current_resource_name;
      return NULL;
    }
    
/*  PROGRAM [RETAIN | NON_RETAIN] program_name [WITH task_name] ':' program_type_name ['(' prog_conf_elements ')'] */
//SYM_REF6(program_configuration_c, retain_option, program_name, task_name, program_type_name, prog_conf_elements, unused)
    void *visit(program_configuration_c *symbol) {
      if (wanted_declaretype == declare_dt) {
        s4o.print(s4o.indent_spaces);
        symbol->program_type_name->accept(*this);
        s4o.print(" ");
        symbol->program_name->accept(*this);
        s4o.print(";\n");
      }
      if (wanted_declaretype == init_dt) {
        s4o.print(s4o.indent_spaces);
        symbol->program_type_name->accept(*this);
        s4o.print(FB_INIT_SUFFIX);
        s4o.print("(&");
        symbol->program_name->accept(*this);
        s4o.print(");\n");
      }
      if (wanted_declaretype == run_dt) {
        current_program_name = ((identifier_c*)(symbol->program_name))->value;
        if (symbol->task_name != NULL) {
          s4o.print(s4o.indent_spaces);
          s4o.print("if (");
          symbol->task_name->accept(*this);
          s4o.print(" == 0) {\n");
          s4o.indent_right(); 
        }
        
        wanted_assigntype = assign_at;
        symbol->prog_conf_elements->accept(*this);
        
        s4o.print(s4o.indent_spaces);
        symbol->program_type_name->accept(*this);
        s4o.print(FB_FUNCTION_SUFFIX);
        s4o.print("(&");
        symbol->program_name->accept(*this);
        s4o.print(");\n");
        
        wanted_assigntype = send_at;
        symbol->prog_conf_elements->accept(*this);
        
        if (symbol->task_name != NULL) {
          s4o.indent_left();
          s4o.print(s4o.indent_spaces + "}\n");
        }
      }
      return NULL;
    }
    
/*  TASK task_name task_initialization */
//SYM_REF2(task_configuration_c, task_name, task_initialization)
    void *visit(task_configuration_c *symbol) {
      s4o.print(s4o.indent_spaces + "int ");
      symbol->task_name->accept(*this);
      s4o.print(" = ");
      symbol->task_initialization->accept(*this);
      s4o.print(";\n");
      return NULL;
    }
    
/*  '(' [SINGLE ASSIGN data_source ','] [INTERVAL ASSIGN data_source ','] PRIORITY ASSIGN integer ')' */
//SYM_REF4(task_initialization_c, single_data_source, interval_data_source, priority_data_source, unused)
    void *visit(task_initialization_c *symbol) {
      if (symbol->interval_data_source != NULL) {
        calculate_time_c calculate_time;
        symbol->interval_data_source->accept(calculate_time);
        unsigned long time = calculate_time.get_time();
        if (time != 0) {
          s4o.print("tick % ");
          s4o.print_integer((int)(time / common_ticktime));
        }
        else
          s4o.print("1");
      }
      else
        s4o.print("1");
      return NULL;
    }

/*  any_symbolic_variable ASSIGN prog_data_source */
//SYM_REF2(prog_cnxn_assign_c, symbolic_variable, prog_data_source)
    void *visit(prog_cnxn_assign_c *symbol) {
      if (wanted_assigntype == assign_at) {
        symbol_c *var_decl;
        unsigned int vartype = 0;
        symbol_c *current_var_reference = ((global_var_reference_c *)(symbol->prog_data_source))->global_var_name;
        var_decl = search_resource_instance->get_decl(current_var_reference);
        if (var_decl == NULL) {
          var_decl = search_config_instance->get_decl(current_var_reference);
          if (var_decl == NULL)
            ERROR;
          else
            vartype = search_config_instance->get_vartype();
        }
        else
          vartype = search_resource_instance->get_vartype();
        
        s4o.print(s4o.indent_spaces + "{extern ");
        var_decl->accept(*this);
        s4o.print(" ");
        symbol->prog_data_source->accept(*this);
        s4o.print("; ");
        s4o.print(current_program_name);
        s4o.print(".");
        symbol->symbolic_variable->accept(*this);
        s4o.print(" = ");
        if (vartype || search_var_instance_decl_c::global_vt)
          s4o.print("*");
        symbol->prog_data_source->accept(*this);
        s4o.print(";}\n");
      }
      return NULL;
    }

/* any_symbolic_variable SENDTO data_sink */
//SYM_REF2(prog_cnxn_sendto_c, symbolic_variable, data_sink)
    void *visit(prog_cnxn_sendto_c *symbol) {
      if (wanted_assigntype == send_at) {
        symbol_c *var_decl;
        unsigned int vartype = 0;
        symbol_c *current_var_reference = ((global_var_reference_c *)(symbol->data_sink))->global_var_name;
        var_decl = search_resource_instance->get_decl(current_var_reference);
        if (var_decl == NULL) {
          var_decl = search_config_instance->get_decl(current_var_reference);
          if (var_decl == NULL)
            ERROR;
          else
            vartype = search_config_instance->get_vartype();
        }
        else
          vartype = search_resource_instance->get_vartype();
        
        s4o.print(s4o.indent_spaces);
        s4o.print(s4o.indent_spaces + "{extern ");
        var_decl->accept(*this);
        s4o.print(" ");
        symbol->data_sink->accept(*this);
        s4o.print("; ");
        if (vartype || search_var_instance_decl_c::global_vt)
          s4o.print("*");
        symbol->data_sink->accept(*this);
        s4o.print(" = ");
        s4o.print(current_program_name);
        s4o.print(".");
        symbol->symbolic_variable->accept(*this);
        s4o.print("};\n");
      }
      return NULL;
    }

};

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_cc_c: public iterator_visitor_c {
  protected:
    stage4out_c &s4o;
    stage4out_c pous_s4o;
    generate_cc_pous_c generate_cc_pous;

    symbol_c *current_configuration;

    const char *current_name;

    unsigned long common_ticktime;

  public:
    generate_cc_c(stage4out_c *s4o_ptr): 
            s4o(*s4o_ptr),
            pous_s4o("POUS", "c"),
            generate_cc_pous(&pous_s4o) {
      current_configuration = NULL;
    }
            
    ~generate_cc_c(void) {}

/***************************/
/* B 0 - Programming Model */
/***************************/
    void *visit(library_c *symbol) {
      generate_location_list_c generate_location_list(&s4o);
      symbol->accept(generate_location_list);
      
      for(int i = 1; i < symbol->n; i++) {
        symbol->elements[i]->accept(*this);
      }
      return NULL;
    }

/*************************/
/* B.1 - Common elements */
/*************************/
/*******************************************/
/* B 1.1 - Letters, digits and identifiers */
/*******************************************/
    void *visit(identifier_c *symbol) {
    	current_name = symbol->value;
    	return NULL;
    }

/**************************************/
/* B.1.5 - Program organization units */
/**************************************/
/***********************/
/* B 1.5.1 - Functions */
/***********************/
    void *visit(function_declaration_c *symbol) {
    	symbol->accept(generate_cc_pous);
    	return NULL;
    }
    
/*****************************/
/* B 1.5.2 - Function Blocks */
/*****************************/
    void *visit(function_block_declaration_c *symbol) {
    	symbol->accept(generate_cc_pous);
    	return NULL;
    }
    
/**********************/
/* B 1.5.3 - Programs */
/**********************/    
    void *visit(program_declaration_c *symbol) {
    	symbol->accept(generate_cc_pous);
    	return NULL;
    }
    

/********************************/
/* B 1.7 Configuration elements */
/********************************/
    void *visit(configuration_declaration_c *symbol) {
  	  static int configuration_count = 0;
  
      if (configuration_count++) {
        /* the first configuration is the one we will use!! */
        ERROR;
      }
      
      current_configuration = symbol;
      
      calculate_common_ticktime_c calculate_common_ticktime;
      symbol->accept(calculate_common_ticktime);
      common_ticktime = calculate_common_ticktime.get_ticktime();
      s4o.print("common_ticktime : ");
      s4o.print_integer((int)(common_ticktime / 1000000));
      s4o.print("ms\n");
      
      symbol->configuration_name->accept(*this);
    	stage4out_c config_s4o(current_name, "c");
    	generate_cc_config_c generate_cc_config(&config_s4o);
    	symbol->accept(generate_cc_config);
      symbol->resource_declarations->accept(*this);
    	
      current_configuration = NULL;
      
      return NULL;
    }

    void *visit(resource_declaration_c *symbol) {
    	symbol->resource_name->accept(*this);
    	stage4out_c resources_s4o(current_name, "c");
      generate_cc_resources_c generate_cc_resources(&resources_s4o, current_configuration, symbol, common_ticktime);
    	symbol->accept(generate_cc_resources);
    	return NULL;
    }

    void *visit(single_resource_declaration_c *symbol) {
    	stage4out_c resources_s4o("RESOURCE", "c");
      generate_cc_resources_c generate_cc_resources(&resources_s4o, current_configuration, symbol, common_ticktime);
    	symbol->accept(generate_cc_resources);
    	return NULL;
    }
    
};

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


