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


/* Determine the data type of an ST expression.
 * A reference to the relevant type definition is returned.
 *
 * For example:
 *       2 + 3       -> returns reference to a int_type_name_c object.
 *       22.2 - 5    -> returns reference to a real_type_name_c object.
 *       etc...
 */

#include "function_type_decl.h"
#include "get_function_type_decl.c"

#if 0
typedef enum {function_add,
              function_sub,
              function_and,
              function_or,
              function_sqrt,
              function_none} function_type_t;


function_type_t get_function_type(identifier_c *function_name) {
  if (!strcasecmp(function_name->value, "ADD"))
    return function_add;
  else if (!strcasecmp(function_name->value, "SUB"))
    return function_sub;
  else if (!strcasecmp(function_name->value, "AND"))
    return function_and;
  else if (!strcasecmp(function_name->value, "OR"))
    return function_or;
  else if (!strcasecmp(function_name->value, "SQRT"))
    return function_sqrt;
  else return function_none;
}
#endif


symbol_c *generate_param_name(const char *name) {
  symbol_c *param_name = new identifier_c(name);
  return param_name;
}


symbol_c *generate_param_name(const char *format, int number) {
  char name[10];
  sprintf(name, format, number);
  symbol_c *param_name = new identifier_c(name);
  return param_name;
}


class search_expression_type_c: public search_constant_type_c {
  private:
    search_varfb_instance_type_c *search_varfb_instance_type;
    search_base_type_c search_base_type;

  public:
    search_expression_type_c(symbol_c *search_scope) {
      search_varfb_instance_type = new search_varfb_instance_type_c(search_scope);
    }

    virtual ~search_expression_type_c(void) {
      delete search_varfb_instance_type;
    }

    /* A helper function... */
    bool is_bool_type(symbol_c *type_symbol) {
      return (typeid(*type_symbol) == typeid(bool_type_name_c));
    }

    /* A helper function... */
    bool is_time_type(symbol_c *type_symbol) {
      if (typeid(*type_symbol) == typeid(time_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(date_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(tod_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(dt_type_name_c)) {return true;}
      return false;
    }

    /* A helper function... */
    bool is_string_type(symbol_c *type_symbol) {
      if (typeid(*type_symbol) == typeid(string_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(wstring_type_name_c)) {return true;}
      return false;
    }

    /* A helper function... */
    bool is_integer_type(symbol_c *type_symbol) {
      if (typeid(*type_symbol) == typeid(sint_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(int_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(dint_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(lint_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(usint_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(uint_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(udint_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(ulint_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(constant_int_type_name_c)) {return true;}
      return false;
    }

    bool is_real_type(symbol_c *type_symbol) {
      if (typeid(*type_symbol) == typeid(real_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(lreal_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(constant_real_type_name_c)) {return true;}
      return false;
    }

    bool is_num_type(symbol_c *type_symbol) {
      return is_real_type(type_symbol) || is_integer_type(type_symbol);
    }

    bool is_nbinary_type(symbol_c *type_symbol) {
      if (typeid(*type_symbol) == typeid(byte_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(word_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(dword_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(lword_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(constant_int_type_name_c)) {return true;}
      return false;
    }

    bool is_binary_type(symbol_c *type_symbol) {
      if (typeid(*type_symbol) == typeid(bool_type_name_c)) {return true;}
      return is_nbinary_type(type_symbol);
    }
    
    bool is_same_type(symbol_c *first_type, symbol_c *second_type) {
      if (typeid(*first_type) == typeid(*second_type)) {return true;}
      if (is_integer_type(first_type) && (typeid(*second_type) == typeid(constant_int_type_name_c))) {return true;}
      if ((typeid(*first_type) == typeid(constant_int_type_name_c) && is_integer_type(second_type))) {return true;}
      if (is_binary_type(first_type) && (typeid(*second_type) == typeid(constant_int_type_name_c))) {return true;}
      if ((typeid(*first_type) == typeid(constant_int_type_name_c) && is_binary_type(second_type))) {return true;}
      if (is_real_type(first_type) && (typeid(*second_type) == typeid(constant_real_type_name_c))) {return true;}
      if ((typeid(*first_type) == typeid(constant_real_type_name_c) && is_real_type(second_type))) {return true;}
      return false;
    }

    symbol_c* common_type(symbol_c *first_type, symbol_c *second_type) {
      if (typeid(*first_type) == typeid(*second_type)) {return first_type;}
      if (is_integer_type(first_type) && (typeid(*second_type) == typeid(constant_int_type_name_c))) {return first_type;}
      if ((typeid(*first_type) == typeid(constant_int_type_name_c) && is_integer_type(second_type))) {return second_type;}
      if (is_binary_type(first_type) && (typeid(*second_type) == typeid(constant_int_type_name_c))) {return first_type;}
      if ((typeid(*first_type) == typeid(constant_int_type_name_c) && is_binary_type(second_type))) {return second_type;}
      if (is_real_type(first_type) && (typeid(*second_type) == typeid(constant_real_type_name_c))) {return first_type;}
      if ((typeid(*first_type) == typeid(constant_real_type_name_c) && is_real_type(second_type))) {return second_type;}
      return NULL;
    }

#include "search_type_code.c"

#if 0
  void *compute_standard_function_st(function_invocation_c *symbol) {
    symbol_c *current_type = NULL;
    symbol_c *return_type = NULL;

    function_type_t current_function_type = get_function_type((identifier_c *)symbol->function_name);
    function_call_param_iterator_c function_call_param_iterator(symbol);
    search_expression_type_c* search_expression_type = this;
    
    for(int current_param = 0; current_param < ((list_c *)symbol->parameter_assignment_list)->n; current_param++) {
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
          else ERROR;
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
      
      symbol_c *param_type = (symbol_c *)param_value->accept(*this);
      
      switch (current_function_type) {
        case function_add:
          if (current_param == 0)
            current_type = param_type;
          else if (current_param == 1) {
            if ((is_integer_type(current_type) && is_same_type(current_type, param_type)) ||
                (is_real_type(current_type) && is_same_type(current_type, param_type))) {
              current_type = common_type(current_type, param_type);
              return_type = current_type;
            }
            else if (is_time_type(current_type)) {
              if ((typeid(*current_type) == typeid(time_type_name_c)) && (typeid(*param_type) == typeid(time_type_name_c))) {return_type = (symbol_c *)&time_type_name;}
              else if (typeid(*current_type) == typeid(tod_type_name_c) && typeid(*param_type) == typeid(time_type_name_c)) {return_type = (symbol_c *)&tod_type_name;}
              else if (typeid(*current_type) == typeid(dt_type_name_c) && typeid(*param_type) == typeid(time_type_name_c)) {return_type = (symbol_c *)&dt_type_name;}
              else ERROR;
            }
            else ERROR;
          }
          else if (!is_time_type(current_type) && is_same_type(current_type, param_type)) {
            current_type = common_type(current_type, param_type);
            return_type = current_type;
          }
          else ERROR;
          break;
        case function_sub:
          if (current_param == 0)
            current_type = param_type;
          else if (current_param == 1) {
            if ((is_integer_type(current_type) && is_same_type(current_type, param_type)) ||
                (is_real_type(current_type) && is_same_type(current_type, param_type)))
              return_type = common_type(current_type, param_type);
            else if (is_time_type(current_type)) {
              if (typeid(*current_type) == typeid(time_type_name_c) && typeid(*param_type) == typeid(time_type_name_c)) {return_type = (symbol_c *)&time_type_name;}
              else if (typeid(*current_type) == typeid(date_type_name_c) && typeid(*param_type) == typeid(date_type_name_c)) {return_type = (symbol_c *)&time_type_name;}
              else if (typeid(*current_type) == typeid(tod_type_name_c) && typeid(*param_type) == typeid(time_type_name_c)) {return_type = (symbol_c *)&tod_type_name;}
              else if (typeid(*current_type) == typeid(tod_type_name_c) && typeid(*param_type) == typeid(tod_type_name_c)) {return_type = (symbol_c *)&time_type_name;}
              else if (typeid(*current_type) == typeid(dt_type_name_c) && typeid(*param_type) == typeid(time_type_name_c)) {return_type = (symbol_c *)&dt_type_name;}
              else if (typeid(*current_type) == typeid(dt_type_name_c) && typeid(*param_type) == typeid(dt_type_name_c)) {return_type = (symbol_c *)&time_type_name;}
              else ERROR;
            }
            else ERROR;
          }
          else ERROR;
          break;
        case function_and:
        case function_or:
          if (current_param == 0)
            if (is_binary_type(param_type))
              current_type = param_type;
            else ERROR;
          else if (is_same_type(current_type, param_type))
            return_type = common_type(current_type, param_type);
          else ERROR;
          break;
        default: ERROR;
      }
    }
    return (void *)return_type;
  }

  void *compute_standard_function_il(il_function_call_c *symbol, symbol_c *param_type) {
    /*symbol_c *current_type = NULL;*/
    symbol_c *return_type = NULL;
    function_type_t current_function_type = get_function_type((identifier_c *)symbol->function_name);
    if (current_function_type == function_none) ERROR;
    
    function_call_param_iterator_c function_call_param_iterator(symbol);
    
    int nb_param = 1;
    if (symbol->il_operand_list != NULL)
      nb_param += ((list_c *)symbol->il_operand_list)->n;

    for(int current_param = 0; current_param < nb_param; current_param++) {
      
      if (current_param != 0) {
        symbol_c *param_name = NULL;
        switch (current_function_type) {
          default: ERROR;
        }
        
        /* Get the value from a foo(<param_name> = <param_value>) style call */
        symbol_c *param_value = function_call_param_iterator.search(param_name);
        delete param_name;
        
        /* Get the value from a foo(<param_value>) style call */
        if (param_value == NULL)
          param_value = function_call_param_iterator.next();
        
        if (param_value == NULL) ERROR;
        
        param_type = (symbol_c *)param_value->accept(*this);
      }
      
      switch (current_function_type) {
        case function_sqrt:
          if (current_param == 0 && is_real_type(param_type))
            return_type = param_type;
          else ERROR;
          break;
        default: ERROR;
      }
    }
    
    return (void *)return_type;
  }
#endif

  /*static bool_type_name_c bool_type_name;*/

  /* A helper function... */
  void *compute_boolean_expression(symbol_c *left_type, symbol_c *right_type) {
    if (!is_same_type(left_type, right_type))
      ERROR;
    if (!is_bool_type(left_type) && !is_binary_type(left_type))
      ERROR;
    if (typeid(*left_type) == typeid(constant_int_type_name_c)) {return (void *)right_type;}
    else {return (void *)left_type;}
  }

  /* A helper function... */
  void *compute_numeric_expression(symbol_c *left_type, symbol_c *right_type) {
    if (!is_same_type(left_type, right_type))
      ERROR;
    if (!is_integer_type(left_type) && !is_real_type(left_type))
      ERROR;
    if ((typeid(*left_type) == typeid(constant_int_type_name_c)) || (typeid(*left_type) == typeid(constant_real_type_name_c))) {return (void *)right_type;}
    else {return (void *)left_type;}
    return NULL;
  }

  /* a helper function... */
  symbol_c *base_type(symbol_c *symbol) {
    return (symbol_c *)symbol->accept(search_base_type);
  }

/*********************/
/* B 1.4 - Variables */
/*********************/

  void *visit(symbolic_variable_c *symbol) {
    symbol_c *res;
    
    /* Nope, now we assume it is a variable, and determine its type... */
    res = search_varfb_instance_type->get_type(symbol);
    if (NULL != res) return res;
    
    return NULL;
  }

/*************************************/
/* B 1.4.2 - Multi-element variables */
/*************************************/

  void *visit(array_variable_c *symbol) {
    symbol_c *res;
    
    /* Nope, now we assume it is a variable, and determine its type... */
    res = search_varfb_instance_type->get_type(symbol);
    if (NULL != res) return res;
    
    return NULL;
  }

  void *visit(structured_variable_c *symbol) {
    symbol_c *res;
    
    /* Nope, now we assume it is a variable, and determine its type... */
    res = search_varfb_instance_type->get_type(symbol);
    if (NULL != res) return res;
    
    return NULL;
  }

/***************************************/
/* B.3 - Language ST (Structured Text) */
/***************************************/
/***********************/
/* B 3.1 - Expressions */
/***********************/
  void *visit(or_expression_c *symbol) {
    symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
    symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
    return compute_boolean_expression(left_type, right_type);
  }

  void *visit(xor_expression_c *symbol) {
    symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
    symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
    return compute_boolean_expression(left_type, right_type);
  }

  void *visit(and_expression_c *symbol) {
    symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
    symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
    return compute_boolean_expression(left_type, right_type); 
  }

  void *visit(equ_expression_c *symbol) {return (void *)&bool_type_name;}
  void *visit(notequ_expression_c *symbol) {return (void *)&bool_type_name;}
  void *visit(lt_expression_c *symbol) {return (void *)&bool_type_name;}
  void *visit(gt_expression_c *symbol) {return (void *)&bool_type_name;}
  void *visit(le_expression_c *symbol) {return (void *)&bool_type_name;}
  void *visit(ge_expression_c *symbol) {return (void *)&bool_type_name;}

  void *visit(add_expression_c *symbol) {
    symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
    symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
    if (typeid(*left_type) == typeid(time_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) {return (void *)&time_type_name;}
    if (typeid(*left_type) == typeid(tod_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) {return (void *)&tod_type_name;}
    if (typeid(*left_type) == typeid(dt_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) {return (void *)&dt_type_name;}
    return compute_numeric_expression(left_type, right_type);
  }

  void *visit(sub_expression_c *symbol) {
    symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
    symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
    if (typeid(*left_type) == typeid(time_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) {return (void *)&time_type_name;}
    if (typeid(*left_type) == typeid(date_type_name_c) && typeid(*right_type) == typeid(date_type_name_c)) {return (void *)&time_type_name;}
    if (typeid(*left_type) == typeid(tod_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) {return (void *)&tod_type_name;}
    if (typeid(*left_type) == typeid(tod_type_name_c) && typeid(*right_type) == typeid(tod_type_name_c)) {return (void *)&time_type_name;}
    if (typeid(*left_type) == typeid(dt_type_name_c) && typeid(*right_type) == typeid(time_type_name_c)) {return (void *)&dt_type_name;}
    if (typeid(*left_type) == typeid(dt_type_name_c) && typeid(*right_type) == typeid(dt_type_name_c)) {return (void *)&time_type_name;}
    return compute_numeric_expression(left_type, right_type);
  }
  
  void *visit(mul_expression_c *symbol) {
    symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
    symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
    if (typeid(*left_type) == typeid(time_type_name_c) && is_num_type(right_type)) {
        return (void *)&time_type_name;
    }
    return compute_numeric_expression(left_type, right_type);
  }
  
  void *visit(div_expression_c *symbol) {
    symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
    symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
    if (typeid(*left_type) == typeid(time_type_name_c) && is_num_type(right_type)){
        return (void *)&time_type_name;
    }
    return compute_numeric_expression(left_type, right_type);
  }

  void *visit(mod_expression_c *symbol) {
    symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
    symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
    return compute_numeric_expression(left_type, right_type);
  }

  void *visit(power_expression_c *symbol) {
    symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
    symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
    if (is_real_type(left_type) && is_num_type(right_type)) {
        return (void *)left_type;
    }
    ERROR;
    return NULL;
  }
  
  void *visit(neg_expression_c *symbol) {
    symbol_c *exp_type = base_type((symbol_c *)symbol->exp->accept(*this));
    if (is_num_type(exp_type) || typeid(*exp_type) == typeid(time_type_name_c)){
        return (void *)exp_type;
    }
    ERROR;
    return NULL;
  }
  
  void *visit(not_expression_c *symbol) {
    symbol_c *exp_type = base_type((symbol_c *)symbol->exp->accept(*this));
    return compute_boolean_expression(exp_type, exp_type);
  }
  
  void *visit(function_invocation_c *symbol) {
	  function_declaration_c *f_decl = function_symtable.find_value(symbol->function_name);
	
	  if (f_decl == function_symtable.end_value()) {
      void *res = compute_standard_function_st(symbol);
	    if (res == NULL)
        ERROR;
      return res;
    }

    return base_type(f_decl->type_name);
  }

};

/*bool_type_name_c     search_expression_type_c::bool_type_name;*/

