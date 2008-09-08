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

class generate_c_sfcdecl_c: protected generate_c_typedecl_c {
  
  public:
      typedef enum {
        sfcdecl_sd,
        sfcinit_sd,
        stepcount_sd,
        stepdef_sd,
        stepundef_sd,
        actiondef_sd,
        actionundef_sd,
        actioncount_sd
       } sfcdeclaration_t;
  
  private:
    char step_number;
    char action_number;
    char transition_number;
    
    sfcdeclaration_t wanted_sfcdeclaration;
    
  public:
    generate_c_sfcdecl_c(stage4out_c *s4o_ptr, sfcdeclaration_t sfcdeclaration)
    : generate_c_typedecl_c(s4o_ptr) {
      wanted_sfcdeclaration = sfcdeclaration;
    }
    ~generate_c_sfcdecl_c(void) {}
    
    void print(symbol_c *symbol, const char *variable_prefix = NULL) {
      this->set_variable_prefix(variable_prefix);
      
      symbol->accept(*this);
    }
    
/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/
    
    void *visit(sequential_function_chart_c *symbol) {
      step_number = 0;
      action_number = 0;
      transition_number = 0;
      switch (wanted_sfcdeclaration) {
        case sfcdecl_sd:
          for(int i = 0; i < symbol->n; i++)
            symbol->elements[i]->accept(*this);
          
          /* steps table declaration */
          s4o.print(s4o.indent_spaces + "STEP __step_list[");
          s4o.print_integer(step_number);
          s4o.print("];\n");
          s4o.print(s4o.indent_spaces + "UINT __nb_steps;\n");
          
          /* actions table declaration */
          s4o.print(s4o.indent_spaces + "ACTION __action_list[");
          s4o.print_integer(action_number);
          s4o.print("];\n");
          s4o.print(s4o.indent_spaces + "UINT __nb_actions;\n");
          
          /* transitions table declaration */
          s4o.print(s4o.indent_spaces + "BOOL __transition_list[");
          s4o.print_integer(transition_number);
          s4o.print("];\n");
          
          /* transitions debug table declaration */
          s4o.print(s4o.indent_spaces + "BOOL __debug_transition_list[");
          s4o.print_integer(transition_number);
          s4o.print("];\n");
          
          /* last_ticktime declaration */
          s4o.print(s4o.indent_spaces + "TIME __lasttick_time;\n");
          break;
        case sfcinit_sd:
          s4o.print(s4o.indent_spaces);
          s4o.print("UINT i;\n");
          
          /* steps table count */
          wanted_sfcdeclaration = stepcount_sd;
          for(int i = 0; i < symbol->n; i++)
            symbol->elements[i]->accept(*this);
          s4o.print(s4o.indent_spaces);
          print_variable_prefix();
          s4o.print("__nb_steps = ");
          s4o.print_integer(step_number);
          s4o.print(";\n");
          step_number = 0;
          wanted_sfcdeclaration = sfcinit_sd;
          
          /* steps table initialisation */
          s4o.print(s4o.indent_spaces + "STEP temp_step = {0, 0, 0};\n");
          s4o.print(s4o.indent_spaces + "for(i = 0; i < ");
          print_variable_prefix();
          s4o.print("__nb_steps; i++) {\n");
          s4o.indent_right();
          s4o.print(s4o.indent_spaces);
          print_variable_prefix();
          s4o.print("__step_list[i] = temp_step;\n");
          s4o.indent_left();
          s4o.print(s4o.indent_spaces + "}\n");
          for(int i = 0; i < symbol->n; i++)
            symbol->elements[i]->accept(*this);
          
          /* steps table count */
          wanted_sfcdeclaration = actioncount_sd;
          for(int i = 0; i < symbol->n; i++)
            symbol->elements[i]->accept(*this);
          s4o.print(s4o.indent_spaces);
          print_variable_prefix();
          s4o.print("__nb_actions = ");
          s4o.print_integer(action_number);
          s4o.print(";\n");
          action_number = 0;
          wanted_sfcdeclaration = sfcinit_sd;
          
          /* actions table initialisation */
          s4o.print(s4o.indent_spaces + "ACTION temp_action = {0, 0, 0, 0, 0, 0};\n");
          s4o.print(s4o.indent_spaces + "for(i = 0; i < ");
          print_variable_prefix();
          s4o.print("__nb_actions; i++) {\n");
          s4o.indent_right();
          s4o.print(s4o.indent_spaces);
          print_variable_prefix();
          s4o.print("__action_list[i] = temp_action;\n");
          s4o.indent_left();
          s4o.print(s4o.indent_spaces + "}\n");
          
          /* last_ticktime initialisation */
          print_variable_prefix();
          s4o.print("__lasttick_time = __CURRENT_TIME;\n");
          break;
        case stepdef_sd:
          s4o.print("// Steps definitions\n");
          for(int i = 0; i < symbol->n; i++)
            symbol->elements[i]->accept(*this);
          s4o.print("\n");
          break;
        case actiondef_sd:
          s4o.print("// Actions definitions\n");
          for(int i = 0; i < symbol->n; i++)
            symbol->elements[i]->accept(*this);
          s4o.print("\n");
          break;
        case stepundef_sd:
          s4o.print("// Steps undefinitions\n");
          for(int i = 0; i < symbol->n; i++)
            symbol->elements[i]->accept(*this);
          s4o.print("\n");
          break;
        case actionundef_sd:
          s4o.print("// Actions undefinitions\n");
          for(int i = 0; i < symbol->n; i++)
            symbol->elements[i]->accept(*this);
          s4o.print("\n");
          break;
        default:
          break;
      }
      return NULL;
    }
    
    void *visit(initial_step_c *symbol) {
      switch (wanted_sfcdeclaration) {
        case stepcount_sd:
        case sfcdecl_sd:
          step_number++;
          break;
        case sfcinit_sd:
          s4o.print(s4o.indent_spaces);
          print_variable_prefix();
          s4o.print("__step_list[");
          s4o.print_integer(step_number);
          s4o.print("].state = 1;\n");
          step_number++;
          break;
        case stepdef_sd:
          s4o.print("#define ");
          s4o.print(SFC_STEP_ACTION_PREFIX);
          symbol->step_name->accept(*this);
          s4o.print(" ");
          s4o.print_integer(step_number);
          s4o.print("\n");
          step_number++;
          break;
        case stepundef_sd:
          s4o.print("#undef ");
          s4o.print(SFC_STEP_ACTION_PREFIX);
          symbol->step_name->accept(*this);
          s4o.print("\n");
          break;
        default:
          break;
      }
      return NULL;
    }
    
    void *visit(step_c *symbol) {
      switch (wanted_sfcdeclaration) {
        case stepcount_sd:
        case sfcdecl_sd:
        case sfcinit_sd:
          step_number++;
          break;
        case stepdef_sd:
          s4o.print("#define ");
          s4o.print(SFC_STEP_ACTION_PREFIX);
          symbol->step_name->accept(*this);
          s4o.print(" ");
          s4o.print_integer(step_number);
          s4o.print("\n");
          step_number++;
          break;
        case stepundef_sd:
          s4o.print("#undef ");
          s4o.print(SFC_STEP_ACTION_PREFIX);
          symbol->step_name->accept(*this);
          s4o.print("\n");
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(transition_c *symbol) {
      switch (wanted_sfcdeclaration) {
        case sfcdecl_sd:
          transition_number++;
          break;
        default:
          break;
      }
      return NULL;
    }

    void *visit(action_c *symbol) {
      switch (wanted_sfcdeclaration) {
        case actiondef_sd:
          s4o.print("#define ");
          s4o.print(SFC_STEP_ACTION_PREFIX);
          symbol->action_name->accept(*this);
          s4o.print(" ");
          s4o.print_integer(action_number);
          s4o.print("\n");
          action_number++;
          break;
        case actionundef_sd:
          s4o.print("#undef ");
          s4o.print(SFC_STEP_ACTION_PREFIX);
          symbol->action_name->accept(*this);
          s4o.print("\n");
          break;
        case actioncount_sd:
        case sfcdecl_sd:
          action_number++;
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

