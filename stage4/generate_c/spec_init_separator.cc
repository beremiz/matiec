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
 * Seperation of type specification and default value constructs
 * (for e.g. simple_spec_init_c), into a type specificiation part,
 * and a default value part.
 */




//#include <stdio.h>  /* required for NULL */
//#include <string>
//#include <iostream>

//#include "../../util/symtable.hh"







class spec_init_sperator_c: public null_visitor_c {
  private:
    /* this is a singleton class... */
    static spec_init_sperator_c *class_instance;
    static spec_init_sperator_c *get_class_instance(void) {
      if (NULL == class_instance)
        class_instance = new spec_init_sperator_c();

      if (NULL == class_instance)
        ERROR;

      return class_instance;
    }

  private:
    typedef enum {search_spec, search_init} search_what_t;
    static search_what_t search_what;

  public:
    /* the only two public functions... */
    static symbol_c *get_spec(symbol_c *spec_init) {
      search_what = search_spec;
      return (symbol_c *)spec_init->accept(*get_class_instance());
    }

    static symbol_c *get_init(symbol_c *spec_init) {
      search_what = search_init;
      return (symbol_c *)spec_init->accept(*get_class_instance());
    }

//  private:
  public:  /* probably needs to be public so it may be visited... !! */


/*******************************************/
/* B 1.1 - Letters, digits and identifiers */
/*******************************************/
// SYM_TOKEN(identifier_c)
void *visit(identifier_c *symbol) {
  TRACE("spec_init_sperator_c::identifier_c");
  switch (search_what) {
    /* if we ever get called sith a simple identifier_c, then it must be a previously declared type... */
    case search_spec: return symbol;
    case search_init: return NULL;
  }
  ERROR; /* should never occur */
  return NULL;
}


/********************************/
/* B 1.3.3 - Derived data types */
/********************************/

/* simple_specification ASSIGN constant */
void *visit(simple_spec_init_c *symbol) {
  TRACE("spec_init_sperator_c::simple_spec_init_c");
  switch (search_what) {
    case search_spec: return symbol->simple_specification;
    case search_init: return symbol->constant;
  }
  ERROR; /* should never occur */
  return NULL;
}

/* subrange_specification ASSIGN signed_integer */
void *visit(subrange_spec_init_c *symbol) {
  TRACE("spec_init_sperator_c::subrange_spec_init_c");
  switch (search_what) {
    case search_spec: return symbol->subrange_specification->accept(*this);
    case search_init: return symbol->signed_integer;
  }
  ERROR; /* should never occur */
  return NULL;
}

/*  integer_type_name '(' subrange')' */
void *visit(subrange_specification_c *symbol) {
  TRACE("spec_init_sperator_c::subrange_specification_c");
  switch (search_what) {
    case search_spec: return symbol->integer_type_name;
    case search_init: return NULL; /* should never occur */
  }
  ERROR; /* should never occur */
  return NULL;
}

/* array_specification [ASSIGN array_initialization} */
/* array_initialization may be NULL ! */
void *visit(array_spec_init_c *symbol) {
  TRACE("spec_init_sperator_c::array_spec_init_c");
  switch (search_what) {
    case search_spec: return symbol->array_specification;
    case search_init: return symbol->array_initialization;
  }
  return NULL;
}

/* enumerated_specification ASSIGN enumerated_value */
void *visit(enumerated_spec_init_c *symbol) {
  TRACE("spec_init_sperator_c::enumerated_spec_init_c");
  switch (search_what) {
    case search_spec: return symbol->enumerated_specification;
    case search_init: return symbol->enumerated_value;
  }
  ERROR; /* should never occur */
  return NULL;
}

/* structure_type_name ASSIGN structure_initialization */
/* structure_initialization may be NULL ! */
//SYM_REF2(initialized_structure_c, structure_type_name, structure_initialization)
void *visit(initialized_structure_c *symbol) {
  TRACE("spec_init_sperator_c::initialized_structure_c");
  switch (search_what) {
    case search_spec: return symbol->structure_type_name;
    case search_init: return symbol->structure_initialization;
  }
  ERROR; /* should never occur */
  return NULL;
}


/******************************************/
/* B 1.4.3 - Declaration & Initialisation */
/******************************************/

/* fb_name_list ':' function_block_type_name ASSIGN structure_initialization */
/* structure_initialization -> may be NULL ! */
void *visit(fb_name_decl_c *symbol) {
  TRACE("spec_init_sperator_c::fb_name_decl_c");
  switch (search_what) {
    case search_spec: return symbol->function_block_type_name;
    case search_init: return symbol->structure_initialization;
  }
  ERROR; /* should never occur */
  return NULL;
}

};   /* class spec_init_sperator_c */



spec_init_sperator_c *spec_init_sperator_c ::class_instance = NULL;
spec_init_sperator_c::search_what_t spec_init_sperator_c::search_what;
