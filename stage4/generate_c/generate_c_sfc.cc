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

typedef struct
{
  transition_c *symbol;
  int priority;
  int index;
} TRANSITION;





/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_c_sfc_elements_c: public generate_c_base_c {
  
  public:
    typedef enum {
      transitionlist_sg,
      transitiontest_sg,
      transitiontestdebug_sg,
      stepset_sg,
      stepreset_sg,
      actionassociation_sg,
      actionbody_sg
    } sfcgeneration_t;

  private:
    generate_c_il_c *generate_c_il;
    generate_c_st_c *generate_c_st;
    generate_c_SFC_IL_ST_c *generate_c_code;
    search_var_instance_decl_c *search_var_instance_decl;
    
    int transition_number;
    std::list<TRANSITION> transition_list;
    
    symbol_c *current_step;
    symbol_c *current_action;

    sfcgeneration_t wanted_sfcgeneration;
    
  public:
    generate_c_sfc_elements_c(stage4out_c *s4o_ptr, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_c_base_c(s4o_ptr) {
      generate_c_il = new generate_c_il_c(s4o_ptr, scope, variable_prefix);
      generate_c_st = new generate_c_st_c(s4o_ptr, scope, variable_prefix);
      generate_c_code = new generate_c_SFC_IL_ST_c(s4o_ptr, scope, variable_prefix);
      search_var_instance_decl = new search_var_instance_decl_c(scope);
      this->set_variable_prefix(variable_prefix);
    }
    
    ~generate_c_sfc_elements_c(void) {
      transition_list.clear();
      delete generate_c_il;
      delete generate_c_st;
      delete generate_c_code;
      delete search_var_instance_decl;
    }

    void reset_transition_number(void) {transition_number = 0;}

    void generate(symbol_c *symbol, sfcgeneration_t generation_type) {
      wanted_sfcgeneration = generation_type;
      switch (wanted_sfcgeneration) {
        case transitiontest_sg:
          {
            std::list<TRANSITION>::iterator pt;
            for(pt = transition_list.begin(); pt != transition_list.end(); pt++) {
              transition_number = pt->index;
              pt->symbol->accept(*this);
            }
          }
          break;
        default:
          symbol->accept(*this);
          break;
      }
    }

    void print_step_argument(symbol_c *step_name, const char* argument) {
      print_variable_prefix();
      s4o.print("__step_list[");
      s4o.print(SFC_STEP_ACTION_PREFIX);
      step_name->accept(*this);
      s4o.print("].");
      s4o.print(argument);
    }

    void print_action_argument(symbol_c *action_name, const char* argument) {
      print_variable_prefix();
      s4o.print("__action_list[");
      s4o.print(SFC_STEP_ACTION_PREFIX);
      action_name->accept(*this);
      s4o.print("].");
      s4o.print(argument);
    }      

    void print_transition_number(void) {
      char str[10];
      sprintf(str, "%d", transition_number);
      s4o.print(str);
    }

    void print_reset_step(symbol_c *step_name) {
      s4o.print(s4o.indent_spaces);
      print_step_argument(step_name, "state");
      s4o.print(" = 0;\n");
    }
    
    void print_set_step(symbol_c *step_name) {
      s4o.print(s4o.indent_spaces);
      print_step_argument(step_name, "state");
      s4o.print(" = 1;\n" + s4o.indent_spaces);
      print_step_argument(step_name, "elapsed_time");
      s4o.print(" = __time_to_timespec(1, 0, 0, 0, 0, 0);\n");
    }
    
    bool is_variable(symbol_c *symbol) {
      /* we try to find the variable instance declaration, to determine its type... */
      symbol_c *var_decl = search_var_instance_decl->get_decl(symbol);
      
      return var_decl != NULL;
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/
    
    void *visit(initial_step_c *symbol) {
      switch (wanted_sfcgeneration) {
        case actionassociation_sg:
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
          break;
        default:
          break;
      }
      return NULL;
    }
    
    void *visit(step_c *symbol) {
      switch (wanted_sfcgeneration) {
        case actionassociation_sg:
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
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(transition_c *symbol) {
      switch (wanted_sfcgeneration) {
        case transitionlist_sg:
          {
            TRANSITION *transition;
            transition = new TRANSITION;
            transition->symbol = symbol;
            transition->index = transition_number;
            if (symbol->integer != NULL) {
              transition->priority = atoi(((token_c *)symbol->integer)->value);
              std::list<TRANSITION>::iterator pt = transition_list.begin();
              while (pt != transition_list.end() && pt->priority <= transition->priority) {
                pt++;
              } 
              transition_list.insert(pt, *transition);
            } 
            else {
              transition->priority = 0;
              transition_list.push_back(*transition);
            }
            transition_number++;
          }
          break;
        case transitiontest_sg:
          s4o.print(s4o.indent_spaces + "if (");
          symbol->from_steps->accept(*this);
          s4o.print(") {\n");
          s4o.indent_right();
          
          // Calculate transition value
          symbol->transition_condition->accept(*this);
          
          if (symbol->integer != NULL) {
            s4o.print(s4o.indent_spaces + "if (");
            print_variable_prefix();
            s4o.print("__transition_list[");
            print_transition_number();
            s4o.print("]) {\n");
            s4o.indent_right();
            wanted_sfcgeneration = stepreset_sg;
            symbol->from_steps->accept(*this);
            wanted_sfcgeneration = transitiontest_sg;
            s4o.indent_left();
            s4o.print(s4o.indent_spaces + "}\n");
          }
          s4o.indent_left();
          s4o.print(s4o.indent_spaces + "}\n");
          s4o.print(s4o.indent_spaces + "else {\n");
          s4o.indent_right();
          // Calculate transition value for debug
          s4o.print(s4o.indent_spaces + "if (__DEBUG) {\n");
          s4o.indent_right();
          wanted_sfcgeneration = transitiontestdebug_sg;
          symbol->transition_condition->accept(*this);
          wanted_sfcgeneration = transitiontest_sg;
          s4o.indent_left();
          s4o.print(s4o.indent_spaces + "}\n");
          s4o.print(s4o.indent_spaces);
          print_variable_prefix();
          s4o.print("__transition_list[");
          print_transition_number();
          s4o.print("] = 0;\n");
          s4o.indent_left();
          s4o.print(s4o.indent_spaces + "}\n");
          break;
        case stepset_sg:
          s4o.print(s4o.indent_spaces + "if (");
          print_variable_prefix();
          s4o.print("__transition_list[");
          print_transition_number();
          s4o.print("]) {\n");
          s4o.indent_right();
          symbol->to_steps->accept(*this);
          s4o.indent_left();
          s4o.print(s4o.indent_spaces + "}\n");
          transition_number++;
          break;
        case stepreset_sg:
          if (symbol->integer == NULL) {
            s4o.print(s4o.indent_spaces + "if (");
            print_variable_prefix();
            s4o.print("__transition_list[");
            print_transition_number();
            s4o.print("]) {\n");
            s4o.indent_right();
            symbol->from_steps->accept(*this);
            s4o.indent_left();
            s4o.print(s4o.indent_spaces + "}\n");
          }
          transition_number++;
          break;
        default:
          break;
      }
      return NULL;
    }
    
    void *visit(transition_condition_c *symbol) {
      switch (wanted_sfcgeneration) {
        case transitiontest_sg:
        case transitiontestdebug_sg:
          // Transition condition is in IL
          if (symbol->transition_condition_il != NULL) {
            generate_c_il->declare_backup_variable();
            s4o.print(s4o.indent_spaces);
            symbol->transition_condition_il->accept(*generate_c_il);
            print_variable_prefix();
            if (wanted_sfcgeneration == transitiontestdebug_sg)
              s4o.print("__debug_");
            else
              s4o.print("__");
            s4o.print("transition_list[");
            print_transition_number();
            s4o.print("] = ");
            generate_c_il->print_backup_variable();
            s4o.print(";\n");
          }
          // Transition condition is in ST
          if (symbol->transition_condition_st != NULL) {
            s4o.print(s4o.indent_spaces);
            print_variable_prefix();
            if (wanted_sfcgeneration == transitiontestdebug_sg)
              s4o.print("__debug_");
            else
              s4o.print("__");
            s4o.print("transition_list[");
            print_transition_number();
            s4o.print("] = ");
            symbol->transition_condition_st->accept(*generate_c_st);
            s4o.print(";\n");
          }
          if (wanted_sfcgeneration == transitiontest_sg) {
            s4o.print(s4o.indent_spaces + "if (__DEBUG) {\n");
            s4o.indent_right();
            s4o.print(s4o.indent_spaces);
            print_variable_prefix();
            s4o.print("__debug_transition_list[");
            print_transition_number();
            s4o.print("] = ");
            print_variable_prefix();
            s4o.print("__transition_list[");
            print_transition_number();
            s4o.print("];\n");
            s4o.indent_left();
            s4o.print(s4o.indent_spaces + "}\n");
          }
          break;
        default:
          break;
      }
      return NULL;
    }
    
    void *visit(action_c *symbol) {
      switch (wanted_sfcgeneration) {
        case actionbody_sg:
          s4o.print(s4o.indent_spaces + "if(");
          print_variable_prefix();
          s4o.print("__action_list[");
          s4o.print(SFC_STEP_ACTION_PREFIX);
          symbol->action_name->accept(*this);
          s4o.print("].state) {\n");
          s4o.indent_right();
          
          // generate action code
          symbol->function_block_body->accept(*generate_c_code);
          
          s4o.indent_left();
          s4o.print(s4o.indent_spaces + "}\n\n");
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(steps_c *symbol) {
      if (symbol->step_name != NULL) {
        switch (wanted_sfcgeneration) {
          case transitiontest_sg:
            print_step_argument(symbol->step_name, "state");
            break;
          case stepset_sg:
            print_set_step(symbol->step_name);
            break;
          case stepreset_sg:
            print_reset_step(symbol->step_name);
            break;
          default:
            break;
        }
      }
      else if (symbol->step_name_list != NULL) {
        symbol->step_name_list->accept(*this);
      }  
      return NULL;
    }
    
    void *visit(step_name_list_c *symbol) {
      switch (wanted_sfcgeneration) {
        case transitiontest_sg:
          for(int i = 0; i < symbol->n; i++) {
            print_step_argument(symbol->elements[i], "state");
            if (i < symbol->n - 1) {
              s4o.print(" && ");
            }
          }
          break;
        case stepset_sg:
          for(int i = 0; i < symbol->n; i++) {
            print_set_step(symbol->elements[i]);
          }
          break;
        case stepreset_sg:
          for(int i = 0; i < symbol->n; i++) {
            print_reset_step(symbol->elements[i]);
          }
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(action_association_list_c* symbol) {
      switch (wanted_sfcgeneration) {
        case actionassociation_sg:
          print_list(symbol, "", "\n", "\n");
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(action_association_c *symbol) {
      switch (wanted_sfcgeneration) {
        case actionassociation_sg:
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
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(action_qualifier_c *symbol) {
      switch (wanted_sfcgeneration) {
        case actionassociation_sg:
          {
            char *qualifier = (char *)symbol->action_qualifier->accept(*this);
            s4o.print(s4o.indent_spaces + "if (");
            if (strcmp(qualifier, "N") == 0 || strcmp(qualifier, "S") == 0 ||
                strcmp(qualifier, "R") == 0) {
              s4o.print("active");
            }
            if (strcmp(qualifier, "P") == 0 || strcmp(qualifier, "SD") == 0 || 
                strcmp(qualifier, "DS") == 0 || strcmp(qualifier, "SL") == 0) {
              s4o.print("activated");
            }
            if (strcmp(qualifier, "D") == 0 || strcmp(qualifier, "L") == 0) {
              s4o.print("active && __TIME_CMP(");
              print_step_argument(current_step, "elapsed_time");
              s4o.print(", ");
              symbol->action_time->accept(*this);
              if (strcmp(qualifier, "D") == 0) {
                s4o.print(") >= 0");
              }
              else {
                s4o.print(") < 0");
              }
            }
            s4o.print(") {\n");
            s4o.indent_right();
            s4o.print(s4o.indent_spaces);
            if (strcmp(qualifier, "N") == 0 || strcmp(qualifier, "P") == 0 ||
                strcmp(qualifier, "D") == 0 || strcmp(qualifier, "L") == 0) {
              print_action_argument(current_action, "state");
              s4o.print(" = 1;\n");  
            }
            if (strcmp(qualifier, "S") == 0) {
              if (is_variable(current_action)) {
                print_variable_prefix();
                current_action->accept(*this);
              }
              else
                print_action_argument(current_action, "set");
              s4o.print(" = 1;\n");
            }
            if (strcmp(qualifier, "R") == 0) {
              if (is_variable(current_action)) {
                print_variable_prefix();
                current_action->accept(*this);
                s4o.print(" = 0;\n");
              }
              else {
                print_action_argument(current_action, "reset");
                s4o.print(" = 1;\n");
              }
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
          }
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(qualifier_c *symbol) {
      return (void *)symbol->value;
    }

    void *visit(timed_qualifier_c *symbol) {
      return (void *)symbol->value;
    }

}; /* generate_c_sfc_actiondecl_c */
 
 
 
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_c_sfc_c: public generate_c_typedecl_c {
  
  private:
    generate_c_sfc_elements_c *generate_c_sfc_elements;
    
  public:
    generate_c_sfc_c(stage4out_c *s4o_ptr, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_c_typedecl_c(s4o_ptr) {
      generate_c_sfc_elements = new generate_c_sfc_elements_c(s4o_ptr, scope, variable_prefix);
      this->set_variable_prefix(variable_prefix);
    }
  
    virtual ~generate_c_sfc_c(void) {
      delete generate_c_sfc_elements;
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/
    
    void *visit(sequential_function_chart_c *symbol) {
      int i;
      
      generate_c_sfc_elements->reset_transition_number();
      for(i = 0; i < symbol->n; i++) {
        generate_c_sfc_elements->generate(symbol->elements[i], generate_c_sfc_elements_c::transitionlist_sg);
      }
      
      s4o.print(s4o.indent_spaces +"INT i;\n");
      s4o.print(s4o.indent_spaces +"BOOL transition;\n");
      s4o.print(s4o.indent_spaces +"TIME elapsed_time, current_time;\n\n");
      
      /* generate elapsed_time initialisations */
      s4o.print(s4o.indent_spaces + "// Calculate elapsed_time\n");
      s4o.print(s4o.indent_spaces +"current_time = __CURRENT_TIME;\n");
      s4o.print(s4o.indent_spaces +"elapsed_time = __time_sub(__BOOL_LITERAL(TRUE), NULL, current_time, ");
      print_variable_prefix();
      s4o.print("__lasttick_time);\n");
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__lasttick_time = current_time;\n");
      
      /* generate step initialisations */
      s4o.print(s4o.indent_spaces + "// Steps initialisation\n");
      s4o.print(s4o.indent_spaces + "for (i = 0; i < ");
      print_variable_prefix();
      s4o.print("__nb_steps; i++) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__step_list[i].prev_state = ");
      print_variable_prefix();
      s4o.print("__step_list[i].state;\n");
      s4o.print(s4o.indent_spaces + "if (");
      print_variable_prefix();
      s4o.print("__step_list[i].state) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__step_list[i].elapsed_time = __time_add(__BOOL_LITERAL(TRUE), NULL, ");
      print_variable_prefix();
      s4o.print("__step_list[i].elapsed_time, elapsed_time);\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");

      /* generate action initilizations */
      s4o.print(s4o.indent_spaces + "// Actions initialisation\n");
      s4o.print(s4o.indent_spaces + "for (i = 0; i < ");
      print_variable_prefix();
      s4o.print("__nb_actions; i++) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__action_list[i].state = 0;\n");
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__action_list[i].set = 0;\n");
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__action_list[i].reset = 0;\n");
      s4o.print(s4o.indent_spaces + "if (");
      s4o.print("__TIME_CMP(");
      print_variable_prefix();
      s4o.print("__action_list[i].set_remaining_time, __time_to_timespec(1, 0, 0, 0, 0, 0)) > 0) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__action_list[i].set_remaining_time = __time_sub(__BOOL_LITERAL(TRUE), NULL, ");
      print_variable_prefix();
      s4o.print("__action_list[i].set_remaining_time, elapsed_time);\n");
      s4o.print(s4o.indent_spaces + "if (");
      s4o.print("__TIME_CMP(");
      print_variable_prefix();
      s4o.print("__action_list[i].set_remaining_time, __time_to_timespec(1, 0, 0, 0, 0, 0)) <= 0) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__action_list[i].set_remaining_time = __time_to_timespec(1, 0, 0, 0, 0, 0);\n");
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__action_list[i].set = 1;\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
      s4o.print(s4o.indent_spaces + "if (");
      s4o.print("__TIME_CMP(");
      print_variable_prefix();
      s4o.print("__action_list[i].reset_remaining_time, __time_to_timespec(1, 0, 0, 0, 0, 0)) > 0) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__action_list[i].reset_remaining_time = __time_sub(__BOOL_LITERAL(TRUE), NULL, ");
      print_variable_prefix();
      s4o.print("__action_list[i].reset_remaining_time, elapsed_time);\n");
      s4o.print(s4o.indent_spaces + "if (");
      s4o.print("__TIME_CMP(");
      print_variable_prefix();
      s4o.print("__action_list[i].reset_remaining_time, __time_to_timespec(1, 0, 0, 0, 0, 0)) <= 0) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__action_list[i].reset_remaining_time = __time_to_timespec(1, 0, 0, 0, 0, 0);\n");
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__action_list[i].reset = 1;\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n\n");
      
      /* generate transition tests */
      s4o.print(s4o.indent_spaces + "// Transitions fire test\n");
      generate_c_sfc_elements->generate((symbol_c *)symbol, generate_c_sfc_elements_c::transitiontest_sg);
      s4o.print("\n");
      
      /* generate transition reset steps */
      s4o.print(s4o.indent_spaces + "// Transitions reset steps\n");
      generate_c_sfc_elements->reset_transition_number();
      for(i = 0; i < symbol->n; i++) {
        generate_c_sfc_elements->generate(symbol->elements[i], generate_c_sfc_elements_c::stepreset_sg);
      }
      s4o.print("\n");
      
      /* generate transition set steps */
      s4o.print(s4o.indent_spaces + "// Transitions set steps\n");
      generate_c_sfc_elements->reset_transition_number();
      for(i = 0; i < symbol->n; i++) {
        generate_c_sfc_elements->generate(symbol->elements[i], generate_c_sfc_elements_c::stepset_sg);
      }
      s4o.print("\n");
      
      /* generate step association */
      s4o.print(s4o.indent_spaces + "// Steps association\n");
      for(i = 0; i < symbol->n; i++) {
        generate_c_sfc_elements->generate(symbol->elements[i], generate_c_sfc_elements_c::actionassociation_sg);
      }
      s4o.print("\n");
      
      /* generate action state evaluation */
      s4o.print(s4o.indent_spaces + "// Actions state evaluation\n");
      s4o.print(s4o.indent_spaces + "for (i = 0; i < ");
      print_variable_prefix();
      s4o.print("__nb_actions; i++) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces + "if (");
      print_variable_prefix();
      s4o.print("__action_list[i].set) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__action_list[i].stored = 1;\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n" + s4o.indent_spaces + "if (");
      print_variable_prefix();
      s4o.print("__action_list[i].reset) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__action_list[i].set_remaining_time = __time_to_timespec(1, 0, 0, 0, 0, 0);\n" + s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__action_list[i].reset_remaining_time = __time_to_timespec(1, 0, 0, 0, 0, 0);\n" + s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__action_list[i].stored = 0;\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n" + s4o.indent_spaces);
      print_variable_prefix();
      s4o.print("__action_list[i].state |= ");
      print_variable_prefix();
      s4o.print("__action_list[i].stored;\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n\n");
      
      /* generate action execution */
      s4o.print(s4o.indent_spaces + "// Actions execution\n");
      for(i = 0; i < symbol->n; i++) {
        generate_c_sfc_elements->generate(symbol->elements[i], generate_c_sfc_elements_c::actionbody_sg);
      }
      s4o.print("\n");
      
      return NULL;
    }
    
    void generate(sequential_function_chart_c *sfc) {
      sfc->accept(*this);
    }

}; /* generate_c_sfc_c */
