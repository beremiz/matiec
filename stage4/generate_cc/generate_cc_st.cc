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
 * Conversion of st statements (i.e. ST code).
 *
 * This is part of the 4th stage that generates
 * a c++ source program equivalent to the IL and ST
 * code.
 */


/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


class generate_cc_st_c: public generate_cc_typedecl_c {

  private:
    /* When calling a function block, we must first find it's type,
     * by searching through the declarations of the variables currently
     * in scope.
     * This class does just that...
     * A new class is instantiated whenever we begin generating the code
     * for a function block type declaration, or a program declaration.
     * This object instance will then later be called while the
     * function block's or the program's body is being handled.
     *
     * Note that functions cannot contain calls to function blocks,
     * so we do not create an object instance when handling
     * a function declaration.
     */
    search_fb_instance_decl_c *search_fb_instance_decl;

    /* When compiling st code, it becomes necessary to determine the
     * data type of st expressions. To do this, we must first find the
     * st operand's declaration, within the scope of the function block
     * or function currently being processed.
     * The following object does just that...
     * This object instance will then later be called while the
     * remaining st code is being handled.
     */
    search_expression_type_c *search_expression_type;

    search_varfb_instance_type_c *search_varfb_instance_type;

  public:
    generate_cc_st_c(stage4out_c *s4o_ptr, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_cc_typedecl_c(s4o_ptr) {
      search_fb_instance_decl = new search_fb_instance_decl_c(scope);
      search_expression_type = new search_expression_type_c(scope);
      search_varfb_instance_type = new search_varfb_instance_type_c(scope);
      this->set_variable_prefix(variable_prefix);
    }

    virtual ~generate_cc_st_c(void) {
      delete search_fb_instance_decl;
      delete search_expression_type;
      delete search_varfb_instance_type;
    }


  private:
    /* Some function calls in the body of functions or function blocks
     * may leave some parameters to their default values, and
     * ignore some output parameters of the function being called.
     * Our conversion of ST functions to C++ does not contemplate that,
     * i.e. each called function must get all it's input and output
     * parameters set correctly.
     * For input parameters we merely need to call the function with
     * the apropriate default value, but for output parameters
     * we must create temporary variables to hold the output value.
     *
     * We declare all the temporary output variables at the begining of
     * the body of each function or function block, and use them as
     * in function calls later on as they become necessary...
     * Note that we cannot create these variables just before a function
     * call, as the function call itself may be integrated within an
     * expression, or another function call!
     *
     * The variables are declared in the exact same order in which they
     * will be used later on during the function calls, which allows us
     * to simply re-create the name that was used for the temporary variable
     * instead of keeping it in some list.
     * The names are recreated by the temp_var_name_factory, after reset()
     * has been called!
     *
     * This function will genertae code similar to...
     *
     *     INT __TMP_0 = 23;
     *     REAL __TMP_1 = 45.5;
     *     ...
     */
    temp_var_name_c temp_var_name_factory;

  public:
    void generate(statement_list_c *stl) {
      generate_cc_tempvardecl_c generate_cc_tempvardecl(&s4o);
      generate_cc_tempvardecl.generate(stl, &temp_var_name_factory);
      stl->accept(*this);
    }

  private:

/*********************/
/* B 1.4 - Variables */
/*********************/
void *visit(symbolic_variable_c *symbol) {
  unsigned int vartype = search_varfb_instance_type->get_vartype(symbol);
  if (vartype == search_var_instance_decl_c::external_vt || vartype == search_var_instance_decl_c::located_vt) {
    s4o.print("*(");
    generate_cc_base_c::visit(symbol);
    s4o.print(")");
  }
  else {
    generate_cc_base_c::visit(symbol);
  }
  return NULL;
}

/***************************************/
/* B.3 - Language ST (Structured Text) */
/***************************************/
/***********************/
/* B 3.1 - Expressions */
/***********************/
void *visit(or_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_bool_type(left_type))
    return print_binary_expression(symbol->l_exp, symbol->r_exp, " || ");
  if (search_expression_type->is_binary_type(left_type))
    return print_binary_expression(symbol->l_exp, symbol->r_exp, " | ");
  ERROR;
  return NULL;
}

void *visit(xor_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_bool_type(left_type)) {
    s4o.print("(");
    symbol->l_exp->accept(*this);
    s4o.print(" && !");
    symbol->r_exp->accept(*this);
    s4o.print(") || (!");
    symbol->l_exp->accept(*this);
    s4o.print(" && ");
    symbol->r_exp->accept(*this);
    s4o.print(")");
  }
  if (search_expression_type->is_binary_type(left_type))
    return print_binary_expression(symbol->l_exp, symbol->r_exp, " ^ ");
  ERROR;
  return NULL;
}

void *visit(and_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_bool_type(left_type))
    return print_binary_expression(symbol->l_exp, symbol->r_exp, " && ");
  if (search_expression_type->is_binary_type(left_type))
    return print_binary_expression(symbol->l_exp, symbol->r_exp, " & ");
  ERROR;
  return NULL;
}

void *visit(equ_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_time_type(left_type))
    return print_compare_function("__compare_timespec", "==", symbol->l_exp, symbol->r_exp);
  return print_binary_expression(symbol->l_exp, symbol->r_exp, " == ");
}

void *visit(notequ_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_time_type(left_type))
    return print_compare_function("__compare_timespec", "!=", symbol->l_exp, symbol->r_exp);
  return print_binary_expression(symbol->l_exp, symbol->r_exp, " != ");
}

void *visit(lt_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_time_type(left_type))
    return print_compare_function("__compare_timespec", "<", symbol->l_exp, symbol->r_exp);
  return print_binary_expression(symbol->l_exp, symbol->r_exp, " < ");
}

void *visit(gt_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_time_type(left_type))
    return print_compare_function("__compare_timespec", ">", symbol->l_exp, symbol->r_exp);
  return print_binary_expression(symbol->l_exp, symbol->r_exp, " > ");
}

void *visit(le_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_time_type(left_type))
    return print_compare_function("__compare_timespec", "<=", symbol->l_exp, symbol->r_exp);
  return print_binary_expression(symbol->l_exp, symbol->r_exp, " <= ");
}

void *visit(ge_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_time_type(left_type))
    return print_compare_function("__compare_timespec", ">=", symbol->l_exp, symbol->r_exp);
  return print_binary_expression(symbol->l_exp, symbol->r_exp, " >= ");
}

void *visit(add_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
	symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
	if ((typeid(*left_type) == typeid(time_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) ||
      (typeid(*left_type) == typeid(tod_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) ||
      (typeid(*left_type) == typeid(dt_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)))
    return print_binary_function("__add_timespec", symbol->l_exp, symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_integer_type(left_type) || search_expression_type->is_real_type(left_type))
    return print_binary_expression(symbol->l_exp, symbol->r_exp, " + ");
  ERROR;
  return NULL;
}

void *visit(sub_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if ((typeid(*left_type) == typeid(time_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) ||
      (typeid(*left_type) == typeid(date_type_name_c) && typeid(*right_type) == typeid(date_type_name_c)) ||
      (typeid(*left_type) == typeid(tod_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) ||
      (typeid(*left_type) == typeid(tod_type_name_c) && typeid(*right_type) == typeid(tod_type_name_c)) ||
      (typeid(*left_type) == typeid(dt_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) ||
      (typeid(*left_type) == typeid(dt_type_name_c) && typeid(*right_type) == typeid(dt_type_name_c)))
    return print_binary_function("__sub_timespec", symbol->l_exp, symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_integer_type(left_type) || search_expression_type->is_real_type(left_type))
    return print_binary_expression(symbol->l_exp, symbol->r_exp, " - ");
  ERROR;
  return NULL;
}

void *visit(mul_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if ((typeid(*left_type) == typeid(time_type_name_c) && search_expression_type->is_integer_type(right_type)) ||
      (typeid(*left_type) == typeid(time_type_name_c) && search_expression_type->is_real_type(right_type)))
    return print_binary_function("__mul_timespec", symbol->l_exp, symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_integer_type(left_type) || search_expression_type->is_real_type(left_type))
    return print_binary_expression(symbol->l_exp, symbol->r_exp, " * ");
  ERROR;
  return NULL;
}

void *visit(div_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_integer_type(left_type) || search_expression_type->is_real_type(left_type))
    return print_binary_expression(symbol->l_exp, symbol->r_exp, " / ");
  ERROR;
  return NULL;
}

void *visit(mod_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_integer_type(left_type) || search_expression_type->is_real_type(left_type)) {
    s4o.print("((");
    symbol->r_exp->accept(*this);
    s4o.print(" == 0)?0:");
    print_binary_expression(symbol->l_exp, symbol->r_exp, " % ");
    s4o.print(")");
    return NULL;
  }
  ERROR;
  return NULL;
}

/* TODO: power expression... */
void *visit(power_expression_c *symbol) {ERROR; return print_binary_expression(symbol->l_exp, symbol->r_exp, " ** ");}
void *visit(neg_expression_c *symbol) {return print_unary_expression(symbol->exp, " -");}
void *visit(not_expression_c *symbol) {return print_unary_expression(symbol->exp, "!");}

void *visit(function_invocation_c *symbol) {
  function_declaration_c *f_decl = function_symtable.find_value(symbol->function_name);
  
  if (f_decl == function_symtable.end_value()) {
    /* The function called is not in the symtable, so we test if it is a
     * standard function defined in standard */
    
    function_type_t current_function_type = get_function_type((identifier_c *)symbol->function_name);
    if (current_function_type == function_none) ERROR;
    
    symbol_c *function_return_type = search_expression_type->get_type(symbol);
    
    function_call_param_iterator_c function_call_param_iterator(symbol);
    
    int nb_param = ((list_c *)symbol->parameter_assignment_list)->n;
    for(int current_param = 0; current_param < nb_param; current_param++) {
      symbol_c *param_name = NULL;
      switch (current_function_type) {
        case function_add:
        case function_and:
        case function_or:
          param_name = generate_param_name("IN%d", current_param + 1);
          break;
        case function_sub:
          if (current_param < 2)
            param_name = generate_param_name("IN%d", current_param + 1);
          else
            ERROR;
          break;
        default: ERROR;
      }
      
      /* Get the value from a foo(<param_name> = <param_value>) style call */
      symbol_c *param_value = function_call_param_iterator.search(param_name);
      delete param_name;
      
      /* Get the value from a foo(<param_value>) style call */
      if (param_value == NULL)
        param_value = function_call_param_iterator.next();
      
      if (param_value == NULL) ERROR;
      
      switch (current_function_type) {
        case function_add:
          if (search_expression_type->is_time_type(function_return_type)) {
            if (current_param == 0) {
              s4o.print("__add_timespec(");
              param_value->accept(*this);
            }
            else if (current_param == 1) {
              s4o.print(", ");
              param_value->accept(*this);
              s4o.print(")");
            }
            else ERROR;
          }
          else {
            if (current_param == 0)
              s4o.print("(");
            else
              s4o.print(" + ");
            param_value->accept(*this);
            if (current_param == nb_param - 1)
              s4o.print(")");
          }
          break;
        case function_sub:
          if (search_expression_type->is_time_type(function_return_type)) {
            if (current_param == 0) {
              s4o.print("__sub_timespec(");
              param_value->accept(*this);
            }
            else if (current_param == 1) {
              s4o.print(", ");
              param_value->accept(*this);
              s4o.print(")");
            }
            else ERROR;
          }
          else {
            if (current_param == 0) {
              s4o.print("(");
              param_value->accept(*this);
            }
            else if (current_param == 1) {
              s4o.print(" - ");
              param_value->accept(*this);
              s4o.print(")");
            }
            else ERROR;
          }
          break;
        case function_and:
          if (current_param == 0)
            s4o.print("(");
          else
            if (search_expression_type->is_bool_type(function_return_type))
              s4o.print(" && ");
            else
              s4o.print(" & ");
          param_value->accept(*this);
          if (current_param == nb_param - 1)
            s4o.print(")");
          break;
        case function_or:
          if (current_param == 0)
            s4o.print("(");
          else
            if (search_expression_type->is_bool_type(function_return_type))
              s4o.print(" || ");
            else
              s4o.print(" | ");
          param_value->accept(*this);
          if (current_param == nb_param - 1)
            s4o.print(")");
          break;
        default: ERROR;
      }
    } /* for(...) */
  }
  else {
    /* loop through each function parameter, find the value we should pass
     * to it, and then output the c equivalent...
     */
    function_param_iterator_c fp_iterator(f_decl);
  
    symbol->function_name->accept(*this);
    s4o.print("(");
  
    identifier_c *param_name;
    function_call_param_iterator_c function_call_param_iterator(symbol);
    for(int i = 1; (param_name = fp_iterator.next()) != NULL; i++) {
      if (i != 1)
        s4o.print(", ");
  
      function_param_iterator_c::param_direction_t param_direction = fp_iterator.param_direction();
  
      /* Get the value from a foo(<param_name> = <param_value>) style call */
      symbol_c *param_value = function_call_param_iterator.search(param_name);
  
      /* Get the value from a foo(<param_value>) style call */
      if (param_value == NULL)
        param_value = function_call_param_iterator.next();
  
      symbol_c *param_type = fp_iterator.param_type();
      if (param_type == NULL) ERROR;
  
      switch (param_direction) {
        case function_param_iterator_c::direction_in:
          if (param_value == NULL) {
            /* No value given for parameter, so we must use the default... */
            /* First check whether default value specified in function declaration...*/
            param_value = fp_iterator.default_value();
          }
          if (param_value == NULL) {
            /* If not, get the default value of this variable's type */
            param_value = (symbol_c *)param_type->accept(*type_initial_value_c::instance());
          }
          if (param_value == NULL) ERROR;
          param_value->accept(*this);
          break;
        case function_param_iterator_c::direction_out:
        case function_param_iterator_c::direction_inout:
          if (param_value == NULL) {
            /* no parameter value given, so we pass a previously declared temporary variable. */
            std::string *temp_var_name = temp_var_name_factory.new_name();
            s4o.print(*temp_var_name);
            delete temp_var_name;
          } else {
            param_value->accept(*this);
          }
          break;
        case function_param_iterator_c::direction_extref:
          /* TODO! */
          ERROR;
          break;
      } /* switch */
    } /* for(...) */
    // symbol->parameter_assignment->accept(*this);
    s4o.print(")");
  }

  return NULL;
}

/********************/
/* B 3.2 Statements */
/********************/
void *visit(statement_list_c *symbol) {
  return print_list(symbol, s4o.indent_spaces, ";\n" + s4o.indent_spaces, ";\n");
}

/*********************************/
/* B 3.2.1 Assignment Statements */
/*********************************/
void *visit(assignment_statement_c *symbol) {
  symbol->l_exp->accept(*this);
  s4o.print(" = ");
  symbol->r_exp->accept(*this);
  return NULL;
}

/*****************************************/
/* B 3.2.2 Subprogram Control Statements */
/*****************************************/

/* fb_name '(' [param_assignment_list] ')' */
/* param_assignment_list -> may be NULL ! */
//SYM_REF2(fb_invocation_c, fb_name, param_assignment_list)
void *visit(fb_invocation_c *symbol) {
  TRACE("fb_invocation_c");
  /* first figure out what is the name of the function block type of the function block being called... */
  symbol_c *function_block_type_name = this->search_fb_instance_decl->get_type_name(symbol->fb_name);
    /* should never occur. The function block instance MUST have been declared... */
  if (function_block_type_name == NULL) ERROR;

  /* Now find the declaration of the function block type being called... */
  function_block_declaration_c *fb_decl = function_block_type_symtable.find_value(function_block_type_name);
    /* should never occur. The function block type being called MUST be in the symtable... */
  if (fb_decl == function_block_type_symtable.end_value()) ERROR;

  /* loop through each function block parameter, find the value we should pass
   * to it, and then output the c equivalent...
   */
  function_param_iterator_c fp_iterator(fb_decl);
  identifier_c *param_name;
  function_call_param_iterator_c function_call_param_iterator(symbol);
  for(int i = 1; (param_name = fp_iterator.next()) != NULL; i++) {
    function_param_iterator_c::param_direction_t param_direction = fp_iterator.param_direction();

    /* Get the value from a foo(<param_name> = <param_value>) style call */
    symbol_c *param_value = function_call_param_iterator.search(param_name);

    /* Get the value from a foo(<param_value>) style call */
    if (param_value == NULL)
      param_value = function_call_param_iterator.next();

    /* now output the value assignment */
    if (param_value != NULL)
      if ((param_direction == function_param_iterator_c::direction_in) ||
          (param_direction == function_param_iterator_c::direction_inout)) {
        print_variable_prefix();
        symbol->fb_name->accept(*this);
        s4o.print(".");
        param_name->accept(*this);
        s4o.print(" = ");
        param_value->accept(*this);
        s4o.print(";\n" + s4o.indent_spaces);
      }
  } /* for(...) */

  /* now call the function... */
  function_block_type_name->accept(*this);
  s4o.print(FB_FUNCTION_SUFFIX);
  s4o.print("(");
  print_variable_prefix();
  symbol->fb_name->accept(*this);
  s4o.print(")");

  /* loop through each function parameter, find the variable to which
   * we should atribute the value of all output or inoutput parameters.
   */
  fp_iterator.reset();
  function_call_param_iterator.reset();
  for(int i = 1; (param_name = fp_iterator.next()) != NULL; i++) {
    function_param_iterator_c::param_direction_t param_direction = fp_iterator.param_direction();

    /* Get the value from a foo(<param_name> = <param_value>) style call */
    symbol_c *param_value = function_call_param_iterator.search(param_name);

    /* Get the value from a foo(<param_value>) style call */
    if (param_value == NULL)
      param_value = function_call_param_iterator.next();

    /* now output the value assignment */
    if (param_value != NULL)
      if ((param_direction == function_param_iterator_c::direction_out) ||
          (param_direction == function_param_iterator_c::direction_inout)) {
        s4o.print(";\n"+ s4o.indent_spaces);
        param_value->accept(*this);
        s4o.print(" = ");
        print_variable_prefix();
        symbol->fb_name->accept(*this);
        s4o.print(".");
        param_name->accept(*this);
      }
  } /* for(...) */

  return NULL;
}




/* helper symbol for fb_invocation */
/* param_assignment_list ',' param_assignment */
void *visit(param_assignment_list_c *symbol) {
  TRACE("param_assignment_list_c");
  /* this should never be called... */
  ERROR;
  return NULL;
//  return print_list(symbol, "", ", ");
}


void *visit(input_variable_param_assignment_c *symbol) {
  TRACE("input_variable_param_assignment_c");
  /* this should never be called... */
  ERROR;
  return NULL;
/*
  symbol->variable_name->accept(*this);
  s4o.print(" = ");
  symbol->expression->accept(*this);
  return NULL;
*/
}

void *visit(output_variable_param_assignment_c *symbol) {
  TRACE("output_variable_param_assignment_c");
  /* this should never be called... */
  ERROR;
  return NULL;
/*
  s4o.print(s4o.indent_spaces);
  if (symbol->not_param != NULL)
    symbol->not_param->accept(*this);
  symbol->variable_name->accept(*this);
  s4o.print(" => ");
  symbol->variable->accept(*this);
  return NULL;
*/
}

// TODO: the NOT symbol in function (block) calls...
void *visit(not_paramassign_c *symbol) {
  TRACE("not_paramassign_c");
  /* this should never be called... */
  ERROR;
  return NULL;
/*
  s4o.print("NOT ");
  return NULL;
*/
}


/********************************/
/* B 3.2.3 Selection Statements */
/********************************/
void *visit(if_statement_c *symbol) {
  s4o.print("if (");
  symbol->expression->accept(*this);
  s4o.print(") {\n");
  s4o.indent_right();
  symbol->statement_list->accept(*this);
  s4o.indent_left();
  symbol->elseif_statement_list->accept(*this);

  if (symbol->else_statement_list != NULL) {
    s4o.print(s4o.indent_spaces); s4o.print("} else {\n");
    s4o.indent_right();
    symbol->else_statement_list->accept(*this);
    s4o.indent_left();
  }
  s4o.print(s4o.indent_spaces); s4o.print("}");
  return NULL;
}

/* helper symbol for if_statement */
void *visit(elseif_statement_list_c *symbol) {return print_list(symbol);}

/* helper symbol for elseif_statement_list */
void *visit(elseif_statement_c *symbol) {
  s4o.print(s4o.indent_spaces); s4o.print("} else if (");
  symbol->expression->accept(*this);
  s4o.print(") {\n");
  s4o.indent_right();
  symbol->statement_list->accept(*this);
  s4o.indent_left();
  return NULL;
}

void *visit(case_statement_c *symbol) {
  s4o.print("switch(");
  symbol->expression->accept(*this);
  s4o.print(") {\n");
  s4o.indent_right();
  symbol->case_element_list->accept(*this);
  if (symbol->statement_list != NULL) {
    s4o.print(s4o.indent_spaces + "default:\n");
    s4o.indent_right();
    symbol->statement_list->accept(*this);
    s4o.print(s4o.indent_spaces + "break;\n");
    s4o.indent_left();
  }
  s4o.indent_left();
  s4o.print(s4o.indent_spaces + "}");
  return NULL;
}

/* helper symbol for case_statement */
void *visit(case_element_list_c *symbol) {return print_list(symbol);}

void *visit(case_element_c *symbol) {
  s4o.print(s4o.indent_spaces + "case ");
  symbol->case_list->accept(*this);
  s4o.print(" :\n");
  s4o.indent_right();
  symbol->statement_list->accept(*this);
  s4o.print(s4o.indent_spaces + "break;\n");
  s4o.indent_left();
  return NULL;
}

void *visit(case_list_c *symbol) {return print_list(symbol, "", ", ");}

/********************************/
/* B 3.2.4 Iteration Statements */
/********************************/
void *visit(for_statement_c *symbol) {
  s4o.print("for(");
  symbol->control_variable->accept(*this);
  s4o.print(" = ");
  symbol->beg_expression->accept(*this);
  s4o.print("; ");
  symbol->control_variable->accept(*this);
  s4o.print(" != ");
  symbol->end_expression->accept(*this);
  s4o.print("; ");
  symbol->control_variable->accept(*this);
  if (symbol->by_expression != NULL) {
    s4o.print(" += ");
    symbol->by_expression->accept(*this);
  } else {
    s4o.print("++");
  }
  s4o.print(") {\n");
  s4o.indent_right();
  symbol->statement_list->accept(*this);
  s4o.indent_left();
  s4o.print(s4o.indent_spaces); s4o.print("}");
  return NULL;
}
void *visit(while_statement_c *symbol) {
  s4o.print("while (");
  symbol->expression->accept(*this);
  s4o.print(") {\n");
  s4o.indent_right();
  symbol->statement_list->accept(*this);
  s4o.indent_left();
  s4o.print(s4o.indent_spaces); s4o.print("}");
  return NULL;
}
void *visit(repeat_statement_c *symbol) {
  s4o.print("do {\n");
  s4o.indent_right();
  symbol->statement_list->accept(*this);
  s4o.indent_left();
  s4o.print(s4o.indent_spaces); s4o.print("} while(");
  symbol->expression->accept(*this);
  s4o.print(")");
  return NULL;
}
void *visit(exit_statement_c *symbol) {
  s4o.print("exit(0)");
  return NULL;
}



}; /* generate_cc_st_c */









