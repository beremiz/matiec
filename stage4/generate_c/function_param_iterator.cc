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
 * Function parameter iterator.
 * Iterate through the in/out parameters of a function declaration.
 * Function blocks are also suported.
 *
 * This is part of the 4th stage that generates
 * a c++ source program equivalent to the IL and ST
 * code.
 */






//#include <stdio.h>  /* required for NULL */
//#include <string>
//#include <iostream>

//#include "../../util/symtable.hh"

//#include "generate_c.hh"


#include "../../absyntax/visitor.hh"


/* given a function_declaration_c, iterate through each
 * function in/out/inout parameter, returning the name
 * of each parameter...function_param_iterator_c
 */
class function_param_iterator_c : public null_visitor_c {
  public:
    /* A type to specify the type of parameter.
     * VAR_INPUT => direction_in
     * VAR_OUTPUT => direction_out
     * VAR_IN_OUT => direction_inout
     * VAR_EXTERNAL => direction_extref
     *
     * Note that VAR_EXTERNAL declares variables that are in reality references
     * to global variables. This is used only inside programs!
     * These references to external variables must be correctly initialised to refer
     * to the correct global variable. Note that the user may define which variable is to be
     * referenced in a CONFIGURATION, and that different instantiations of a program
     * may have the same external variable reference diffenrent global variables!
     * The references must therefore be correctly initialised when the program instance
     * is created. This may be done by the PROGRAM class constructor since the ST and IL
     * languages do not allow the VAR_EXTERNAL reference to change at runtime
     * for a specific instance.
     *
     * We therefore need to call a PROGRAM class constructor with the variables
     * that should be refernced by the VAR_EXTERNAL variables. The direction_extref will
     * be used to identify these parameters!
     */
    typedef enum {direction_in, direction_out, direction_inout, direction_extref} param_direction_t ;


  private:
      /* a pointer to the function_block_declaration_c
       * or function_declaration_c currently being analysed.
       */
    symbol_c *f_decl;
    int next_param, param_count;
    identifier_c *current_param_name;
    symbol_c *current_param_type;
    symbol_c *current_param_default_value;
    param_direction_t current_param_direction;
    bool en_declared;
    bool eno_declared;

  private:
    void* handle_param_list(list_c *list) {
      if (next_param <= param_count + list->n)
        return list->elements[next_param - param_count - 1];

      /* the desired param is not on this list... */
      param_count += list->n;
     return NULL;
    }

    void* handle_single_param(symbol_c *var_name) {
      param_count++;
      if (next_param == param_count)
        return var_name;

      /* not yet the desired param... */
     return NULL;
    }

    void* iterate_list(list_c *list) {
      void *res;
      for (int i = 0; i < list->n; i++) {
        res = list->elements[i]->accept(*this);
        if (res != NULL)
	        return res;
      }
      return NULL;
   }


  public:
    /* start off at the first parameter once again... */
    void reset(void) {
      next_param = param_count = 0;
      current_param_name = NULL;
      current_param_type = current_param_default_value = NULL;
      en_declared = false;
      eno_declared = false;
    }

    /* initialise the iterator object.
     * We must be given a reference to the function declaration
     * that will be analysed...
     */
    function_param_iterator_c(function_declaration_c *f_decl) {
      this->f_decl = f_decl;
      reset();
    }

    /* initialise the iterator object.
     * We must be given a reference to the function block declaration
     * that will be analysed...
     */
    function_param_iterator_c(function_block_declaration_c *fb_decl) {
      this->f_decl = fb_decl;
      reset();
    }

    /* initialise the iterator object.
     * We must be given a reference to the program declaration
     * that will be analysed...
     */
    function_param_iterator_c(program_declaration_c *p_decl) {
      this->f_decl = p_decl;
      reset();
    }

    /* Skip to the next parameter. After object creation,
     * the object references on parameter _before_ the first, so
     * this function must be called once to get the object to
     * reference the first parameter...
     *
     * Returns the parameter's name!
     */
    identifier_c *next(void) {
      void *res;
      identifier_c *identifier;
      param_count = 0;
      next_param++;
      res = f_decl->accept(*this);
      if (res != NULL) {
        symbol_c *sym = (symbol_c *)res;
        identifier = dynamic_cast<identifier_c *>(sym);
        if (identifier == NULL)
          ERROR;
      }
      else if (!en_declared) {
        current_param_direction = direction_in;
        identifier = declare_en_param();
      }
      else if (!eno_declared) {
        current_param_direction = direction_out;
        identifier = declare_eno_param();
      }
      else
        return NULL;
      
      current_param_name = identifier;
      return current_param_name;
    }

    identifier_c *declare_en_param(void) {
      en_declared = true;
      identifier_c *identifier = new identifier_c("EN");
      current_param_type = (symbol_c*)(new bool_type_name_c());
      current_param_default_value = (symbol_c*)(new boolean_literal_c(current_param_type, new boolean_true_c()));
      return identifier;
    }

    identifier_c *declare_eno_param(void) {
      eno_declared = true;
      identifier_c *identifier = new identifier_c("ENO");
      current_param_type = (symbol_c*)(new bool_type_name_c());
      current_param_default_value = NULL;
      return identifier;
    }

    /* Returns the currently referenced parameter's default value,
     * or NULL if none is specified in the function declrataion itself.
     */
    symbol_c *default_value(void) {
      return current_param_default_value;
    }

    /* Returns the currently referenced parameter's type name. */
    symbol_c *param_type(void) {
      return current_param_type;
    }

    /* Returns the currently referenced parameter's data passing direction.
     * i.e. VAR_INPUT, VAR_OUTPUT or VAR_INOUT
     */
    param_direction_t param_direction(void) {
      return current_param_direction;
    }

/******************************************/
/* B 1.4.3 - Declaration & Initialisation */
/******************************************/
    void *visit(input_declarations_c *symbol) {
      TRACE("input_declarations_c");
      current_param_direction = direction_in;
      return symbol->input_declaration_list->accept(*this);
    }
    void *visit(input_declaration_list_c *symbol) {TRACE("input_declaration_list_c"); return iterate_list(symbol);}
    void *visit(edge_declaration_c *symbol) {TRACE("edge_declaration_c"); return symbol->var1_list->accept(*this);}
    void *visit(en_param_declaration_c *symbol) {
      TRACE("en_param_declaration_c");
      if (en_declared) ERROR;
      return (void *)declare_en_param();
    }

    /* var1_list ':' array_spec_init */
    //SYM_REF2(array_var_init_decl_c, var1_list, array_spec_init)
    void *visit(array_var_init_decl_c *symbol) {TRACE("array_var_init_decl_c"); return symbol->var1_list->accept(*this);}
    
    /*  var1_list ':' initialized_structure */
    //SYM_REF2(structured_var_init_decl_c, var1_list, initialized_structure)
    void *visit(structured_var_init_decl_c *symbol) {TRACE("structured_var_init_decl_c"); return symbol->var1_list->accept(*this);}
    
#if 0
/* name_list ':' function_block_type_name ASSIGN structure_initialization */
/* structure_initialization -> may be NULL ! */
SYM_REF4(fb_name_decl_c, fb_name_list, function_block_type_name, structure_initialization, unused)

/* name_list ',' fb_name */
SYM_LIST(fb_name_list_c)
#endif

    void *visit(output_declarations_c *symbol) {
      TRACE("output_declarations_c");
      current_param_direction = direction_out;
      return symbol->var_init_decl_list->accept(*this);
    }
    void *visit(eno_param_declaration_c *symbol) {
      TRACE("eno_param_declaration_c");
      if (eno_declared) ERROR;
      return (void *)declare_eno_param();
    }
    void *visit(input_output_declarations_c *symbol) {
      TRACE("input_output_declarations_c");
      current_param_direction = direction_inout;
      return symbol->var_declaration_list->accept(*this);
    }
    void *visit(var_declaration_list_c *symbol) {TRACE("var_declaration_list_c"); return iterate_list(symbol);}


    /*  var1_list ':' array_specification */
    //SYM_REF2(array_var_declaration_c, var1_list, array_specification)
    void *visit(array_var_declaration_c *symbol) {TRACE("array_var_declaration_c"); return symbol->var1_list->accept(*this);}

    /*  var1_list ':' structure_type_name */
    //SYM_REF2(structured_var_declaration_c, var1_list, structure_type_name)
    void *visit(structured_var_declaration_c *symbol) {TRACE("structured_var_declaration_c"); return symbol->var1_list->accept(*this);}

    /* VAR [CONSTANT] var_init_decl_list END_VAR */
    void *visit(var_declarations_c *symbol) {TRACE("var_declarations_c"); return NULL;}

#if 0
/*  VAR RETAIN var_init_decl_list END_VAR */
SYM_REF2(retentive_var_declarations_c, var_init_decl_list, unused)

/*  VAR [CONSTANT|RETAIN|NON_RETAIN] located_var_decl_list END_VAR */
/* option -> may be NULL ! */
SYM_REF2(located_var_declarations_c, option, located_var_decl_list)

/* helper symbol for located_var_declarations */
/* located_var_decl_list located_var_decl ';' */
SYM_LIST(located_var_decl_list_c)

/*  [variable_name] location ':' located_var_spec_init */
/* variable_name -> may be NULL ! */
SYM_REF4(located_var_decl_c, variable_name, location, located_var_spec_init, unused)
#endif

/*| VAR_EXTERNAL [CONSTANT] external_declaration_list END_VAR */
/* option -> may be NULL ! */
// SYM_REF2(external_var_declarations_c, option, external_declaration_list)
    void *visit(external_var_declarations_c *symbol) {
      TRACE("external_var_declarations_c");
      current_param_direction = direction_extref;
      return symbol->external_declaration_list->accept(*this);
    }

/* helper symbol for external_var_declarations */
/*| external_declaration_list external_declaration';' */
// SYM_LIST(external_declaration_list_c)
    void *visit(external_declaration_list_c *symbol) {TRACE("external_declaration_list_c"); return iterate_list(symbol);}

/*  global_var_name ':' (simple_specification|subrange_specification|enumerated_specification|array_specification|prev_declared_structure_type_name|function_block_type_name */
//SYM_REF2(external_declaration_c, global_var_name, specification)
    void *visit(external_declaration_c *symbol) {
      TRACE("external_declaration_c");
      /* It is OK to store these values in the current_param_XXX
       * variables, because if the desired parameter is not in the
       * variable list we will be analysing, the current_param_XXXX
       * variables will get overwritten when we visit the next
       * var1_init_decl_c list!
       */
      current_param_default_value = spec_init_sperator_c::get_init(symbol->specification);
      current_param_type = spec_init_sperator_c::get_spec(symbol->specification);

      return handle_single_param(symbol->global_var_name);
    }


#if 0
/*| VAR_GLOBAL [CONSTANT|RETAIN] global_var_decl_list END_VAR */
/* option -> may be NULL ! */
SYM_REF2(global_var_declarations_c, option, global_var_decl_list)

/* helper symbol for global_var_declarations */
/*| global_var_decl_list global_var_decl ';' */
SYM_LIST(global_var_decl_list_c)

/*| global_var_spec ':' [located_var_spec_init|function_block_type_name] */
/* type_specification ->may be NULL ! */
SYM_REF2(global_var_decl_c, global_var_spec, type_specification)

/*| global_var_name location */
SYM_REF2(global_var_spec_c, global_var_name, location)

/*  AT direct_variable */
SYM_REF2(location_c, direct_variable, unused)

/*| global_var_list ',' global_var_name */
SYM_LIST(global_var_list_c)

/*  var1_list ':' single_byte_string_spec */
SYM_REF2(single_byte_string_var_declaration_c, var1_list, single_byte_string_spec)

/*  STRING ['[' integer ']'] [ASSIGN single_byte_character_string] */
/* integer ->may be NULL ! */
/* single_byte_character_string ->may be NULL ! */
SYM_REF2(single_byte_string_spec_c, integer, single_byte_character_string)

/*  var1_list ':' double_byte_string_spec */
SYM_REF2(double_byte_string_var_declaration_c, var1_list, double_byte_string_spec)

/*  WSTRING ['[' integer ']'] [ASSIGN double_byte_character_string] */
/* integer ->may be NULL ! */
/* double_byte_character_string ->may be NULL ! */
SYM_REF2(double_byte_string_spec_c, integer, double_byte_character_string)

/*| VAR [RETAIN|NON_RETAIN] incompl_located_var_decl_list END_VAR */
/* option ->may be NULL ! */
SYM_REF2(incompl_located_var_declarations_c, option, incompl_located_var_decl_list)

/* helper symbol for incompl_located_var_declarations */
/*| incompl_located_var_decl_list incompl_located_var_decl ';' */
SYM_LIST(incompl_located_var_decl_list_c)

/*  variable_name incompl_location ':' var_spec */
SYM_REF4(incompl_located_var_decl_c, variable_name, incompl_location, var_spec, unused)

/*  AT incompl_location_token */
SYM_TOKEN(incompl_location_c)
#endif


    void *visit(var1_init_decl_c *symbol) {
      TRACE("var1_init_decl_c");
      /* It is OK to store these values in the current_param_XXX
       * variables, because if the desired parameter is not in the
       * variable list we will be analysing, the current_param_XXXX
       * variables will get overwritten when we visit the next
       * var1_init_decl_c list!
       */
      current_param_default_value = spec_init_sperator_c::get_init(symbol->spec_init);
      current_param_type = spec_init_sperator_c::get_spec(symbol->spec_init);

      return symbol->var1_list->accept(*this);
    }



    void *visit(var1_list_c *symbol) {
      TRACE("var1_list_c");
      return handle_param_list(symbol);
    }

    void *visit(var_init_decl_list_c *symbol) {TRACE("var_init_decl_list_c"); return iterate_list(symbol);}


/***********************/
/* B 1.5.1 - Functions */
/***********************/
    void *visit(function_declaration_c *symbol) {TRACE("function_declaration_c"); return symbol->var_declarations_list->accept(*this);}
    /* intermediate helper symbol for function_declaration */
    void *visit(var_declarations_list_c *symbol) {TRACE("var_declarations_list_c"); return iterate_list(symbol);}
    void *visit(function_var_decls_c *symbol) {TRACE("function_var_decls_c"); /* ignore */ return NULL;}


/*****************************/
/* B 1.5.2 - Function Blocks */
/*****************************/
/*  FUNCTION_BLOCK derived_function_block_name io_OR_other_var_declarations function_block_body END_FUNCTION_BLOCK */
    void *visit(function_block_declaration_c *symbol) {TRACE("function_block_declaration_c"); return symbol->var_declarations->accept(*this);}

/* intermediate helper symbol for function_declaration */
/*  { io_var_declarations | other_var_declarations }   */
/*
 * NOTE: we re-use the var_declarations_list_c
 */

/*  VAR_TEMP temp_var_decl_list END_VAR */
    void *visit(temp_var_decls_c *symbol) {TRACE("temp_var_decls_c"); /* ignore */ return NULL;}
    void *visit(temp_var_decls_list_c *symbol) {TRACE("temp_var_decls_list_c"); /* ignore */ return NULL;}

/*  VAR NON_RETAIN var_init_decl_list END_VAR */
    void *visit(non_retentive_var_decls_c *symbol) {TRACE("non_retentive_var_decls_c"); /* ignore */ return NULL;}


/**********************/
/* B 1.5.3 - Programs */
/**********************/
/*  PROGRAM program_type_name program_var_declarations_list function_block_body END_PROGRAM */
// SYM_REF4(program_declaration_c, program_type_name, var_declarations, function_block_body, unused)
    void *visit(program_declaration_c *symbol) {TRACE("program_declaration_c"); return symbol->var_declarations->accept(*this);}

/* intermediate helper symbol for program_declaration_c */
/*  { io_var_declarations | other_var_declarations }   */
/*
 * NOTE: we re-use the var_declarations_list_c
 */

};







