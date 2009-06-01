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


/* Determine the data type on which another data type is based on.
 * If a new default initial value is given, we DO NOT consider it a
 * new base class, and continue looking further!
 *
 * E.g. TYPE new_int_t : INT; END_TYPE;
 *      TYPE new_int2_t : INT = 2; END_TYPE;
 *      TYPE new_subr_t : INT (4..5); END_TYPE;
 *
 *    new_int_t is really an INT!!
 *    new_int2_t is also really an INT!!
 *    new_subr_t is also really an INT!!
 */


class search_base_type_c: public null_visitor_c {

  private:
    symbol_c *current_type_name;
    bool is_subrange;
    bool is_enumerated;

  public:
    search_base_type_c(void);

  public:
    void *visit(identifier_c *type_name);
    bool type_is_subrange(symbol_c* type_decl);
    bool type_is_enumerated(symbol_c* type_decl);

  public:
  /***********************************/
  /* B 1.3.1 - Elementary Data Types */
  /***********************************/
    void *visit(time_type_name_c *symbol);
    void *visit(bool_type_name_c *symbol);
    void *visit(sint_type_name_c *symbol);
    void *visit(int_type_name_c *symbol);
    void *visit(dint_type_name_c *symbol);
    void *visit(lint_type_name_c *symbol);
    void *visit(usint_type_name_c *symbol);
    void *visit(uint_type_name_c *symbol);
    void *visit(udint_type_name_c *symbol);
    void *visit(ulint_type_name_c *symbol);
    void *visit(real_type_name_c *symbol);
    void *visit(lreal_type_name_c *symbol);
    void *visit(date_type_name_c *symbol);
    void *visit(tod_type_name_c *symbol);
    void *visit(dt_type_name_c *symbol)	;
    void *visit(byte_type_name_c *symbol);
    void *visit(word_type_name_c *symbol);
    void *visit(dword_type_name_c *symbol);
    void *visit(lword_type_name_c *symbol);
    void *visit(string_type_name_c *symbol);
    void *visit(wstring_type_name_c *symbol);
    void *visit(constant_int_type_name_c *symbol);
    void *visit(constant_real_type_name_c *symbol);
    void *visit(direct_variable_type_name_c *symbol);

    /******************************************************/
    /* Extensions to the base standard as defined in      */
    /* "Safety Software Technical Specification,          */
    /*  Part 1: Concepts and Function Blocks,             */
    /*  Version 1.0 – Official Release"                   */
    /* by PLCopen - Technical Committee 5 - 2006-01-31    */
    /******************************************************/
    void *visit(safebool_type_name_c *symbol);

  /********************************/
  /* B 1.3.3 - Derived data types */
  /********************************/
  /*  simple_type_name ':' simple_spec_init */
    void *visit(simple_type_declaration_c *symbol);
  /* simple_specification ASSIGN constant */
    void *visit(simple_spec_init_c *symbol);
  /*  subrange_type_name ':' subrange_spec_init */
    void *visit(subrange_type_declaration_c *symbol);
  /* subrange_specification ASSIGN signed_integer */
    void *visit(subrange_spec_init_c *symbol);
  /*  integer_type_name '(' subrange')' */
    void *visit(subrange_specification_c *symbol);
  /*  signed_integer DOTDOT signed_integer */
    void *visit(subrange_c *symbol);

  /*  enumerated_type_name ':' enumerated_spec_init */
    void *visit(enumerated_type_declaration_c *symbol);
  /* enumerated_specification ASSIGN enumerated_value */
    void *visit(enumerated_spec_init_c *symbol);
  /* helper symbol for enumerated_specification->enumerated_spec_init */
  /* enumerated_value_list ',' enumerated_value */
    void *visit(enumerated_value_list_c *symbol);
  /* enumerated_type_name '#' identifier */
  // SYM_REF2(enumerated_value_c, type, value)
    void *visit(enumerated_value_c *symbol);
  /*  identifier ':' array_spec_init */
    void *visit(array_type_declaration_c *symbol);
  /* array_specification [ASSIGN array_initialization} */
  /* array_initialization may be NULL ! */
    void *visit(array_spec_init_c *symbol);
  /* ARRAY '[' array_subrange_list ']' OF non_generic_type_name */
    void *visit(array_specification_c *symbol);
  /* helper symbol for array_specification */
  /* array_subrange_list ',' subrange */
    void *visit(array_subrange_list_c *symbol);
  /* array_initialization:  '[' array_initial_elements_list ']' */
  /* helper symbol for array_initialization */
  /* array_initial_elements_list ',' array_initial_elements */
    void *visit(array_initial_elements_list_c *symbol);
  /* integer '(' [array_initial_element] ')' */
  /* array_initial_element may be NULL ! */
    void *visit(array_initial_elements_c *symbol);
  /*  structure_type_name ':' structure_specification */
      /* NOTE: structure_specification will point to either a
       *       initialized_structure_c
       *       OR A
       *       structure_element_declaration_list_c
       */
    void *visit(structure_type_declaration_c *symbol);
  /* structure_type_name ASSIGN structure_initialization */
  /* structure_initialization may be NULL ! */
    void *visit(initialized_structure_c *symbol);
  /* helper symbol for structure_declaration */
  /* structure_declaration:  STRUCT structure_element_declaration_list END_STRUCT */
  /* structure_element_declaration_list structure_element_declaration ';' */
    void *visit(structure_element_declaration_list_c *symbol);
  /*  structure_element_name ':' *_spec_init */
    void *visit(structure_element_declaration_c *symbol);
  /* helper symbol for structure_initialization */
  /* structure_initialization: '(' structure_element_initialization_list ')' */
  /* structure_element_initialization_list ',' structure_element_initialization */
    void *visit(structure_element_initialization_list_c *symbol);
  /*  structure_element_name ASSIGN value */
    void *visit(structure_element_initialization_c *symbol);
  /*  string_type_name ':' elementary_string_type_name string_type_declaration_size string_type_declaration_init */
  /*
  SYM_REF4(string_type_declaration_c,	string_type_name,
  					elementary_string_type_name,
  					string_type_declaration_size,
  					string_type_declaration_init) // may be == NULL!
  */
    void *visit(string_type_declaration_c *symbol);
}; // search_base_type_c




