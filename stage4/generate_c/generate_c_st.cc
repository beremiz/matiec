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
 * This code is made available on the understanding that it will not be
 * used in safety-critical situations without a full and competent review.
 *
 * Based on the
 * FINAL DRAFT - IEC 61131-3, 2nd Ed. (2001-12-10)
 *
 */


/*
 * Conversion of st statements (i.e. ST code).
 *
 * This is part of the 4th stage that generates
 * a C source program equivalent to the IL and ST, or SFC
 * code.
 */


/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


class generate_c_st_c: public generate_c_typedecl_c {

  public:
    typedef enum {
      expression_vg,
      assignment_vg,
      complextype_base_vg,
      complextype_suffix_vg,
      fparam_output_vg
    } variablegeneration_t;

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

    search_base_type_c search_base_type;

    symbol_c* current_array_type;
    symbol_c* current_param_type;

    int fcall_number;
    symbol_c *fbname;

    variablegeneration_t wanted_variablegeneration;

  public:
    generate_c_st_c(stage4out_c *s4o_ptr, symbol_c *name, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_c_typedecl_c(s4o_ptr) {
      search_fb_instance_decl = new search_fb_instance_decl_c(scope);
      search_expression_type = new search_expression_type_c(scope);
      search_varfb_instance_type = new search_varfb_instance_type_c(scope);
      this->set_variable_prefix(variable_prefix);
      current_array_type = NULL;
      current_param_type = NULL;
      fcall_number = 0;
      fbname = name;
      wanted_variablegeneration = expression_vg;
    }

    virtual ~generate_c_st_c(void) {
      delete search_fb_instance_decl;
      delete search_expression_type;
      delete search_varfb_instance_type;
    }


  public:
    void generate(statement_list_c *stl) {
      stl->accept(*this);
    }

  private:

void *print_getter(symbol_c *symbol) {
  unsigned int vartype = search_varfb_instance_type->get_vartype(symbol);
  if (wanted_variablegeneration == fparam_output_vg) {
  	if (vartype == search_var_instance_decl_c::external_vt)
      s4o.print(GET_EXTERNAL_BY_REF);
    else if (vartype == search_var_instance_decl_c::located_vt)
      s4o.print(GET_LOCATED_BY_REF);
    else
      s4o.print(GET_VAR_BY_REF);
  }
  else {
	if (vartype == search_var_instance_decl_c::external_vt)
	  s4o.print(GET_EXTERNAL);
	else if (vartype == search_var_instance_decl_c::located_vt)
	  s4o.print(GET_LOCATED);
	else
	  s4o.print(GET_VAR);
  }
  s4o.print("(");

  variablegeneration_t old_wanted_variablegeneration = wanted_variablegeneration;
  wanted_variablegeneration = complextype_base_vg;
  symbol->accept(*this);
  if (search_varfb_instance_type->type_is_complex())
    s4o.print(",");
  wanted_variablegeneration = complextype_suffix_vg;
  symbol->accept(*this);
  s4o.print(")");
  wanted_variablegeneration = old_wanted_variablegeneration;
  return NULL;
}

void *print_setter(symbol_c* symbol,
		symbol_c* type,
		symbol_c* value,
		symbol_c* fb_symbol = NULL,
		symbol_c* fb_value = NULL) {
  unsigned int vartype = search_varfb_instance_type->get_vartype(symbol);
  if (vartype == search_var_instance_decl_c::external_vt) {
    symbolic_variable_c *variable = dynamic_cast<symbolic_variable_c *>(symbol);
    /* TODO Find a solution for forcing global complex variables */
    if (variable != NULL) {
      s4o.print(SET_EXTERNAL);
      s4o.print("(");
      variable->var_name->accept(*this);
      s4o.print(",");
    }
    else {
      s4o.print(SET_COMPLEX_EXTERNAL);
      s4o.print("(");
    }
  }
  else {
    if (vartype == search_var_instance_decl_c::located_vt)
      s4o.print(SET_LOCATED);
    else
      s4o.print(SET_VAR);
    s4o.print("(");
  }

  if (fb_symbol != NULL) {
    print_variable_prefix();
    fb_symbol->accept(*this);
    s4o.print(".");
  }
  else
    wanted_variablegeneration = complextype_base_vg;
  symbol->accept(*this);
  s4o.print(",");
  wanted_variablegeneration = expression_vg;
  print_check_function(type, value, fb_value);
  if (search_varfb_instance_type->type_is_complex()) {
    s4o.print(",");
    wanted_variablegeneration = complextype_suffix_vg;
    symbol->accept(*this);
  }
  s4o.print(")");
  wanted_variablegeneration = expression_vg;
  return NULL;
}

/*********************/
/* B 1.4 - Variables */
/*********************/
void *visit(symbolic_variable_c *symbol) {
  unsigned int vartype;
  if (wanted_variablegeneration == complextype_base_vg)
	generate_c_base_c::visit(symbol);
  else if (wanted_variablegeneration == complextype_suffix_vg)
	return NULL;
  else if (this->is_variable_prefix_null()) {
	vartype = search_varfb_instance_type->get_vartype(symbol);
	if (wanted_variablegeneration == fparam_output_vg) {
	  s4o.print("&(");
      generate_c_base_c::visit(symbol);
      s4o.print(")");
    }
    else {
      generate_c_base_c::visit(symbol);
    }
  }
  else
	print_getter(symbol);
  return NULL;
}

/********************************************/
/* B.1.4.1   Directly Represented Variables */
/********************************************/
// direct_variable: direct_variable_token   {$$ = new direct_variable_c($1);};
void *visit(direct_variable_c *symbol) {
  TRACE("direct_variable_c");
  /* Do not use print_token() as it will change everything into uppercase */
  if (strlen(symbol->value) == 0) ERROR;
  if (this->is_variable_prefix_null()) {
    if (wanted_variablegeneration != fparam_output_vg)
	  s4o.print("*(");
  }
  else {
    switch (wanted_variablegeneration) {
      case expression_vg:
  	    s4o.print(GET_LOCATED);
  	    s4o.print("(");
  	    break;
      case fparam_output_vg:
        s4o.print(GET_LOCATED_BY_REF);
        s4o.print("(");
        break;
      default:
        break;
    }
  }
  this->print_variable_prefix();
  s4o.printlocation(symbol->value + 1);
  if ((this->is_variable_prefix_null() && wanted_variablegeneration != fparam_output_vg) ||
	  wanted_variablegeneration != assignment_vg)
    s4o.print(")");
  return NULL;
}

/*************************************/
/* B.1.4.2   Multi-element Variables */
/*************************************/

// SYM_REF2(structured_variable_c, record_variable, field_selector)
void *visit(structured_variable_c *symbol) {
  TRACE("structured_variable_c");
  switch (wanted_variablegeneration) {
    case complextype_base_vg:
      symbol->record_variable->accept(*this);
      break;
    case complextype_suffix_vg:
      symbol->record_variable->accept(*this);
      s4o.print(".");
      symbol->field_selector->accept(*this);
      break;
    default:
      if (this->is_variable_prefix_null()) {
    	symbol->record_variable->accept(*this);
    	s4o.print(".");
    	symbol->field_selector->accept(*this);
      }
      else
    	print_getter(symbol);
      break;
  }
  return NULL;
}

/*  subscripted_variable '[' subscript_list ']' */
//SYM_REF2(array_variable_c, subscripted_variable, subscript_list)
void *visit(array_variable_c *symbol) {
  switch (wanted_variablegeneration) {
    case complextype_base_vg:
      symbol->subscripted_variable->accept(*this);
      break;
    case complextype_suffix_vg:
      symbol->subscripted_variable->accept(*this);

      current_array_type = search_varfb_instance_type->get_rawtype(symbol->subscripted_variable);
      if (current_array_type == NULL) ERROR;

      s4o.print(".table");
      symbol->subscript_list->accept(*this);

      current_array_type = NULL;
      break;
    default:
      if (this->is_variable_prefix_null()) {
    	symbol->subscripted_variable->accept(*this);

    	current_array_type = search_varfb_instance_type->get_rawtype(symbol->subscripted_variable);
    	if (current_array_type == NULL) ERROR;

    	s4o.print(".table");
        symbol->subscript_list->accept(*this);

        current_array_type = NULL;
      }
      else
    	print_getter(symbol);
      break;
  }
  return NULL;
}

/* subscript_list ',' subscript */
void *visit(subscript_list_c *symbol) {
  for (int i =  0; i < symbol->n; i++) {
    s4o.print("[__");
    current_array_type->accept(*this);
    s4o.print("_TRANSIDX");
    print_integer(i);
    s4o.print("(");
    symbol->elements[i]->accept(*this);
    s4o.print(")]");
  }
  return NULL;
}

/******************************************/
/* B 1.4.3 - Declaration & Initialisation */
/******************************************/

/* helper symbol for structure_initialization */
/* structure_element_initialization_list ',' structure_element_initialization */
void *visit(structure_element_initialization_list_c *symbol) {
  generate_c_structure_initialization_c *structure_initialization = new generate_c_structure_initialization_c(&s4o);
  structure_initialization->init_structure_default(this->current_param_type);
  structure_initialization->init_structure_values(symbol);
  delete structure_initialization;
  return NULL;
}

/* helper symbol for array_initialization */
/* array_initial_elements_list ',' array_initial_elements */
void *visit(array_initial_elements_list_c *symbol) {
  generate_c_array_initialization_c *array_initialization = new generate_c_array_initialization_c(&s4o);
  array_initialization->init_array_size(this->current_param_type);
  array_initialization->init_array_values(symbol);
  delete array_initialization;
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
    return NULL;
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
  if (search_expression_type->is_time_type(left_type) ||
      search_expression_type->is_string_type(left_type))
    return print_compare_function("__eq_", left_type, symbol->l_exp, symbol->r_exp);
  return print_binary_expression(symbol->l_exp, symbol->r_exp, " == ");
}

void *visit(notequ_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_time_type(left_type) ||
      search_expression_type->is_string_type(left_type))
    return print_compare_function("__ne_", left_type, symbol->l_exp, symbol->r_exp);
  return print_binary_expression(symbol->l_exp, symbol->r_exp, " != ");
}

void *visit(lt_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_time_type(left_type) ||
      search_expression_type->is_string_type(left_type))
    return print_compare_function("__lt_", left_type, symbol->l_exp, symbol->r_exp);
  if (!search_base_type.type_is_enumerated(left_type))
    return print_binary_expression(symbol->l_exp, symbol->r_exp, " < ");
  ERROR;
  return NULL;
}

void *visit(gt_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_time_type(left_type) ||
      search_expression_type->is_string_type(left_type))
    return print_compare_function("__gt_", left_type, symbol->l_exp, symbol->r_exp);
  if (!search_base_type.type_is_enumerated(left_type))
    return print_binary_expression(symbol->l_exp, symbol->r_exp, " > ");
  ERROR;
  return NULL;
}

void *visit(le_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_time_type(left_type) ||
      search_expression_type->is_string_type(left_type))
    return print_compare_function("__le_", left_type, symbol->l_exp, symbol->r_exp);
  if (!search_base_type.type_is_enumerated(left_type))
    return print_binary_expression(symbol->l_exp, symbol->r_exp, " <= ");
  ERROR;
  return NULL;
}

void *visit(ge_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
  symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
  if (!search_expression_type->is_same_type(left_type, right_type))
      ERROR;
  if (search_expression_type->is_time_type(left_type) ||
      search_expression_type->is_string_type(left_type))
    return print_compare_function("__ge_", left_type, symbol->l_exp, symbol->r_exp);
  if (!search_base_type.type_is_enumerated(left_type))
    return print_binary_expression(symbol->l_exp, symbol->r_exp, " >= ");
  ERROR;
  return NULL;
}

void *visit(add_expression_c *symbol) {
  symbol_c *left_type = search_expression_type->get_type(symbol->l_exp);
	symbol_c *right_type = search_expression_type->get_type(symbol->r_exp);
	if ((typeid(*left_type) == typeid(time_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) ||
      (typeid(*left_type) == typeid(tod_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) ||
      (typeid(*left_type) == typeid(dt_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)))
    return print_binary_function("__TIME_ADD", symbol->l_exp, symbol->r_exp);
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
    return print_binary_function("__TIME_SUB", symbol->l_exp, symbol->r_exp);
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
    return print_binary_function("__TIME_MUL", symbol->l_exp, symbol->r_exp);
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
  if ((typeid(*left_type) == typeid(time_type_name_c) && search_expression_type->is_integer_type(right_type)) ||
      (typeid(*left_type) == typeid(time_type_name_c) && search_expression_type->is_real_type(right_type)))
    return print_binary_function("__TIME_DIV", symbol->l_exp, symbol->r_exp);
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
void *visit(power_expression_c *symbol) {
  ERROR; 
  return print_binary_expression(symbol->l_exp, symbol->r_exp, " ** ");
}

void *visit(neg_expression_c *symbol) {
  return print_unary_expression(symbol->exp, " -");
}

void *visit(not_expression_c *symbol) {
  symbol_c *exp_type = search_expression_type->get_type(symbol->exp);
  if (search_expression_type->is_binary_type(exp_type))
    return print_unary_expression(symbol->exp, search_expression_type->is_bool_type(exp_type)?"!":"~");
  ERROR;
  return NULL;
}

void *visit(function_invocation_c *symbol) {
  symbol_c* function_type_prefix = NULL;
  symbol_c* function_name = NULL;
  symbol_c* function_type_suffix = NULL;
  DECLARE_PARAM_LIST()

  symbol_c *parameter_assignment_list = NULL;
  if (NULL != symbol->   formal_param_list) parameter_assignment_list = symbol->   formal_param_list;
  if (NULL != symbol->nonformal_param_list) parameter_assignment_list = symbol->nonformal_param_list;
  if (NULL == parameter_assignment_list) ERROR;

  function_call_param_iterator_c function_call_param_iterator(symbol);

  function_declaration_c *f_decl = function_symtable.find_value(symbol->function_name);
  if (f_decl == function_symtable.end_value()) {
    /* The function called is not in the symtable, so we test if it is a
     * standard function defined in standard */

    function_type_t current_function_type = get_function_type((identifier_c *)symbol->function_name);
    if (current_function_type == function_none) ERROR;

    symbol_c *function_return_type = search_expression_type->get_type(symbol);

    int nb_param = ((list_c *)parameter_assignment_list)->n;

    symbol_c *en_param_name = (symbol_c *)(new identifier_c("EN"));
    /* Get the value from EN param */
    symbol_c *EN_param_value = function_call_param_iterator.search_f(en_param_name);
    if (EN_param_value == NULL)
      EN_param_value = (symbol_c*)(new boolean_literal_c((symbol_c*)(new bool_type_name_c()), new boolean_true_c()));
    else
      nb_param --;
    ADD_PARAM_LIST(en_param_name, EN_param_value, (symbol_c*)(new bool_type_name_c()), function_param_iterator_c::direction_in)

    symbol_c *eno_param_name = (symbol_c *)(new identifier_c("ENO"));
    /* Get the value from ENO param */
    symbol_c *ENO_param_value = function_call_param_iterator.search_f(eno_param_name);
    if (ENO_param_value != NULL)
      nb_param --;
    ADD_PARAM_LIST(eno_param_name, ENO_param_value, (symbol_c*)(new bool_type_name_c()), function_param_iterator_c::direction_out)

    #include "st_code_gen.c"

  }
  else {
	function_name = symbol->function_name;

	/* loop through each function parameter, find the value we should pass
     * to it, and then output the c equivalent...
     */
    function_param_iterator_c fp_iterator(f_decl);
    identifier_c *param_name;
    for(int i = 1; (param_name = fp_iterator.next()) != NULL; i++) {
      
      symbol_c *param_type = fp_iterator.param_type();
      if (param_type == NULL) ERROR;

      function_param_iterator_c::param_direction_t param_direction = fp_iterator.param_direction();
      
      /* Get the value from a foo(<param_name> = <param_value>) style call */
      symbol_c *param_value = function_call_param_iterator.search_f(param_name);
  
      /* Get the value from a foo(<param_value>) style call */
      if (param_value == NULL) {
        param_value = function_call_param_iterator.next_nf();
        if (param_value != NULL && fp_iterator.is_en_eno_param_implicit()) ERROR;
      }
      
      if (param_value == NULL && param_direction == function_param_iterator_c::direction_in) {
        /* No value given for parameter, so we must use the default... */
        /* First check whether default value specified in function declaration...*/
        param_value = fp_iterator.default_value();
      }
      
      ADD_PARAM_LIST(param_name, param_value, param_type, param_direction)
    } /* for(...) */
    // symbol->parameter_assignment->accept(*this);
  }
  
  if (function_call_param_iterator.next_nf() != NULL) ERROR;

  bool has_output_params = false;

  if (!this->is_variable_prefix_null()) {
    PARAM_LIST_ITERATOR() {
	  if ((PARAM_DIRECTION == function_param_iterator_c::direction_out ||
		   PARAM_DIRECTION == function_param_iterator_c::direction_inout) &&
		  PARAM_VALUE != NULL) {
	    if (!has_output_params) {
		  has_output_params = true;
		}
	  }
    }
  }

  if (function_type_prefix != NULL) {
    s4o.print("(");
    function_type_prefix->accept(*this);
    s4o.print(")");
  }
  if (has_output_params) {
	fcall_number++;
	s4o.print("__");
    fbname->accept(*this);
    s4o.print("_");
    function_name->accept(*this);
    if (function_type_suffix != NULL)
      function_type_suffix->accept(*this);
    s4o.print_integer(fcall_number);
  }
  else {
    function_name->accept(*this);
    if (function_type_suffix != NULL)
      function_type_suffix->accept(*this);
  }
  s4o.print("(");
  s4o.indent_right();
  
  int nb_param = 0;
  PARAM_LIST_ITERATOR() {
    symbol_c *param_value = PARAM_VALUE;
    current_param_type = PARAM_TYPE;
          
    switch (PARAM_DIRECTION) {
      case function_param_iterator_c::direction_in:
    	if (nb_param > 0)
    	  s4o.print(",\n"+s4o.indent_spaces);
    	if (param_value == NULL) {
          /* If not, get the default value of this variable's type */
          param_value = (symbol_c *)current_param_type->accept(*type_initial_value_c::instance());
        }
        if (param_value == NULL) ERROR;
        s4o.print("(");
        if (search_expression_type->is_literal_integer_type(current_param_type))
          search_expression_type->lint_type_name.accept(*this);
        else if (search_expression_type->is_literal_real_type(current_param_type))
          search_expression_type->lreal_type_name.accept(*this);
        else
          current_param_type->accept(*this);
        s4o.print(")");
        print_check_function(current_param_type, param_value);
        nb_param++;
        break;
      case function_param_iterator_c::direction_out:
      case function_param_iterator_c::direction_inout:
    	if (!has_output_params) {
          if (nb_param > 0)
        	s4o.print(",\n"+s4o.indent_spaces);
    	  if (param_value == NULL)
            s4o.print("NULL");
          else {
            wanted_variablegeneration = fparam_output_vg;
            param_value->accept(*this);
            wanted_variablegeneration = expression_vg;
          }
    	  nb_param++;
    	}
        break;
      case function_param_iterator_c::direction_extref:
        /* TODO! */
        ERROR;
        break;
    } /* switch */
  }
  if (has_output_params) {
    if (nb_param > 0)
      s4o.print(",\n"+s4o.indent_spaces);
    s4o.print(FB_FUNCTION_PARAM);
  }
  s4o.print(")");
  s4o.indent_left();

  CLEAR_PARAM_LIST()

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
  symbol_c *left_type = search_varfb_instance_type->get_rawtype(symbol->l_exp);
  
  if (this->is_variable_prefix_null()) {
    symbol->l_exp->accept(*this);
    s4o.print(" = ");
    print_check_function(left_type, symbol->r_exp);
  }
  else {
	print_setter(symbol->l_exp, left_type, symbol->r_exp);
  }
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
    
    /*fprintf(stderr, "param : %s\n", param_name->value);*/
    
    /* Get the value from a foo(<param_name> = <param_value>) style call */
    symbol_c *param_value = function_call_param_iterator.search_f(param_name);

    /* Get the value from a foo(<param_value>) style call */
    if (param_value == NULL)
      param_value = function_call_param_iterator.next_nf();

    symbol_c *param_type = fp_iterator.param_type();
    if (param_type == NULL) ERROR;
    
    /* now output the value assignment */
    if (param_value != NULL)
      if ((param_direction == function_param_iterator_c::direction_in) ||
          (param_direction == function_param_iterator_c::direction_inout)) {
        if (this->is_variable_prefix_null()) {
          symbol->fb_name->accept(*this);
          s4o.print(".");
          param_name->accept(*this);
          s4o.print(" = ");
          print_check_function(param_type, param_value);
        }
        else {
          print_setter(param_name, param_type, param_value, symbol->fb_name);
        }
        s4o.print(";\n" + s4o.indent_spaces);
      }
  } /* for(...) */

  /* now call the function... */
  function_block_type_name->accept(*this);
  s4o.print(FB_FUNCTION_SUFFIX);
  s4o.print("(&");
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
    symbol_c *param_value = function_call_param_iterator.search_f(param_name);

    /* Get the value from a foo(<param_value>) style call */
    if (param_value == NULL)
      param_value = function_call_param_iterator.next_nf();

    /* now output the value assignment */
    if (param_value != NULL)
      if ((param_direction == function_param_iterator_c::direction_out) ||
          (param_direction == function_param_iterator_c::direction_inout)) {
        symbol_c *param_type = search_varfb_instance_type->get_rawtype(param_value);
        s4o.print(";\n" + s4o.indent_spaces);
        if (this->is_variable_prefix_null()) {
          param_value->accept(*this);
          s4o.print(" = ");
          print_check_function(param_type, param_name, symbol->fb_name);
        }
        else {
          print_setter(param_value, param_type, param_name, NULL, symbol->fb_name);
        }
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
  s4o.print("break");
  return NULL;
}



}; /* generate_c_st_c */









