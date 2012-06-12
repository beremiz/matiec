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

#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <list>
#include <map>
#include <sstream>
#include <strings.h>

#include "../../util/symtable.hh"
#include "../../util/dsymtable.hh"
#include "../../absyntax/visitor.hh"
#include "../../absyntax_utils/absyntax_utils.hh"

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


#define STAGE4_ERROR(symbol1, symbol2, ...) {stage4err("while generating C code", symbol1, symbol2, __VA_ARGS__); exit(EXIT_FAILURE);}



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


/* Variable declaration symbol for accessor macros */
#define DECLARE_VAR "__DECLARE_VAR"
#define DECLARE_GLOBAL "__DECLARE_GLOBAL"
#define DECLARE_GLOBAL_LOCATION "__DECLARE_GLOBAL_LOCATION"
#define DECLARE_GLOBAL_LOCATED "__DECLARE_GLOBAL_LOCATED"
#define DECLARE_EXTERNAL "__DECLARE_EXTERNAL"
#define DECLARE_LOCATED "__DECLARE_LOCATED"
#define DECLARE_GLOBAL_PROTOTYPE "__DECLARE_GLOBAL_PROTOTYPE"

/* Variable declaration symbol for accessor macros */
#define INIT_VAR "__INIT_VAR"
#define INIT_GLOBAL "__INIT_GLOBAL"
#define INIT_GLOBAL_LOCATED "__INIT_GLOBAL_LOCATED"
#define INIT_EXTERNAL "__INIT_EXTERNAL"
#define INIT_LOCATED "__INIT_LOCATED"
#define INIT_LOCATED_VALUE "__INIT_LOCATED_VALUE"

/* Variable getter symbol for accessor macros */
#define GET_VAR "__GET_VAR"
#define GET_EXTERNAL "__GET_EXTERNAL"
#define GET_LOCATED "__GET_LOCATED"
#define GET_VAR_BY_REF "__GET_VAR_BY_REF"
#define GET_EXTERNAL_BY_REF "__GET_EXTERNAL_BY_REF"
#define GET_LOCATED_BY_REF "__GET_LOCATED_BY_REF"

/* Variable setter symbol for accessor macros */
#define SET_VAR "__SET_VAR"
#define SET_EXTERNAL "__SET_EXTERNAL"
#define SET_LOCATED "__SET_LOCATED"

/* Variable initial value symbol for accessor macros */
#define INITIAL_VALUE "__INITIAL_VALUE"

/* Generate a name for a temporary variable.
 * Each new name generated is appended a different number,
 * starting off from 0.
 * After calling reset(), the names will start off again from 0.
 */
#define VAR_LEADER "__"
#define TEMP_VAR VAR_LEADER "TMP_"
#define SOURCE_VAR VAR_LEADER "SRC_"

/* please see the comment before the RET_operator_c visitor for details... */
#define END_LABEL VAR_LEADER "end"


/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

#include "generate_c_base.cc"
#include "generate_c_typedecl.cc"
#include "generate_c_sfcdecl.cc"
#include "generate_c_vardecl.cc"
#include "generate_c_configbody.cc"
#include "generate_location_list.cc"
#include "generate_var_list.cc"

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


#include "generate_c.hh"


/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

/* A helper class that prints out the identifiers for function calls to overloaded functions */
/* Given a function declaration of the function being called, it 
 * will simply print out the returned data type,
 * followed by the data types of all input, output, and in_out parameters.
 *   for e.g.; 
 *     SIN( REAL) : REAL      -> prints out ->  REAL__REAL
 *     LEN( STRING) : INT     -> prints out ->  INT__STRING
 *     MUL(TIME, INT) : TIME  -> prints out ->  TIME__TIME__INT
 */
class print_function_parameter_data_types_c: public generate_c_base_c {
  private:
    symbol_c *current_type;
    bool_type_name_c tmp_bool;

    void print_list(symbol_c *var_list, symbol_c *data_type) { 
      if (data_type != NULL) {
        /* print out the data type once for every variable! */
        list_c *list = dynamic_cast<list_c *>(var_list);
        if (list == NULL) ERROR;  
        for (int i=0; i < list->n; i++) {
          s4o.print("__");
          data_type->accept(*this);
        }  
      }
    }
    
  public:
    print_function_parameter_data_types_c(stage4out_c *s4o_ptr): 
      generate_c_base_c(s4o_ptr)
      {current_type = NULL;}

    /**************************************/
    /* B.1.5 - Program organization units */
    /**************************************/
    /***********************/
    /* B 1.5.1 - Functions */
    /***********************/
    /*   FUNCTION derived_function_name ':' elementary_type_name io_OR_function_var_declarations_list function_body END_FUNCTION */
    /* | FUNCTION derived_function_name ':' derived_type_name io_OR_function_var_declarations_list function_body END_FUNCTION */
    void *visit(function_declaration_c *symbol) {
      symbol->type_name->accept(*this); /* return type */
      symbol->var_declarations_list->accept(*this);
      return NULL;
    }

    /* already handled by iterator base class (note that generate_c_base_c inherits from iterator_c) */
    //void *visit(var_declarations_list_c *symbol) {// iterate through list}
    
    /* already handled by iterator base class (note that generate_c_base_c inherits from iterator_c) */
    //void *visit(input_declarations_c *symbol) {// iterate through list}
        
    /* already handled by iterator base class (note that generate_c_base_c inherits from iterator_c) */
    //void *visit(input_declaration_list_c *symbol) {// iterate through list}

    void *visit(edge_declaration_c *symbol) {
      current_type = &tmp_bool; 
      symbol->var1_list->accept(*this);
      current_type = NULL; 
      return NULL;
    }
    
    /* We do NOT print out EN and ENO parameters! */
    void *visit(en_param_declaration_c *symbol) {return NULL;}

    /* already handled by iterator base class (note that generate_c_base_c inherits from iterator_c) */
    //void *visit(output_declarations_c *symbol) {// iterate through list}    
    
    /* already handled by iterator base class (note that generate_c_base_c inherits from iterator_c) */
    //void *visit(var_init_decl_list_c *symbol) {// iterate through list}

    void *visit(simple_spec_init_c *symbol) {
      /* return the data type */
      return symbol->simple_specification; 
    }

    /* currently we do not support data types defined in the declaration itself */
    /* For now, sugest the user define a TYPE .. END_TYPE */
    /* NOTE: although this class may also sometimes point to a previously_declared_subrange_type_name
     * we don't need this for now, so it is easier to just skip it allocation
     */
    void *visit(subrange_spec_init_c *symbol) {return NULL;}

    /* currently we do not support data types defined in the declaration itself */
    /* For now, sugest the user define a TYPE .. END_TYPE */
    /* NOTE: although this class may also sometimes point to a previously_declared_enumerated_type_name
     * we don't need this for now, so it is easier to just skip it allocation
     */
    void *visit(enumerated_spec_init_c *symbol) {return NULL;}

    /* currently we do not support data types defined in the declaration itself */
    /* For now, sugest the user define a TYPE .. END_TYPE */
    /* NOTE: although this class may also sometimes point to a previously_declared_array_type_name
     * we don't need this for now, so it is easier to just skip it allocation
     */
    void *visit(array_var_init_decl_c *symbol) {return NULL;}

    /* currently we do not support data types defined in the declaration itself */
    /* For now, sugest the user define a TYPE .. END_TYPE */
    /* NOTE: although this class may also sometimes point to a previously_declared_structured_type_name
     * we don't need this for now, so it is easier to just skip it allocation
     */
    void *visit(structured_var_init_decl_c *symbol) {return NULL;}

    /* We do NOT print out EN and ENO parameters! */
    void *visit(eno_param_declaration_c *symbol) {return NULL;}

    /* already handled by iterator base class (note that generate_c_base_c inherits from iterator_c) */
    //void *visit(input_output_declarations_c *symbol) {// iterate through list}    

    /* already handled by iterator base class (note that generate_c_base_c inherits from iterator_c) */
    //void *visit(var_declaration_list_c *symbol) {iterate through list}

    void *visit(fb_name_decl_c *symbol) {
      print_list(symbol->fb_name_list, symbol->function_block_type_name); 
      return NULL;
    }

    void *visit(var1_init_decl_c *symbol) {
      print_list(symbol->var1_list, (symbol_c *)symbol->spec_init->accept(*this));
      return NULL;
    }

    /* currently we do not support data types defined in the declaration itself */
    /* For now, sugest the user define a TYPE .. END_TYPE */
    void *visit(array_var_declaration_c *symbol) {return NULL;}

    void *visit(structured_var_declaration_c *symbol) {
      current_type = symbol->structure_type_name; 
      symbol->var1_list->accept(*this);
      current_type = NULL; 
      return NULL;
    }

    /* currently we do not support data types defined in the declaration itself */
    /* For now, sugest the user define a TYPE .. END_TYPE */
    /* Note that this class is used for fixed length strings...
     *   STRING [ 42 ]
     */
    void *visit(single_byte_string_var_declaration_c *symbol) {return NULL;}

    /* currently we do not support data types defined in the declaration itself */
    /* For now, sugest the user define a TYPE .. END_TYPE */
    /* Note that this class is used for fixed length strings...
     *   WSTRING [ 42 ]
     */
    void *visit(double_byte_string_var_declaration_c *symbol) {return NULL;}
};
    

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


#include "generate_c_st.cc"
#include "generate_c_il.cc"
#include "generate_c_inlinefcall.cc"

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

#define MILLISECOND 1000000
#define SECOND 1000 * MILLISECOND

/* A helper class that knows how to generate code for both the IL and ST languages... */
class calculate_time_c: public iterator_visitor_c {
  private:
    unsigned long long time;
    float current_value;
  
  public:
    calculate_time_c(void){time = 0;};
    
    unsigned long long get_time(void) {return time;};

    /* NOTE: we should really remove this function, and replace it with  extract_integer_value() (in absyntax_utils.h)
     *       but right now I don't want to spend time checking if this change will introduce some conversion bug
     *       since it returns a long long, and not a float!
     */
    void *get_integer_value(token_c *token) {
      std::string str = "";
      for (unsigned int i = 0; i < strlen(token->value); i++)
        if (token->value[i] != '_')
          str += token->value[i];
      current_value = atof(str.c_str());
      return NULL;
    }

    /* NOTE: this function is incomplete, as it should also be removing '_' inserted into the literal,
     *       but we leave it for now.
     *       In truth, we should really have an extract_real_value() in absyntax_util.h !!!
     */
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
        {STAGE4_ERROR(symbol, symbol, "Negative TIME literals are not currently supported"); ERROR;}
      symbol->interval->accept(*this);
      return NULL;
    }
    
    /* SYM_TOKEN(fixed_point_c) */
    void *visit(fixed_point_c *symbol) {return get_float_value(symbol);}
    
    
    /* SYM_REF5(interval_c, days, hours, minutes, seconds, milliseconds) */
    void *visit(interval_c *symbol) {
      current_value = 0;
      if (NULL != symbol->milliseconds) symbol->milliseconds->accept(*this);
      time += (unsigned long long)(current_value * MILLISECOND);
   
      current_value = 0;
      if (NULL != symbol->seconds)      symbol->seconds->accept(*this);
      time += (unsigned long long)(current_value * SECOND);
   
      current_value = 0;
      if (NULL != symbol->minutes)      symbol->minutes->accept(*this);
      time += (unsigned long long)(current_value * 60 * SECOND);
   
      current_value = 0;
      if (NULL != symbol->hours)        symbol->hours->accept(*this);
      time += (unsigned long long)(current_value * 60 * 60 * SECOND);
   
      current_value = 0;
      if (NULL != symbol->days)         symbol->days->accept(*this);
      time += (unsigned long long)(current_value * 60 * 60 * 24 * SECOND);
   
      return NULL;
    }      
};

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class calculate_common_ticktime_c: public iterator_visitor_c {
  private:
    unsigned long long common_ticktime;
    unsigned long long least_common_ticktime;
    
  public:
    calculate_common_ticktime_c(void){
      common_ticktime = 0;
      least_common_ticktime = 0;
    }
    
    unsigned long long euclide(unsigned long long a, unsigned long long b) {
      unsigned long long c = a % b;
      if (c == 0)
        return b;
      else
        return euclide(b, c);
    }
    
    void update_ticktime(unsigned long long time) {
      if (common_ticktime == 0)
        common_ticktime = time;
      else if (time > common_ticktime)
        common_ticktime = euclide(time, common_ticktime);
      else
        common_ticktime = euclide(common_ticktime, time);
      if (least_common_ticktime == 0)
        least_common_ticktime = time;
      else
        least_common_ticktime = (least_common_ticktime * time) / common_ticktime;
    }

    unsigned long long get_common_ticktime(void) {
      return common_ticktime;
    }

    unsigned long get_greatest_tick_count(void) {
      unsigned long long least_common_tick = least_common_ticktime / common_ticktime;
      if (least_common_tick >> 32)
        ERROR;
      return (unsigned long)(~(((unsigned long)-1) % (unsigned long)least_common_tick) + 1);
    }

/*  TASK task_name task_initialization */
//SYM_REF2(task_configuration_c, task_name, task_initialization)  
    void *visit(task_initialization_c *symbol) {
      calculate_time_c calculate_time;
      unsigned long long time = 0;
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

/* A helper class that knows how to generate code for the SFC, IL and ST languages... */
class generate_c_SFC_IL_ST_c: public null_visitor_c {
  private:
    stage4out_c *s4o_ptr;
    symbol_c *scope;
    symbol_c *fbname;
    const char *variable_prefix;

  public:
    generate_c_SFC_IL_ST_c(stage4out_c *s4o_ptr, symbol_c *name, symbol_c *scope, const char *variable_prefix = NULL);
    
    /********************/
    /* 2.1.6 - Pragmas  */
    /********************/
    void *visit(enable_code_generation_pragma_c * symbol)   {s4o_ptr->enable_output();  return NULL;}
    void *visit(disable_code_generation_pragma_c * symbol)  {s4o_ptr->disable_output(); return NULL;} 
    
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
    
    /* Remainder implemented in generate_c_il_c... */
    
    /***************************************/
    /* B.3 - Language ST (Structured Text) */
    /***************************************/
    /***********************/
    /* B 3.1 - Expressions */
    /***********************/
    /* Implemented in generate_c_st_c */
    
    /********************/
    /* B 3.2 Statements */
    /********************/
    void *visit(statement_list_c *symbol);

/* Remainder implemented in generate_c_st_c... */
};

#include "generate_c_sfc.cc"

generate_c_SFC_IL_ST_c::generate_c_SFC_IL_ST_c(stage4out_c *s4o_ptr, symbol_c *name, symbol_c *scope, const char *variable_prefix) {
  if (NULL == scope) ERROR;
  this->s4o_ptr = s4o_ptr;
  this->scope = scope;
  this->fbname = name;
  this->variable_prefix = variable_prefix;
}

void *generate_c_SFC_IL_ST_c::visit(sequential_function_chart_c * symbol) {
  generate_c_sfc_c generate_c_sfc(s4o_ptr, fbname, scope, variable_prefix);
  generate_c_sfc.generate(symbol);
  return NULL;
}

void *generate_c_SFC_IL_ST_c::visit(instruction_list_c *symbol) {
  generate_c_il_c generate_c_il(s4o_ptr, fbname, scope, variable_prefix);
  generate_c_il.generate(symbol);
  return NULL;
}

void *generate_c_SFC_IL_ST_c::visit(statement_list_c *symbol) {
  generate_c_st_c generate_c_st(s4o_ptr, fbname, scope, variable_prefix);
  generate_c_st.generate(symbol);
  return NULL;
}




/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


class generate_c_datatypes_c: public generate_c_typedecl_c {
  public:
    typedef enum {
      none_im,
      arrayname_im,
      arraydeclaration_im,
    } inlinearray_mode_t;

  private:
    stage4out_c *s4o_ptr;
    std::map<std::string, int> inline_array_defined;
    std::string current_array_name;
    inlinearray_mode_t current_mode;

  public:
    generate_c_datatypes_c(stage4out_c *s4o_ptr, stage4out_c *s4o_incl_ptr)
      : generate_c_typedecl_c(s4o_ptr, s4o_incl_ptr) {
      generate_c_datatypes_c::s4o_ptr = s4o_ptr;
      current_mode = none_im;
    };
    virtual ~generate_c_datatypes_c(void) {
      while (!inline_array_defined.empty()) {
    	inline_array_defined.erase(inline_array_defined.begin());
      }
    }

    /*************************/
    /* B.1 - Common elements */
    /*************************/
    /*******************************************/
    /* B 1.1 - Letters, digits and identifiers */
    /*******************************************/
    void *visit(identifier_c *symbol) {
      switch (current_mode) {
        case arrayname_im:
          current_array_name += symbol->value;
          break;
        case arraydeclaration_im:
          s4o_incl.print(symbol->value);
          break;
        default:
          return generate_c_base_c::visit(symbol);
          break;
      }
      return NULL;
    }

    /**********************/
    /* B.1.3 - Data types */
    /**********************/
    /***********************************/
    /* B 1.3.1 - Elementary Data Types */
    /***********************************/

    #define HANDLE_ELEMENTARY_DATA_TYPE(datatype_symbol, datatype_name)\
    void *visit(datatype_symbol *symbol) {\
	  switch (current_mode) {\
		case arrayname_im:\
		  current_array_name += datatype_name;\
		  break;\
        case arraydeclaration_im:\
          s4o_incl.print(datatype_name);\
          break;\
		default:\
		  return generate_c_base_c::visit(symbol);\
		  break;\
	  }\
	  return NULL;\
	}

    HANDLE_ELEMENTARY_DATA_TYPE(time_type_name_c, "TIME")
    HANDLE_ELEMENTARY_DATA_TYPE(bool_type_name_c, "BOOL")
    HANDLE_ELEMENTARY_DATA_TYPE(sint_type_name_c, "SINT")
    HANDLE_ELEMENTARY_DATA_TYPE(int_type_name_c, "INT")
    HANDLE_ELEMENTARY_DATA_TYPE(dint_type_name_c, "DINT")
    HANDLE_ELEMENTARY_DATA_TYPE(lint_type_name_c, "LINT")
    HANDLE_ELEMENTARY_DATA_TYPE(usint_type_name_c, "USINT")
    HANDLE_ELEMENTARY_DATA_TYPE(uint_type_name_c, "UINT")
    HANDLE_ELEMENTARY_DATA_TYPE(udint_type_name_c, "UDINT")
    HANDLE_ELEMENTARY_DATA_TYPE(ulint_type_name_c, "ULINT")
    HANDLE_ELEMENTARY_DATA_TYPE(real_type_name_c, "REAL")
    HANDLE_ELEMENTARY_DATA_TYPE(lreal_type_name_c, "LREAL")
    HANDLE_ELEMENTARY_DATA_TYPE(date_type_name_c, "DATE")
    HANDLE_ELEMENTARY_DATA_TYPE(tod_type_name_c, "TOD")
    HANDLE_ELEMENTARY_DATA_TYPE(dt_type_name_c, "DT")
    HANDLE_ELEMENTARY_DATA_TYPE(byte_type_name_c, "BYTE")
    HANDLE_ELEMENTARY_DATA_TYPE(word_type_name_c, "WORD")
    HANDLE_ELEMENTARY_DATA_TYPE(dword_type_name_c, "DWORD")
    HANDLE_ELEMENTARY_DATA_TYPE(lword_type_name_c, "LWORD")
    HANDLE_ELEMENTARY_DATA_TYPE(string_type_name_c, "STRING")
    HANDLE_ELEMENTARY_DATA_TYPE(wstring_type_name_c, "WSTRING")

    HANDLE_ELEMENTARY_DATA_TYPE(safetime_type_name_c, "TIME")
	HANDLE_ELEMENTARY_DATA_TYPE(safebool_type_name_c, "BOOL")
	HANDLE_ELEMENTARY_DATA_TYPE(safesint_type_name_c, "SINT")
	HANDLE_ELEMENTARY_DATA_TYPE(safeint_type_name_c, "INT")
	HANDLE_ELEMENTARY_DATA_TYPE(safedint_type_name_c, "DINT")
	HANDLE_ELEMENTARY_DATA_TYPE(safelint_type_name_c, "LINT")
	HANDLE_ELEMENTARY_DATA_TYPE(safeusint_type_name_c, "USINT")
	HANDLE_ELEMENTARY_DATA_TYPE(safeuint_type_name_c, "UINT")
	HANDLE_ELEMENTARY_DATA_TYPE(safeudint_type_name_c, "UDINT")
	HANDLE_ELEMENTARY_DATA_TYPE(safeulint_type_name_c, "ULINT")
	HANDLE_ELEMENTARY_DATA_TYPE(safereal_type_name_c, "REAL")
	HANDLE_ELEMENTARY_DATA_TYPE(safelreal_type_name_c, "LREAL")
	HANDLE_ELEMENTARY_DATA_TYPE(safedate_type_name_c, "DATE")
	HANDLE_ELEMENTARY_DATA_TYPE(safetod_type_name_c, "TOD")
	HANDLE_ELEMENTARY_DATA_TYPE(safedt_type_name_c, "DT")
	HANDLE_ELEMENTARY_DATA_TYPE(safebyte_type_name_c, "BYTE")
	HANDLE_ELEMENTARY_DATA_TYPE(safeword_type_name_c, "WORD")
	HANDLE_ELEMENTARY_DATA_TYPE(safedword_type_name_c, "DWORD")
	HANDLE_ELEMENTARY_DATA_TYPE(safelword_type_name_c, "LWORD")
	HANDLE_ELEMENTARY_DATA_TYPE(safestring_type_name_c, "STRING")
	HANDLE_ELEMENTARY_DATA_TYPE(safewstring_type_name_c, "WSTRING")

    /******************************************/
    /* B 1.4.3 - Declaration & Initialization */
    /******************************************/

    void *visit(input_declarations_c *symbol) {
      symbol->input_declaration_list->accept(*this);
      return NULL;
    }

    void *visit(edge_declaration_c *symbol) {
      return NULL;
    }

    void *visit(en_param_declaration_c *symbol) {
      return NULL;
    }

    void *visit(eno_param_declaration_c *symbol) {
      return NULL;
    }

    void *visit(var1_init_decl_c *symbol) {
      return NULL;
    }

    /*  var1_list ':' array_spec_init */
    // SYM_REF2(array_var_init_decl_c, var1_list, array_spec_init)
    void *visit(array_var_init_decl_c *symbol) {
      current_mode = arrayname_im;
      symbol->array_spec_init->accept(*this);
      current_mode = none_im;
      return NULL;
    }

    /* array_specification [ASSIGN array_initialization] */
    /* array_initialization may be NULL ! */
    void *visit(array_spec_init_c *symbol) {
      switch (current_mode) {
    	case arrayname_im:
    	  {
    	    array_specification_c *specification = dynamic_cast<array_specification_c*>(symbol->array_specification);
            if (specification != NULL)
              symbol->array_specification->accept(*this);
          }
          break;
    	default:
    	  return generate_c_typedecl_c::visit(symbol);
          break;
      }
      return NULL;
    }

    /* ARRAY '[' array_subrange_list ']' OF non_generic_type_name */
    void *visit(array_specification_c *symbol) {
      switch (current_mode) {
        case arrayname_im:
          {
            std::map<std::string,int>::iterator definition;
            current_array_name = "__";
            symbol->non_generic_type_name->accept(*this);
            symbol->array_subrange_list->accept(*this);

            definition = inline_array_defined.find(current_array_name);
            if (definition == inline_array_defined.end()) {
              current_mode = arraydeclaration_im;

              s4o_incl.print("__DECLARE_ARRAY_TYPE(");
              s4o_incl.print(current_array_name);
              s4o_incl.print(",");
              symbol->non_generic_type_name->accept(*this);
              s4o_incl.print(",");
              symbol->array_subrange_list->accept(*this);
              s4o_incl.print(")\n\n");

              inline_array_defined[current_array_name] = 0;
            }
          }
          break;
        default:
          return generate_c_typedecl_c::visit(symbol);
          break;
      }
      return NULL;
    }

    /*  signed_integer DOTDOT signed_integer */
    //SYM_REF2(subrange_c, lower_limit, upper_limit)
    void *visit(subrange_c *symbol) {
      int dimension = extract_int64_value(symbol->upper_limit) - extract_int64_value(symbol->lower_limit) + 1;
      switch (current_mode) {
        case arrayname_im:
          current_array_name += "_";
          {
            std::stringstream ss;
            ss << dimension;
            current_array_name += ss.str();
          }
          break;
        case arraydeclaration_im:
          s4o_incl.print("[");
          s4o_incl.print_integer(dimension);
          s4o_incl.print("]");
        default:
          generate_c_typedecl_c::visit(symbol);
          break;
      }
      return NULL;
    }

    /*  var1_list ':' initialized_structure */
    // SYM_REF2(structured_var_init_decl_c, var1_list, initialized_structure)
    void *visit(structured_var_init_decl_c *symbol) {
      return NULL;
    }

    /* fb_name_list ':' function_block_type_name ASSIGN structure_initialization */
    /* structure_initialization -> may be NULL ! */
    void *visit(fb_name_decl_c *symbol) {
      return NULL;
    }

    /* VAR_OUTPUT [RETAIN | NON_RETAIN] var_init_decl_list END_VAR */
    /* option -> may be NULL ! */
    void *visit(output_declarations_c *symbol) {
      symbol->var_init_decl_list->accept(*this);
      return NULL;
    }

    /*  VAR_IN_OUT var_declaration_list END_VAR */
    void *visit(input_output_declarations_c *symbol) {
      symbol->var_declaration_list->accept(*this);
      return NULL;
    }

    /*  var1_list ':' array_specification */
    //SYM_REF2(array_var_declaration_c, var1_list, array_specification)
    void *visit(array_var_declaration_c *symbol) {
      array_specification_c *specification = dynamic_cast<array_specification_c*>(symbol->array_specification);
	  if (specification != NULL) {
        current_mode = arrayname_im;
        symbol->array_specification->accept(*this);
        current_mode = none_im;
      }
      return NULL;
    }

    /* VAR [CONSTANT] var_init_decl_list END_VAR */
    /* option -> may be NULL ! */
    /* helper symbol for input_declarations */
    void *visit(var_declarations_c *symbol) {
      symbol->var_init_decl_list->accept(*this);
      return NULL;
    }

    /*  VAR RETAIN var_init_decl_list END_VAR */
    void *visit(retentive_var_declarations_c *symbol) {
      symbol->var_init_decl_list->accept(*this);
      return NULL;
    }

    /*  VAR [CONSTANT|RETAIN|NON_RETAIN] located_var_decl_list END_VAR */
    /* option -> may be NULL ! */
    //SYM_REF2(located_var_declarations_c, option, located_var_decl_list)
    void *visit(located_var_declarations_c *symbol) {
      symbol->located_var_decl_list->accept(*this);
      return NULL;
    }

    /*  [variable_name] location ':' located_var_spec_init */
    /* variable_name -> may be NULL ! */
    //SYM_REF4(located_var_decl_c, variable_name, location, located_var_spec_init, unused)
    void *visit(located_var_decl_c *symbol) {
      array_spec_init_c* array_spec_init = dynamic_cast<array_spec_init_c*>(symbol->located_var_spec_init);
      if (array_spec_init != NULL) {
    	current_mode = arrayname_im;
    	symbol->located_var_spec_init->accept(*this);
    	current_mode = none_im;
      }
      return NULL;
    }

    /*| VAR_EXTERNAL [CONSTANT] external_declaration_list END_VAR */
    /* option -> may be NULL ! */
    //SYM_REF2(external_var_declarations_c, option, external_declaration_list)
    void *visit(external_var_declarations_c *symbol) {
      symbol->external_declaration_list->accept(*this);
      return NULL;
    }

    /*  global_var_name ':' (simple_specification|subrange_specification|enumerated_specification|array_specification|prev_declared_structure_type_name|function_block_type_name */
    //SYM_REF2(external_declaration_c, global_var_name, specification)
    void *visit(external_declaration_c *symbol) {
      array_specification_c* array_specification = dynamic_cast<array_specification_c*>(symbol->specification);
      if (array_specification != NULL) {
        current_mode = arrayname_im;
        symbol->specification->accept(*this);
        current_mode = none_im;
      }
      return NULL;
    }

    /*| VAR_GLOBAL [CONSTANT|RETAIN] global_var_decl_list END_VAR */
    /* option -> may be NULL ! */
    // SYM_REF2(global_var_declarations_c, option, global_var_decl_list)
    void *visit(global_var_declarations_c *symbol) {
      symbol->global_var_decl_list->accept(*this);
      return NULL;
    }

    /*| global_var_spec ':' [located_var_spec_init|function_block_type_name] */
    /* type_specification ->may be NULL ! */
    // SYM_REF2(global_var_decl_c, global_var_spec, type_specification)
    void *visit(global_var_decl_c *symbol) {
      array_spec_init_c* array_spec_init = dynamic_cast<array_spec_init_c*>(symbol->type_specification);
      if (array_spec_init != NULL) {
        current_mode = arrayname_im;
        symbol->type_specification->accept(*this);
        current_mode = none_im;
      }
      return NULL;
    }

    void *visit(function_var_decls_c *symbol) {
      symbol->decl_list->accept(*this);
      return NULL;
    }

    /*****************************/
    /* B 1.5.2 - Function Blocks */
    /*****************************/

    /*  VAR_TEMP temp_var_decl_list END_VAR */
    void *visit(temp_var_decls_c *symbol) {
      symbol->var_decl_list->accept(*this);
      return NULL;
    }

    /*  VAR NON_RETAIN var_init_decl_list END_VAR */
    void *visit(non_retentive_var_decls_c *symbol) {
      symbol->var_decl_list->accept(*this);
      return NULL;
    }

};




/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


class generate_c_pous_c: public generate_c_typedecl_c {
  private:
    stage4out_c *s4o_ptr;
    
  public:
    generate_c_pous_c(stage4out_c *s4o_ptr, stage4out_c *s4o_incl_ptr)
      : generate_c_typedecl_c(s4o_ptr, s4o_incl_ptr) {
      generate_c_pous_c::s4o_ptr = s4o_ptr;
    };
    virtual ~generate_c_pous_c(void) {}

  private:
    void print_end_of_block_label(void) {
      /* Print and __end label for return statements!
       * If label is not used by at least one goto, compiler will generate a warning.
       * To work around this we introduce the useless goto.
       */
      s4o.print("\n");
      s4o.print(s4o.indent_spaces);
      s4o.print("/* to humour the compiler, we insert a goto */\n");
      s4o.print(s4o.indent_spaces);
      s4o.print("goto ");
      s4o.print(END_LABEL);
      s4o.print(";\n");
      s4o.indent_left();

      /* write the label marking the end of the code block */
      /* please see the comment before the RET_operator_c visitor for details... */
      /* also needed for return_statement_c */
      s4o.print("\n");
      s4o.print(s4o.indent_spaces);
      s4o.print(END_LABEL);
      s4o.print(":\n");
      s4o.indent_right();
    }
  


  public:
/********************/
/* 2.1.6 - Pragmas  */
/********************/
void *visit(enable_code_generation_pragma_c * symbol)   {s4o_ptr->enable_output();  return NULL;}
void *visit(disable_code_generation_pragma_c * symbol)  {s4o_ptr->disable_output(); return NULL;} 

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
  generate_c_vardecl_c *vardecl;
  TRACE("function_declaration_c");

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
  vardecl = new generate_c_vardecl_c(&s4o,
                                     generate_c_vardecl_c::finterface_vf,
                                     generate_c_vardecl_c::input_vt    |
                                     generate_c_vardecl_c::output_vt   |
                                     generate_c_vardecl_c::inoutput_vt |
                                     generate_c_vardecl_c::en_vt       |
                                     generate_c_vardecl_c::eno_vt);
  vardecl->print(symbol->var_declarations_list);
  delete vardecl;
  
  s4o.indent_left();
  
  s4o.print(")\n" + s4o.indent_spaces + "{\n");

  /* (B) Function local variable declaration */
  /* (B.1) Variables declared in ST source code */
  s4o.indent_right();
  
  vardecl = new generate_c_vardecl_c(&s4o,
                generate_c_vardecl_c::localinit_vf,
                generate_c_vardecl_c::output_vt   |
                generate_c_vardecl_c::inoutput_vt |
                generate_c_vardecl_c::private_vt  |
                generate_c_vardecl_c::eno_vt);
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
    initialization_analyzer_c initialization_analyzer(default_value);
    switch (initialization_analyzer.get_initialization_type()) {
      case initialization_analyzer_c::struct_it:
        {
          generate_c_structure_initialization_c *structure_initialization = new generate_c_structure_initialization_c(&s4o);
          structure_initialization->init_structure_default(symbol->type_name);
          structure_initialization->init_structure_values(default_value);
          delete structure_initialization;
        }
        break;
      case initialization_analyzer_c::array_it:
        {
          generate_c_array_initialization_c *array_initialization = new generate_c_array_initialization_c(&s4o);
          array_initialization->init_array_size(symbol->type_name);
          array_initialization->init_array_values(default_value);
          delete array_initialization;
        }
        break;
      default:
        default_value->accept(*this);
        break;
    }
  }
  s4o.print(";\n\n");
  
  s4o.print(s4o.indent_spaces + "// Control execution\n");
  s4o.print(s4o.indent_spaces + "if (!EN) {\n");
  s4o.indent_right();
  s4o.print(s4o.indent_spaces + "if (__ENO != NULL) {\n");
  s4o.indent_right();
  s4o.print(s4o.indent_spaces + "*__ENO = __BOOL_LITERAL(FALSE);\n");
  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "}\n");
  s4o.print(s4o.indent_spaces + "return ");
  symbol->derived_function_name->accept(*this);
  s4o.print(";\n");
  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "}\n");

  /* (C) Function body */
  generate_c_SFC_IL_ST_c generate_c_code(&s4o, symbol->derived_function_name, symbol);
  symbol->function_body->accept(generate_c_code);
  
  print_end_of_block_label();
  
  vardecl = new generate_c_vardecl_c(&s4o,
                generate_c_vardecl_c::foutputassign_vf,
                generate_c_vardecl_c::output_vt   |
                generate_c_vardecl_c::inoutput_vt |
                generate_c_vardecl_c::eno_vt);
  vardecl->print(symbol->var_declarations_list);
  delete vardecl;
  
  s4o.print(s4o.indent_spaces + "return ");
  symbol->derived_function_name->accept(*this);
  s4o.print(";\n");
  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "}\n\n\n");

  return NULL;
}


/* The remaining var_declarations_list_c, function_var_decls_c
 * and var2_init_decl_list_c are handled in the generate_c_vardecl_c class
 */


/*****************************/
/* B 1.5.2 - Function Blocks */
/*****************************/
public:
/*  FUNCTION_BLOCK derived_function_block_name io_OR_other_var_declarations function_block_body END_FUNCTION_BLOCK */
//SYM_REF4(function_block_declaration_c, fblock_name, var_declarations, fblock_body, unused)
void *visit(function_block_declaration_c *symbol) {
  generate_c_vardecl_c *vardecl;
  generate_c_sfcdecl_c *sfcdecl;
  generate_c_typedecl_c *typedecl;
  generate_c_inlinefcall_c *inlinedecl;
  TRACE("function_block_declaration_c");

  /* (A) Function Block data structure declaration... */
  typedecl = new generate_c_typedecl_c(&s4o_incl);
  /* (A.1) Data structure declaration */
  s4o_incl.print("// FUNCTION_BLOCK ");
  symbol->fblock_name->accept(*typedecl);
  s4o_incl.print("\n// Data part\n");
  s4o_incl.print("typedef struct {\n");
  s4o_incl.indent_right();
  /* (A.2) Public variables: i.e. the function parameters... */
  s4o_incl.print(s4o_incl.indent_spaces + "// FB Interface - IN, OUT, IN_OUT variables\n");
  vardecl = new generate_c_vardecl_c(&s4o_incl,
                                     generate_c_vardecl_c::local_vf,
                                     generate_c_vardecl_c::input_vt    |
                                     generate_c_vardecl_c::output_vt   |
                                     generate_c_vardecl_c::inoutput_vt |
                                     generate_c_vardecl_c::en_vt       |
                                     generate_c_vardecl_c::eno_vt);
  vardecl->print(symbol->var_declarations);
  delete vardecl;
  s4o_incl.print("\n");
  /* (A.3) Private internal variables */
  s4o_incl.print(s4o_incl.indent_spaces + "// FB private variables - TEMP, private and located variables\n");
  vardecl = new generate_c_vardecl_c(&s4o_incl,
                                     generate_c_vardecl_c::local_vf,
                                     generate_c_vardecl_c::temp_vt    |
                                     generate_c_vardecl_c::private_vt |
                                     generate_c_vardecl_c::located_vt |
                                     generate_c_vardecl_c::external_vt);
  vardecl->print(symbol->var_declarations);
  delete vardecl;
  
  /* (A.4) Generate private internal variables for SFC */
  sfcdecl = new generate_c_sfcdecl_c(&s4o_incl, symbol);
  sfcdecl->generate(symbol->fblock_body, generate_c_sfcdecl_c::sfcdecl_sd);
  delete sfcdecl;
  s4o_incl.print("\n");

  /* (A.5) Function Block data structure type name. */
  s4o_incl.indent_left();
  s4o_incl.print("} ");
  symbol->fblock_name->accept(*typedecl);
  s4o_incl.print(";\n\n");
  delete typedecl;

  /* (A.6) Function Block inline function declaration for function invocation */
  inlinedecl = new generate_c_inlinefcall_c(&s4o, symbol->fblock_name, symbol, FB_FUNCTION_PARAM"->");
  symbol->fblock_body->accept(*inlinedecl);
  delete inlinedecl;

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
  s4o.print(", BOOL retain) {\n");
  s4o.indent_right();

  /* (B.2) Member initializations... */
  s4o.print(s4o.indent_spaces);
  vardecl = new generate_c_vardecl_c(&s4o,
                                     generate_c_vardecl_c::constructorinit_vf,
                                     generate_c_vardecl_c::input_vt    |
                                     generate_c_vardecl_c::output_vt   |
                                     generate_c_vardecl_c::inoutput_vt |
                                     generate_c_vardecl_c::private_vt  |
                                     generate_c_vardecl_c::located_vt  |
                                     generate_c_vardecl_c::external_vt |
                                     generate_c_vardecl_c::en_vt       |
                                     generate_c_vardecl_c::eno_vt);
  vardecl->print(symbol->var_declarations, NULL, FB_FUNCTION_PARAM"->");
  delete vardecl;
  s4o.print("\n");

  sfcdecl = new generate_c_sfcdecl_c(&s4o, symbol, FB_FUNCTION_PARAM"->");

  /* (B.3) Generate private internal variables for SFC */
  sfcdecl->generate(symbol->fblock_body, generate_c_sfcdecl_c::sfcinit_sd);

  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "}\n\n");

  
  /* (C) Function with FB body */
  /* (C.1) Step definitions */
  sfcdecl->generate(symbol->fblock_body, generate_c_sfcdecl_c::stepdef_sd);
  
  /* (C.2) Action definitions */
  sfcdecl->generate(symbol->fblock_body, generate_c_sfcdecl_c::actiondef_sd);

  /* (C.3) Function declaration */
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

  s4o.print(s4o.indent_spaces + "// Control execution\n");
  s4o.print(s4o.indent_spaces + "if (!");
  s4o.print(GET_VAR);
  s4o.print("(");
  s4o.print(FB_FUNCTION_PARAM);
  s4o.print("->EN)) {\n");
  s4o.indent_right();
  s4o.print(s4o.indent_spaces);
  s4o.print(SET_VAR);
  s4o.print("(");
  s4o.print(FB_FUNCTION_PARAM);
  s4o.print("->,ENO,__BOOL_LITERAL(FALSE));\n");
  s4o.print(s4o.indent_spaces + "return;\n");
  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "}\n");
  s4o.print(s4o.indent_spaces + "else {\n");
  s4o.indent_right();
  s4o.print(s4o.indent_spaces);
  s4o.print(SET_VAR);
  s4o.print("(");
  s4o.print(FB_FUNCTION_PARAM);
  s4o.print("->,ENO,__BOOL_LITERAL(TRUE));\n");
  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "}\n");

  /* (C.4) Initialize TEMP variables */
  /* function body */
  s4o.print(s4o.indent_spaces + "// Initialise TEMP variables\n");
  vardecl = new generate_c_vardecl_c(&s4o,
                                     generate_c_vardecl_c::init_vf,
                                     generate_c_vardecl_c::temp_vt);
  vardecl->print(symbol->var_declarations, NULL,  FB_FUNCTION_PARAM"->");
  delete vardecl;
  s4o.print("\n");

  /* (C.5) Function code */
  generate_c_SFC_IL_ST_c generate_c_code(&s4o, symbol->fblock_name, symbol, FB_FUNCTION_PARAM"->");
  symbol->fblock_body->accept(generate_c_code);
  print_end_of_block_label();
  s4o.print(s4o.indent_spaces + "return;\n");
  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "} // ");
  symbol->fblock_name->accept(*this);
  s4o.print(FB_FUNCTION_SUFFIX);
  s4o.print(s4o.indent_spaces + "() \n\n");

  /* (C.6) Step undefinitions */
  sfcdecl->generate(symbol->fblock_body, generate_c_sfcdecl_c::stepundef_sd);

  /* (C.7) Action undefinitions */
  sfcdecl->generate(symbol->fblock_body, generate_c_sfcdecl_c::actionundef_sd);

  delete sfcdecl;

  s4o.indent_left();
  s4o.print("\n\n\n\n");

  return NULL;
}


/* The remaining temp_var_decls_c, temp_var_decls_list_c
 * and non_retentive_var_decls_c are handled in the generate_c_vardecl_c class
 */


/**********************/
/* B 1.5.3 - Programs */
/**********************/



public:
/*  PROGRAM program_type_name program_var_declarations_list function_block_body END_PROGRAM */
//SYM_REF4(program_declaration_c, program_type_name, var_declarations, function_block_body, unused)
void *visit(program_declaration_c *symbol) {
  generate_c_vardecl_c *vardecl;
  generate_c_sfcdecl_c *sfcdecl;
  generate_c_typedecl_c *typedecl;
  generate_c_inlinefcall_c *inlinedecl;
  TRACE("program_declaration_c");

  /* (A) Program data structure declaration... */
  typedecl = new generate_c_typedecl_c(&s4o_incl);
  /* (A.1) Data structure declaration */
  s4o_incl.print("// PROGRAM ");
  symbol->program_type_name->accept(*typedecl);
  s4o_incl.print("\n// Data part\n");
  s4o_incl.print("typedef struct {\n");
  s4o_incl.indent_right();

  /* (A.2) Public variables: i.e. the program parameters... */
  s4o_incl.print(s4o_incl.indent_spaces + "// PROGRAM Interface - IN, OUT, IN_OUT variables\n");
  vardecl = new generate_c_vardecl_c(&s4o_incl,
                                     generate_c_vardecl_c::local_vf,
                                     generate_c_vardecl_c::input_vt  |
                                     generate_c_vardecl_c::output_vt |
                                     generate_c_vardecl_c::inoutput_vt);
  vardecl->print(symbol->var_declarations);
  delete vardecl;
  s4o_incl.print("\n");
  /* (A.3) Private internal variables */
  s4o_incl.print(s4o_incl.indent_spaces + "// PROGRAM private variables - TEMP, private and located variables\n");
  vardecl = new generate_c_vardecl_c(&s4o_incl,
                generate_c_vardecl_c::local_vf,
                generate_c_vardecl_c::temp_vt    |
                generate_c_vardecl_c::private_vt |
                generate_c_vardecl_c::located_vt |
                generate_c_vardecl_c::external_vt);
  vardecl->print(symbol->var_declarations);
  delete vardecl;

  /* (A.4) Generate private internal variables for SFC */
  sfcdecl = new generate_c_sfcdecl_c(&s4o_incl, symbol);
  sfcdecl->generate(symbol->function_block_body, generate_c_sfcdecl_c::sfcdecl_sd);
  delete sfcdecl;
  s4o_incl.print("\n");
  
  /* (A.5) Program data structure type name. */
  s4o_incl.indent_left();
  s4o_incl.print("} ");
  symbol->program_type_name->accept(*typedecl);
  s4o_incl.print(";\n\n");
  delete typedecl;

  /* (A.6) Function Block inline function declaration for function invocation */
  inlinedecl = new generate_c_inlinefcall_c(&s4o, symbol->program_type_name, symbol, FB_FUNCTION_PARAM"->");
  symbol->function_block_body->accept(*inlinedecl);
  delete inlinedecl;

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
  s4o.print(", BOOL retain) {\n");
  s4o.indent_right();

  /* (B.2) Member initializations... */
  s4o.print(s4o.indent_spaces);
  vardecl = new generate_c_vardecl_c(&s4o,
                                     generate_c_vardecl_c::constructorinit_vf,
                                     generate_c_vardecl_c::input_vt    |
                                     generate_c_vardecl_c::output_vt   |
                                     generate_c_vardecl_c::inoutput_vt |
                                     generate_c_vardecl_c::private_vt  |
                                     generate_c_vardecl_c::located_vt  |
                                     generate_c_vardecl_c::external_vt);
  vardecl->print(symbol->var_declarations, NULL,  FB_FUNCTION_PARAM"->");
  delete vardecl;
  s4o.print("\n");

  sfcdecl = new generate_c_sfcdecl_c(&s4o, symbol, FB_FUNCTION_PARAM"->");

  /* (B.3) Generate private internal variables for SFC */
  sfcdecl->generate(symbol->function_block_body, generate_c_sfcdecl_c::sfcinit_sd);

  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "}\n\n");

  /* (C) Function with PROGRAM body */
  /* (C.1) Step definitions */
  sfcdecl->generate(symbol->function_block_body, generate_c_sfcdecl_c::stepdef_sd);
  
  /* (C.2) Action definitions */
  sfcdecl->generate(symbol->function_block_body, generate_c_sfcdecl_c::actiondef_sd);

  /* (C.3) Function declaration */
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

  /* (C.4) Initialize TEMP variables */
  /* function body */
  s4o.print(s4o.indent_spaces + "// Initialise TEMP variables\n");
  vardecl = new generate_c_vardecl_c(&s4o,
                                     generate_c_vardecl_c::init_vf,
                                     generate_c_vardecl_c::temp_vt);
  vardecl->print(symbol->var_declarations, NULL,  FB_FUNCTION_PARAM"->");
  delete vardecl;
  s4o.print("\n");

  /* (C.5) Function code */
  generate_c_SFC_IL_ST_c generate_c_code(&s4o, symbol->program_type_name, symbol, FB_FUNCTION_PARAM"->");
  symbol->function_block_body->accept(generate_c_code);
  print_end_of_block_label();
  s4o.print(s4o.indent_spaces + "return;\n");
  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "} // ");
  symbol->program_type_name->accept(*this);
  s4o.print(FB_FUNCTION_SUFFIX);
  s4o.print(s4o.indent_spaces + "() \n\n");

  /* (C.6) Step undefinitions */
  sfcdecl->generate(symbol->function_block_body, generate_c_sfcdecl_c::stepundef_sd);
  
  /* (C.7) Action undefinitions */
  sfcdecl->generate(symbol->function_block_body, generate_c_sfcdecl_c::actionundef_sd);
  
  delete sfcdecl;

  s4o.indent_left();
  s4o.print("\n\n\n\n");

  return NULL;
}

}; /* generate_c_pous_c */

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_c_config_c: public generate_c_typedecl_c {
    private:
    stage4out_c *s4o_ptr;
    stage4out_c *s4o_incl_ptr;
    
    public:
    generate_c_config_c(stage4out_c *s4o_ptr, stage4out_c *s4o_incl_ptr)
      : generate_c_typedecl_c(s4o_ptr, s4o_incl_ptr) {
      generate_c_config_c::s4o_ptr = s4o_ptr;
      generate_c_config_c::s4o_incl_ptr = s4o_incl_ptr;
    };

    virtual ~generate_c_config_c(void) {}

    typedef enum {
      initprotos_dt,
      initdeclare_dt,
      runprotos_dt,
      rundeclare_dt
    } declaretype_t;

    declaretype_t wanted_declaretype;

    
public:
/********************/
/* 2.1.6 - Pragmas  */
/********************/
void *visit(enable_code_generation_pragma_c * symbol)   {
    s4o_ptr->enable_output();
    s4o_incl_ptr->enable_output();
    return NULL;
}

void *visit(disable_code_generation_pragma_c * symbol)  {
    s4o_ptr->disable_output();
    s4o_incl_ptr->disable_output();    
    return NULL;
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
void *visit(configuration_declaration_c *symbol) {
  generate_c_vardecl_c *vardecl;
  
  /* Insert the header... */
  s4o.print("/*******************************************/\n");
  s4o.print("/*     FILE GENERATED BY iec2c             */\n");
  s4o.print("/* Editing this file is not recommended... */\n");
  s4o.print("/*******************************************/\n\n");
  s4o.print("#include \"iec_std_lib.h\"\n\n");
  s4o.print("#include \"accessor.h\"\n\n"); 
  s4o.print("#include \"POUS.h\"\n\n");

  /* (A) configuration declaration... */
  /* (A.1) configuration name in comment */
  s4o.print("// CONFIGURATION ");
  symbol->configuration_name->accept(*this);
  s4o.print("\n");
  
  /* (A.2) Global variables */
  vardecl = new generate_c_vardecl_c(&s4o,
                                     generate_c_vardecl_c::local_vf,
                                     generate_c_vardecl_c::global_vt,
                                     symbol->configuration_name);
  vardecl->print(symbol);
  delete vardecl;
  s4o.print("\n");

  /* (A.3) Declare global prototypes in include file */
  vardecl = new generate_c_vardecl_c(&s4o_incl,
                                     generate_c_vardecl_c::globalprototype_vf,
                                     generate_c_vardecl_c::global_vt,
                                     symbol->configuration_name);
  vardecl->print(symbol);
  delete vardecl;
  s4o_incl.print("\n");

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
  s4o.print(s4o.indent_spaces);
  s4o.print("BOOL retain;\n");
  s4o.print(s4o.indent_spaces);
  s4o.print("retain = 0;\n");
  
  /* (B.3) Global variables initializations... */
  s4o.print(s4o.indent_spaces);
  vardecl = new generate_c_vardecl_c(&s4o,
                                     generate_c_vardecl_c::constructorinit_vf,
                                     generate_c_vardecl_c::global_vt,
                                     symbol->configuration_name);
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
  s4o.print("(unsigned long tick) {\n");
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
      s4o.print("(unsigned long tick);\n");
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
      s4o.print("(unsigned long tick);\n");
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


class generate_c_resources_c: public generate_c_typedecl_c {

  search_var_instance_decl_c *search_config_instance;
  search_var_instance_decl_c *search_resource_instance;

  private:
    /* The name of the resource curretnly being processed... */
    symbol_c *current_configuration;
    symbol_c *current_resource_name;
    symbol_c *current_task_name;
    symbol_c *current_global_vars;
    bool configuration_name;
    stage4out_c *s4o_ptr;

  public:
    generate_c_resources_c(stage4out_c *s4o_ptr, symbol_c *config_scope, symbol_c *resource_scope, unsigned long time)
      : generate_c_typedecl_c(s4o_ptr) {
      current_configuration = config_scope;
      search_config_instance   = new search_var_instance_decl_c(config_scope);
      search_resource_instance = new search_var_instance_decl_c(resource_scope);
      common_ticktime = time;
      current_resource_name = NULL;
      current_task_name = NULL;
      current_global_vars = NULL;
      configuration_name = false;
      generate_c_resources_c::s4o_ptr = s4o_ptr;
    };

    virtual ~generate_c_resources_c(void) {
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

    /* the qualifier of variables that need to be processed... */
    static const unsigned int none_vq        = 0x0000;
    static const unsigned int constant_vq    = 0x0001;  // CONSTANT
    static const unsigned int retain_vq      = 0x0002;  // RETAIN
    static const unsigned int non_retain_vq  = 0x0004;  // NON_RETAIN

    /* variable used to store the qualifier of program currently being processed... */
    unsigned int current_varqualifier;

    void *print_retain(void) {
      s4o.print(",");
      switch (current_varqualifier) {
        case retain_vq:
          s4o.print("1");
          break;
        case non_retain_vq:
          s4o.print("0");
          break;
        default:
          s4o.print("retain");
          break;
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
        if (configuration_name)
          s4o.print(symbol->value);
        else
          generate_c_base_c::visit(symbol);
        return NULL;
    }

    /********************/
    /* 2.1.6 - Pragmas  */
    /********************/
    void *visit(enable_code_generation_pragma_c * symbol)   {s4o_ptr->enable_output();  return NULL;}
    void *visit(disable_code_generation_pragma_c * symbol)  {s4o_ptr->disable_output(); return NULL;} 
    

    /******************************************/
    /* B 1.4.3 - Declaration & Initialisation */
    /******************************************/

    void *visit(constant_option_c *symbol) {
      current_varqualifier = constant_vq;
      return NULL;
    }

    void *visit(retain_option_c *symbol) {
      current_varqualifier = retain_vq;
      return NULL;
    }

    void *visit(non_retain_option_c *symbol) {
      current_varqualifier = non_retain_vq;
      return NULL;
    }

    /********************************/
    /* B 1.7 Configuration elements */
    /********************************/

    void *visit(configuration_declaration_c *symbol) {
      return symbol->configuration_name->accept(*this);
    }

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
      generate_c_vardecl_c *vardecl;
      
      /* Insert the header... */
      s4o.print("/*******************************************/\n");
      s4o.print("/*     FILE GENERATED BY iec2c             */\n");
      s4o.print("/* Editing this file is not recommended... */\n");
      s4o.print("/*******************************************/\n\n");
      s4o.print("#include \"iec_std_lib.h\"\n\n");
      
      /* (A) resource declaration... */
      /* (A.1) resource name in comment */
      s4o.print("// RESOURCE ");
      current_resource_name->accept(*this);
      s4o.print("\n\n");
      
      s4o.print("extern unsigned long long common_ticktime__;\n\n");

      s4o.print("#include \"accessor.h\"\n");
      s4o.print("#include \"POUS.h\"\n\n");
      s4o.print("#include \"");
      configuration_name = true;
      current_configuration->accept(*this);
      configuration_name = false;
      s4o.print(".h\"\n");

      /* (A.2) Global variables... */
      if (current_global_vars != NULL) {
        vardecl = new generate_c_vardecl_c(&s4o,
                                           generate_c_vardecl_c::local_vf,
                                           generate_c_vardecl_c::global_vt,
                                           current_resource_name);
        vardecl->print(current_global_vars);
        delete vardecl;
        s4o.print("\n");
      }
      
      /* (A.3) POUs inclusion */
      s4o.print("#include \"POUS.c\"\n\n");
      
      wanted_declaretype = declare_dt;
      
      /* (A.4) Resource programs declaration... */
      symbol->task_configuration_list->accept(*this);
      
      /* (A.5) Resource programs declaration... */
      symbol->program_configuration_list->accept(*this);
      
      s4o.print("\n");
      
      /* (B) resource initialisation function... */
      /* (B.1) initialisation function name... */
      s4o.print("void ");
      current_resource_name->accept(*this);
      s4o.print(FB_INIT_SUFFIX);
      s4o.print("(void) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      s4o.print("BOOL retain;\n");
      s4o.print(s4o.indent_spaces);
      s4o.print("retain = 0;\n");
      
      /* (B.2) Global variables initialisations... */
      if (current_global_vars != NULL) {
        s4o.print(s4o.indent_spaces);
        vardecl = new generate_c_vardecl_c(&s4o,
                                           generate_c_vardecl_c::constructorinit_vf,
                                           generate_c_vardecl_c::global_vt,
                                           current_resource_name);
        vardecl->print(current_global_vars);
        delete vardecl;
      }
      s4o.print("\n");
      
      wanted_declaretype = init_dt;
      
      /* (B.3) Tasks initialisations... */
      symbol->task_configuration_list->accept(*this);
      
      /* (B.4) Resource programs initialisations... */
      symbol->program_configuration_list->accept(*this);
      
      s4o.indent_left();
      s4o.print("}\n\n");
      
      /* (C) Resource run function... */
      /* (C.1) Run function name... */
      s4o.print("void ");
      current_resource_name->accept(*this);
      s4o.print(FB_RUN_SUFFIX);
      s4o.print("(unsigned long tick) {\n");
      s4o.indent_right();
      
      wanted_declaretype = run_dt;
      
      /* (C.2) Task management... */
      symbol->task_configuration_list->accept(*this);
      
      /* (C.3) Program run declaration... */
      symbol->program_configuration_list->accept(*this);
      
      s4o.indent_left();
      s4o.print("}\n\n");
      
      if (single_resource) {
        delete current_resource_name;
        current_resource_name = NULL;
      }
      return NULL;
    }
    
/*  PROGRAM [RETAIN | NON_RETAIN] program_name [WITH task_name] ':' program_type_name ['(' prog_conf_elements ')'] */
//SYM_REF6(program_configuration_c, retain_option, program_name, task_name, program_type_name, prog_conf_elements, unused)
    void *visit(program_configuration_c *symbol) {
      switch (wanted_declaretype) {
        case declare_dt:
          s4o.print(s4o.indent_spaces);
          symbol->program_type_name->accept(*this);
          s4o.print(" ");
          current_resource_name->accept(*this);
          s4o.print("__");
          symbol->program_name->accept(*this);
          s4o.print(";\n#define ");
          symbol->program_name->accept(*this);
          s4o.print(" ");
          current_resource_name->accept(*this);
          s4o.print("__");
          symbol->program_name->accept(*this);
          s4o.print("\n");
          break;
        case init_dt:
          if (symbol->retain_option != NULL)
            symbol->retain_option->accept(*this);
          s4o.print(s4o.indent_spaces);
          symbol->program_type_name->accept(*this);
          s4o.print(FB_INIT_SUFFIX);
          s4o.print("(&");
          symbol->program_name->accept(*this);
          print_retain();
          s4o.print(");\n");
          break;
        case run_dt:
          current_program_name = ((identifier_c*)(symbol->program_name))->value;
          if (symbol->task_name != NULL) {
            s4o.print(s4o.indent_spaces);
            s4o.print("if (");
            symbol->task_name->accept(*this);
            s4o.print(") {\n");
            s4o.indent_right(); 
          }
        
          wanted_assigntype = assign_at;
          if (symbol->prog_conf_elements != NULL)
            symbol->prog_conf_elements->accept(*this);
          
          s4o.print(s4o.indent_spaces);
          symbol->program_type_name->accept(*this);
          s4o.print(FB_FUNCTION_SUFFIX);
          s4o.print("(&");
          symbol->program_name->accept(*this);
          s4o.print(");\n");
          
          wanted_assigntype = send_at;
          if (symbol->prog_conf_elements != NULL)
            symbol->prog_conf_elements->accept(*this);
          
          if (symbol->task_name != NULL) {
            s4o.indent_left();
            s4o.print(s4o.indent_spaces + "}\n");
          }
          break;
        default:
          break;
      }
      return NULL;
    }
    
/*  TASK task_name task_initialization */
//SYM_REF2(task_configuration_c, task_name, task_initialization)
    void *visit(task_configuration_c *symbol) {
      current_task_name = symbol->task_name;
      switch (wanted_declaretype) {
        case declare_dt:
          s4o.print(s4o.indent_spaces + "BOOL ");
          current_task_name->accept(*this);
          s4o.print(";\n");
          symbol->task_initialization->accept(*this);
          break;
        case init_dt:
          s4o.print(s4o.indent_spaces);
          current_task_name->accept(*this);
          s4o.print(" = __BOOL_LITERAL(FALSE);\n");
          symbol->task_initialization->accept(*this);
          break;
        case run_dt:
          symbol->task_initialization->accept(*this);
          break;
        default:
          break;
      }
      current_task_name = NULL;
      return NULL;
    }
    
/*  '(' [SINGLE ASSIGN data_source ','] [INTERVAL ASSIGN data_source ','] PRIORITY ASSIGN integer ')' */
//SYM_REF4(task_initialization_c, single_data_source, interval_data_source, priority_data_source, unused)
    void *visit(task_initialization_c *symbol) {
      switch (wanted_declaretype) {
        case declare_dt:
          if (symbol->single_data_source != NULL) {
            s4o.print(s4o.indent_spaces + "R_TRIG ");
            current_task_name->accept(*this);
            s4o.print("_R_TRIG;\n");
          }
          break;
        case init_dt:
          if (symbol->single_data_source != NULL) {
            s4o.print(s4o.indent_spaces + "R_TRIG");
            s4o.print(FB_INIT_SUFFIX);
            s4o.print("(&");
            current_task_name->accept(*this);
            s4o.print("_R_TRIG, retain);\n");
          }
          break;
        case run_dt:
          if (symbol->single_data_source != NULL) {
            symbol_c *config_var_decl = NULL;
            symbol_c *res_var_decl = NULL;
            s4o.print(s4o.indent_spaces + "{");
            symbol_c *current_var_reference = ((global_var_reference_c *)(symbol->single_data_source))->global_var_name;
            res_var_decl = search_resource_instance->get_decl(current_var_reference);
            if (res_var_decl == NULL) {
              config_var_decl = search_config_instance->get_decl(current_var_reference);
              if (config_var_decl == NULL)
                ERROR;
              config_var_decl->accept(*this);
            }
            else {
              res_var_decl->accept(*this);
            }
            s4o.print("* ");
            symbol->single_data_source->accept(*this);
            s4o.print(" = __GET_GLOBAL_");
            symbol->single_data_source->accept(*this);
            s4o.print("();");
            s4o.print(SET_VAR);
            s4o.print("(");
            current_task_name->accept(*this);
            s4o.print("_R_TRIG.,CLK, *");
            symbol->single_data_source->accept(*this);
            s4o.print(");}\n");
            s4o.print(s4o.indent_spaces + "R_TRIG");
            s4o.print(FB_FUNCTION_SUFFIX);
            s4o.print("(&");
            current_task_name->accept(*this);
            s4o.print("_R_TRIG);\n");
            s4o.print(s4o.indent_spaces);
            current_task_name->accept(*this);
            s4o.print(" = ");
            s4o.print(GET_VAR);
            s4o.print("(");
            current_task_name->accept(*this);
            s4o.print("_R_TRIG.Q)");
          }
          else {
            s4o.print(s4o.indent_spaces);
            current_task_name->accept(*this);
            s4o.print(" = ");
            if (symbol->interval_data_source != NULL) {
              calculate_time_c calculate_time;
              symbol->interval_data_source->accept(calculate_time);
              unsigned long time = calculate_time.get_time();
              if (time != 0) {
                s4o.print("!(tick % ");
                s4o.print_integer((int)(time / common_ticktime));
                s4o.print(")");
              }
              else
                s4o.print("1");
            }
            else 
              s4o.print("1");
          }
          s4o.print(";\n");
          break;
        default:
          break;
      }
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
            vartype = search_config_instance->get_vartype(current_var_reference);
        }
        else
          vartype = search_resource_instance->get_vartype(current_var_reference);
        
        s4o.print(s4o.indent_spaces + "{extern ");
        var_decl->accept(*this);
        s4o.print(" *");
        symbol->prog_data_source->accept(*this);
        s4o.print("; ");
        s4o.printupper(current_program_name);
        s4o.print(".");
        symbol->symbolic_variable->accept(*this);
        s4o.print(" = ");
        if (vartype == search_var_instance_decl_c::global_vt)
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
            vartype = search_config_instance->get_vartype(current_var_reference);
        }
        else
          vartype = search_resource_instance->get_vartype(current_var_reference);
        
        s4o.print(s4o.indent_spaces + "{extern ");
        var_decl->accept(*this);
        s4o.print(" *");
        symbol->data_sink->accept(*this);
        s4o.print("; ");
        if (vartype == search_var_instance_decl_c::global_vt)
          s4o.print("*");
        symbol->data_sink->accept(*this);
        s4o.print(" = ");
        s4o.printupper(current_program_name);
        s4o.print(".");
        symbol->symbolic_variable->accept(*this);
        s4o.print(";};\n");
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

class generate_c_c: public iterator_visitor_c {
  public:
    typedef enum {
      none_gm,
      datatypes_gm,
      pous_gm,
    } generate_mode_t;

  protected:
    stage4out_c &s4o;
    stage4out_c pous_s4o;
    stage4out_c pous_incl_s4o;
    stage4out_c located_variables_s4o;
    stage4out_c variables_s4o;
    generate_c_datatypes_c generate_c_datatypes;
    generate_c_pous_c generate_c_pous;
    
    symbol_c *current_configuration;

    const char *current_name;
    const char *current_builddir;

    unsigned long long common_ticktime;

    generate_mode_t current_mode;

  public:
    generate_c_c(stage4out_c *s4o_ptr, const char *builddir): 
            s4o(*s4o_ptr),
            pous_s4o(builddir, "POUS", "c"),
            pous_incl_s4o(builddir, "POUS", "h"),
            located_variables_s4o(builddir, "LOCATED_VARIABLES","h"),
            variables_s4o(builddir, "VARIABLES","csv"),
            generate_c_datatypes(&pous_s4o, &pous_incl_s4o),
            generate_c_pous(&pous_s4o, &pous_incl_s4o) {
      current_builddir = builddir;
      current_configuration = NULL;
      current_mode = none_gm;
    }
            
    ~generate_c_c(void) {}



/********************/
/* 2.1.6 - Pragmas  */
/********************/
    void *visit(enable_code_generation_pragma_c * symbol)  {
      s4o                  .enable_output();  
      pous_s4o             .enable_output();  
      pous_incl_s4o        .enable_output();  
      located_variables_s4o.enable_output();  
      variables_s4o        .enable_output();  
      return NULL;
    }
    
    void *visit(disable_code_generation_pragma_c * symbol)  {
      s4o                  .disable_output();  
      pous_s4o             .disable_output();  
      pous_incl_s4o        .disable_output();  
      located_variables_s4o.disable_output();  
      variables_s4o        .disable_output();  
      return NULL;
    } 


/***************************/
/* B 0 - Programming Model */
/***************************/
    void *visit(library_c *symbol) {
      pous_incl_s4o.print("#ifndef __POUS_H\n#define __POUS_H\n\n#include \"accessor.h\"\n\n");

      current_mode = datatypes_gm;
      for(int i = 0; i < symbol->n; i++) {
        symbol->elements[i]->accept(*this);
      }

      current_mode = pous_gm;
      for(int i = 0; i < symbol->n; i++) {
        symbol->elements[i]->accept(*this);
      }

      pous_incl_s4o.print("#endif //__POUS_H\n");
      
      generate_var_list_c generate_var_list(&variables_s4o, symbol);
      generate_var_list.generate_programs(symbol);
      generate_var_list.generate_variables(symbol);
      variables_s4o.print("\n// Ticktime\n");
      variables_s4o.print_long_long_integer(common_ticktime, false);
      variables_s4o.print("\n");

      generate_location_list_c generate_location_list(&located_variables_s4o);
      symbol->accept(generate_location_list);
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

/********************************/
/* B 1.3.3 - Derived data types */
/********************************/
    /*  TYPE type_declaration_list END_TYPE */
    void *visit(data_type_declaration_c *symbol) {
      switch (current_mode) {
        case datatypes_gm:
          symbol->accept(generate_c_datatypes);
          break;
        default:
          break;
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
      switch (current_mode) {
        case datatypes_gm:
          symbol->var_declarations_list->accept(generate_c_datatypes);
          break;
        case pous_gm:
          symbol->accept(generate_c_pous);
          break;
        default:
          break;
      }
      return NULL;
    }
    
/*****************************/
/* B 1.5.2 - Function Blocks */
/*****************************/
    void *visit(function_block_declaration_c *symbol) {
        switch (current_mode) {
          case datatypes_gm:
            symbol->var_declarations->accept(generate_c_datatypes);
            break;
          case pous_gm:
            symbol->accept(generate_c_pous);
            break;
          default:
            break;
        }
        return NULL;
    }
    
/**********************/
/* B 1.5.3 - Programs */
/**********************/    
    void *visit(program_declaration_c *symbol) {
        switch (current_mode) {
          case datatypes_gm:
            symbol->var_declarations->accept(generate_c_datatypes);
            break;
          case pous_gm:
            symbol->accept(generate_c_pous);
            break;
          default:
            break;
        }
        return NULL;
    }
    

/********************************/
/* B 1.7 Configuration elements */
/********************************/
    void *visit(configuration_declaration_c *symbol) {
      switch (current_mode) {
        case datatypes_gm:
          if (symbol->global_var_declarations != NULL)
            symbol->global_var_declarations->accept(generate_c_datatypes);
          break;

        case pous_gm:
          static int configuration_count = 0;

          if (configuration_count++) {
            /* the first configuration is the one we will use!! */
            STAGE4_ERROR(symbol, symbol, "A previous CONFIGURATION has already been declared (C code generation currently only allows a single configuration).");
            ERROR;
          }

          current_configuration = symbol;

          {
            calculate_common_ticktime_c calculate_common_ticktime;
            symbol->accept(calculate_common_ticktime);
            common_ticktime = calculate_common_ticktime.get_common_ticktime();
            if (common_ticktime == 0) {
              STAGE4_ERROR(symbol, symbol, "You must define at least one periodic task (to set cycle period)!");
              ERROR;
            }

            symbol->configuration_name->accept(*this);
            
            stage4out_c config_s4o(current_builddir, current_name, "c");
            stage4out_c config_incl_s4o(current_builddir, current_name, "h");
            generate_c_config_c generate_c_config(&config_s4o, &config_incl_s4o);
            symbol->accept(generate_c_config);

            config_s4o.print("unsigned long long common_ticktime__ = ");
            config_s4o.print_long_long_integer(common_ticktime);
            config_s4o.print("; /*ns*/\n");
            config_s4o.print("unsigned long greatest_tick_count__ = ");
            config_s4o.print_long_integer(calculate_common_ticktime.get_greatest_tick_count());
            config_s4o.print("; /*tick*/\n");
          }

          symbol->resource_declarations->accept(*this);

          current_configuration = NULL;
          break;

        default:
          break;
      }
      return NULL;
    }

    void *visit(resource_declaration_c *symbol) {
      switch (current_mode) {
        case datatypes_gm:
          if (symbol->global_var_declarations != NULL)
            symbol->global_var_declarations->accept(generate_c_datatypes);
          break;
        case pous_gm:
          symbol->resource_name->accept(*this);
          {
            stage4out_c resources_s4o(current_builddir, current_name, "c");
            generate_c_resources_c generate_c_resources(&resources_s4o, current_configuration, symbol, common_ticktime);
            symbol->accept(generate_c_resources);
          }
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(single_resource_declaration_c *symbol) {
      switch (current_mode) {
        case pous_gm:
          {
            stage4out_c resources_s4o(current_builddir, "RESOURCE", "c");
            generate_c_resources_c generate_c_resources(&resources_s4o, current_configuration, symbol, common_ticktime);
            symbol->accept(generate_c_resources);
          }
          break;
        default:
          break;
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




visitor_c *new_code_generator(stage4out_c *s4o, const char *builddir)  {return new generate_c_c(s4o, builddir);}
void delete_code_generator(visitor_c *code_generator) {delete code_generator;}


