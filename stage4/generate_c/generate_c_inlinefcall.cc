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


#define INLINE_RESULT_TEMP_VAR "__res"

class generate_c_inlinefcall_c: public generate_c_typedecl_c {

  public:
    typedef enum {
      expression_vg,
      assignment_vg,
      complextype_base_vg,
      complextype_suffix_vg
    } variablegeneration_t;

  private:

    /* The initial value that should be given to the IL default variable
	 * imediately after a parenthesis is opened.
	 * This variable is only used to pass data from the
	 * il_expression_c visitor to the simple_instr_list_c visitor.
	 *
	 * e.g.:
	 *         LD var1
	 *         AND ( var2
	 *         OR var3
	 *         )
	 *
	 * In the above code sample, the line 'AND ( var2' constitutes
	 * an il_expression_c, where var2 should be loaded into the
	 * il default variable before continuing with the expression
	 * inside the parenthesis.
	 * Unfortunately, only the simple_instr_list_c may do the
	 * initial laoding of the var2 bariable following the parenthesis,
	 * so the il_expression_c visitor will have to pass 'var2' as a
	 * parameter to the simple_instr_list_c visitor.
	 * Ergo, the existance of the following parameter...!
	 */
	symbol_c *il_default_variable_init_value;

    /* Operand to the IL operation currently being processed... */
	/* These variables are used to pass data from the
	 * il_simple_operation_c and il_expression_c visitors
	 * to the il operator visitors (i.e. LD_operator_c,
	 * LDN_operator_c, ST_operator_c, STN_operator_c, ...)
	 */
	symbol_c *current_operand;
	symbol_c *current_operand_type;

	 /* The result of the comparison IL operations (GT, EQ, LT, ...)
	 * is a boolean variable.
	 * This class keeps track of the current data type stored in the
	 * il default variable. This is usually done by keeping a reference
	 * to the data type of the last operand. Nevertheless, in the case of
	 * the comparison IL operators, the data type of the result (a boolean)
	 * is not the data type of the operand. We therefore need an object
	 * of the boolean data type to keep as a reference of the current
	 * data type.
	 * The following object is it...
	 */
	bool_type_name_c bool_type;
	lint_type_name_c lint_type;
	lword_type_name_c lword_type;
	lreal_type_name_c lreal_type;

    /* The name of the IL default variable... */
	#define IL_DEFVAR   VAR_LEADER "IL_DEFVAR"

	/* The name of the variable used to pass the result of a
	 * parenthesised instruction list to the immediately preceding
	 * scope ...
	 */
    #define IL_DEFVAR_BACK   VAR_LEADER "IL_DEFVAR_BACK"
    il_default_variable_c default_variable_name;
	il_default_variable_c default_variable_back_name;

	symbol_c* current_array_type;

	int fcall_number;
	symbol_c *fbname;

    search_expression_type_c *search_expression_type;

    search_varfb_instance_type_c *search_varfb_instance_type;

    search_base_type_c search_base_type;

    variablegeneration_t wanted_variablegeneration;

  public:
    generate_c_inlinefcall_c(stage4out_c *s4o_ptr, symbol_c *name, symbol_c *scope, const char *variable_prefix = NULL)
    : generate_c_typedecl_c(s4o_ptr),
      default_variable_name(IL_DEFVAR, NULL),
      default_variable_back_name(IL_DEFVAR_BACK, NULL)
    {
      search_expression_type = new search_expression_type_c(scope);
      search_varfb_instance_type = new search_varfb_instance_type_c(scope);
      this->set_variable_prefix(variable_prefix);
      fcall_number = 0;
      fbname = name;
      wanted_variablegeneration = expression_vg;
    }

    virtual ~generate_c_inlinefcall_c(void) {
      delete search_expression_type;
      delete search_varfb_instance_type;
    }

    void print(symbol_c* symbol) {
      function_call_iterator_c fc_iterator(symbol);
      symbol_c* function_call;
      while ((function_call = fc_iterator.next()) != NULL) {
    	function_call->accept(*this);
      }
    }

    void generate_inline(symbol_c *function_name,
            symbol_c *function_type_prefix,
            symbol_c *function_type_suffix,
            std::list<FUNCTION_PARAM*> param_list) {
            std::list<FUNCTION_PARAM*>::iterator pt;

      fcall_number++;
      function_type_prefix = search_expression_type->default_literal_type(function_type_prefix);
      if (function_type_suffix) {
        function_type_suffix = search_expression_type->default_literal_type(function_type_suffix);
      }

      s4o.print(s4o.indent_spaces);
      s4o.print("inline ");
      function_type_prefix->accept(*this);
      s4o.print(" __");
      fbname->accept(*this);
      s4o.print("_");
      function_name->accept(*this);
      if (function_type_suffix) {
    	function_type_suffix->accept(*this);
      }
      s4o.print_integer(fcall_number);
      s4o.print("(");
      s4o.indent_right();

      PARAM_LIST_ITERATOR() {
        if (PARAM_DIRECTION == function_param_iterator_c::direction_in) {
          search_expression_type->default_literal_type(PARAM_TYPE)->accept(*this);
          s4o.print(" ");
          PARAM_NAME->accept(*this);
          s4o.print(",\n" + s4o.indent_spaces);
        }
      }
      fbname->accept(*this);
	  s4o.print(" *");
	  s4o.print(FB_FUNCTION_PARAM);
	  s4o.indent_left();
	  s4o.print(")\n" + s4o.indent_spaces);
	  s4o.print("{\n");
      s4o.indent_right();

      s4o.print(s4o.indent_spaces);
      function_type_prefix->accept(*this);
      s4o.print(" "),
      s4o.print(INLINE_RESULT_TEMP_VAR);
      s4o.print(";\n");

	  PARAM_LIST_ITERATOR() {
		if ((PARAM_DIRECTION == function_param_iterator_c::direction_out ||
		     PARAM_DIRECTION == function_param_iterator_c::direction_inout) &&
		    PARAM_VALUE != NULL) {
		  s4o.print(s4o.indent_spaces);
		  PARAM_TYPE->accept(*this);
          s4o.print(" ");
          s4o.print(TEMP_VAR);
          PARAM_NAME->accept(*this);
          s4o.print(" = ");
          print_check_function(PARAM_TYPE, PARAM_VALUE);
          s4o.print(";\n");
		}
	  }

	  s4o.print(s4o.indent_spaces + INLINE_RESULT_TEMP_VAR),
			  s4o.print(" = ");
	  function_name->accept(*this);
	  if (function_type_suffix)
        function_type_suffix->accept(*this);
	  s4o.print("(");
	  s4o.indent_right();

	  PARAM_LIST_ITERATOR() {
		if (pt != param_list.begin())
		  s4o.print(",\n" + s4o.indent_spaces);
		if (PARAM_DIRECTION == function_param_iterator_c::direction_in)
		  PARAM_NAME->accept(*this);
		else if (PARAM_VALUE != NULL){
          s4o.print("&");
          s4o.print(TEMP_VAR);
          PARAM_NAME->accept(*this);
        }
		else {
		  s4o.print("NULL");
		}
	  }
	  s4o.print(");\n");
	  s4o.indent_left();

	  PARAM_LIST_ITERATOR() {
        if ((PARAM_DIRECTION == function_param_iterator_c::direction_out ||
        	 PARAM_DIRECTION == function_param_iterator_c::direction_inout) &&
        	PARAM_VALUE != NULL) {

          s4o.print(s4o.indent_spaces);
          print_setter(PARAM_VALUE, PARAM_TYPE, PARAM_NAME);
          s4o.print(";\n");
		}
	  }
	  s4o.print(s4o.indent_spaces + "return ");
	  s4o.print(INLINE_RESULT_TEMP_VAR);
	  s4o.print(";\n");

      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "}\n\n");
    }

  private:

    /* A helper function... */
	void CMP_operator_result_type() {
	  /* the data type resulting from this operation... */
	  this->default_variable_name.current_type = &(this->bool_type);
	}

	/* A helper function... */
    void BYTE_operator_result_type(void) {
	  if (search_expression_type->is_literal_integer_type(this->default_variable_name.current_type)) {
		if (search_expression_type->is_literal_integer_type(this->current_operand_type))
		  this->default_variable_name.current_type = &(this->lword_type);
		else
		  this->default_variable_name.current_type = this->current_operand_type;
	  }
	  else if (search_expression_type->is_literal_integer_type(this->current_operand_type))
		  this->current_operand_type = this->default_variable_name.current_type;
	}

    /* A helper function... */
    void NUM_operator_result_type(void) {
	  if (search_expression_type->is_literal_real_type(this->default_variable_name.current_type)) {
		if (search_expression_type->is_literal_integer_type(this->current_operand_type) ||
			search_expression_type->is_literal_real_type(this->current_operand_type))
		  this->default_variable_name.current_type = &(this->lreal_type);
		else
		  this->default_variable_name.current_type = this->current_operand_type;
	  }
	  else if (search_expression_type->is_literal_integer_type(this->default_variable_name.current_type)) {
		if (search_expression_type->is_literal_integer_type(this->current_operand_type))
		  this->default_variable_name.current_type = &(this->lint_type);
		else if (search_expression_type->is_literal_real_type(this->current_operand_type))
		  this->default_variable_name.current_type = &(this->lreal_type);
		else
		  this->default_variable_name.current_type = this->current_operand_type;
	  }
	  else if (search_expression_type->is_literal_integer_type(this->current_operand_type) ||
			   search_expression_type->is_literal_real_type(this->current_operand_type))
		this->current_operand_type = this->default_variable_name.current_type;
	}

    void *print_getter(symbol_c *symbol) {
      unsigned int vartype = search_varfb_instance_type->get_vartype(symbol);
      if (vartype == search_var_instance_decl_c::external_vt)
    	s4o.print(GET_EXTERNAL);
      else if (vartype == search_var_instance_decl_c::located_vt)
    	s4o.print(GET_LOCATED);
      else
    	s4o.print(GET_VAR);
      s4o.print("(");

      wanted_variablegeneration = complextype_base_vg;
      symbol->accept(*this);
      if (search_varfb_instance_type->type_is_complex())
    	s4o.print(",");
      wanted_variablegeneration = complextype_suffix_vg;
      symbol->accept(*this);
      s4o.print(")");
      wanted_variablegeneration = expression_vg;
      return NULL;
    }

    void *print_setter(symbol_c* symbol,
    		symbol_c* type,
    		symbol_c* value) {
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

      wanted_variablegeneration = complextype_base_vg;
      symbol->accept(*this);
      s4o.print(",");
      wanted_variablegeneration = expression_vg;
      print_check_function(type, value, NULL, true);
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
      s4o.print(GET_LOCATED);
      s4o.print("(");
      this->print_variable_prefix();
      s4o.printlocation(symbol->value + 1);
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

          current_array_type = search_varfb_instance_type->get_type_id(symbol->subscripted_variable);
          if (current_array_type == NULL) ERROR;

          s4o.print(".table");
          symbol->subscript_list->accept(*this);

          current_array_type = NULL;
          break;
        default:
          print_getter(symbol);
          break;
      }
      return NULL;
    }

    /****************************************/
    /* B.2 - Language IL (Instruction List) */
    /****************************************/

    /***********************************/
    /* B 2.1 Instructions and Operands */
    /***********************************/

    /* | label ':' [il_incomplete_instruction] eol_list */
    // SYM_REF2(il_instruction_c, label, il_instruction)
    void *visit(il_instruction_c *symbol) {
      if (NULL != symbol->il_instruction) {
        symbol->il_instruction->accept(*this);
      }
      return NULL;
    }
    /* | il_simple_operator [il_operand] */
    //SYM_REF2(il_simple_operation_c, il_simple_operator, il_operand)
    void *visit(il_simple_operation_c *symbol) {
      this->current_operand = symbol->il_operand;
      if (NULL == this->current_operand) {
        this->current_operand_type = NULL;
      } else {
        this->current_operand_type = search_expression_type->get_type(this->current_operand);
        if (NULL == this->current_operand_type) ERROR;
      }

      symbol->il_simple_operator->accept(*this);

      this->current_operand = NULL;
      this->current_operand_type = NULL;
      return NULL;
    }

    void *visit(il_function_call_c *symbol) {
      symbol_c* function_type_prefix = NULL;
      symbol_c* function_name = NULL;
      symbol_c* function_type_suffix = NULL;
      DECLARE_PARAM_LIST()

      symbol_c *param_data_type = default_variable_name.current_type;

      function_call_param_iterator_c function_call_param_iterator(symbol);

      function_declaration_c *f_decl = function_symtable.find_value(symbol->function_name);
	  if (f_decl == function_symtable.end_value()) {
        function_type_t current_function_type = get_function_type((identifier_c *)symbol->function_name);
        if (current_function_type == function_none) ERROR;

        function_type_prefix = (symbol_c *)search_expression_type->compute_standard_function_il(symbol, param_data_type);

        symbol_c *en_param_name = (symbol_c *)(new identifier_c("EN"));
        /* Add the value from EN param */
        ADD_PARAM_LIST(en_param_name,
                       (symbol_c*)(new boolean_literal_c((symbol_c*)(new bool_type_name_c()), new boolean_true_c())),
                       (symbol_c*)(new bool_type_name_c()),
                       function_param_iterator_c::direction_in)

        symbol_c *eno_param_name = (symbol_c *)(new identifier_c("ENO"));
        /* Add the value from ENO param */
        ADD_PARAM_LIST(eno_param_name, NULL, (symbol_c*)(new bool_type_name_c()), function_param_iterator_c::direction_out)

        int nb_param = 1;
        if (symbol->il_operand_list != NULL)
          nb_param += ((list_c *)symbol->il_operand_list)->n;

        #include "il_code_gen.c"

      }
	  else {
		function_name = symbol->function_name;

		/* determine the base data type returned by the function being called... */
		search_base_type_c search_base_type;
		function_type_prefix = (symbol_c *)f_decl->type_name->accept(search_base_type);

		/* loop through each function parameter, find the value we should pass
		 * to it, and then output the c equivalent...
		 */

		function_param_iterator_c fp_iterator(f_decl);
		identifier_c *param_name;
		for(int i = 1; (param_name = fp_iterator.next()) != NULL; i++) {
		  symbol_c *param_type = fp_iterator.param_type();
		  if (param_type == NULL) ERROR;

		  function_param_iterator_c::param_direction_t param_direction = fp_iterator.param_direction();

		  symbol_c *param_value = NULL;

		  /* if it is the first parameter, semantics specifies that we should
		   * get the value off the IL default variable!
		   */
		  if (1 == i)
		    param_value = &this->default_variable_name;

		  /* Get the value from a foo(<param_name> = <param_value>) style call */
		  /* NOTE: the following line of code is not required in this case, but it doesn't
		   * harm to leave it in, as in the case of a non-formal syntax function call,
		   * it will always return NULL.
		   * We leave it in in case we later decide to merge this part of the code together
		   * with the function calling code in generate_c_st_c, which does require
		   * the following line...
		   */
		  if (param_value == NULL)
			param_value = function_call_param_iterator.search_f(param_name);

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

		  ADD_PARAM_LIST(param_name, param_value, param_type, fp_iterator.param_direction())
		} /* for(...) */
	  }

	  if (function_call_param_iterator.next_nf() != NULL) ERROR;
      if (NULL == function_type_prefix) ERROR;

      bool has_output_params = false;

      PARAM_LIST_ITERATOR() {
        if ((PARAM_DIRECTION == function_param_iterator_c::direction_out ||
             PARAM_DIRECTION == function_param_iterator_c::direction_inout) &&
             PARAM_VALUE != NULL) {
          has_output_params = true;
        }
      }

      if (has_output_params)
        generate_inline(function_name, function_type_prefix, function_type_suffix, param_list);

      CLEAR_PARAM_LIST()

      /* the data type resulting from this operation... */
      default_variable_name.current_type = function_type_prefix;
      return NULL;
    }

    /* | il_expr_operator '(' [il_operand] eol_list [simple_instr_list] ')' */
    //SYM_REF4(il_expression_c, il_expr_operator, il_operand, simple_instr_list, unused)
    void *visit(il_expression_c *symbol) {
      /* We will be recursevely interpreting an instruction list,
       * so we store a backup of the data type of the value currently stored
       * in the default variable, and set the current data type to NULL
       */
      symbol_c *old_current_default_variable_data_type = this->default_variable_name.current_type;
      this->default_variable_name.current_type = NULL;

     /* Pass the symbol->il_operand to the simple_instr_list visitor
      * using the il_default_variable_init_value parameter...
      * Note that the simple_instr_list_c visitor will set this parameter
      * to NULL as soon as it does not require it any longer,
      * so we don't do it here again after the
      *   symbol->simple_instr_list->accept(*this);
      * returns...
      */
      this->il_default_variable_init_value = symbol->il_operand;

      /* Now do the parenthesised instructions... */
      /* NOTE: the following code line will get the variable
       * this->default_variable_name.current_type updated!
       */
      symbol->simple_instr_list->accept(*this);

      /* Now do the operation, using the previous result! */
      /* NOTE: The result of the previous instruction list will be stored
       * in a variable named IL_DEFVAR_BACK. This is done in the visitor
       * to instruction_list_c objects...
       */
      this->current_operand = &(this->default_variable_back_name);
      this->current_operand_type = this->default_variable_back_name.current_type;

      this->default_variable_name.current_type = old_current_default_variable_data_type;
      if (NULL == this->current_operand_type) ERROR;

      symbol->il_expr_operator->accept(*this);

      this->current_operand = NULL;
      this->current_operand_type = NULL;
      this->default_variable_back_name.current_type = NULL;
      return NULL;
    }

    /* | function_name '(' eol_list [il_param_list] ')' */
    // SYM_REF2(il_formal_funct_call_c, function_name, il_param_list)
    void *visit(il_formal_funct_call_c *symbol) {
      symbol_c* function_type_prefix = NULL;
      symbol_c* function_name = NULL;
      symbol_c* function_type_suffix = NULL;
      DECLARE_PARAM_LIST()

      function_call_param_iterator_c function_call_param_iterator(symbol);

      function_declaration_c *f_decl = function_symtable.find_value(symbol->function_name);
      if (f_decl == function_symtable.end_value()) {
        function_type_t current_function_type = get_function_type((identifier_c *)symbol->function_name);
        if (current_function_type == function_none) ERROR;

        function_type_prefix = (symbol_c *)search_expression_type->compute_standard_function_default(NULL, symbol);

        int nb_param = 0;
        if (symbol->il_param_list != NULL)
          nb_param += ((list_c *)symbol->il_param_list)->n;

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

		/* determine the base data type returned by the function being called... */
		search_base_type_c search_base_type;
		function_type_prefix = (symbol_c *)f_decl->type_name->accept(search_base_type);

		/* loop through each function parameter, find the value we should pass
		 * to it, and then output the c equivalent...
		 */

		function_param_iterator_c fp_iterator(f_decl);
		identifier_c *param_name;
		for(int i = 1; (param_name = fp_iterator.next()) != NULL; i++) {
		  symbol_c *param_type = fp_iterator.param_type();
		  if (param_type == NULL) ERROR;

		  function_param_iterator_c::param_direction_t param_direction = fp_iterator.param_direction();


		  symbol_c *param_value = NULL;

		  /* Get the value from a foo(<param_name> = <param_value>) style call */
		  if (param_value == NULL)
			param_value = function_call_param_iterator.search_f(param_name);

		  /* Get the value from a foo(<param_value>) style call */
		  /* NOTE: the following line of code is not required in this case, but it doesn't
		   * harm to leave it in, as in the case of a formal syntax function call,
		   * it will always return NULL.
		   * We leave it in in case we later decide to merge this part of the code together
		   * with the function calling code in generate_c_st_c, which does require
		   * the following line...
		   */
		  if (param_value == NULL) {
            param_value = function_call_param_iterator.next_nf();
            if (param_value != NULL && fp_iterator.is_en_eno_param_implicit()) ERROR;
          }

		  if (param_value == NULL) {
			/* No value given for parameter, so we must use the default... */
			/* First check whether default value specified in function declaration...*/
			param_value = fp_iterator.default_value();
		  }

		  ADD_PARAM_LIST(param_name, param_value, param_type, fp_iterator.param_direction())
		}
      }

      if (function_call_param_iterator.next_nf() != NULL) ERROR;
      if (NULL == function_type_prefix) ERROR;

      bool has_output_params = false;

      PARAM_LIST_ITERATOR() {
        if ((PARAM_DIRECTION == function_param_iterator_c::direction_out ||
             PARAM_DIRECTION == function_param_iterator_c::direction_inout) &&
             PARAM_VALUE != NULL) {
          has_output_params = true;
        }
      }

      if (has_output_params)
        generate_inline(function_name, function_type_prefix, function_type_suffix, param_list);

      CLEAR_PARAM_LIST()

      /* the data type resulting from this operation... */
      default_variable_name.current_type = function_type_prefix;
      return NULL;
    }

    /* | simple_instr_list il_simple_instruction */
    // SYM_LIST(simple_instr_list_c)
    void *visit(simple_instr_list_c *symbol) {
      /* Check whether we should initiliase the il default variable... */
      if (NULL != this->il_default_variable_init_value) {
        /* Yes, we must... */
        /* We will do it by instatiating a LD operator, and having this
         * same generate_c_il_c class visiting it!
         */
        LD_operator_c ld_oper;
        il_simple_operation_c il_simple_oper(&ld_oper, this->il_default_variable_init_value);

        il_simple_oper.accept(*this);
      }

      /* this parameter no longer required... */
      this->il_default_variable_init_value = NULL;

      iterator_visitor_c::visit(symbol);

      /* copy the result in the default variable to the variable
	   * used to pass the data out to the scope enclosing
	   * the current scope!
	   *
	   * We also need to update the data type currently stored within
	   * the variable used to pass the data to the outside scope...
	   */
	  this->default_variable_back_name.current_type = this->default_variable_name.current_type;
	  return NULL;
    }

    void *visit(LD_operator_c *symbol)	{
      /* the data type resulting from this operation... */
      this->default_variable_name.current_type = this->current_operand_type;
      return NULL;
    }

    void *visit(LDN_operator_c *symbol)	{
      /* the data type resulting from this operation... */
      this->default_variable_name.current_type = this->current_operand_type;
      return NULL;
    }

    void *visit(ADD_operator_c *symbol)	{
      if (search_expression_type->is_time_type(this->default_variable_name.current_type) &&
          search_expression_type->is_time_type(this->current_operand_type)) {
        /* the data type resulting from this operation... */
        this->default_variable_name.current_type = this->current_operand_type;
      }
      else if (search_expression_type->is_num_type(this->default_variable_name.current_type) &&
          search_expression_type->is_same_type(this->default_variable_name.current_type, this->current_operand_type)) {
        NUM_operator_result_type();
      }
      else {ERROR;}
      return NULL;
    }

    void *visit(SUB_operator_c *symbol)	{
      if (search_expression_type->is_time_type(this->default_variable_name.current_type) &&
          search_expression_type->is_time_type(this->current_operand_type)) {
        /* the data type resulting from this operation... */
        this->default_variable_name.current_type = this->current_operand_type;
      }
      else if (search_expression_type->is_num_type(this->default_variable_name.current_type) &&
          search_expression_type->is_same_type(this->default_variable_name.current_type, this->current_operand_type)) {
    	NUM_operator_result_type();
      }
      else {ERROR;}
      return NULL;
    }

    void *visit(MUL_operator_c *symbol)	{
      if (search_expression_type->is_time_type(this->default_variable_name.current_type) &&
          search_expression_type->is_integer_type(this->current_operand_type)) {
        /* the data type resulting from this operation is unchanged! */
      }
      else if (search_expression_type->is_num_type(this->default_variable_name.current_type) &&
          search_expression_type->is_same_type(this->default_variable_name.current_type, this->current_operand_type)) {
    	NUM_operator_result_type();
      }
      else {ERROR;}
      return NULL;
    }

    void *visit(DIV_operator_c *symbol)	{
      if (search_expression_type->is_time_type(this->default_variable_name.current_type) &&
          search_expression_type->is_integer_type(this->current_operand_type)) {
        /* the data type resulting from this operation is unchanged! */
      }
      else if (search_expression_type->is_num_type(this->default_variable_name.current_type) &&
          search_expression_type->is_same_type(this->default_variable_name.current_type, this->current_operand_type)) {
        NUM_operator_result_type();
      }
      else {ERROR;}
      return NULL;
    }

    void *visit(MOD_operator_c *symbol)	{
      if (search_expression_type->is_num_type(this->default_variable_name.current_type) &&
          search_expression_type->is_same_type(this->default_variable_name.current_type, this->current_operand_type)) {
        NUM_operator_result_type();
      }
      else {ERROR;}
      return NULL;
    }

    void *visit(GT_operator_c *symbol)	{
      if (!search_base_type.type_is_enumerated(this->default_variable_name.current_type) &&
          search_expression_type->is_same_type(this->default_variable_name.current_type, this->current_operand_type)) {
        CMP_operator_result_type();
      }
      else {ERROR;}
      return NULL;
    }

    void *visit(GE_operator_c *symbol)	{
      if (!search_base_type.type_is_enumerated(this->default_variable_name.current_type) &&
          search_expression_type->is_same_type(this->default_variable_name.current_type, this->current_operand_type)) {
        CMP_operator_result_type();
      }
      else {ERROR;}
      return NULL;
    }

    void *visit(EQ_operator_c *symbol)	{
      if (search_expression_type->is_same_type(this->default_variable_name.current_type, this->current_operand_type)) {
        CMP_operator_result_type();
      }
      else {ERROR;}
      return NULL;
    }

    void *visit(LT_operator_c *symbol)	{
      if (!search_base_type.type_is_enumerated(this->default_variable_name.current_type) &&
          search_expression_type->is_same_type(this->default_variable_name.current_type, this->current_operand_type)) {
        CMP_operator_result_type();
      }
      else {ERROR;}
      return NULL;
    }

    void *visit(LE_operator_c *symbol)	{
      if (!search_base_type.type_is_enumerated(this->default_variable_name.current_type) &&
          search_expression_type->is_same_type(this->default_variable_name.current_type, this->current_operand_type)) {
        CMP_operator_result_type();
      }
      else {ERROR;}
      return NULL;
    }

    void *visit(NE_operator_c *symbol)	{
      if (search_expression_type->is_same_type(this->default_variable_name.current_type, this->current_operand_type)) {
        CMP_operator_result_type();
      }
      else {ERROR;}
      return NULL;
    }

    /***************************************/
    /* B.3 - Language ST (Structured Text) */
    /***************************************/
    /***********************/
    /* B 3.1 - Expressions */
    /***********************/

    void *visit(statement_list_c *symbol) {
	  function_call_iterator_c fc_iterator(symbol);
	  symbol_c* function_call;
	  while ((function_call = fc_iterator.next()) != NULL) {
		function_call->accept(*this);
	  }
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

        function_type_prefix = search_expression_type->get_type(symbol);

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

	    /* determine the base data type returned by the function being called... */
		search_base_type_c search_base_type;
		function_type_prefix = (symbol_c *)f_decl->type_name->accept(search_base_type);

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
      if (NULL == function_type_prefix) ERROR;

	  bool has_output_params = false;

	  PARAM_LIST_ITERATOR() {
        if ((PARAM_DIRECTION == function_param_iterator_c::direction_out ||
             PARAM_DIRECTION == function_param_iterator_c::direction_inout) &&
             PARAM_VALUE != NULL) {
          has_output_params = true;
        }
      }

      if (has_output_params)
        generate_inline(function_name, function_type_prefix, function_type_suffix, param_list);

      CLEAR_PARAM_LIST()

      return NULL;
    }

};  /* generate_c_inlinefcall_c */


