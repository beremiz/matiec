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
 * Conversion of type declaration constructs.
 *
 * This is part of the 4th stage that generates
 * a c++ source program equivalent to the IL and ST
 * code.
 */






//#include <stdio.h>  /* required for NULL */
//#include <string>
//#include <iostream>

//#include "../../util/symtable.hh"





class generate_c_typedecl_c: public generate_c_base_c {

  public:
    generate_c_typedecl_c(stage4out_c *s4o_ptr): generate_c_base_c(s4o_ptr) {}
    ~generate_c_typedecl_c(void) {}


/***************************/
/* B 0 - Programming Model */
/***************************/
  /* leave for derived classes... */

/*************************/
/* B.1 - Common elements */
/*************************/
/*******************************************/
/* B 1.1 - Letters, digits and identifiers */
/*******************************************/
  /* done in base class(es) */

/*********************/
/* B 1.2 - Constants */
/*********************/
  /* originally empty... */

/******************************/
/* B 1.2.1 - Numeric Literals */
/******************************/
  /* done in base class(es) */

/*******************************/
/* B.1.2.2   Character Strings */
/*******************************/
  /* done in base class(es) */

/***************************/
/* B 1.2.3 - Time Literals */
/***************************/
/************************/
/* B 1.2.3.1 - Duration */
/************************/
  /* done in base class(es) */

/************************************/
/* B 1.2.3.2 - Time of day and Date */
/************************************/
  /* done in base class(es) */

/**********************/
/* B.1.3 - Data types */
/**********************/
/***********************************/
/* B 1.3.1 - Elementary Data Types */
/***********************************/
  /* done in base class(es) */

/********************************/
/* B.1.3.2 - Generic data types */
/********************************/
  /* originally empty... */

/********************************/
/* B 1.3.3 - Derived data types */
/********************************/
void *visit(subrange_spec_init_c *symbol) {
  TRACE("subrange_spec_init_c");
  // TODO...
  ERROR;
  return NULL;
}

void *visit(enumerated_spec_init_c *symbol) {
  TRACE("enumerated_spec_init_c");
  // TODO...
  ERROR;
  return NULL;
}

/*  TYPE type_declaration_list END_TYPE */
void *visit(data_type_declaration_c *symbol) {
  TRACE("data_type_declaration_c");
  symbol->type_declaration_list->accept(*this);
  s4o.print("\n\n");
  return NULL;
}

/* helper symbol for data_type_declaration */
void *visit(type_declaration_list_c *symbol) {
  TRACE("type_declaration_list_c");
  return print_list(symbol);
}

/*  simple_type_name ':' simple_spec_init */
void *visit(simple_type_declaration_c *symbol) {
  TRACE("simple_type_declaration_c");
  /* add this type declaration to the type symbol table... */
  type_symtable.insert(symbol->simple_type_name, symbol->simple_spec_init);

  s4o.print("typedef ");
  symbol->simple_spec_init->accept(*this);
  s4o.print(" ");
  symbol->simple_type_name->accept(*this);
  s4o.print(";\n");
  return NULL;
}

/* simple_specification [ASSIGN constant] */
//SYM_REF2(simple_spec_init_c, simple_specification, constant)
// <constant> may be NULL
void *visit(simple_spec_init_c *symbol) {
  TRACE("simple_spec_init_c");
  symbol->simple_specification->accept(*this);
  return NULL;
}

#if 0
/*  subrange_type_name ':' subrange_spec_init */
SYM_REF2(subrange_type_declaration_c, subrange_type_name, subrange_spec_init)

/* subrange_specification ASSIGN signed_integer */
SYM_REF2(subrange_spec_init_c, subrange_specification, signed_integer)

/*  integer_type_name '(' subrange')' */
SYM_REF2(subrange_specification_c, integer_type_name, subrange)

/*  signed_integer DOTDOT signed_integer */
SYM_REF2(subrange_c, lower_limit, upper_limit)

/*  enumerated_type_name ':' enumerated_spec_init */
SYM_REF2(enumerated_type_declaration_c, enumerated_type_name, enumerated_spec_init)

/* enumerated_specification ASSIGN enumerated_value */
SYM_REF2(enumerated_spec_init_c, enumerated_specification, enumerated_value)

/* helper symbol for enumerated_specification->enumerated_spec_init */
/* enumerated_value_list ',' enumerated_value */
SYM_LIST(enumerated_value_list_c)

/* enumerated_type_name '#' identifier */
SYM_REF2(enumerated_value_c, type, value)

/*  identifier ':' array_spec_init */
SYM_REF2(array_type_declaration_c, identifier, array_spec_init)

/* array_specification [ASSIGN array_initialization} */
/* array_initialization may be NULL ! */
SYM_REF2(array_spec_init_c, array_specification, array_initialization)

/* ARRAY '[' array_subrange_list ']' OF non_generic_type_name */
SYM_REF2(array_specification_c, array_subrange_list, non_generic_type_name)

/* helper symbol for array_specification */
/* array_subrange_list ',' subrange */
SYM_LIST(array_subrange_list_c)

/* array_initialization:  '[' array_initial_elements_list ']' */
/* helper symbol for array_initialization */
/* array_initial_elements_list ',' array_initial_elements */
SYM_LIST(array_initial_elements_list_c)

/* integer '(' [array_initial_element] ')' */
/* array_initial_element may be NULL ! */
SYM_REF2(array_initial_elements_c, integer, array_initial_element)
#endif

/*  structure_type_name ':' structure_specification */
//SYM_REF2(structure_type_declaration_c, structure_type_name, structure_specification)
void *visit(structure_type_declaration_c *symbol) {
  TRACE("structure_type_declaration_c");
  /* add this type declaration to the type symbol table... */
  type_symtable.insert(symbol->structure_type_name, symbol->structure_specification);

  s4o.print("typedef ");
  symbol->structure_specification->accept(*this);
  s4o.print(" ");
  symbol->structure_type_name->accept(*this);
  s4o.print(";\n");
  return NULL;
}

/* structure_type_name ASSIGN structure_initialization */
/* structure_initialization may be NULL ! */
//SYM_REF2(initialized_structure_c, structure_type_name, structure_initialization)
void *visit(initialized_structure_c *symbol) {
  TRACE("initialized_structure_c");
  symbol->structure_type_name->accept(*this);
  return NULL;
}

/* helper symbol for structure_declaration */
/* structure_declaration:  STRUCT structure_element_declaration_list END_STRUCT */
/* structure_element_declaration_list structure_element_declaration ';' */
//SYM_LIST(structure_element_declaration_list_c)
void *visit(structure_element_declaration_list_c *symbol) {
  TRACE("structure_element_declaration_list_c");
  s4o.print("struct {\n");
  s4o.indent_right();
  s4o.print(s4o.indent_spaces);

  print_list(symbol);

  s4o.indent_left();
  s4o.print(s4o.indent_spaces);
  s4o.print("}");
  return NULL;
}

/*  structure_element_name ':' spec_init */
//SYM_REF2(structure_element_declaration_c, structure_element_name, spec_init)
void *visit(structure_element_declaration_c *symbol) {
  TRACE("structure_element_declaration_c");

  symbol->spec_init->accept(*this);
  s4o.print(" ");
  symbol->structure_element_name->accept(*this);
  s4o.print(";\n");
  s4o.print(s4o.indent_spaces);

  return NULL;
}

/* helper symbol for structure_initialization */
/* structure_initialization: '(' structure_element_initialization_list ')' */
/* structure_element_initialization_list ',' structure_element_initialization */
//SYM_LIST(structure_element_initialization_list_c)
void *visit(structure_element_initialization_list_c *symbol) {
  TRACE("structure_element_initialization_list_c");

  // TODO ???
  ERROR;
  return NULL;
}

/*  structure_element_name ASSIGN value */
//SYM_REF2(structure_element_initialization_c, structure_element_name, value)
void *visit(structure_element_initialization_c *symbol) {
  TRACE("structure_element_initialization_c");

  // TODO ???
  ERROR;
  return NULL;
}

#if 0
/*  string_type_name ':' elementary_string_type_name string_type_declaration_size string_type_declaration_init */
/*
 * NOTE:
 * (Summary: Contrary to what is expected, the
 *           string_type_declaration_c is not used to store
 *           simple string type declarations that do not include
 *           size limits.
 *           For e.g.:
 *             str1_type: STRING := "hello!"
 *           will be stored in a simple_type_declaration_c
 *           instead of a string_type_declaration_c.
 *           The following:
 *             str2_type: STRING [64] := "hello!"
 *           will be stored in a sring_type_declaration_c
 *
 *           Read on for why this is done...
 * End Summary)
 *
 * According to the spec, the valid construct
 * TYPE new_str_type : STRING := "hello!"; END_TYPE
 * has two possible routes to type_declaration...
 *
 * Route 1:
 * type_declaration: single_element_type_declaration
 * single_element_type_declaration: simple_type_declaration
 * simple_type_declaration: identifier ':' simple_spec_init
 * simple_spec_init: simple_specification ASSIGN constant
 * (shift:  identifier <- 'new_str_type')
 * simple_specification: elementary_type_name
 * elementary_type_name: STRING
 * (shift: elementary_type_name <- STRING)
 * (reduce: simple_specification <- elementary_type_name)
 * (shift: constant <- "hello!")
 * (reduce: simple_spec_init: simple_specification ASSIGN constant)
 * (reduce: ...)
 *
 *
 * Route 2:
 * type_declaration: string_type_declaration
 * string_type_declaration: identifier ':' elementary_string_type_name string_type_declaration_size string_type_declaration_init
 * (shift:  identifier <- 'new_str_type')
 * elementary_string_type_name: STRING
 * (shift: elementary_string_type_name <- STRING)
 * (shift: string_type_declaration_size <-  empty )
 * string_type_declaration_init: ASSIGN character_string
 * (shift: character_string <- "hello!")
 * (reduce: string_type_declaration_init <- ASSIGN character_string)
 * (reduce: string_type_declaration <- identifier ':' elementary_string_type_name string_type_declaration_size string_type_declaration_init )
 * (reduce: type_declaration <- string_type_declaration)
 *
 *
 * At first glance it seems that removing route 1 would make
 * the most sense. Unfortunately the construct 'simple_spec_init'
 * shows up multiple times in other rules, so changing this construct
 * would also mean changing all the rules in which it appears.
 * I (Mario) therefore chose to remove route 2 instead. This means
 * that the above declaration gets stored in a
 * simple_type_declaration_c, and not in a string_type_declaration_c
 * as would be expected!
 */
/*  string_type_name ':' elementary_string_type_name string_type_declaration_size string_type_declaration_init */
SYM_REF4(string_type_declaration_c,	string_type_name,
					elementary_string_type_name,
					string_type_declaration_size,
					string_type_declaration_init) /* may be == NULL! */
#endif

/*********************/
/* B 1.4 - Variables */
/*********************/
  /* done in base class(es) */

/********************************************/
/* B.1.4.1   Directly Represented Variables */
/********************************************/
// direct_variable: direct_variable_token	{$$ = new direct_variable_c($1);};
void *visit(direct_variable_c *symbol) {
  TRACE("direct_variable_c");
  /* Do not use print_token() as it will change everything into uppercase */
  if (strlen(symbol->value) == 0) ERROR;
  return s4o.printlocation(symbol->value + 1);
}


/*************************************/
/* B.1.4.2   Multi-element Variables */
/*************************************/
  /* done in base class(es) */

/******************************************/
/* B 1.4.3 - Declaration & Initialisation */
/******************************************/
  /* leave for derived classes... */

/**************************************/
/* B.1.5 - Program organization units */
/**************************************/
/***********************/
/* B 1.5.1 - Functions */
/***********************/
  /* leave for derived classes... */

/*****************************/
/* B 1.5.2 - Function Blocks */
/*****************************/
  /* leave for derived classes... */

/**********************/
/* B 1.5.3 - Programs */
/**********************/
  /* leave for derived classes... */

/*********************************************/
/* B.1.6  Sequential function chart elements */
/*********************************************/

/********************************/
/* B 1.7 Configuration elements */
/********************************/
  /* leave for derived classes... */

/****************************************/
/* B.2 - Language IL (Instruction List) */
/****************************************/
/***********************************/
/* B 2.1 Instructions and Operands */
/***********************************/
  /* leave for derived classes... */

/*******************/
/* B 2.2 Operators */
/*******************/
  /* leave for derived classes... */


/***************************************/
/* B.3 - Language ST (Structured Text) */
/***************************************/
/***********************/
/* B 3.1 - Expressions */
/***********************/
  /* leave for derived classes... */

/********************/
/* B 3.2 Statements */
/********************/
  /* leave for derived classes... */

/*********************************/
/* B 3.2.1 Assignment Statements */
/*********************************/
  /* leave for derived classes... */

/*****************************************/
/* B 3.2.2 Subprogram Control Statements */
/*****************************************/
  /* leave for derived classes... */

/********************************/
/* B 3.2.3 Selection Statements */
/********************************/
  /* leave for derived classes... */

/********************************/
/* B 3.2.4 Iteration Statements */
/********************************/
  /* leave for derived classes... */




}; /* generate_c_typedecl_c */



