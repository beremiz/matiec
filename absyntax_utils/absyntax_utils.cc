/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2009-2011  Mario de Sousa (msousa@fe.up.pt)
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

/*
 * An IEC 61131-3 compiler.
 *
 * Based on the
 * FINAL DRAFT - IEC 61131-3, 2nd Ed. (2001-12-10)
 *
 */


/*
 * This is the main stage 3a file.
 *
 * In stage 3a some helpful symbol tables are instanciated and populated.
 * These symbol tables wll then be used by stage3b and atage4 code generators.
 */






// #include <stdio.h>  /* required for NULL */
#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <list>
#include <strings.h>
#include <string.h>  /* required for strlen() */
#include <stdlib.h>  /* required for atoi() */

#include "../util/symtable.hh"
#include "../util/dsymtable.hh"
#include "../absyntax/visitor.hh"



//#define DEBUG
#ifdef DEBUG
#define TRACE(classname) printf("\n____%s____\n",classname);
#else
#define TRACE(classname)
#endif

#define ERROR error_exit(__FILE__,__LINE__)
/* function defined in main.cc */
extern void error_exit(const char *file_name, int line_no);


/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


/* returns 0 if the names are equal!! */
/* NOTE: it must ignore case!! */
int compare_identifiers(symbol_c *ident1, symbol_c *ident2) {

  token_c *name1 = dynamic_cast<token_c *>(ident1);
  token_c *name2 = dynamic_cast<token_c *>(ident2);
  
  if ((name1 == NULL) || (name2 == NULL))
    /* invalid identifiers... */
    return -1;

  if (strcasecmp(name1->value, name2->value) == 0)
    return 0;

  /* identifiers do not match! */
  return 1;
}


/* extract the value of an integer from an integer_c object !! */
/* NOTE: it must ignore underscores! */
int extract_integer(symbol_c *sym) {
  std::string str = "";
  integer_c *integer;
  neg_integer_c * neg_integer;

  if ((neg_integer = dynamic_cast<neg_integer_c *>(sym)) != NULL)
    return - extract_integer((integer_c *)neg_integer->exp);
  
  if ((integer = dynamic_cast<integer_c *>(sym)) == NULL) ERROR;

  for(unsigned int i = 0; i < strlen(integer->value); i++)
    if (integer->value[i] != '_')  str += integer->value[i];

  return atoi(str.c_str());
}



/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/



/* A symbol table with all globally declared functions... */
function_declaration_c null_symbol1(NULL,NULL,NULL,NULL);
dsymtable_c<function_declaration_c *, &null_symbol1> function_symtable;

/* A symbol table with all globally declared functions block types... */
function_block_declaration_c null_symbol2(NULL,NULL,NULL);
symtable_c<function_block_declaration_c *, &null_symbol2> function_block_type_symtable;

/* A symbol table with all globally declared program types... */
program_declaration_c null_symbol3(NULL,NULL,NULL);
symtable_c<program_declaration_c *, &null_symbol3> program_type_symtable;

/* A symbol table with all user declared type definitions... */
/* Note that function block types and program types have their
 * own symbol tables, so do not get placed in this symbol table!
 *
 * The symbol_c * associated to the value will point to the data type declaration.
 */
symbol_c null_symbol4;
symtable_c<symbol_c *, &null_symbol4> type_symtable;

/* A symbol table with all values declared for enumerated type... */
/* Notes:
 * - if the value is defined multiple times the value
 * is the null pointer.
 *
 * - The stored symbol_c * associated to the value points to the enumerated_type_name
 * (i.e. the name of the enumerated data type) in which the the value/identifier
 * is used/declared.
 *
 * - We could re-use the null_symbol4 object, but it is safer to use a distinct object
 *   (i.e. it might make it easier to find strange bugs).
 */
symbol_c null_symbol5;
symtable_c<symbol_c *, &null_symbol5> enumerated_value_symtable;


/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


class populate_symtables_c: public iterator_visitor_c {

  private:
	symbol_c *current_enumerated_type;

  public:
    populate_symtables_c(void) {
    	current_enumerated_type = NULL;
    };
    virtual ~populate_symtables_c(void) {}


  public:

  /*************************/
  /* B.1 - Common elements */
  /*************************/
  /*******************************************/
  /* B 1.1 - Letters, digits and identifiers */
  /*******************************************/
  /*********************/
  /* B 1.2 - Constants */
  /*********************/
  /******************************/
  /* B 1.2.1 - Numeric Literals */
  /******************************/
  /*******************************/
  /* B.1.2.2   Character Strings */
  /*******************************/
  /***************************/
  /* B 1.2.3 - Time Literals */
  /***************************/
  /************************/
  /* B 1.2.3.1 - Duration */
  /************************/
  /************************************/
  /* B 1.2.3.2 - Time of day and Date */
  /************************************/
  /**********************/
  /* B.1.3 - Data types */
  /**********************/
  /***********************************/
  /* B 1.3.1 - Elementary Data Types */
  /***********************************/
  /********************************/
  /* B.1.3.2 - Generic data types */
  /********************************/
  /********************************/
  /* B 1.3.3 - Derived data types */
  /********************************/

  /*  subrange_type_name ':' subrange_spec_init */
  void *visit(subrange_type_declaration_c *symbol) {
    TRACE("subrange_type_declaration_c");  
    type_symtable.insert(symbol->subrange_type_name, symbol->subrange_spec_init);
    return NULL;
  }
  

  /*  enumerated_type_name ':' enumerated_spec_init */
  void *visit(enumerated_type_declaration_c *symbol) {
    TRACE("enumerated_type_declaration_c");
    type_symtable.insert(symbol->enumerated_type_name, symbol->enumerated_spec_init);
    current_enumerated_type = symbol->enumerated_type_name;
    symbol->enumerated_spec_init->accept(*this);
    current_enumerated_type = NULL;
    return NULL;
  }

  /* enumerated_specification ASSIGN enumerated_value */
  void *visit(enumerated_spec_init_c *symbol) {
    return symbol->enumerated_specification->accept(*this);
  }

  /* [enumerated_type_name '#'] identifier */
  void *visit(enumerated_value_c *symbol) {
    if (current_enumerated_type != NULL) {
      if (symbol->type != NULL) ERROR;

      symbol_c *value_type = enumerated_value_symtable.find_value(symbol->value);
      /* NOTE: The following condition checks whether the same identifier is used more than once
       *       when defining the enumerated values of the type declaration of the new enumerated type.
       *       If this occurs, then the program beeing compiled contains a semantic error, which
       *       must be caught and reported by the semantic analyser. However, since
       *       this code is run before the semantic analyser, we must not yet raise the ERROR (internal
       *       compiler error message).
       *       For this reason, the follosing check is commented out.
       */
      /* if (value_type == current_enumerated_type) ERROR; */

      if (value_type == enumerated_value_symtable.end_value())
	/* This identifier has not yet been used in any previous declaration of an enumeration data type.
	 * so we add it to the symbol table.
	 */
        enumerated_value_symtable.insert(symbol->value, current_enumerated_type);
      else if (value_type != NULL)
	/* This identifier has already been used in a previous declaration of an enumeration data type.
	 * so we set the symbol in symbol table pointing to NULL.
	 */
        enumerated_value_symtable.set(symbol->value, NULL);
    }
    return NULL;
  }

  /*  identifier ':' array_spec_init */
  void *visit(array_type_declaration_c *symbol) {
    TRACE("array_type_declaration_c");
    type_symtable.insert(symbol->identifier, symbol->array_spec_init);
    return NULL;
  }


  /*  simple_type_name ':' simple_spec_init */
  void *visit(simple_type_declaration_c *symbol) {
    TRACE("simple_type_declaration_c");
    type_symtable.insert(symbol->simple_type_name, symbol->simple_spec_init);
    return NULL;
  }


  /*  structure_type_name ':' structure_specification */
  void *visit(structure_type_declaration_c *symbol) {
    TRACE("structure_type_declaration_c");
    type_symtable.insert(symbol->structure_type_name, symbol->structure_specification);
    return NULL;
  }
  
  
  /*  string_type_name ':' elementary_string_type_name string_type_declaration_size string_type_declaration_init */
  // SYM_REF4(string_type_declaration_c,	string_type_name,
  //    					elementary_string_type_name,
  //    					string_type_declaration_size,
  //    					string_type_declaration_init) /* may be == NULL! */
  void *visit(string_type_declaration_c *symbol)	{
    TRACE("string_type_declaration_c");
    type_symtable.insert(symbol->string_type_name, symbol);
    return NULL;
}

  /*********************/
  /* B 1.4 - Variables */
  /*********************/
  /********************************************/
  /* B.1.4.1   Directly Represented Variables */
  /********************************************/
  /*************************************/
  /* B.1.4.2   Multi-element Variables */
  /*************************************/
  /******************************************/
  /* B 1.4.3 - Declaration & Initialisation */
  /******************************************/
  /**************************************/
  /* B.1.5 - Program organization units */
  /**************************************/
  /***********************/
  /* B 1.5.1 - Functions */
  /***********************/
  public:
  /*   FUNCTION derived_function_name ':' elementary_type_name io_OR_function_var_declarations_list function_body END_FUNCTION */
  /* | FUNCTION derived_function_name ':' derived_type_name io_OR_function_var_declarations_list function_body END_FUNCTION */
  void *visit(function_declaration_c *symbol) {
    TRACE("function_declaration_c");
    function_symtable.insert(symbol->derived_function_name, symbol);
  
    /* symbol->derived_function_name->accept(*this);  */ /* Function name */
    /* symbol->type_name->accept(*this);              */ /* return data type */
    /* symbol->var_declarations_list->accept(*this);  */ /* Function parameters and variables */
    /* symbol->function_body->accept(*this);          */ /* Function body */
    return NULL;
  }
  

  /*****************************/
  /* B 1.5.2 - Function Blocks */
  /*****************************/
  public:
  /*  FUNCTION_BLOCK derived_function_block_name io_OR_other_var_declarations function_block_body END_FUNCTION_BLOCK */
  //SYM_REF4(function_block_declaration_c, fblock_name, var_declarations, fblock_body, unused)
  void *visit(function_block_declaration_c *symbol) {
    TRACE("function_block_declaration_c");
    function_block_type_symtable.insert(symbol->fblock_name, symbol);
  /*
    symbol->fblock_name->accept(*this);
    symbol->var_declarations->accept(*this);
    symbol->fblock_body->accept(*this);
  */
    return NULL;
  }
  
  
  /**********************/
  /* B 1.5.3 - Programs */
  /**********************/
  public:
  /*  PROGRAM program_type_name program_var_declarations_list function_block_body END_PROGRAM */
  //SYM_REF4(program_declaration_c, program_type_name, var_declarations, function_block_body, unused)
  void *visit(program_declaration_c *symbol) {
    TRACE("program_declaration_c");
    program_type_symtable.insert(symbol->program_type_name, symbol);
  /*
    symbol->program_type_name->accept(*this);
    symbol->var_declarations->accept(*this);
    symbol->function_block_body->accept(*this);
  */
    return NULL;
  }
  
}; /* populate_symtables_c */





void absyntax_utils_init(symbol_c *tree_root) {
  populate_symtables_c populate_symbols;

  tree_root->accept(populate_symbols);
}

