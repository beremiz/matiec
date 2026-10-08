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

typedef struct
{
  transition_c *symbol;
  int priority;
} TRANSITION;

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_c_sfc_elements_c: public generate_c_base_and_typeid_c {

  public:
    typedef enum {
      transitionlist_sg,
      transitiontest_sg,
      stepset_sg,
      stepreset_sg,
      stepsetreset_sg,
      actionassociation_sg,
      actionbody_sg,
      steptmpinit_sg,
      stepinit_sg,
      actioninit_sg,
      actionstateeval_sg,
      actionprevq_sg
    } sfcgeneration_t;

  private:
    generate_c_il_c *generate_c_il;
    generate_c_st_c *generate_c_st;
    generate_c_SFC_IL_ST_c *generate_c_code;
    search_var_instance_decl_c *search_var_instance_decl;

    std::list<TRANSITION> transition_list;

    symbol_c *current_step;
    symbol_c *current_action;
    transition_c *current_transition;

    sfcgeneration_t wanted_sfcgeneration;

  public:
    generate_c_sfc_elements_c(stage4out_c *s4o_ptr, symbol_c *name, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_c_base_and_typeid_c(s4o_ptr) {
      generate_c_il = new generate_c_il_c(s4o_ptr, name, scope, variable_prefix);
      generate_c_st = new generate_c_st_c(s4o_ptr, name, scope, variable_prefix);
      generate_c_code = new generate_c_SFC_IL_ST_c(s4o_ptr, name, scope, variable_prefix);
      search_var_instance_decl = new search_var_instance_decl_c(scope);
      this->set_variable_prefix(variable_prefix);
      current_transition = NULL;
    }

    ~generate_c_sfc_elements_c(void) {
      transition_list.clear();
      delete generate_c_il;
      delete generate_c_st;
      delete generate_c_code;
      delete search_var_instance_decl;
    }


	bool is_variable(symbol_c *symbol) {
	  /* we try to find the variable instance declaration, to determine if symbol is variable... */
	  symbol_c *var_decl = search_var_instance_decl->get_decl(symbol);

	  return var_decl != NULL;
	}

    void generate(symbol_c *symbol, sfcgeneration_t generation_type) {
      wanted_sfcgeneration = generation_type;
      switch (wanted_sfcgeneration) {
        case transitiontest_sg:
          {
            std::list<TRANSITION>::iterator pt;
            for(pt = transition_list.begin(); pt != transition_list.end(); pt++) {
              current_transition = pt->symbol;
              pt->symbol->accept(*this);
            }
          }
          break;
        default:
          symbol->accept(*this);
          break;
      }
    }

    /* Emit per-action init code (Q=0, set=0, reset=0, timer countdowns) */
    void print_action_init_code(symbol_c *action_name) {
      /* Q = 0 */
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_action_argument(action_name, "Q", true);
      s4o.print(",,0);\n");
      /* set = 0 */
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_action_argument(action_name, "set", true);
      s4o.print(",,0);\n");
      /* reset = 0 */
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_action_argument(action_name, "reset", true);
      s4o.print(",,0);\n");
      /* timer countdown for set_remaining_time */
      print_action_timer_countdown(action_name, "set_remaining_time", "set");
      /* timer countdown for reset_remaining_time */
      print_action_timer_countdown(action_name, "reset_remaining_time", "reset");
    }

    /* Print step variable with underscore separator: StepName_suffix */
    void print_step_argument(symbol_c *step_name, const char* argument, bool setter=false) {
      print_variable_prefix();
      if (setter) s4o.print(",");
      step_name->accept(*this);
      s4o.print("_");
      s4o.print(argument);
    }

    /* Print action variable with underscore separator: ActionName_suffix */
    void print_action_argument(symbol_c *action_name, const char* argument, bool setter=false) {
      print_variable_prefix();
      if (setter) s4o.print(",");
      action_name->accept(*this);
      s4o.print("_");
      s4o.print(argument);
    }

    /* Print the current transition variable name */
    void print_current_transition(bool setter=false) {
      print_variable_prefix();
      if (setter) s4o.print(",");
      print_transition_name(s4o, *this, current_transition);
    }

    void print_reset_step(symbol_c *step_name) {
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_step_argument(step_name, "X", true);
      s4o.print(",,0);\n");
    }

    void print_set_step(symbol_c *step_name) {
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_step_argument(step_name, "X", true);
      s4o.print(",,1);\n");

      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_step_argument(step_name, "T", true);
      s4o.print(",,__time_to_timespec(1, 0, 0, 0, 0, 0));\n");
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/

    void *visit(initial_step_c *symbol) {
      switch (wanted_sfcgeneration) {
        case steptmpinit_sg:
          // remember step activity
          s4o.print(s4o.indent_spaces + "IEC_BOOL ");
          symbol->step_name->accept(*this);
          s4o.print("_X = ");
          s4o.print(GET_VAR);
          s4o.print("(");
          print_step_argument(symbol->step_name, "X");
          s4o.print(");\n");
          break;
        case stepinit_sg:
          /* prev_state = GET_VAR(X) */
          s4o.print(s4o.indent_spaces);
          s4o.print(SET_VAR);
          s4o.print("(");
          print_step_argument(symbol->step_name, "prev_state", true);
          s4o.print(",,");
          symbol->step_name->accept(*this);
          s4o.print("_X);\n");

          /* if (X) T += elapsed_time */
          s4o.print(s4o.indent_spaces + "if (");
          symbol->step_name->accept(*this);
          s4o.print("_X) {\n");
          s4o.indent_right();
          s4o.print(s4o.indent_spaces);
          s4o.print(SET_VAR);
          s4o.print("(");
          print_step_argument(symbol->step_name, "T", true);
          s4o.print(",,__time_add(");
          s4o.print(GET_VAR);
          s4o.print("(");
          print_step_argument(symbol->step_name, "T");
          s4o.print("), elapsed_time));\n");
          s4o.indent_left();
          s4o.print(s4o.indent_spaces + "}\n");
          break;
        case actionassociation_sg:
          if (((list_c*)symbol->action_association_list)->n > 0) {
            s4o.print(s4o.indent_spaces + "// ");
            symbol->step_name->accept(*this);
            s4o.print(" action associations\n");
            current_step = symbol->step_name;
            s4o.print(s4o.indent_spaces + "{\n");
            s4o.indent_right();
            s4o.print(s4o.indent_spaces + "char active = ");
            s4o.print(GET_VAR);
            s4o.print("(");
            print_step_argument(current_step, "X");
            s4o.print(");\n");
            s4o.print(s4o.indent_spaces + "char activated = active && !");
            s4o.print(GET_VAR);
            s4o.print("(");
            print_step_argument(current_step, "prev_state");
            s4o.print(");\n");
            s4o.print(s4o.indent_spaces + "char desactivated = !active && ");
            s4o.print(GET_VAR);
            s4o.print("(");
            print_step_argument(current_step, "prev_state");
            s4o.print(");\n\n");

            // Avoid unused variable warnings
            s4o.print(s4o.indent_spaces + "(void)active;\n");
            s4o.print(s4o.indent_spaces + "(void)activated;\n");
            s4o.print(s4o.indent_spaces + "(void)desactivated;\n\n");

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
        case steptmpinit_sg:
          // remember step activity
          s4o.print(s4o.indent_spaces + "IEC_BOOL ");
          symbol->step_name->accept(*this);
          s4o.print("_X = ");
          s4o.print(GET_VAR);
          s4o.print("(");
          print_step_argument(symbol->step_name, "X");
          s4o.print(");\n");
          break;
        case stepinit_sg:
          /* prev_state = GET_VAR(X) */
          s4o.print(s4o.indent_spaces);
          s4o.print(SET_VAR);
          s4o.print("(");
          print_step_argument(symbol->step_name, "prev_state", true);
          s4o.print(",,");
          symbol->step_name->accept(*this);
          s4o.print("_X);\n");

          /* if (X) T += elapsed_time */
          s4o.print(s4o.indent_spaces + "if (");
          symbol->step_name->accept(*this);
          s4o.print("_X) {\n");
          s4o.indent_right();
          s4o.print(s4o.indent_spaces);
          s4o.print(SET_VAR);
          s4o.print("(");
          print_step_argument(symbol->step_name, "T", true);
          s4o.print(",,__time_add(");
          s4o.print(GET_VAR);
          s4o.print("(");
          print_step_argument(symbol->step_name, "T");
          s4o.print("), elapsed_time));\n");
          s4o.indent_left();
          s4o.print(s4o.indent_spaces + "}\n");
          break;
        case actionassociation_sg:
          if (((list_c*)symbol->action_association_list)->n > 0) {
            s4o.print(s4o.indent_spaces + "// ");
            symbol->step_name->accept(*this);
            s4o.print(" action associations\n");
            current_step = symbol->step_name;
            s4o.print(s4o.indent_spaces + "{\n");
            s4o.indent_right();
            s4o.print(s4o.indent_spaces + "char active = ");
            s4o.print(GET_VAR);
            s4o.print("(");
            print_step_argument(current_step, "X");
            s4o.print(");\n");
            s4o.print(s4o.indent_spaces + "char activated = active && !");
            s4o.print(GET_VAR);
            s4o.print("(");
            print_step_argument(current_step, "prev_state");
            s4o.print(");\n");
            s4o.print(s4o.indent_spaces + "char desactivated = !active && ");
            s4o.print(GET_VAR);
            s4o.print("(");
            print_step_argument(current_step, "prev_state");
            s4o.print(");\n\n");

            // Avoid unused variable warnings
            s4o.print(s4o.indent_spaces + "(void)active;\n");
            s4o.print(s4o.indent_spaces + "(void)activated;\n");
            s4o.print(s4o.indent_spaces + "(void)desactivated;\n\n");

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
          }
          break;
        case transitiontest_sg:
          current_transition = symbol;
          // Always evaluate transition condition
          symbol->transition_condition->accept(*this);
          break;
        case stepsetreset_sg:
          current_transition = symbol;
          s4o.print(s4o.indent_spaces + "if (");
          wanted_sfcgeneration = transitiontest_sg;
          symbol->from_steps->accept(*this);
          wanted_sfcgeneration = stepreset_sg;
          s4o.print(" && ");
          s4o.print(GET_VAR);
          s4o.print("(");
          print_current_transition();
          s4o.print(")) {\n");
          s4o.indent_right();
          symbol->from_steps->accept(*this);
          wanted_sfcgeneration = stepset_sg;
          symbol->to_steps->accept(*this);
          s4o.indent_left();
          s4o.print(s4o.indent_spaces + "}\n");
          wanted_sfcgeneration = stepsetreset_sg;
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(transition_condition_c *symbol) {
      switch (wanted_sfcgeneration) {
        case transitiontest_sg:
          // Transition condition is in IL
          if (symbol->transition_condition_il != NULL) {
            generate_c_il->declare_implicit_variable_back();
            s4o.print(s4o.indent_spaces);
            symbol->transition_condition_il->accept(*generate_c_il);
            s4o.print(SET_VAR);
            s4o.print("(");
            print_current_transition(true);
            s4o.print(",,");
            generate_c_il->print_implicit_variable_back();
            s4o.print(");\n");
          }
          // Transition condition is in ST
          if (symbol->transition_condition_st != NULL) {
            s4o.print(s4o.indent_spaces);
            s4o.print(SET_VAR);
            s4o.print("(");
            print_current_transition(true);
            s4o.print(",,");
            symbol->transition_condition_st->accept(*generate_c_st);
            s4o.print(");\n");
          }
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(action_c *symbol) {
      switch (wanted_sfcgeneration) {
        case actioninit_sg:
          print_action_init_code(symbol->action_name);
          break;
        case actionstateeval_sg:
          print_action_state_eval(symbol->action_name);
          break;
        case actionbody_sg:
          /* Executed while A = Q OR F_TRIG(Q) (IEC 61131-3 action control, 'final scan'):
           * pass 0 runs the actions whose Q fell in this scan (one last execution, the step
           * flags of the deactivated steps are already FALSE), pass 1 runs the active ones. */
          s4o.print(s4o.indent_spaces + "if(__sfc_pass ? ");
          s4o.print(GET_VAR);
          s4o.print("(");
          print_action_argument(symbol->action_name, "Q");
          s4o.print(") : (!");
          s4o.print(GET_VAR);
          s4o.print("(");
          print_action_argument(symbol->action_name, "Q");
          s4o.print(") && ");
          s4o.print(GET_VAR);
          s4o.print("(");
          print_action_argument(symbol->action_name, "prev_Q");
          s4o.print("))) {\n");
          s4o.indent_right();

          // generate action code
          symbol->function_block_body->accept(*generate_c_code);

          s4o.indent_left();
          s4o.print(s4o.indent_spaces + "}\n\n");
          break;
        case actionprevq_sg:
          /* prev_Q = Q: edge memory of the F_TRIG behind the final scan */
          s4o.print(s4o.indent_spaces);
          s4o.print(SET_VAR);
          s4o.print("(");
          print_action_argument(symbol->action_name, "prev_Q", true);
          s4o.print(",,");
          s4o.print(GET_VAR);
          s4o.print("(");
          print_action_argument(symbol->action_name, "Q");
          s4o.print("));\n");
          break;
        default:
          break;
      }
      return NULL;
    }

    /* Generate timer countdown code for an action */
    void print_action_timer_countdown(symbol_c *action_name, const char *timer_suffix, const char *flag_suffix) {
      s4o.print(s4o.indent_spaces + "if (");
      s4o.print("__time_cmp(");
      s4o.print(GET_VAR);
      s4o.print("(");
      print_action_argument(action_name, timer_suffix);
      s4o.print("), __time_to_timespec(1, 0, 0, 0, 0, 0)) > 0) {\n");
      s4o.indent_right();

      /* timer -= elapsed_time */
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_action_argument(action_name, timer_suffix, true);
      s4o.print(",,__time_sub(");
      s4o.print(GET_VAR);
      s4o.print("(");
      print_action_argument(action_name, timer_suffix);
      s4o.print("), elapsed_time));\n");

      /* if timer expired */
      s4o.print(s4o.indent_spaces + "if (");
      s4o.print("__time_cmp(");
      s4o.print(GET_VAR);
      s4o.print("(");
      print_action_argument(action_name, timer_suffix);
      s4o.print("), __time_to_timespec(1, 0, 0, 0, 0, 0)) <= 0) {\n");
      s4o.indent_right();

      /* reset timer */
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_action_argument(action_name, timer_suffix, true);
      s4o.print(",,__time_to_timespec(1, 0, 0, 0, 0, 0));\n");

      /* flag = 1 */
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_action_argument(action_name, flag_suffix, true);
      s4o.print(",,1);\n");

      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
    }

    /* Generate action state evaluation: if(set) stored=1, if(reset) stored=0, Q = Q | stored */
    void print_action_state_eval(symbol_c *action_name) {
      /* if (set) { set_remaining_time = 0; stored = 1; } */
      s4o.print(s4o.indent_spaces + "if (");
      s4o.print(GET_VAR);
      s4o.print("(");
      print_action_argument(action_name, "set");
      s4o.print(")) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_action_argument(action_name, "set_remaining_time", true);
      s4o.print(",,__time_to_timespec(1, 0, 0, 0, 0, 0));\n");
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_action_argument(action_name, "stored", true);
      s4o.print(",,1);\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");

      /* if (reset) { reset_remaining_time = 0; stored = 0; } */
      s4o.print(s4o.indent_spaces + "if (");
      s4o.print(GET_VAR);
      s4o.print("(");
      print_action_argument(action_name, "reset");
      s4o.print(")) {\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_action_argument(action_name, "reset_remaining_time", true);
      s4o.print(",,__time_to_timespec(1, 0, 0, 0, 0, 0));\n");
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_action_argument(action_name, "stored", true);
      s4o.print(",,0);\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");

      /* Q = Q | stored */
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_action_argument(action_name, "Q", true);
      s4o.print(",,");
      s4o.print(GET_VAR);
      s4o.print("(");
      print_action_argument(action_name, "Q");
      s4o.print(") | ");
      s4o.print(GET_VAR);
      s4o.print("(");
      print_action_argument(action_name, "stored");
      s4o.print("));\n");
    }

    void *visit(steps_c *symbol) {
      if (symbol->step_name != NULL) {
        switch (wanted_sfcgeneration) {
          case transitiontest_sg:
            symbol->step_name->accept(*this);
            s4o.print("_X");
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
            symbol->get_element(i)->accept(*this);
            s4o.print("_X");
            if (i < symbol->n - 1) {
              s4o.print(" && ");
            }
          }
          break;
        case stepset_sg:
          for(int i = 0; i < symbol->n; i++) {
            print_set_step(symbol->get_element(i));
          }
          break;
        case stepreset_sg:
          for(int i = 0; i < symbol->n; i++) {
            print_reset_step(symbol->get_element(i));
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
            current_step->accept(*this);
            s4o.print("_X) {\n");
            s4o.indent_right();
            s4o.print(s4o.indent_spaces);
            s4o.print(SET_VAR);
            s4o.print("(");
            print_action_argument(symbol->action_name, "Q", true);
            s4o.print(",,1);\n");
            s4o.indent_left();
            s4o.print(s4o.indent_spaces + "}");
          }
          break;
        default:
          break;
      }
      return NULL;
    }


    void print_set_var(symbol_c *var, const char *value) {
      unsigned int vartype = search_var_instance_decl->get_vartype(var);
      s4o.print("{"); // it is safer to embed these macros inside a {..} block
      if (vartype == search_var_instance_decl_c::external_vt)
        s4o.print(SET_EXTERNAL);
      else if (vartype == search_var_instance_decl_c::located_vt)
        s4o.print(SET_LOCATED);
      else
        s4o.print(SET_VAR);
      s4o.print("(");
      print_variable_prefix();
      s4o.print(",");
      var->accept(*this);
      s4o.print(",,");
      s4o.print(value);
      s4o.print(");}");
    }

    void print_set_action_state(symbol_c *action, const char *value) {
      s4o.print("{"); // it is safer to embed these macros inside a {..} block
      s4o.print(SET_VAR);
      s4o.print("(");
      print_action_argument(action, "Q", true);
      s4o.print(",,");
      s4o.print(value);
      s4o.print(");}");
    }

    void print_set_var_or_action_state(symbol_c *action, const char *value) {
      if (is_variable(current_action))
        print_set_var         (action, value);
      else
        print_set_action_state(action, value);
    }

    void *visit(action_qualifier_c *symbol) {
      switch (wanted_sfcgeneration) {
        case actionassociation_sg:
          {
            char *qualifier = (char *)symbol->action_qualifier->accept(*this);
            /* N qualifier */
            if (strcmp(qualifier, "N") == 0) {
              s4o.print(s4o.indent_spaces + "if (active)       ");
              print_set_var_or_action_state(current_action, "1");
              s4o.print(";\n");
              s4o.print(s4o.indent_spaces + "if (desactivated) ");
              print_set_var_or_action_state(current_action, "0");
              s4o.print(";\n");
              return NULL;
            }
            /* S qualifier */
            if (strcmp(qualifier, "S") == 0) {
              s4o.print(s4o.indent_spaces + "if (active)       {");
              s4o.print(SET_VAR);
              s4o.print("(");
              print_action_argument(current_action, "set", true);
              s4o.print(",,1);};\n");
              return NULL;
            }
            /* R qualifier */
            if (strcmp(qualifier, "R") == 0) {
              s4o.print(s4o.indent_spaces + "if (active)       {");
              s4o.print(SET_VAR);
              s4o.print("(");
              print_action_argument(current_action, "reset", true);
              s4o.print(",,1);};\n");
              return NULL;
            }
            /* L or D qualifiers */
            if ((strcmp(qualifier, "L") == 0) ||
                (strcmp(qualifier, "D") == 0)) {
              s4o.print(s4o.indent_spaces + "if (active && __time_cmp(");
              s4o.print(GET_VAR);
              s4o.print("(");
              print_step_argument(current_step, "T");
              s4o.print("), ");
              symbol->action_time->accept(*generate_c_st);
              if (strcmp(qualifier, "L") == 0)
                s4o.print(") < 0) ");
              else
                s4o.print(") >= 0) ");
              s4o.print("\n" + s4o.indent_spaces + "                  ");
              print_set_var_or_action_state(current_action, "1");
              if (strcmp(qualifier, "L") == 0)
                // in L, we force to zero while state is active and time has been reached
                // or when the state is deactivated.
                s4o.print("\n" + s4o.indent_spaces + "else if (desactivated || active)");
              else
                s4o.print("\n" + s4o.indent_spaces + "else if (desactivated)");
              s4o.print("\n" + s4o.indent_spaces + "                  ");
              print_set_var_or_action_state(current_action, "0");
              s4o.print(";\n");
              return NULL;
            }
            /* P, P1 or P0 qualifiers */
            if ( (strcmp(qualifier, "P" ) == 0) ||
                 (strcmp(qualifier, "P1") == 0) ||
                 (strcmp(qualifier, "P0") == 0)) {
              if (strcmp(qualifier, "P0") == 0) {
                s4o.print(s4o.indent_spaces + "if (desactivated) ");
                print_set_var_or_action_state(current_action, "1");
                s4o.print("\n" + s4o.indent_spaces + "else if (activated || active)");
                print_set_var_or_action_state(current_action, "0");
                s4o.print(";\n");
              }
              else {
                s4o.print(s4o.indent_spaces + "if (activated)    ");
                print_set_var_or_action_state(current_action, "1");
                s4o.print("\n" + s4o.indent_spaces + "else if (desactivated || active)");
                print_set_var_or_action_state(current_action, "0");
                s4o.print(";\n");
              }
              return NULL;
            }
            /* SL qualifier */
            if (strcmp(qualifier, "SL") == 0) {
              s4o.print(s4o.indent_spaces + "if (activated) {");
              s4o.indent_right();
              s4o.print("\n" + s4o.indent_spaces);
              s4o.print(SET_VAR);
              s4o.print("(");
              print_action_argument(current_action, "set", true);
              s4o.print(",,1);\n" + s4o.indent_spaces);
              s4o.print(SET_VAR);
              s4o.print("(");
              print_action_argument(current_action, "reset_remaining_time", true);
              s4o.print(",,");
              symbol->action_time->accept(*generate_c_st);
              s4o.print(");\n");
              s4o.indent_left();
              s4o.print(s4o.indent_spaces + "}\n");
              return NULL;
            }
            /* SD and DS qualifiers */
            if ( (strcmp(qualifier, "SD") == 0) ||
                 (strcmp(qualifier, "DS") == 0)) {
              s4o.print(s4o.indent_spaces + "if (activated) {");
              s4o.indent_right();
              s4o.print("\n" + s4o.indent_spaces);
              s4o.print(SET_VAR);
              s4o.print("(");
              print_action_argument(current_action, "set_remaining_time", true);
              s4o.print(",,");
              symbol->action_time->accept(*generate_c_st);
              s4o.print(");\n");
              s4o.indent_left();
              s4o.print(s4o.indent_spaces + "}\n");
              if (strcmp(qualifier, "DS") == 0) {
                s4o.print(s4o.indent_spaces + "if (desactivated) {");
                s4o.indent_right();
                s4o.print("\n" + s4o.indent_spaces);
                s4o.print(SET_VAR);
                s4o.print("(");
                print_action_argument(current_action, "set_remaining_time", true);
                s4o.print(",,__time_to_timespec(1, 0, 0, 0, 0, 0));\n");
                s4o.indent_left();
                s4o.print(s4o.indent_spaces + "}\n");
              }
              return NULL;
            }
            ERROR;
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

}; /* generate_c_sfc_elements_c */


/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_c_sfc_c: public generate_c_base_and_typeid_c {

  private:
    std::list<VARIABLE> variable_list;

    generate_c_sfc_elements_c *generate_c_sfc_elements;
    search_var_instance_decl_c *search_var_instance_decl;

  public:
    generate_c_sfc_c(stage4out_c *s4o_ptr, symbol_c *name, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_c_base_and_typeid_c(s4o_ptr) {
      generate_c_sfc_elements = new generate_c_sfc_elements_c(s4o_ptr, name, scope, variable_prefix);
      search_var_instance_decl = new search_var_instance_decl_c(scope);
      this->set_variable_prefix(variable_prefix);
    }

    virtual ~generate_c_sfc_c(void) {
      variable_list.clear();
      delete generate_c_sfc_elements;
      delete search_var_instance_decl;
    }

    bool is_variable(symbol_c *symbol) {
      /* we try to find the variable instance declaration, to determine if symbol is variable... */
      symbol_c *var_decl = search_var_instance_decl->get_decl(symbol);

      return var_decl != NULL;
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/

    void *visit(sequential_function_chart_c *symbol) {
      int i;

      /* Build transition list with priorities */
      for(i = 0; i < symbol->n; i++) {
        symbol->get_element(i)->accept(*this);
        generate_c_sfc_elements->generate(symbol->get_element(i), generate_c_sfc_elements_c::transitionlist_sg);
      }

      s4o.print(s4o.indent_spaces +"TIME elapsed_time, current_time;\n\n");

      /* generate elapsed_time initializations */
      s4o.print(s4o.indent_spaces + "// Calculate elapsed_time\n");
      s4o.print(s4o.indent_spaces +"current_time = __CURRENT_TIME;\n");
      s4o.print(s4o.indent_spaces +"elapsed_time = __time_sub(current_time, ");
      s4o.print(GET_VAR);
      s4o.print("(");
      print_variable_prefix();
      s4o.print("__lasttick_time));\n");
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_variable_prefix();
      s4o.print(",__lasttick_time,,current_time);\n");

      for(i = 0; i < symbol->n; i++) {
        generate_c_sfc_elements->generate(symbol->get_element(i), generate_c_sfc_elements_c::steptmpinit_sg);
      }
      /* generate step initializations (per-step) */
      s4o.print(s4o.indent_spaces + "// Steps initialization\n");
      for(i = 0; i < symbol->n; i++) {
        generate_c_sfc_elements->generate(symbol->get_element(i), generate_c_sfc_elements_c::stepinit_sg);
      }

      /* generate action initializations (per-action block) */
      s4o.print(s4o.indent_spaces + "// Actions initialization\n");
      for(i = 0; i < symbol->n; i++) {
        generate_c_sfc_elements->generate(symbol->get_element(i), generate_c_sfc_elements_c::actioninit_sg);
      }
      /* init variable-actions */
      {
        std::list<VARIABLE>::iterator pt;
        for(pt = variable_list.begin(); pt != variable_list.end(); pt++) {
          generate_c_sfc_elements->print_action_init_code(pt->symbol);
        }
      }
      s4o.print("\n");

      /* generate transition tests */
      s4o.print(s4o.indent_spaces + "// Transitions fire test\n");
      generate_c_sfc_elements->generate((symbol_c *)symbol, generate_c_sfc_elements_c::transitiontest_sg);
      s4o.print("\n");

      /* generate transition set reset steps */
      s4o.print(s4o.indent_spaces + "// Transitions set and reset steps\n");
      for(i = 0; i < symbol->n; i++) {
        generate_c_sfc_elements->generate(symbol->get_element(i), generate_c_sfc_elements_c::stepsetreset_sg);
      }
      s4o.print("\n");

      /* generate step association */
      s4o.print(s4o.indent_spaces + "// Steps association\n");
      for(i = 0; i < symbol->n; i++) {
        generate_c_sfc_elements->generate(symbol->get_element(i), generate_c_sfc_elements_c::actionassociation_sg);
      }
      s4o.print("\n");

      /* generate action state evaluation (per-action block) */
      s4o.print(s4o.indent_spaces + "// Actions state evaluation\n");
      for(i = 0; i < symbol->n; i++) {
        generate_c_sfc_elements->generate(symbol->get_element(i), generate_c_sfc_elements_c::actionstateeval_sg);
      }
      /* state eval for variable-actions */
      {
        std::list<VARIABLE>::iterator pt;
        for(pt = variable_list.begin(); pt != variable_list.end(); pt++) {
          generate_c_sfc_elements->print_action_state_eval(pt->symbol);
        }
      }
      s4o.print("\n");

      /* generate action execution */
      s4o.print(s4o.indent_spaces + "// Actions execution\n");
      {
        std::list<VARIABLE>::iterator pt;
        for(pt = variable_list.begin(); pt != variable_list.end(); pt++) {

          if (is_variable(pt->symbol)) {
            unsigned int vartype = search_var_instance_decl->get_vartype(pt->symbol);

            s4o.print(s4o.indent_spaces + "if (");
            s4o.print(GET_VAR);
            s4o.print("(");
            generate_c_sfc_elements->print_action_argument(pt->symbol, "reset");
            s4o.print(")) {\n");
            s4o.indent_right();
            s4o.print(s4o.indent_spaces);
            if (vartype == search_var_instance_decl_c::external_vt)
              s4o.print(SET_EXTERNAL);
            else if (vartype == search_var_instance_decl_c::located_vt)
              s4o.print(SET_LOCATED);
            else
              s4o.print(SET_VAR);
            s4o.print("(");
            print_variable_prefix();
            s4o.print(",");
            pt->symbol->accept(*this);
            s4o.print(",,0);\n");
            s4o.indent_left();
            s4o.print(s4o.indent_spaces + "}\n");
            s4o.print(s4o.indent_spaces + "else if (");
            s4o.print(GET_VAR);
            s4o.print("(");
            generate_c_sfc_elements->print_action_argument(pt->symbol, "set");
            s4o.print(")) {\n");
            s4o.indent_right();
            s4o.print(s4o.indent_spaces);
            if (vartype == search_var_instance_decl_c::external_vt)
              s4o.print(SET_EXTERNAL);
            else if (vartype == search_var_instance_decl_c::located_vt)
              s4o.print(SET_LOCATED);
            else
              s4o.print(SET_VAR);
            s4o.print("(");
            print_variable_prefix();
            s4o.print(",");
            pt->symbol->accept(*this);
            s4o.print(",,1);\n");
            s4o.indent_left();
            s4o.print(s4o.indent_spaces + "}\n");
          }
        }
      }
      /* Two passes over the action bodies, each body emitted once: first the final scan of
       * the actions deactivated in this scan, then the active actions (same order as
       * CODESYS IEC actions), so a value written by an active action wins. */
      s4o.print(s4o.indent_spaces + "{\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces + "int __sfc_pass;\n");
      s4o.print(s4o.indent_spaces + "for (__sfc_pass = 0; __sfc_pass < 2; __sfc_pass++) {\n");
      s4o.indent_right();
      for(i = 0; i < symbol->n; i++) {
        generate_c_sfc_elements->generate(symbol->get_element(i), generate_c_sfc_elements_c::actionbody_sg);
      }
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n");
      for(i = 0; i < symbol->n; i++) {
        generate_c_sfc_elements->generate(symbol->get_element(i), generate_c_sfc_elements_c::actionprevq_sg);
      }
      s4o.print("\n");

      return NULL;
    }

    void *visit(initial_step_c *symbol) {
      symbol->action_association_list->accept(*this);
      return NULL;
    }

    void *visit(step_c *symbol) {
      symbol->action_association_list->accept(*this);
      return NULL;
    }

    void *visit(action_association_c *symbol) {
      if (is_variable(symbol->action_name)) {
        std::list<VARIABLE>::iterator pt;
        for(pt = variable_list.begin(); pt != variable_list.end(); pt++) {
          if (!compare_identifiers(pt->symbol, symbol->action_name))
            return NULL;
        }
        VARIABLE *variable;
        variable = new VARIABLE;
        variable->symbol = (identifier_c*)(symbol->action_name);
        variable_list.push_back(*variable);
      }
      return NULL;
    }

    void *visit(transition_c *symbol) {
      return NULL;
    }

    void *visit(action_c *symbol) {
      return NULL;
    }

    void generate(sequential_function_chart_c *sfc) {
      sfc->accept(*this);
    }

}; /* generate_c_sfc_c */
