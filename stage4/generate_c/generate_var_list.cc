/*
 * (c) 2007 Mario de Sousa and Laurent Bessard
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

//#include <stdio.h>  /* required for NULL */
//#include <string>
//#include <iostream>

//#include "../../util/symtable.hh"




typedef struct
{
  symbol_c *symbol;
} SYMBOL;




/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_var_list_c: protected generate_c_typedecl_c {
  
  private:
    symbol_c *current_var_type_symbol;
    unsigned int current_var_number;
    unsigned int step_number;
    unsigned int transition_number;
    unsigned int action_number;
    std::list<SYMBOL> current_symbol_list;
    search_base_type_c search_base_type;
    search_fb_typedecl_c *search_fb_typedecl;
    
  public:
    generate_var_list_c(stage4out_c *s4o_ptr, symbol_c *scope)
    : generate_c_typedecl_c(s4o_ptr) {
      search_fb_typedecl = new search_fb_typedecl_c(scope);
      current_var_type_symbol = NULL;
      current_var_number = 0;
    }
    
    ~generate_var_list_c(void) {
      delete search_fb_typedecl;
    }
    
    void update_var_type_symbol(symbol_c *symbol, bool is_fb = false) {
      this->current_var_type_symbol = spec_init_sperator_c::get_spec(symbol);
      if (this->current_var_type_symbol == NULL)
        ERROR;
      
      if (is_fb)
        this->current_var_type_symbol = search_fb_typedecl->get_decl(this->current_var_type_symbol);
      else
        this->current_var_type_symbol = (symbol_c *)(this->current_var_type_symbol->accept(search_base_type));
      if (this->current_var_type_symbol == NULL)
        ERROR;
    }

    void reset_var_type_symbol(void) {
      this->current_var_type_symbol = NULL;
    }
    
    void declare_variables(symbol_c *symbol, bool is_fb = false) {
      list_c *list = dynamic_cast<list_c *>(symbol);
      /* should NEVER EVER occur!! */
      if (list == NULL) ERROR;

      for(int i = 0; i < list->n; i++) {
        declare_variable(list->elements[i], is_fb);
      }
    }
    
    void declare_variable(symbol_c *symbol, bool is_fb = false) {
      if (is_fb) {
        SYMBOL *current_name;
        current_name = new SYMBOL;
        current_name->symbol = symbol;
        current_symbol_list.push_back(*current_name);
        this->current_var_type_symbol->accept(*this);
        current_symbol_list.pop_back();
      }
      else {
        print_var_number();
        s4o.print(";");
        print_symbol_list();
        symbol->accept(*this);
        s4o.print(";");
        print_symbol_list();
        symbol->accept(*this);
        s4o.print(";");
        this->current_var_type_symbol->accept(*this);
        s4o.print(";\n");
      }
    }
    
    void print_var_number(void) {
      char str[10];
      sprintf(str, "%d", current_var_number);
      s4o.print(str);
      current_var_number++;
    }
        
    void print_step_number(void) {
      char str[10];
      sprintf(str, "%d", step_number);
      s4o.print(str);
    }
    
    void print_transition_number(void) {
      char str[10];
      sprintf(str, "%d", transition_number);
      s4o.print(str);
    }
    
    void print_action_number(void) {
      char str[10];
      sprintf(str, "%d", action_number);
      s4o.print(str);
    }
    
    void print_symbol_list(void) {
      std::list<SYMBOL>::iterator pt;
      for(pt = current_symbol_list.begin(); pt != current_symbol_list.end(); pt++) {
        pt->symbol->accept(*this);
        s4o.print(".");
      }
    }
    
    /********************************************/
    /* B.1.4.3   Declaration and initilization  */
    /********************************************/
    
    /*  [variable_name] location ':' located_var_spec_init */
    /* variable_name -> may be NULL ! */
    //SYM_REF4(located_var_decl_c, variable_name, location, located_var_spec_init, unused)
    void *visit(located_var_decl_c *symbol) {
        /* Start off by setting the current_var_type_symbol and
         * current_var_init_symbol private variables...
         */
        update_var_type_symbol(symbol->located_var_spec_init);
        
        if (symbol->variable_name != NULL)
          declare_variable(symbol->variable_name);
        
        current_var_type_symbol = NULL;
        return NULL;
    }
    
    /*  var1_list ':' array_spec_init */
    // SYM_REF2(array_var_init_decl_c, var1_list, array_spec_init)
    void *visit(array_var_init_decl_c *symbol) {
      TRACE("array_var_init_decl_c");
      /* Start off by setting the current_var_type_symbol and
       * current_var_init_symbol private variables...
       */
      update_var_type_symbol(symbol->array_spec_init);
    
      declare_variables(symbol->var1_list);
    
      /* Values no longer in scope, and therefore no longer used.
       * Make an effort to keep them set to NULL when not in use
       * in order to catch bugs as soon as possible...
       */
      reset_var_type_symbol();
    
      return NULL;
    }

    /*  var1_list ':' initialized_structure */
    // SYM_REF2(structured_var_init_decl_c, var1_list, initialized_structure)
    void *visit(structured_var_init_decl_c *symbol) {
      TRACE("structured_var_init_decl_c");
      /* Please read the comments inside the var1_init_decl_c
       * visitor, as they apply here too.
       */
    
      /* Start off by setting the current_var_type_symbol and
       * current_var_init_symbol private variables...
       */
      update_var_type_symbol(symbol->initialized_structure);
    
      /* now to produce the c equivalent... */
      declare_variables(symbol->var1_list);
    
      /* Values no longer in scope, and therefore no longer used.
       * Make an effort to keep them set to NULL when not in use
       * in order to catch bugs as soon as possible...
       */
      reset_var_type_symbol();
    
      return NULL;
    }
    
    /* fb_name_list ':' function_block_type_name ASSIGN structure_initialization */
    /* structure_initialization -> may be NULL ! */
    void *visit(fb_name_decl_c *symbol) {
      TRACE("fb_name_decl_c");
      /* Please read the comments inside the var1_init_decl_c
       * visitor, as they apply here too.
       */
    
      /* Start off by setting the current_var_type_symbol and
       * current_var_init_symbol private variables...
       */
      update_var_type_symbol(symbol, true);
    
      /* now to produce the c equivalent... */
      declare_variables(symbol->fb_name_list, true);
    
      /* Values no longer in scope, and therefore no longer used.
       * Make an effort to keep them set to NULL when not in use
       * in order to catch bugs as soon as possible...
       */
      reset_var_type_symbol();
    
      return NULL;
    }

    /*  global_var_name ':' (simple_specification|subrange_specification|enumerated_specification|array_specification|prev_declared_structure_type_name|function_block_type_name */
    //SYM_REF2(external_declaration_c, global_var_name, specification)
    void *visit(external_declaration_c *symbol) {
      TRACE("external_declaration_c");
      /* Please read the comments inside the var1_init_decl_c
       * visitor, as they apply here too.
       */
    
      /* Start off by setting the current_var_type_symbol and
       * current_var_init_symbol private variables...
       */
      this->current_var_type_symbol = (symbol_c *)(symbol->specification->accept(*search_fb_typedecl));
      if (this->current_var_type_symbol == NULL) {
        this->current_var_type_symbol = symbol->specification;
      
        declare_variable(symbol->global_var_name);
      }
      else
        declare_variable(symbol->global_var_name, true);
      
      /* Values no longer in scope, and therefore no longer used.
       * Make an effort to keep them set to NULL when not in use
       * in order to catch bugs as soon as possible...
       */
      reset_var_type_symbol();
    
      return NULL;
    }

    /*| global_var_spec ':' [located_var_spec_init|function_block_type_name] */
    /* type_specification ->may be NULL ! */
    // SYM_REF2(global_var_decl_c, global_var_spec, type_specification)
    void *visit(global_var_decl_c *symbol) {
      TRACE("global_var_decl_c");
      /* Please read the comments inside the var1_init_decl_c
       * visitor, as they apply here too.
       */
    
      /* Start off by setting the current_var_type_symbol and
       * current_var_init_symbol private variables...
       */
      update_var_type_symbol(symbol->type_specification);
    
      /* now to produce the c equivalent... */
      symbol->global_var_spec->accept(*this);
    
      /* Values no longer in scope, and therefore no longer used.
       * Make an effort to keep them set to NULL when not in use
       * in order to catch bugs as soon as possible...
       */
      reset_var_type_symbol();
    
      return NULL;
    }
    
    void *visit(global_var_list_c *symbol) {
      declare_variables(symbol);
      return NULL;
    }
    
    /*| global_var_name location */
    // SYM_REF2(global_var_spec_c, global_var_name, location)
    void *visit(global_var_spec_c *symbol) {
      if (symbol->global_var_name != NULL)
        declare_variable(symbol->global_var_name);
      return NULL;
    }
    
    void *visit(var1_init_decl_c *symbol) {
      TRACE("var1_init_decl_c");
    
      /* Start off by setting the current_var_type_symbol and
       * current_var_init_symbol private variables...
       */
      update_var_type_symbol(symbol->spec_init);
    
      /* now to produce the c equivalent... */
      declare_variables(symbol->var1_list);
    
      /* Values no longer in scope, and therefore no longer used.
       * Make an effort to keep them set to NULL when not in use
       * in order to catch bugs as soon as possible...
       */
      reset_var_type_symbol();
    
      return NULL;
    }

/**************************************/
/* B.1.5 - Program organization units */
/**************************************/

/*****************************/
/* B 1.5.2 - Function Blocks */
/*****************************/
    void *visit(function_block_declaration_c *symbol) {
      symbol->var_declarations->accept(*this);
      symbol->fblock_body->accept(*this);
      return NULL;
    }

/**********************/
/* B 1.5.3 - Programs */
/**********************/
    void *visit(program_declaration_c *symbol) {
      symbol->var_declarations->accept(*this);
      symbol->function_block_body->accept(*this);
      return NULL;
    }

/**********************************************/
/* B 1.6 - Sequential function chart elements */
/**********************************************/
    
    /* | sequential_function_chart sfc_network */
    //SYM_LIST(sequential_function_chart_c)
    void *visit(sequential_function_chart_c *symbol) {
      step_number = 0;
      transition_number = 0;
      action_number = 0;
      for(int i = 0; i < symbol->n; i++) {
        symbol->elements[i]->accept(*this);
      }
      return NULL;
    }
    
    /* INITIAL_STEP step_name ':' action_association_list END_STEP */
    //SYM_REF2(initial_step_c, step_name, action_association_list)
    void *visit(initial_step_c *symbol) {
      print_var_number();
      s4o.print(";");
      print_symbol_list();
      symbol->step_name->accept(*this);
      s4o.print(".X;");
      print_symbol_list();
      s4o.print("step_list[");
      print_step_number();
      s4o.print("].state;STEP;\n");
      step_number++;
      return NULL;
    }
    
    /* STEP step_name ':' action_association_list END_STEP */
    //SYM_REF2(step_c, step_name, action_association_list)
    void *visit(step_c *symbol) {
      print_var_number();
      s4o.print(";");
      print_symbol_list();
      symbol->step_name->accept(*this);
      s4o.print(".X;");
      print_symbol_list();
      s4o.print("step_list[");
      print_step_number();
      s4o.print("].state;STEP;\n");
      step_number++;
      return NULL;
    }
    
    /* TRANSITION [transition_name] ['(' PRIORITY ASSIGN integer ')'] 
     *   FROM steps TO steps 
     *   transition_condition 
     * END_TRANSITION
     */
    /* transition_name -> may be NULL ! */
    /* integer -> may be NULL ! */
    //SYM_REF5(transition_c, transition_name, integer, from_steps, to_steps, transition_condition)
    void *visit(transition_c *symbol) {
      print_var_number();
      s4o.print(";");
      print_symbol_list();
      symbol->from_steps->accept(*this);
      s4o.print("->");
      symbol->to_steps->accept(*this);
      s4o.print(";");
      print_symbol_list();
      s4o.print("transition_list[");
      print_transition_number();
      s4o.print("];TRANSITION;\n");
      transition_number++;
      return NULL;
    }
    
    /* step_name | '(' step_name_list ')' */
    /* step_name      -> may be NULL ! */
    /* step_name_list -> may be NULL ! */
    //SYM_REF2(steps_c, step_name, step_name_list)
    void *visit(steps_c *symbol) {
      if (symbol->step_name != NULL)
        symbol->step_name->accept(*this);
      if (symbol->step_name_list != NULL)
        symbol->step_name_list->accept(*this);
      return NULL;
    }
    
    /* | step_name_list ',' step_name */
    //SYM_LIST(step_name_list_c)
    void *visit(step_name_list_c *symbol) {
      for(int i = 0; i < symbol->n; i++) {
        symbol->elements[i]->accept(*this);
        if (i < symbol->n - 1)
          s4o.print(",");
      }
      return NULL;
    }

    /* ACTION action_name ':' function_block_body END_ACTION */
    //SYM_REF2(action_c, action_name, function_block_body)
    void *visit(action_c *symbol) {
      print_var_number();
      s4o.print(";");
      print_symbol_list();
      symbol->action_name->accept(*this);
      s4o.print(".Q;");
      print_symbol_list();
      s4o.print("action_list[");
      print_action_number();
      s4o.print("].state;ACTION;\n");
      action_number++;
      return NULL;
    }


/**************************************/
/* B.1.7 - Configuration elements     */
/**************************************/

    /*  PROGRAM [RETAIN | NON_RETAIN] program_name [WITH task_name] ':' program_type_name ['(' prog_conf_elements ')'] */
    //SYM_REF6(program_configuration_c, retain_option, program_name, task_name, program_type_name, prog_conf_elements, unused)
    void *visit(program_configuration_c *symbol) {
      
      /* Start off by setting the current_var_type_symbol and
       * current_var_init_symbol private variables...
       */
      update_var_type_symbol(symbol->program_type_name, true);
      
      declare_variable(symbol->program_name, true);
      
      /* Values no longer in scope, and therefore no longer used.
       * Make an effort to keep them set to NULL when not in use
       * in order to catch bugs as soon as possible...
       */
      reset_var_type_symbol();
      
      return NULL;
    }

    /* CONFIGURATION configuration_name
     *   optional_global_var_declarations
     *   (resource_declaration_list | single_resource_declaration)
     *   optional_access_declarations
     *   optional_instance_specific_initializations
     * END_CONFIGURATION
     */
    //SYM_REF5(configuration_declaration_c, configuration_name, global_var_declarations, resource_declarations, access_declarations, instance_specific_initializations)
    void *visit(configuration_declaration_c *symbol) {
      SYMBOL *current_name;
      current_name = new SYMBOL;
      current_name->symbol = symbol->configuration_name;
      current_symbol_list.push_back(*current_name);
      symbol->resource_declarations->accept(*this);
      current_symbol_list.pop_back();
      return NULL;
    }
    
    /* RESOURCE resource_name ON resource_type_name
     *   optional_global_var_declarations
     *   single_resource_declaration
     * END_RESOURCE
     */
    //SYM_REF4(resource_declaration_c, resource_name, resource_type_name, global_var_declarations, resource_declaration)
    void *visit(resource_declaration_c *symbol) {
      SYMBOL *current_name;
      current_name = new SYMBOL;
      current_name->symbol = symbol->resource_name;
      current_symbol_list.push_back(*current_name);
      
      if (symbol->global_var_declarations != NULL)
        symbol->global_var_declarations->accept(*this);
      
      symbol->resource_declaration->accept(*this);
      
      current_symbol_list.pop_back();
      return NULL;
    }

    /* task_configuration_list program_configuration_list */
    //SYM_REF2(single_resource_declaration_c, task_configuration_list, program_configuration_list)
    void *visit(single_resource_declaration_c *symbol) {
      symbol->program_configuration_list->accept(*this);
      return NULL;
    }
    
    
/*************************************/
/* B 2.1 - Instructions and operands */
/*************************************/
    void *visit(instruction_list_c *symbol) {
      return NULL;
    }
    
/************************/
/* B 3.2 - Statements   */
/************************/
    void *visit(statement_list_c *symbol) {
      return NULL;
    }
    
};
