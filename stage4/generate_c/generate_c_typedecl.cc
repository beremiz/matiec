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
#include <stdlib.h>

class generate_c_typedecl_c: public generate_c_base_c {

  protected:
    stage4out_c &s4o_incl;

  private:
    symbol_c* current_type_name;
    bool array_is_derived;
    search_base_type_c search_base_type;

    generate_c_base_c *basedecl;

  public:
    generate_c_typedecl_c(stage4out_c *s4o_ptr, stage4out_c *s4o_incl_ptr): generate_c_base_c(s4o_ptr), s4o_incl(*s4o_incl_ptr) {
      current_typedefinition = none_td;
      current_basetypedeclaration = none_bd;
      basedecl = new generate_c_base_c(&s4o_incl);
    }
    generate_c_typedecl_c(stage4out_c *s4o_ptr): generate_c_base_c(s4o_ptr), s4o_incl(*s4o_ptr) {
      current_typedefinition = none_td;
      current_basetypedeclaration = none_bd;
      basedecl = new generate_c_base_c(&s4o_incl);
    }
    ~generate_c_typedecl_c(void) {
      delete basedecl;
    }

    typedef enum {
      none_td,
      enumerated_td,
      subrange_td,
      array_td,
      struct_td,
    } typedefinition_t;

    typedefinition_t current_typedefinition;

    typedef enum {
      none_bd,
      subrangebasetype_bd,
      subrangetest_bd,
      arrayderiveddeclaration_bd,
      arraybasetype_bd,
      arraybasetypeincl_bd,
      arraysubrange_bd,
      arraytranslateindex_bd
    } basetypedeclaration_t;
    
    basetypedeclaration_t current_basetypedeclaration;

    int extract_integer(symbol_c *integer) {
      return atoi(((integer_c *)integer)->value);
    }

    void print_integer(unsigned int integer) {
      char str[10];
      sprintf(str, "%d", integer);
      s4o.print(str);
    }

    void print_integer_incl(unsigned int integer) {
      char str[10];
      sprintf(str, "%d", integer);
      s4o_incl.print(str);
    }

    void *print_list_incl(list_c *list,
         std::string pre_elem_str = "",
         std::string inter_elem_str = "",
         std::string post_elem_str = "",
         visitor_c *visitor = NULL) {
      if (visitor == NULL) visitor = this;

      if (list->n > 0) {
//std::cout << "generate_c_base_c::print_list(n = " << list->n << ")   000\n";
        s4o_incl.print(pre_elem_str);
        list->elements[0]->accept(*visitor);
      }

      for(int i = 1; i < list->n; i++) {
//std::cout << "generate_c_base_c::print_list   " << i << "\n";
        s4o_incl.print(inter_elem_str);
        list->elements[i]->accept(*visitor);
      }

      if (list->n > 0)
        s4o_incl.print(post_elem_str);

      return NULL;
    }


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
/*  subrange_type_name ':' subrange_spec_init */
void *visit(subrange_type_declaration_c *symbol) {
  TRACE("subrange_type_declaration_c");  
  
  current_typedefinition = subrange_td;

  s4o_incl.print("__DECLARE_DERIVED_TYPE(");
  current_basetypedeclaration = subrangebasetype_bd;
  symbol->subrange_spec_init->accept(*this);
  current_basetypedeclaration = none_bd;
  s4o_incl.print(",");
  symbol->subrange_type_name->accept(*basedecl);
  s4o_incl.print(")\n");
  
  current_type_name = symbol->subrange_type_name;
  
  current_basetypedeclaration = subrangetest_bd;
  symbol->subrange_spec_init->accept(*this);
  current_basetypedeclaration = none_bd;
  
  current_typedefinition = none_td;

  return NULL;
}

/* subrange_specification ASSIGN signed_integer */
void *visit(subrange_spec_init_c *symbol) {
  TRACE("subrange_spec_init_c");
  symbol->subrange_specification->accept(*this);
  return NULL;
}

/*  integer_type_name '(' subrange')' */
void *visit(subrange_specification_c *symbol) {
  if (current_typedefinition == subrange_td) {
    switch (current_basetypedeclaration) {
      case subrangebasetype_bd:
        symbol->integer_type_name->accept(*basedecl);
        break;
      case subrangetest_bd:
        if (symbol->subrange != NULL) {
          current_type_name->accept(*this);
          s4o.print(" __CHECK_");
          current_type_name->accept(*this);
          s4o.print("(");
          current_type_name->accept(*this);
          s4o.print(" value) {\n");
          s4o.indent_right();

          if (search_base_type.type_is_subrange(symbol->integer_type_name)) {
            s4o.print(s4o.indent_spaces + "value = __CHECK_");
            symbol->integer_type_name->accept(*this);
            s4o.print("(value);\n");
          }

          symbol->subrange->accept(*this);

          s4o.indent_left();
          s4o.print("}\n");
        }
        else {
          s4o.print("#define __CHECK_");
          current_type_name->accept(*this);
          s4o.print(" __CHECK_");
          symbol->integer_type_name->accept(*this);
          s4o.print("\n");
        }
        break;
      default:
        break;
    }
  }
  else {
    symbol->integer_type_name->accept(*basedecl);
  }
  return NULL;
}

/*  signed_integer DOTDOT signed_integer */
void *visit(subrange_c *symbol) {
  int dimension;
  switch (current_typedefinition) {
    case array_td:
      if (current_basetypedeclaration == arraysubrange_bd) {
        s4o_incl.print("[");
        dimension = extract_integer(symbol->upper_limit) - extract_integer(symbol->lower_limit) + 1;
        print_integer_incl(dimension);
        s4o_incl.print("]");
      }
      else
        symbol->lower_limit->accept(*this);
      break;
    case subrange_td:
      s4o.print(s4o.indent_spaces + "if (value < ");
      symbol->lower_limit->accept(*this);
      s4o.print(")\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces + "return ");
      symbol->lower_limit->accept(*this);
      s4o.print(";\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "else if (value > ");
      symbol->upper_limit->accept(*this);
      s4o.print(")\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces + "return ");
      symbol->upper_limit->accept(*this);
      s4o.print(";\n");
      s4o.indent_left();
      s4o.print(s4o.indent_spaces + "else\n");
      s4o.indent_right();
      s4o.print(s4o.indent_spaces + "return value;\n");
      s4o.indent_left();
    default:
      break;
  }
  return NULL;
}

/*  enumerated_type_name ':' enumerated_spec_init */
void *visit(enumerated_type_declaration_c *symbol) {
  TRACE("enumerated_type_declaration_c");
  
  current_typedefinition = enumerated_td;

  s4o_incl.print("typedef enum {\n");
  s4o_incl.indent_right();
  symbol->enumerated_spec_init->accept(*this);
  s4o_incl.indent_left();
  s4o_incl.print("} ");
  symbol->enumerated_type_name->accept(*basedecl);
  s4o_incl.print(";\n");

  current_typedefinition = none_td;

  return NULL;
}

void *visit(enumerated_spec_init_c *symbol) {
  TRACE("enumerated_spec_init_c");
  if (current_typedefinition == enumerated_td)
    symbol->enumerated_specification->accept(*this);
  else
    symbol->enumerated_specification->accept(*basedecl);
  return NULL;
}

/* helper symbol for enumerated_specification->enumerated_spec_init */
/* enumerated_value_list ',' enumerated_value */
void *visit(enumerated_value_list_c *symbol) {
  print_list_incl(symbol, s4o_incl.indent_spaces, ",\n"+s4o_incl.indent_spaces, "\n");
  return NULL;
}

/* enumerated_type_name '#' identifier */
void *visit(enumerated_value_c *symbol) {
  symbol->value->accept(*basedecl);
  return NULL;
}

/*  identifier ':' array_spec_init */
void *visit(array_type_declaration_c *symbol) {
  TRACE("array_type_declaration_c");
  
  current_typedefinition = array_td;

  array_is_derived = false;
  current_basetypedeclaration = arrayderiveddeclaration_bd;
  symbol->array_spec_init->accept(*this);
  current_basetypedeclaration = none_bd;

  if (array_is_derived)
	s4o_incl.print("__DECLARE_DERIVED_TYPE(");
  else
    s4o_incl.print("__DECLARE_ARRAY_TYPE(");
  current_basetypedeclaration = arraybasetypeincl_bd;
  symbol->array_spec_init->accept(*this);
  current_basetypedeclaration = none_bd;
  s4o_incl.print(",");
  symbol->identifier->accept(*basedecl);
  if (!array_is_derived) {
    s4o_incl.print(",");
    current_basetypedeclaration = arraysubrange_bd;
    symbol->array_spec_init->accept(*this);
    current_basetypedeclaration = none_bd;
  }
  s4o_incl.print(")\n");
  
  if (search_base_type.type_is_subrange(symbol->identifier)) {
    s4o.print("#define __CHECK_");
    symbol->identifier->accept(*this);
    s4o.print(" __CHECK_");
    current_basetypedeclaration = arraybasetype_bd;
    symbol->array_spec_init->accept(*this);
    current_basetypedeclaration = none_bd;
    s4o.print("\n");
  }
  
  current_type_name = symbol->identifier;
  current_basetypedeclaration = arraytranslateindex_bd;
  symbol->array_spec_init->accept(*this);
  current_basetypedeclaration = none_bd;
  s4o.print("\n");
  
  current_typedefinition = none_td;

  return NULL;
}

/* array_specification [ASSIGN array_initialization] */
/* array_initialization may be NULL ! */
void *visit(array_spec_init_c *symbol) {
  TRACE("array_spec_init_c");
  
  identifier_c *array_type_name;

  switch (current_basetypedeclaration) {
    case arrayderiveddeclaration_bd:
      array_type_name = dynamic_cast<identifier_c *>(symbol->array_specification);
      array_is_derived = array_type_name != NULL;
      break;
    case arraytranslateindex_bd:
      if (!array_is_derived)
    	symbol->array_specification->accept(*this);

      s4o.print("#define __");
      current_type_name->accept(*this);
      s4o.print("_TRANSIDX(row, index) __");
      if (array_is_derived)
         symbol->array_specification->accept(*this);
      else
         current_type_name->accept(*this);
      s4o.print("_TRANSIDX##row(index)");
      break;
    default:
      if (array_is_derived)
        symbol->array_specification->accept(*basedecl);
      else
        symbol->array_specification->accept(*this);
      break;
  }
  return NULL;
}

/* ARRAY '[' array_subrange_list ']' OF non_generic_type_name */
void *visit(array_specification_c *symbol) {
  switch (current_basetypedeclaration) {
    case arraybasetype_bd:
      symbol->non_generic_type_name->accept(*this);
      break;
    case arraybasetypeincl_bd:
      symbol->non_generic_type_name->accept(*basedecl);
      break;
    case arraysubrange_bd:
    case arraytranslateindex_bd:
      symbol->array_subrange_list->accept(*this);
      break;
    default:
      break;
  }
  return NULL;
}

/* helper symbol for array_specification */
/* array_subrange_list ',' subrange */
void *visit(array_subrange_list_c *symbol) {
  if (current_basetypedeclaration == arraytranslateindex_bd) {
    for (int i = 0; i < symbol->n; i++) {
      s4o.print("#define __");
      current_type_name->accept(*this);
      s4o.print("_TRANSIDX");
      print_integer(i);
      s4o.print("(index) (index) - ");
      symbol->elements[i]->accept(*this);
      s4o.print("\n");
    }
  }
  else
    print_list(symbol);
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
  return print_list_incl(symbol, "", "\n", "\n");
}

/*  simple_type_name ':' simple_spec_init */
void *visit(simple_type_declaration_c *symbol) {
  TRACE("simple_type_declaration_c");

  s4o_incl.print("__DECLARE_DERIVED_TYPE(");
  symbol->simple_spec_init->accept(*this);
  s4o_incl.print(",");
  symbol->simple_type_name->accept(*basedecl);
  s4o_incl.print(")\n");
  return NULL;
}

/* simple_specification [ASSIGN constant] */
//SYM_REF2(simple_spec_init_c, simple_specification, constant)
// <constant> may be NULL
void *visit(simple_spec_init_c *symbol) {
  TRACE("simple_spec_init_c");
  symbol->simple_specification->accept(*basedecl);
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

  current_typedefinition = struct_td;

  s4o_incl.print("__DECLARE_STRUCT_TYPE(");
  symbol->structure_specification->accept(*this);
  s4o_incl.print(",");
  symbol->structure_type_name->accept(*basedecl);
  s4o_incl.print(");\n");

  current_typedefinition = none_td;

  return NULL;
}

/* structure_type_name ASSIGN structure_initialization */
/* structure_initialization may be NULL ! */
//SYM_REF2(initialized_structure_c, structure_type_name, structure_initialization)
void *visit(initialized_structure_c *symbol) {
  TRACE("initialized_structure_c");
  
  symbol->structure_type_name->accept(*basedecl);
  
  return NULL;
}

/* helper symbol for structure_declaration */
/* structure_declaration:  STRUCT structure_element_declaration_list END_STRUCT */
/* structure_element_declaration_list structure_element_declaration ';' */
//SYM_LIST(structure_element_declaration_list_c)
void *visit(structure_element_declaration_list_c *symbol) {
  TRACE("structure_element_declaration_list_c");
  s4o_incl.print("struct {\n");
  s4o_incl.indent_right();
  s4o_incl.print(s4o_incl.indent_spaces);

  print_list_incl(symbol, "", s4o_incl.indent_spaces, "");

  s4o_incl.indent_left();
  s4o_incl.print(s4o_incl.indent_spaces);
  s4o_incl.print("}");
  return NULL;
}

/*  structure_element_name ':' spec_init */
//SYM_REF2(structure_element_declaration_c, structure_element_name, spec_init)
void *visit(structure_element_declaration_c *symbol) {
  TRACE("structure_element_declaration_c");

  symbol->spec_init->accept(*this);
  s4o_incl.print(" ");
  symbol->structure_element_name->accept(*basedecl);
  s4o_incl.print(";\n");
  s4o_incl.print(s4o.indent_spaces);

  return NULL;
}

/* helper symbol for structure_initialization */
/* structure_initialization: '(' structure_element_initialization_list ')' */
/* structure_element_initialization_list ',' structure_element_initialization */
//SYM_LIST(structure_element_initialization_list_c)
void *visit(structure_element_initialization_list_c *symbol) {
  TRACE("structure_element_initialization_list_c");

  // TODO ???
  //ERROR;
  return NULL;
}

/*  structure_element_name ASSIGN value */
//SYM_REF2(structure_element_initialization_c, structure_element_name, value)
void *visit(structure_element_initialization_c *symbol) {
  TRACE("structure_element_initialization_c");

  // TODO ???
  //ERROR;
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



