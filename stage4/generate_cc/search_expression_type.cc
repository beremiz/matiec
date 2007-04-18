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
    bool is_time_compatible(symbol_c *type_symbol) {
      if (typeid(*type_symbol) == typeid(time_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(date_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(tod_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(dt_type_name_c)) {return true;}
      return false;
    }

    /* A helper function... */
    bool is_numeric_compatible(symbol_c *type_symbol) {
      if (typeid(*type_symbol) == typeid(sint_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(int_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(dint_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(lint_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(usint_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(uint_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(udint_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(ulint_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(real_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(lreal_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(bool_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(byte_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(word_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(dword_type_name_c)) {return true;}
      if (typeid(*type_symbol) == typeid(lword_type_name_c)) {return true;}
      return false;
    }
    
  private:

  static bool_type_name_c bool_type_name;

  /* A helper function... */
  void *compute_boolean_expression(symbol_c *left_type, symbol_c *right_type) {
    if (typeid(*left_type) == typeid(bool_type_name_c) and typeid(*right_type) == typeid(bool_type_name_c)) {return (void *)left_type;}
    if (is_numeric_compatible(left_type) && is_numeric_compatible(right_type)) {return (void *)left_type;}
    ERROR;
    return NULL;
  }

  /* A helper function... */
  void *compute_numeric_expression(symbol_c *left_type, symbol_c *right_type) {
    if (is_numeric_compatible(left_type) && is_numeric_compatible(right_type)) {return (void *)left_type;}
    ERROR;
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
    if (is_time_compatible(left_type) && is_time_compatible(right_type)) {return left_type;}
    return compute_numeric_expression(left_type, right_type);
  }

  void *visit(sub_expression_c *symbol) {
    symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
    symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
    if (is_time_compatible(left_type) && is_time_compatible(right_type)) {return left_type;}
    return compute_numeric_expression(left_type, right_type);
  }
  
  void *visit(mul_expression_c *symbol) {
    symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
    symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
    if (is_time_compatible(left_type) && is_time_compatible(right_type)) {return left_type;}
    return compute_numeric_expression(left_type, right_type);
  }
  
  void *visit(div_expression_c *symbol) {
    symbol_c *left_type = base_type((symbol_c *)symbol->l_exp->accept(*this));
    symbol_c *right_type = base_type((symbol_c *)symbol->r_exp->accept(*this));
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
    if (typeid(*left_type) == typeid(real_type_name_c) and typeid(*right_type) == typeid(sint_type_name_c)) {return (void *)left_type;}
    if (typeid(*left_type) == typeid(real_type_name_c) and typeid(*right_type) == typeid(int_type_name_c)) {return (void *)left_type;}
    if (typeid(*left_type) == typeid(real_type_name_c) and typeid(*right_type) == typeid(dint_type_name_c)) {return (void *)left_type;}
    if (typeid(*left_type) == typeid(real_type_name_c) and typeid(*right_type) == typeid(lint_type_name_c)) {return (void *)left_type;}
    if (typeid(*left_type) == typeid(real_type_name_c) and typeid(*right_type) == typeid(usint_type_name_c)) {return (void *)left_type;}
    if (typeid(*left_type) == typeid(real_type_name_c) and typeid(*right_type) == typeid(uint_type_name_c)) {return (void *)left_type;}
    if (typeid(*left_type) == typeid(real_type_name_c) and typeid(*right_type) == typeid(udint_type_name_c)) {return (void *)left_type;}
    if (typeid(*left_type) == typeid(real_type_name_c) and typeid(*right_type) == typeid(ulint_type_name_c)) {return (void *)left_type;}
    if (typeid(*left_type) == typeid(lreal_type_name_c) and typeid(*right_type) == typeid(sint_type_name_c)) {return (void *)left_type;}
    if (typeid(*left_type) == typeid(lreal_type_name_c) and typeid(*right_type) == typeid(int_type_name_c)) {return (void *)left_type;}
    if (typeid(*left_type) == typeid(lreal_type_name_c) and typeid(*right_type) == typeid(dint_type_name_c)) {return (void *)left_type;}
    if (typeid(*left_type) == typeid(lreal_type_name_c) and typeid(*right_type) == typeid(lint_type_name_c)) {return (void *)left_type;}
    if (typeid(*left_type) == typeid(lreal_type_name_c) and typeid(*right_type) == typeid(usint_type_name_c)) {return (void *)left_type;}
    if (typeid(*left_type) == typeid(lreal_type_name_c) and typeid(*right_type) == typeid(uint_type_name_c)) {return (void *)left_type;}
    if (typeid(*left_type) == typeid(lreal_type_name_c) and typeid(*right_type) == typeid(udint_type_name_c)) {return (void *)left_type;}
    if (typeid(*left_type) == typeid(lreal_type_name_c) and typeid(*right_type) == typeid(ulint_type_name_c)) {return (void *)left_type;}
    ERROR;
    return NULL;
  }
  
  void *visit(neg_expression_c *symbol) {
    symbol_c *exp_type = base_type((symbol_c *)symbol->exp->accept(*this));
    if (typeid(*exp_type) == typeid(sint_type_name_c)) {return (void *)exp_type;}
    if (typeid(*exp_type) == typeid(int_type_name_c)) {return (void *)exp_type;}
    if (typeid(*exp_type) == typeid(dint_type_name_c)) {return (void *)exp_type;}
    if (typeid(*exp_type) == typeid(lint_type_name_c)) {return (void *)exp_type;}
    if (typeid(*exp_type) == typeid(usint_type_name_c)) {return (void *)exp_type;}
    if (typeid(*exp_type) == typeid(uint_type_name_c)) {return (void *)exp_type;}
    if (typeid(*exp_type) == typeid(udint_type_name_c)) {return (void *)exp_type;}
    if (typeid(*exp_type) == typeid(ulint_type_name_c)) {return (void *)exp_type;}
    if (typeid(*exp_type) == typeid(real_type_name_c)) {return (void *)exp_type;}
    if (typeid(*exp_type) == typeid(lreal_type_name_c)) {return (void *)exp_type;}
    if (typeid(*exp_type) == typeid(time_type_name_c)) {return (void *)exp_type;}
    ERROR;
    return NULL;
  }
  
  void *visit(not_expression_c *symbol) {
    symbol_c *exp_type = base_type((symbol_c *)symbol->exp->accept(*this));
    if (typeid(*exp_type) == typeid(bool_type_name_c)) {return (void *)exp_type;}
    ERROR;
    return NULL;
  }
  
  void *visit(function_invocation_c *symbol) {
	  function_declaration_c *f_decl = function_symtable.find_value(symbol->function_name);
	
	  if (f_decl == function_symtable.end_value())
	    /* should never occur. The function being called MUST be in the symtable... */
	    ERROR;

    return base_type(f_decl->type_name);
  }

};

bool_type_name_c     search_expression_type_c::bool_type_name;

