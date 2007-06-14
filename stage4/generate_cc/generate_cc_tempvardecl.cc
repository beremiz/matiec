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
 * Declare temporary variables to be later used as output parameters
 * in function calls for which not all output parameters were
 * defined in the original (st or il) source code.
 *
 * This is part of the 4th stage that generates
 * a c++ source program equivalent to the IL and ST
 * code.
 */




class temp_var_name_c {
  private:
    int counter;

  public:
    void reset(void) {counter = 0;}
    temp_var_name_c(void) {reset();}

  public:
    std::string *new_name(void) {
      std::string *new_str = new std::string(TEMP_VAR);
      /* yikes!!! How to convert an int to a string elegantly???
       * Right now I (Mario) can only think of snprintf()
       * C++ must have a more elegant method!
       */
      int int_str_size = snprintf(NULL, 0, "%d", counter);
      if (int_str_size <= 0) ERROR;
      char *int_str = (char *)malloc(int_str_size+1);
      if (snprintf(int_str, int_str_size+1, "%d", counter++) >= int_str_size+1) ERROR;
      *new_str += int_str;
      free(int_str);
      return new_str;
    }

};



/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/



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

class generate_cc_tempvardecl_c: generate_cc_typedecl_c {
  public:
    generate_cc_tempvardecl_c(stage4out_c *s4o_ptr): generate_cc_typedecl_c(s4o_ptr) {}

    void generate(symbol_c *body, temp_var_name_c *temp_var_name_factory) {
      temp_var_name_factory->reset();
      function_call_iterator_c fcall_iterator(body);
      for(symbol_c *finvocation = NULL; (finvocation = fcall_iterator.next()) != NULL;) {
        /* get the name of the next function that gets called */
        identifier_c *fcalled_name = fcall_iterator.fname();
        /* get that function's declaration... */
        function_declaration_c *fdecl = function_symtable.find_value(fcalled_name);
        if (fdecl == function_symtable.end_value()) {
          function_type_t function_type = get_function_type(fcalled_name);
          if (function_type == function_none) ERROR;
          return;
        }
        /* create iterator to iterate through each of the called function's parameters... */
        function_param_iterator_c fp_iterator(fdecl);

        /* iterate through each of the called function's parameters... */
        identifier_c *param_name = NULL;
        function_call_param_iterator_c function_call_param_iterator(finvocation);
        for(int i = 1; (param_name = fp_iterator.next()) != NULL; i++) {

          function_param_iterator_c::param_direction_t param_direction = fp_iterator.param_direction();
          if (param_direction == function_param_iterator_c::direction_in)
            /* ignore input only parameters...
             * we do not need to create temporary variables for these!
             */
            continue;

          /* Get the value from a foo(<param_name> = <param_value>) style call */
          symbol_c *param_value = function_call_param_iterator.search(param_name);

          /* Get the value from a foo(<param_value>) style call */
          if (param_value == NULL)
            param_value = function_call_param_iterator.next();

          if (param_value != NULL)
            /* ignore output parameters to which a variable is passed...
             * we do not need to create temporary variables for these!
             */
            continue;

          symbol_c *param_type = fp_iterator.param_type();

          /* get the parameter's default value */
          param_value = fp_iterator.default_value();

          /* If no default value specified in function declaration,
           * get the default value of this variable's type
           */
          if (param_value == NULL)
            param_value = (symbol_c *)param_type->accept(*type_initial_value_c::instance());
          if (param_value == NULL) ERROR;

          /* now declare a temporary variable, with the correct default value... */
          s4o.print(s4o.indent_spaces);
          param_type->accept(*this);
          s4o.print(" ");

          std::string *temp_var_name = temp_var_name_factory->new_name();
          s4o.print(*temp_var_name);
          delete temp_var_name;

          s4o.print(" = ");
          param_value->accept(*this);
          s4o.print(";\n");
        }
      }
      temp_var_name_factory->reset();
      s4o.print("\n");
    }
};
