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
  identifier_c *symbol;
} VARIABLE;

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

/* Print step names from a steps_c, separated by sep */
static void print_steps_names(stage4out_c &s4o, generate_c_base_and_typeid_c &printer, symbol_c *steps, const char *sep) {
  steps_c *s = dynamic_cast<steps_c *>(steps);
  if (s == NULL) return;
  if (s->step_name != NULL) {
    s->step_name->accept(printer);
  } else if (s->step_name_list != NULL) {
    step_name_list_c *lst = dynamic_cast<step_name_list_c *>(s->step_name_list);
    if (lst != NULL) {
      for (int i = 0; i < lst->n; i++) {
        if (i > 0) s4o.print(sep);
        lst->get_element(i)->accept(printer);
      }
    }
  }
}

/* Print a transition variable name: FromStep_TO_ToStep */
static void print_transition_name(stage4out_c &s4o, generate_c_base_and_typeid_c &printer, transition_c *t) {
  print_steps_names(s4o, printer, t->from_steps, "_");
  s4o.print("_TO_");
  print_steps_names(s4o, printer, t->to_steps, "_");
}

class generate_c_sfcdecl_c: protected generate_c_base_and_typeid_c {

  public:
      typedef enum {
        sfcdecl_sd,
        sfcinit_sd
       } sfcdeclaration_t;

  private:
    std::list<VARIABLE> variable_list;

    sfcdeclaration_t wanted_sfcdeclaration;

    search_var_instance_decl_c *search_var_instance_decl;

  public:
    generate_c_sfcdecl_c(stage4out_c *s4o_ptr, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_c_base_and_typeid_c(s4o_ptr) {
      this->set_variable_prefix(variable_prefix);
      search_var_instance_decl = new search_var_instance_decl_c(scope);
    }
    ~generate_c_sfcdecl_c(void) {
      variable_list.clear();
      delete search_var_instance_decl;
    }

    void generate(symbol_c *symbol, sfcdeclaration_t declaration_type) {
      wanted_sfcdeclaration = declaration_type;

      symbol->accept(*this);
    }

    void print_step_decl(symbol_c *step_name) {
      s4o.print(s4o.indent_spaces + "__DECLARE_VAR(BOOL,");
      step_name->accept(*this);
      s4o.print("_X)\n");
      s4o.print(s4o.indent_spaces + "__DECLARE_VAR(TIME,");
      step_name->accept(*this);
      s4o.print("_T)\n");
      s4o.print(s4o.indent_spaces + "__DECLARE_VAR(BOOL,");
      step_name->accept(*this);
      s4o.print("_prev_state)\n");
    }

    void print_step_init(symbol_c *step_name, bool is_initial) {
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_variable_prefix();
      s4o.print(",");
      step_name->accept(*this);
      s4o.print("_X,,");
      s4o.print(is_initial ? "1" : "0");
      s4o.print(");\n");

      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_variable_prefix();
      s4o.print(",");
      step_name->accept(*this);
      s4o.print("_T,,__time_to_timespec(1, 0, 0, 0, 0, 0));\n");

      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_variable_prefix();
      s4o.print(",");
      step_name->accept(*this);
      s4o.print("_prev_state,,0);\n");
    }

    void print_action_decl(symbol_c *action_name) {
      const char *suffixes[] = {"_Q", "_prev_Q", "_stored", "_set", "_reset"};
      for (int i = 0; i < 5; i++) {
        s4o.print(s4o.indent_spaces + "__DECLARE_VAR(BOOL,");
        action_name->accept(*this);
        s4o.print(suffixes[i]);
        s4o.print(")\n");
      }
      const char *time_suffixes[] = {"_set_remaining_time", "_reset_remaining_time"};
      for (int i = 0; i < 2; i++) {
        s4o.print(s4o.indent_spaces + "__DECLARE_VAR(TIME,");
        action_name->accept(*this);
        s4o.print(time_suffixes[i]);
        s4o.print(")\n");
      }
    }

    void print_set_var_init(symbol_c *name, const char *suffix, const char *value) {
      s4o.print(s4o.indent_spaces);
      s4o.print(SET_VAR);
      s4o.print("(");
      print_variable_prefix();
      s4o.print(",");
      name->accept(*this);
      s4o.print(suffix);
      s4o.print(",,");
      s4o.print(value);
      s4o.print(");\n");
    }

    void print_action_init(symbol_c *action_name) {
      print_set_var_init(action_name, "_Q", "0");
      print_set_var_init(action_name, "_prev_Q", "0");
      print_set_var_init(action_name, "_stored", "0");
      print_set_var_init(action_name, "_set", "0");
      print_set_var_init(action_name, "_reset", "0");
      print_set_var_init(action_name, "_set_remaining_time", "__time_to_timespec(1, 0, 0, 0, 0, 0)");
      print_set_var_init(action_name, "_reset_remaining_time", "__time_to_timespec(1, 0, 0, 0, 0, 0)");
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/

    void *visit(sequential_function_chart_c *symbol) {
      switch (wanted_sfcdeclaration) {
        case sfcdecl_sd:
          for(int i = 0; i < symbol->n; i++)
            symbol->get_element(i)->accept(*this);

          /* last_ticktime declaration */
          s4o.print(s4o.indent_spaces + "__DECLARE_VAR(TIME,__lasttick_time)\n");
          break;
        case sfcinit_sd:
          for(int i = 0; i < symbol->n; i++)
            symbol->get_element(i)->accept(*this);

          /* last_ticktime initialisation */
          s4o.print(s4o.indent_spaces);
          s4o.print(SET_VAR);
          s4o.print("(");
          print_variable_prefix();
          s4o.print(",__lasttick_time,,__CURRENT_TIME);\n");
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(initial_step_c *symbol) {
      switch (wanted_sfcdeclaration) {
        case sfcdecl_sd:
          print_step_decl(symbol->step_name);
          symbol->action_association_list->accept(*this);
          break;
        case sfcinit_sd:
          print_step_init(symbol->step_name, true);
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(step_c *symbol) {
      switch (wanted_sfcdeclaration) {
        case sfcdecl_sd:
          print_step_decl(symbol->step_name);
          symbol->action_association_list->accept(*this);
          break;
        case sfcinit_sd:
          print_step_init(symbol->step_name, false);
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(action_association_c *symbol) {
      if (wanted_sfcdeclaration != sfcdecl_sd) return NULL;
      /* we try to find the variable instance declaration, to determine if symbol is variable... */
      symbol_c *var_decl = search_var_instance_decl->get_decl(symbol->action_name);
      if (var_decl != NULL) {
        std::list<VARIABLE>::iterator pt;
        for(pt = variable_list.begin(); pt != variable_list.end(); pt++) {
          if (!compare_identifiers(pt->symbol, symbol->action_name))
            return NULL;
        }
        VARIABLE *variable;
        variable = new VARIABLE;
        variable->symbol = (identifier_c*)(symbol->action_name);
        variable_list.push_back(*variable);
        print_action_decl(symbol->action_name);
      }
      return NULL;
    }

    void *visit(transition_c *symbol) {
      switch (wanted_sfcdeclaration) {
        case sfcdecl_sd:
          s4o.print(s4o.indent_spaces + "__DECLARE_VAR(BOOL,");
          print_transition_name(s4o, *this, symbol);
          s4o.print(")\n");
          break;
        case sfcinit_sd:
          s4o.print(s4o.indent_spaces);
          s4o.print(SET_VAR);
          s4o.print("(");
          print_variable_prefix();
          s4o.print(",");
          print_transition_name(s4o, *this, symbol);
          s4o.print(",,0);\n");
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(action_c *symbol) {
      switch (wanted_sfcdeclaration) {
        case sfcdecl_sd:
          print_action_decl(symbol->action_name);
          break;
        case sfcinit_sd:
          print_action_init(symbol->action_name);
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(instruction_list_c *symbol) {
      return NULL;
    }

    void *visit(statement_list_c *symbol) {
      return NULL;
    }

}; /* generate_c_sfcdecl_c */

