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

class transition_element {
  
  private:
    transition_c *transition;
    char priority;
    char index;
    transition_element *prev;
    transition_element *next;

  public:
    transition_element(transition_c *tr, char pr, char idx) {
      transition = tr;
      priority = pr;
      index = idx;
    }

    void set_prev(transition_element *tr) {prev = tr;}
    void set_next(transition_element *tr) {next = tr;}
    transition_element *get_prev(void) {return prev;}
    transition_element *get_next(void) {return next;}
    transition_c *get_transition(void) {return transition;}
    char get_priority(void) {return priority;}
    char get_index(void) {return index;}
};




/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_cc_sfc_transitionresetsteps_c: public generate_cc_base_c {
  
  private:
    char transition_number;
  
  public:
    generate_cc_sfc_transitionresetsteps_c(stage4out_c *s4o_ptr, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_cc_base_c(s4o_ptr) {
      this->set_variable_prefix(variable_prefix);
    }
    
    void set_transition_number(char number) {transition_number = number;}
    void reset_transition_number(void) {transition_number = 0;}
    void print_transition_number(void) {
      char str[10];
      sprintf(str, "%d", transition_number);
      s4o.print(str);
    }
    
    void print_step_argument(symbol_c *step_name, const char* argument) {
      print_variable_prefix();
      s4o.print("step_list[");
      s4o.print(SFC_STEP_ACTION_PREFIX);
      step_name->accept(*this);
      s4o.print("].");
      s4o.print(argument);
    }

    void print_reset_step(symbol_c *step_name) {
      s4o.print(s4o.indent_spaces);
      print_step_argument(step_name, "state");
      s4o.print(" = 0;\n" + s4o.indent_spaces);
      print_step_argument(step_name, "elapsed_time");
      s4o.print(" = __time_to_timespec(1, 0, 0, 0, 0, 0);\n");
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/
    
    void *visit(initial_step_c *symbol) {return NULL;}
    
    void *visit(step_c *symbol) {return NULL;}

    void *visit(transition_c *symbol) {
      if (symbol->integer == NULL) {
        s4o.print(s4o.indent_spaces + "if (");
        print_variable_prefix();
        s4o.print("transition_list[");
        print_transition_number();
        s4o.print("]) {\n");
        s4o.indent_right();
        symbol->from_steps->accept(*this);
        s4o.indent_left();
        s4o.print(s4o.indent_spaces + "}\n");
      }
      transition_number++;
      return NULL;
    }
    
    void *visit(steps_c *symbol) {
      if (symbol->step_name != NULL) {
        print_reset_step(symbol->step_name);
      }
      if (symbol->step_name_list != NULL) {
        symbol->step_name_list->accept(*this);
      }
      return NULL;
    }
    
    void *visit(step_name_list_c *symbol) {
      for(int i = 0; i < symbol->n; i++) {
        print_reset_step(symbol->elements[i]);
      }
      return NULL;
    }
    
    void *visit(action_c *symbol) {return NULL;}

}; /* generate_cc_sfc_transitionresetsteps_c */
      



/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_cc_sfc_transitionsetsteps_c: public generate_cc_base_c {
  
  private:
    char transition_number;
  
  public:
    generate_cc_sfc_transitionsetsteps_c(stage4out_c *s4o_ptr, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_cc_base_c(s4o_ptr) {
      this->set_variable_prefix(variable_prefix);
    }
    
    void reset_transition_number(void) {transition_number = 0;}
    void print_transition_number(void) {
      char str[10];
      sprintf(str, "%d", transition_number);
      s4o.print(str);
    }
    
    void print_step_argument(symbol_c *step_name, const char* argument) {
      print_variable_prefix();
      s4o.print("step_list[");
      s4o.print(SFC_STEP_ACTION_PREFIX);
      step_name->accept(*this);
      s4o.print("].");
      s4o.print(argument);
    }

    void print_set_step(symbol_c *step_name) {
      s4o.print(s4o.indent_spaces);
      print_step_argument(step_name, "state");
      s4o.print(" = 1;\n");
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/
    
    void *visit(initial_step_c *symbol) {return NULL;}
    
    void *visit(step_c *symbol) {return NULL;}

    void *visit(transition_c *symbol) {
      s4o.print(s4o.indent_spaces + "if (");
      print_variable_prefix();
      s4o.print("transition_list[");
      print_transition_number();
      s4o.print("]) {\n");
      s4o.indent_right();
      symbol->to_steps->accept(*this);
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
      transition_number++;
      return NULL;
    }
    
    void *visit(steps_c *symbol) {
      if (symbol->step_name != NULL) {
        print_set_step(symbol->step_name);
      }
      if (symbol->step_name_list != NULL) {
        symbol->step_name_list->accept(*this);
      }
      return NULL;
    }
    
    void *visit(step_name_list_c *symbol) {
      for(int i = 0; i < symbol->n; i++) {
        print_set_step(symbol->elements[i]);
      }
      return NULL;
    }
    
    void *visit(action_c *symbol) {return NULL;}

}; /* generate_cc_sfc_transitionsetsteps_c */




/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_cc_sfc_transitiontest_c: public generate_cc_base_c {
  
  private:
    char transition_number;
  
  private:
    generate_cc_il_c *generate_cc_il;
    generate_cc_st_c *generate_cc_st;
    generate_cc_sfc_transitionresetsteps_c *generate_cc_sfc_transitionresetsteps;
    
  public:
    generate_cc_sfc_transitiontest_c(stage4out_c *s4o_ptr, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_cc_base_c(s4o_ptr) {
      generate_cc_il = new generate_cc_il_c(s4o_ptr, scope, variable_prefix);
      generate_cc_st = new generate_cc_st_c(s4o_ptr, scope, variable_prefix);
      generate_cc_sfc_transitionresetsteps = new generate_cc_sfc_transitionresetsteps_c(s4o_ptr, scope, variable_prefix);
      this->set_variable_prefix(variable_prefix);
    }
    
    ~generate_cc_sfc_transitiontest_c(void) {
      delete generate_cc_il;
      delete generate_cc_st;
      delete generate_cc_sfc_transitionresetsteps;
    }

    void set_transition_number(char number) {transition_number = number;}
    void print_transition_number(void) {
      char str[10];
      sprintf(str, "%d", transition_number);
      s4o.print(str);
    }

    void print_step_argument(symbol_c *step_name, const char* argument) {
      print_variable_prefix();
      s4o.print("step_list[");
      s4o.print(SFC_STEP_ACTION_PREFIX);
      step_name->accept(*this);
      s4o.print("].");
      s4o.print(argument);
    }

    void print_reset_step(symbol_c *step_name) {
      s4o.print(s4o.indent_spaces);
      print_step_argument(step_name, "state");
      s4o.print(" = 0;\n" + s4o.indent_spaces);
      print_step_argument(step_name, "elapsed_time");
      s4o.print(" = __time_to_timespec(1, 0, 0, 0, 0, 0);\n");
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/
    
    void *visit(transition_c *symbol) {
      s4o.print(s4o.indent_spaces + "if (");
      symbol->from_steps->accept(*this);
      s4o.print(") {\n");
      s4o.indent_right();
      
      // Calculate transition value
      if (symbol->transition_condition_il != NULL) {
        generate_cc_il->declare_backup_variable();
        s4o.print(s4o.indent_spaces);
        symbol->transition_condition_il->accept(*generate_cc_il);
        print_variable_prefix();
        s4o.print("transition_list[");
        print_transition_number();
        s4o.print("] = ");
        generate_cc_il->print_backup_variable();
        s4o.print(";\n");
      }
      if (symbol->transition_condition_st != NULL) {
        print_variable_prefix();
        s4o.print("transition_list[");
        print_transition_number();
        s4o.print("] = ");
        symbol->transition_condition_st->accept(*generate_cc_st);
        s4o.print(";\n");
      }
      if (symbol->integer != NULL) {
        s4o.print(s4o.indent_spaces + "if (");
        print_variable_prefix();
        s4o.print("transition_list[");
        print_transition_number();
        s4o.print("]) {\n");
        s4o.indent_right();
        symbol->from_steps->accept(*generate_cc_sfc_transitionresetsteps);
        s4o.indent_left();
        s4o.print(s4o.indent_spaces + "}\n");
      }
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n" + s4o.indent_spaces + "else {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("transition_list[");
      print_transition_number();
      s4o.print("] = 0;\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
      
      transition_number++;
      return NULL;
    }
    
    void *visit(steps_c *symbol) {
      if (symbol->step_name != NULL) {
        print_step_argument(symbol->step_name, "state");
      }
      if (symbol->step_name_list != NULL) {
        symbol->step_name_list->accept(*this);
      }
      return NULL;
    }
    
    void *visit(step_name_list_c *symbol) {
      for(int i = 0; i < symbol->n; i++) {
        print_step_argument(symbol->elements[i], "state");
        if (i < symbol->n - 1) {
          s4o.print(" && ");
        }
      }
      return NULL;
    }

}; /* generate_cc_sfc_transitiontest_c */




/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_cc_sfc_transitionsort_c: public iterator_visitor_c {
  
  private:
    char transition_number;
    transition_element *first_transition;
    transition_element *last_transition;
  
  private:
    generate_cc_sfc_transitiontest_c *generate_cc_sfc_transitiontest;
    
  public:
    generate_cc_sfc_transitionsort_c(stage4out_c *s4o_ptr, symbol_c *scope, const char *variable_prefix = NULL) {
      generate_cc_sfc_transitiontest = new generate_cc_sfc_transitiontest_c(s4o_ptr, scope, variable_prefix);
      first_transition = NULL;
      last_transition = NULL;
    }

    ~generate_cc_sfc_transitionsort_c(void) {
      delete generate_cc_sfc_transitiontest;
    }
    
    void append_transition(transition_c *transition, char priority, char index) {
      transition_element *new_transition = new transition_element(transition, priority, index);
      new_transition->set_prev(last_transition);
      if (last_transition != NULL) {
        last_transition->set_next(new_transition);
      }
      else {
        first_transition = new_transition;
      }
      last_transition = new_transition;
      transition_number++;
    }
    
    void sort_transitions(void) {
      int i, j;
      transition_element *current_transition;
      transition_element *next_transition;
      for (i = transition_number; i > 1; i--) {
        current_transition = first_transition;
        for (j = 0; j < i - 1; j++) {
          next_transition = current_transition->get_next();
          if (current_transition->get_priority() > next_transition->get_priority()) {
            if (current_transition->get_prev() != NULL) {
              current_transition->get_prev()->set_next(next_transition);
            }
            else {
              first_transition = next_transition;
            }
            if (next_transition->get_next() != NULL) {
              next_transition->get_next()->set_prev(current_transition);
            }
            else {
              last_transition = current_transition;
            }
            current_transition->set_next(next_transition->get_next());
            next_transition->set_prev(current_transition->get_prev());
            current_transition->set_prev(next_transition);
            next_transition->set_next(current_transition);
          }
          else {
            current_transition = next_transition;
          }
        }
      }
    }
    
    void reset_transition_number(void) {transition_number = 0;}
    
    void generate(symbol_c *symbol) {
      symbol->accept(*this);
      sort_transitions();
      transition_element *next_transition = first_transition;
      while (next_transition != NULL) {
        generate_cc_sfc_transitiontest->set_transition_number(next_transition->get_index());
        next_transition->get_transition()->accept(*generate_cc_sfc_transitiontest);
        next_transition = next_transition->get_next();
      }
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/
    
    void *visit(initial_step_c *symbol) {return NULL;}
    
    void *visit(step_c *symbol) {return NULL;}
    
    void *visit(transition_c *symbol) {
      if (symbol->integer != NULL) {
        append_transition(symbol, atoi(((token_c *)symbol->integer)->value), transition_number);
      }
      else {
        append_transition(symbol, 0, transition_number);
      }
      return NULL;
    }
    
    void *visit(action_c *symbol) {return NULL;}

};/* generate_cc_sfc_transitionsort_c */




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
      s4o.print(SFC_STEP_ACTION_PREFIX);
      step_name->accept(*this);
      s4o.print("].");
      s4o.print(argument);
    }

    void print_action_argument(symbol_c *action_name, const char* argument) {
      print_variable_prefix();
      s4o.print("action_list[");
      s4o.print(SFC_STEP_ACTION_PREFIX);
      action_name->accept(*this);
      s4o.print("].");
      s4o.print(argument);
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/
    
    void *visit(initial_step_c *symbol) {
      if (((list_c*)symbol->action_association_list)->n > 0) {
        s4o.print(s4o.indent_spaces + "// ");
        symbol->step_name->accept(*this);
        s4o.print(" action associations\n");
        current_step = symbol->step_name;
        s4o.print(s4o.indent_spaces + "{\n");
        s4o.indent_right();
        s4o.print(s4o.indent_spaces + "char activated = ");
        print_step_argument(current_step, "state");
        s4o.print(" && !");
        print_step_argument(current_step, "prev_state");
        s4o.print(";\n");
        s4o.print(s4o.indent_spaces + "char desactivated = !");
        print_step_argument(current_step, "state");
        s4o.print(" && ");
        print_step_argument(current_step, "prev_state");
        s4o.print(";\n");
        s4o.print(s4o.indent_spaces + "char active = ");
        print_step_argument(current_step, "state");
        s4o.print(";\n");
        symbol->action_association_list->accept(*this);
        s4o.indent_left();
        s4o.print(s4o.indent_spaces + "}\n\n");
      }
      return NULL;
    }
    
    void *visit(step_c *symbol) {
      if (((list_c*)symbol->action_association_list)->n > 0) {
        s4o.print(s4o.indent_spaces + "// ");
        symbol->step_name->accept(*this);
        s4o.print(" action associations\n");
        current_step = symbol->step_name;
        s4o.print(s4o.indent_spaces + "{\n");
        s4o.indent_right();
        s4o.print(s4o.indent_spaces + "char activated = ");
        print_step_argument(current_step, "state");
        s4o.print(" && !");
        print_step_argument(current_step, "prev_state");
        s4o.print(";\n");
        s4o.print(s4o.indent_spaces + "char desactivated = !");
        print_step_argument(current_step, "state");
        s4o.print(" && ");
        print_step_argument(current_step, "prev_state");
        s4o.print(";\n");
        s4o.print(s4o.indent_spaces + "char active = ");
        print_step_argument(current_step, "state");
        s4o.print(";\n");
        symbol->action_association_list->accept(*this);
        s4o.indent_left();
        s4o.print(s4o.indent_spaces + "}\n\n");
      }
      return NULL;
    }

    void *visit(transition_c *symbol) {return NULL;}
    
    void *visit(action_c *symbol) {return NULL;}

    void *visit(action_association_list_c* symbol) {
      print_list(symbol, "", "\n", "\n");
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
        s4o.print("active");
      }
      if (strcmp(qualifier, "P") == 0 || strcmp(qualifier, "SD") == 0 || 
          strcmp(qualifier, "DS") == 0 || strcmp(qualifier, "SL") == 0) {
        s4o.print("activated");
      }
      if (strcmp(qualifier, "D") == 0 || strcmp(qualifier, "L") == 0) {
        s4o.print("active && ");
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
        s4o.print("desactivated");
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
      s4o.print(SFC_STEP_ACTION_PREFIX);
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
    generate_cc_sfc_transitionsort_c *generate_cc_sfc_transitionsort;
    generate_cc_sfc_transitionresetsteps_c *generate_cc_sfc_transitionresetsteps;
    generate_cc_sfc_transitionsetsteps_c *generate_cc_sfc_transitionsetsteps;
    generate_cc_sfc_stepassociation_c *generate_cc_sfc_stepassociation;
    generate_cc_sfc_actionexecution_c *generate_cc_sfc_actionexecution;
  
  public:
    generate_cc_sfc_c(stage4out_c *s4o_ptr, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_cc_typedecl_c(s4o_ptr) {
      generate_cc_sfc_transitionsort = new generate_cc_sfc_transitionsort_c(s4o_ptr, scope, variable_prefix);
      generate_cc_sfc_transitionresetsteps = new generate_cc_sfc_transitionresetsteps_c(s4o_ptr, scope, variable_prefix);
      generate_cc_sfc_transitionsetsteps = new generate_cc_sfc_transitionsetsteps_c(s4o_ptr, scope, variable_prefix);
      generate_cc_sfc_stepassociation = new generate_cc_sfc_stepassociation_c(s4o_ptr, scope, variable_prefix);
      generate_cc_sfc_actionexecution = new generate_cc_sfc_actionexecution_c(s4o_ptr, scope, variable_prefix);
      this->set_variable_prefix(variable_prefix);
    }
  
    virtual ~generate_cc_sfc_c(void) {
      delete generate_cc_sfc_transitionsort;
      delete generate_cc_sfc_transitionresetsteps;
      delete generate_cc_sfc_transitionsetsteps;
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
      s4o.print("step_list[i].prev_state = ");
      print_variable_prefix();
      s4o.print("step_list[i].state;\n");
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
      generate_cc_sfc_transitionsort->reset_transition_number();
      generate_cc_sfc_transitionsort->generate(symbol);
      s4o.print("\n");
      
      /* generate transition reset steps */
      s4o.print(s4o.indent_spaces + "// Transitions reset steps\n");
      generate_cc_sfc_transitionresetsteps->reset_transition_number();
      symbol->accept(*generate_cc_sfc_transitionresetsteps);
      s4o.print("\n");
      
      /* generate transition set steps */
      s4o.print(s4o.indent_spaces + "// Transitions set steps\n");
      generate_cc_sfc_transitionsetsteps->reset_transition_number();
      symbol->accept(*generate_cc_sfc_transitionsetsteps);
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
