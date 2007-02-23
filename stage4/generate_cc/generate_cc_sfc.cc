/*
 * (c) 2007 Mario de Sousa, Laurent Bessard
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
 * Conversion of sfc networks (i.e. SFC code).
 *
 * This is part of the 4th stage that generates
 * a c++ source program equivalent to the SFC, IL and ST
 * code.
 */



/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_cc_sfc_transitiontest_c: public generate_cc_base_c {
  
  private:
    generate_cc_il_c *generate_cc_il;
    generate_cc_st_c *generate_cc_st;
    
  public:
    generate_cc_sfc_transitiontest_c(stage4out_c *s4o_ptr, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_cc_base_c(s4o_ptr) {
      generate_cc_il = new generate_cc_il_c(s4o_ptr, scope, variable_prefix);
      generate_cc_st = new generate_cc_st_c(s4o_ptr, scope, variable_prefix);
      this->set_variable_prefix(variable_prefix);
    }
    
    ~generate_cc_sfc_transitiontest_c(void) {
      delete generate_cc_il;
      delete generate_cc_st;
    }

    void print_step_argument(symbol_c *step_name, const char* argument) {
      print_variable_prefix();
      s4o.print("step_list[");
      step_name->accept(*this);
      s4o.print("].");
      s4o.print(argument);
    }
    
    void print_reset_step(symbol_c *step_name) {
      s4o.print(s4o.indent_spaces);
      print_step_argument(step_name, "state");
      s4o.print(" = 0;\n" + s4o.indent_spaces + "if (");
      print_step_argument(step_name, "pulse");
      s4o.print(" != 1 {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_step_argument(step_name, "pulse");
      s4o.print(" = 2;\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n" + s4o.indent_spaces + "else {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_step_argument(step_name, "pulse");
      s4o.print(" = 0;\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n" + s4o.indent_spaces);
      print_step_argument(step_name, "elapsed_time");
      s4o.print(" = __time_to_timespec(1, 0, 0, 0, 0, 0);");
    }
    
    void print_set_step(symbol_c *step_name) {
      s4o.print(s4o.indent_spaces);
      print_step_argument(step_name, "state");
      s4o.print(" = 1;\n" + s4o.indent_spaces);
      print_step_argument(step_name, "pulse");
      s4o.print(" = 1;");
    } 
    
    void print_steps_state_test(steps_c *symbol) {
      if (symbol->step_name != NULL) {
        print_step_argument(symbol->step_name, "state");
      }
      if (symbol->step_name_list != NULL) {
        for(int i = 0; i < ((list_c*)symbol->step_name_list)->n; i++) {
          print_step_argument(((list_c*)symbol->step_name_list)->elements[i], "state");
          if (i < ((list_c*)symbol->step_name_list)->n - 1) {
            s4o.print(" && ");
          }
        }
      }
    }
      
    void print_reset_steps(steps_c *symbol) {
      if (symbol->step_name != NULL) {
        print_reset_step(symbol->step_name);
        s4o.print("\n");
      }
      if (symbol->step_name_list != NULL) {
        for(int i = 0; i < ((list_c*)symbol->step_name_list)->n; i++) {
          print_reset_step(((list_c*)symbol->step_name_list)->elements[i]);
          s4o.print("\n");
        }
      }
    }

    void print_set_steps(steps_c *symbol) {
      if (symbol->step_name != NULL) {
        print_set_step(symbol->step_name);
        s4o.print("\n");
      }
      if (symbol->step_name_list != NULL) {
        for(int i = 0; i < ((list_c*)symbol->step_name_list)->n; i++) {
          print_set_step(((list_c*)symbol->step_name_list)->elements[i]);
          s4o.print("\n");
        }
      }
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/
    
    void *visit(initial_step_c *symbol) {return NULL;}
    
    void *visit(step_c *symbol) {return NULL;}

    void *visit(transition_c *symbol) {
      s4o.print(s4o.indent_spaces + "if (");
      print_steps_state_test((steps_c *)symbol->from_steps);
      s4o.print(") {\n");
      s4o.indent_right();
      
      // Calculate transition value
      if (symbol->transition_condition_il != NULL) {
        generate_cc_il->declare_backup_variable();
        s4o.print(s4o.indent_spaces);
        symbol->transition_condition_il->accept(*generate_cc_il);
        s4o.print("if (");
        generate_cc_il->print_backup_variable();
        s4o.print(") {\n");
      }
      if (symbol->transition_condition_st != NULL) {
        s4o.print(s4o.indent_spaces + "if (");
        symbol->transition_condition_st->accept(*generate_cc_st);
        s4o.print(") {\n");
      }
      
      s4o.indent_right();      
      print_reset_steps((steps_c *)symbol->from_steps);
      print_set_steps((steps_c *)symbol->to_steps);      
      s4o.indent_left();

      s4o.print(s4o.indent_spaces + "}\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n\n");
      return NULL;
    }
    
    void *visit(action_c *symbol) {return NULL;}

}; /* generate_cc_sfc_transitiontest_c */




/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_cc_sfc_stepassociation_c: public generate_cc_base_c {
  
  private:
    symbol_c *current_step;
    symbol_c *current_action;
  
  public:
    generate_cc_sfc_stepassociation_c(stage4out_c *s4o_ptr, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_cc_base_c(s4o_ptr) {
      this->set_variable_prefix(variable_prefix);
    }

    void print_step_argument(symbol_c *step_name, const char* argument) {
      print_variable_prefix();
      s4o.print("step_list[");
      step_name->accept(*this);
      s4o.print("].");
      s4o.print(argument);
    }

    void print_action_argument(symbol_c *action_name, const char* argument) {
      print_variable_prefix();
      s4o.print("action_list[");
      action_name->accept(*this);
      s4o.print("].");
      s4o.print(argument);
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/
    
    void *visit(initial_step_c *symbol) {
      s4o.print(s4o.indent_spaces + "// ");
      symbol->step_name->accept(*this);
      s4o.print(" action associations\n");
      current_step = symbol->step_name;
      symbol->action_association_list->accept(*this);
      return NULL;
    }
    
    void *visit(step_c *symbol) {
      s4o.print(s4o.indent_spaces + "// ");
      symbol->step_name->accept(*this);
      s4o.print(" action associations\n");
      current_step = symbol->step_name;
      symbol->action_association_list->accept(*this);
      return NULL;
    }

    void *visit(transition_c *symbol) {return NULL;}
    
    void *visit(action_c *symbol) {return NULL;}

    void *visit(action_association_list_c* symbol) {
      print_list(symbol, "", "\n", "\n\n");
      return NULL;
    }

    void *visit(action_association_c *symbol) {
      if (symbol->action_qualifier != NULL) {
        current_action = symbol->action_name;
        symbol->action_qualifier->accept(*this);
      }
      else {
        s4o.print(s4o.indent_spaces + "if (");
        print_step_argument(current_step, "state");
        s4o.print(") {\n");
        s4o.indent_right();
        s4o.print(s4o.indent_spaces);
        print_action_argument(symbol->action_name, "state");
        s4o.print(" = 1;\n");
        s4o.indent_left();
        s4o.print(s4o.indent_spaces + "}");
      }
      return NULL;
    }

    void *visit(action_qualifier_c *symbol) {
      char *qualifier = (char *)symbol->action_qualifier->accept(*this);
      
      s4o.print(s4o.indent_spaces + "if (");
      if (strcmp(qualifier, "N") == 0) {
        print_step_argument(current_step, "state");
      }
      if (strcmp(qualifier, "P") == 0 || strcmp(qualifier, "SD") == 0 || 
          strcmp(qualifier, "DS") == 0 || strcmp(qualifier, "SL") == 0) {
        print_step_argument(current_step, "pulse");
        s4o.print(" == 1");
      }
      if (strcmp(qualifier, "D") == 0 || strcmp(qualifier, "L") == 0) {
        print_step_argument(current_step, "state");
        s4o.print(" && ");
        print_step_argument(current_step, "elapsed_time");
        if (strcmp(qualifier, "D") == 0) {
          s4o.print(" >= ");
        }
        else {
          s4o.print(" < ");
        }
        symbol->action_time->accept(*this);  
      }
      s4o.print(") {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      if (strcmp(qualifier, "N") == 0 || strcmp(qualifier, "P") == 0 ||
          strcmp(qualifier, "D") == 0 || strcmp(qualifier, "L") == 0) {
        print_action_argument(current_action, "state");
        s4o.print(" = 1;\n");  
      }
      if (strcmp(qualifier, "SD") == 0 || strcmp(qualifier, "DS") == 0 || 
          strcmp(qualifier, "SL") == 0) {
        if (strcmp(qualifier, "SL") == 0) {
          print_action_argument(current_action, "reset_remaining_time");  
        }
        else {
          print_action_argument(current_action, "set_remaining_time");
        }
        s4o.print(" = ");
        symbol->action_time->accept(*this);
        s4o.print(";\n");
      }
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}");
      if (strcmp(qualifier, "DS") == 0) {
        print_step_argument(current_step, "pulse");
        s4o.print(" == 2) {\n");
        s4o.indent_right();
        s4o.print(s4o.indent_spaces);
        print_action_argument(current_action, "set_remaining_time");
        s4o.print(" = __time_to_timespec(1, 0, 0, 0, 0, 0);\n");
      }
      return NULL;
    }

    void *visit(qualifier_c *symbol) {
      return (void *)symbol->value;
    }

    void *visit(timed_qualifier_c *symbol) {
      return (void *)symbol->value;
    }

}; /* generate_cc_sfc_actiondecl_c */




/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_cc_sfc_actionexecution_c: public generate_cc_base_c {
  
  private:
    generate_cc_SFC_IL_ST_c *generate_cc_code;
    
  public:
    generate_cc_sfc_actionexecution_c(stage4out_c *s4o_ptr, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_cc_base_c(s4o_ptr) {
      generate_cc_code = new generate_cc_SFC_IL_ST_c(s4o_ptr, scope, variable_prefix);
      this->set_variable_prefix(variable_prefix);
    }
    
    ~generate_cc_sfc_actionexecution_c(void) {
      delete generate_cc_code;
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/
    
    void *visit(initial_step_c *symbol) {return NULL;}
    
    void *visit(step_c *symbol) {return NULL;}

    void *visit(transition_c *symbol) {return NULL;}
    
    void *visit(action_c *symbol) {
      s4o.print(s4o.indent_spaces + "if(");
      print_variable_prefix();
      s4o.print("action_list[");
      symbol->action_name->accept(*this);
      s4o.print("].state) {");
      s4o.indent_right();
      
      // generate action code
      symbol->function_block_body->accept(*generate_cc_code);
      
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n\n");
      return NULL;
    }

}; /* generate_cc_sfc_actiondecl_c */
 
 
 
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_cc_sfc_c: public generate_cc_typedecl_c {
  
  private:
    generate_cc_sfc_transitiontest_c *generate_cc_sfc_transitiontest;
    generate_cc_sfc_stepassociation_c *generate_cc_sfc_stepassociation;
    generate_cc_sfc_actionexecution_c *generate_cc_sfc_actionexecution;
  
  public:
    generate_cc_sfc_c(stage4out_c *s4o_ptr, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_cc_typedecl_c(s4o_ptr) {
      generate_cc_sfc_transitiontest = new generate_cc_sfc_transitiontest_c(s4o_ptr, scope, variable_prefix);
      generate_cc_sfc_stepassociation = new generate_cc_sfc_stepassociation_c(s4o_ptr, scope, variable_prefix);
      generate_cc_sfc_actionexecution = new generate_cc_sfc_actionexecution_c(s4o_ptr, scope, variable_prefix);
      this->set_variable_prefix(variable_prefix);
    }
  
    virtual ~generate_cc_sfc_c(void) {
      delete generate_cc_sfc_transitiontest;
      delete generate_cc_sfc_stepassociation;
      delete generate_cc_sfc_actionexecution;
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/

    void *visit(sfc_network_c *symbol) {
      s4o.print(s4o.indent_spaces +"INT i;\n\n");
      s4o.print(s4o.indent_spaces +"BOOL transition;\n\n");
            
      /* generate step initilizations */
      s4o.print(s4o.indent_spaces + "// Steps initialisation\n");
      s4o.print(s4o.indent_spaces + "for (i = 0; i < ");
      print_variable_prefix();
      s4o.print("nb_steps; i++) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("step_list[i].pulse = 0;\n");
      s4o.print(s4o.indent_spaces + "if (");
      print_variable_prefix();
      s4o.print("step_list[i].state) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("step_list[i].elapsed_time = __add_timespec(");
      print_variable_prefix();
      s4o.print("step_list[i].elapsed_time, PERIOD);\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");

      /* generate action initilizations */
      s4o.print(s4o.indent_spaces + "// Actions initialisation\n");
      s4o.print(s4o.indent_spaces + "for (i = 0; i < ");
      print_variable_prefix();
      s4o.print("nb_actions; i++) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("action_list[i].state = 0;\n");
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("action_list[i].set = 0;\n");
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("action_list[i].reset = 0;\n");
      s4o.print(s4o.indent_spaces + "if (");
      print_variable_prefix();
      s4o.print("__compare_timespec(>, action_list[i].set_remaining_time, __time_to_timespec(1, 0, 0, 0, 0, 0)) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("action_list[i].set_remaining_time = __sub_timespec(");
      print_variable_prefix();
      s4o.print("action_list[i].set_remaining_time, PERIOD);\n");
      s4o.print(s4o.indent_spaces + "if (");
      print_variable_prefix();
      s4o.print("__compare_timespec(<=, action_list[i].set_remaining_time, __time_to_timespec(1, 0, 0, 0, 0, 0)) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("action_list[i].set_remaining_time = __time_to_timespec(1, 0, 0, 0, 0, 0);\n");
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("action_list[i].set = 1;\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
      s4o.print(s4o.indent_spaces + "if (");
      print_variable_prefix();
      s4o.print("__compare_timespec(>, action_list[i].reset_remaining_time, __time_to_timespec(1, 0, 0, 0, 0, 0)) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("action_list[i].reset_remaining_time = __sub_timespec(");
      print_variable_prefix();
      s4o.print("action_list[i].reset_remaining_time, PERIOD);\n");
      s4o.print(s4o.indent_spaces + "if (");
      print_variable_prefix();
      s4o.print("__compare_timespec(<=, action_list[i].reset_remaining_time, __time_to_timespec(1, 0, 0, 0, 0, 0)) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("action_list[i].reset_remaining_time = __time_to_timespec(1, 0, 0, 0, 0, 0);\n");
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("action_list[i].reset = 1;\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n\n");
      
      /* generate transition tests */
      s4o.print(s4o.indent_spaces + "// Transitions fire test\n");
      symbol->accept(*generate_cc_sfc_transitiontest);
      s4o.print("\n");
      
       /* generate step association */
      s4o.print(s4o.indent_spaces + "// Steps association\n");
      symbol->accept(*generate_cc_sfc_stepassociation);
      s4o.print("\n");
      
      /* generate action state evaluation */
      s4o.print(s4o.indent_spaces + "// Actions state evaluation\n");
      s4o.print(s4o.indent_spaces + "for (i = 0; i < ");
      print_variable_prefix();
      s4o.print("nb_actions; i++) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces + "if (");
      print_variable_prefix();
      s4o.print("action_list[i].set) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("action_list[i].stored = 1;\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n" + s4o.indent_spaces + "if (");
      print_variable_prefix();
      s4o.print("action_list[i].set) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("action_list[i].set_remaining_time = 0;\n" + s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("action_list[i].reset_remaining_time = 0;\n" + s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("action_list[i].stored = 0;\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n" + s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("action_list[i].state |= ");
      print_variable_prefix();
      s4o.print("action_list[i].stored;\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n\n");
      
      /* generate action execution */
      s4o.print(s4o.indent_spaces + "// Actions execution\n");
      symbol->accept(*generate_cc_sfc_actionexecution);
      s4o.print("\n");
      
      return NULL;
    }

    void generate(sequential_function_chart_c *sfc) {
      sfc->accept(*this);
    }

}; /* generate_cc_sfc_c */
