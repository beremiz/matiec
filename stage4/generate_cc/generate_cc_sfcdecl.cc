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

class generate_cc_sfc_stepdecl_c: public generate_cc_base_c {
  
  private:
    char step_number;
    
  public:
    generate_cc_sfc_stepdecl_c(stage4out_c *s4o_ptr): generate_cc_base_c(s4o_ptr) {}
    ~generate_cc_sfc_stepdecl_c(void) {}
    
    void reset_step_number(void) {step_number = 0;}
    char get_step_number(void) {return step_number;}
    void increment_step_number(void) {step_number++;}
    void print_step_number(void) {
      char str[10];
      sprintf(str, "%d", step_number);
      s4o.print(str);
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/
    
    void *visit(initial_step_c *symbol) {
      s4o.print("#define ");
      symbol->step_name->accept(*this);
      s4o.print(" ");
      print_step_number();
      s4o.print("\n");
      increment_step_number();
      return NULL;
    }
    
    void *visit(step_c *symbol) {
      s4o.print("#define ");
      symbol->step_name->accept(*this);
      s4o.print(" ");
      print_step_number();
      s4o.print("\n");
      increment_step_number();
      return NULL;
    }

    void *visit(transition_c *symbol) {return NULL;}

    void *visit(action_c *symbol) {return NULL;}

}; /* generate_cc_sfc_stepdecl_c */




/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_cc_sfc_actiondecl_c: public generate_cc_base_c {
  
  private:
    char action_number;
    
  public:
    generate_cc_sfc_actiondecl_c(stage4out_c *s4o_ptr): generate_cc_base_c(s4o_ptr) {}
    ~generate_cc_sfc_actiondecl_c(void) {}
    
    void reset_action_number(void) {action_number = 0;}
    char get_action_number(void) {return action_number;}
    void increment_action_number(void) {action_number++;}
    void print_action_number(void) {
      char str[10];
      sprintf(str, "%d", action_number);
      s4o.print(str);
    }

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/
    
    void *visit(initial_step_c *symbol) {return NULL;}
    
    void *visit(step_c *symbol) {return NULL;}

    void *visit(transition_c *symbol) {return NULL;}

    void *visit(action_c *symbol) {
      s4o.print("#define ");
      symbol->action_name->accept(*this);
      s4o.print(" ");
      print_action_number();
      s4o.print("\n");
      increment_action_number();
      return NULL;
    }

}; /* generate_cc_sfc_actiondecl_c */



/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

class generate_cc_sfcdecl_c: public iterator_visitor_c {
  
  protected:
    stage4out_c &s4o;
  
  private:
    generate_cc_sfc_stepdecl_c *generate_cc_sfc_stepdecl;
    generate_cc_sfc_actiondecl_c *generate_cc_sfc_actiondecl;

  public:
    generate_cc_sfcdecl_c(stage4out_c *s4o_ptr) : s4o(*s4o_ptr) {
      generate_cc_sfc_stepdecl = new generate_cc_sfc_stepdecl_c(s4o_ptr);
      generate_cc_sfc_actiondecl = new generate_cc_sfc_actiondecl_c(s4o_ptr);
    }

    virtual ~generate_cc_sfcdecl_c(void) {
      delete generate_cc_sfc_stepdecl;
      delete generate_cc_sfc_actiondecl;
    }

  public:

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/

    /*| sequential_function_chart sfc_network*/
    void *visit(sfc_network_c *symbol) {
      char i;
      
      /* generate step number definitions */
      s4o.print(s4o.indent_spaces + "// Steps declaration\n");
      generate_cc_sfc_stepdecl->reset_step_number();
      symbol->accept(*generate_cc_sfc_stepdecl);
      s4o.print("\n" + s4o.indent_spaces + "nb_steps = ");
      generate_cc_sfc_stepdecl->print_step_number();
      s4o.print(";\n" + s4o.indent_spaces + "STEP step_list[");
      generate_cc_sfc_stepdecl->print_step_number();
      s4o.print("] = {\n");
      s4o.indent_right();
      for (i = 0; i < generate_cc_sfc_stepdecl->get_step_number(); i++) {
        if (i == 0) {
          s4o.print(s4o.indent_spaces + "{1, 0, 0}");
        }
        else {
          s4o.print(",\n" + s4o.indent_spaces + "{0, 0, 0}");
        }
      }
      s4o.indent_left();  
      s4o.print("\n" + s4o.indent_spaces + "};\n\n");
      
      /* generate action number definitions */
      s4o.print(s4o.indent_spaces + "// Actions declaration\n");
      generate_cc_sfc_actiondecl->reset_action_number();
      symbol->accept(*generate_cc_sfc_actiondecl);
      s4o.print("\n" + s4o.indent_spaces + "nb_actions = ");
      generate_cc_sfc_actiondecl->print_action_number();
      s4o.print(";\n" + s4o.indent_spaces + "STEP step_list[");
      generate_cc_sfc_actiondecl->print_action_number();
      s4o.print("] = {\n");
      s4o.indent_right();
      for (i = 0; i < generate_cc_sfc_actiondecl->get_action_number(); i++) {
        if (i == 0) {
          s4o.print(s4o.indent_spaces + "{0, 0, 0, 0, 0, 0}");
        }
        else {
          s4o.print(",\n" + s4o.indent_spaces + "{0, 0, 0, 0, 0, 0}");
        }
      }
      s4o.indent_left();  
      s4o.print("\n" + s4o.indent_spaces + "};\n\n");
      
      return NULL;
    }

/***********************************/
/* B 2.1 Instructions and Operands */
/***********************************/
/*| instruction_list il_instruction */
    void *visit(instruction_list_c *symbol) {return NULL;}

/***************************************/
/* B.3 - Language ST (Structured Text) */
/***************************************/
/********************/
/* B 3.2 Statements */
/********************/
void *visit(statement_list_c *symbol) {return NULL;}

/* Remainder implemented in generate_cc_sfcdecl_c... */
};
