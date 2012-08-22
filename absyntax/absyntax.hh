/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
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

/*
 * An IEC 61131-3 compiler.
 *
 * Based on the
 * FINAL DRAFT - IEC 61131-3, 2nd Ed. (2001-12-10)
 *
 */

/*
 * Declaration of the Abstract Syntax data structure components
 */

/*
 * ABSYNTAX.H
 *
 * This generates the parse tree structure used to bind the components
 * identified by Bison in the correct syntax order. At the end of the
 * Bison analysis the tree is walked in a sequential fashion generating
 * the relavent code.
 */

#ifndef _ABSYNTAX_HH
#define _ABSYNTAX_HH


#include <stdio.h> // required for NULL
#include <vector>
#include <string>
#include <stdint.h>  // required for uint64_t, etc...
#include "../main.hh" // required for uint8_t, real_64_t, ..., and the macros INT8_MAX, REAL32_MAX, ... */




/* Forward declaration of the visitor interface
 * declared in the visitor.hh file
 * We cannot include the visitor.hh file, as it will
 * include this same file first, as it too requires references
 * to the abstract syntax classes defined here.
 */
class visitor_c; // forward declaration


class symbol_c; // forward declaration











/* The base class of all symbols */
class symbol_c {

  public:
    /*
     * Line number for the purposes of error checking.
     * Annotated (inserted) by stage1_2
     */
    int first_line;
    int first_column;
    const char *first_file;  /* filename referenced by first line/column */
    long int first_order;    /* relative order in which it is read by lexcial analyser */
    int last_line;
    int last_column;
    const char *last_file;  /* filename referenced by last line/column */
    long int last_order;    /* relative order in which it is read by lexcial analyser */


    /*
     * Annotations produced during stage 3
     */
    /*** Data type analysis ***/
    std::vector <symbol_c *> candidate_datatypes; /* All possible data types the expression/literal/etc. may take. Filled in stage3 by fill_candidate_datatypes_c class */
    /* Data type of the expression/literal/etc. Filled in stage3 by narrow_candidate_datatypes_c 
     * If set to NULL, it means it has not yet been evaluated.
     * If it points to an object of type invalid_type_name_c, it means it is invalid.
     * Otherwise, it points to an object of the apropriate data type (e.g. int_type_name_c, bool_type_name_c, ...)
     */
    symbol_c *datatype;

    /*** constant folding ***/
    /* During stage 3 (semantic analysis/checking) we will be doing constant folding.
     * That algorithm will anotate the abstract syntax tree with the result of operations
     * on literals (i.e. 44 + 55 will store the result 99).
     * Since the same source code (e.g. 1 + 0) may actually be a BOOL or an ANY_INT,
     * or an ANY_BIT, we need to handle all possibilities, and determine the result of the
     * operation assuming each type.
     * For this reason, we have one entry for each possible type, with some expressions
     * having more than one entry filled in!
     */
    typedef enum { cs_undefined,   /* not defined/not yet evaluated --> const_value is not valid! */
                   cs_non_const,   /* we have deternmined that expression is not a const value --> const_value is not valid! */
                   cs_const_value, /* const value is valid */
                   cs_overflow     /* result produced overflow or underflow --> const_value is not valid! */
                 } const_status_t;
 
    typedef struct {const_status_t status;  real64_t  value; } const_value_real64_t;
    typedef struct {const_status_t status;   int64_t  value; } const_value_int64_t;
    typedef struct {const_status_t status;  uint64_t  value; } const_value_uint64_t;
    typedef struct {const_status_t status;      bool  value; } const_value_bool_t;

    typedef struct {
      const_value_real64_t _real64; /* status is initialised to UNDEFINED */
      const_value_int64_t   _int64; /* status is initialised to UNDEFINED */
      const_value_uint64_t _uint64; /* status is initialised to UNDEFINED */
      const_value_bool_t     _bool; /* status is initialised to UNDEFINED */
    } const_value_t;
    const_value_t const_value;
    

  public:
    /* default constructor */
    symbol_c(int fl = 0, int fc = 0, const char *ffile = NULL /* filename */, long int forder=0, /* order in which it is read by lexcial analyser */
             int ll = 0, int lc = 0, const char *lfile = NULL /* filename */, long int lorder=0  /* order in which it is read by lexcial analyser */
            );

    /* default destructor */
    /* must be virtual so compiler does not complain... */ 
    virtual ~symbol_c(void) {return;};

    virtual void *accept(visitor_c &visitor) {return NULL;};
};


class token_c: public symbol_c {
  public:
    /* the value of the symbol. */
    const char *value;

  public:
    token_c(const char *value, 
            int fl = 0, int fc = 0, const char *ffile = NULL /* filename */, long int forder=0, /* order in which it is read by lexcial analyser */
            int ll = 0, int lc = 0, const char *lfile = NULL /* filename */, long int lorder=0  /* order in which it is read by lexcial analyser */
           );
};


 /* a list of symbols... */
class list_c: public symbol_c {
  public:
    int n;
    symbol_c **elements;

  public:
    list_c(int fl = 0, int fc = 0, const char *ffile = NULL /* filename */, long int forder=0, /* order in which it is read by lexcial analyser */
           int ll = 0, int lc = 0, const char *lfile = NULL /* filename */, long int lorder=0  /* order in which it is read by lexcial analyser */
          );

    list_c(symbol_c *elem, 
           int fl = 0, int fc = 0, const char *ffile = NULL /* filename */, long int forder=0, /* order in which it is read by lexcial analyser */
           int ll = 0, int lc = 0, const char *lfile = NULL /* filename */, long int lorder=0  /* order in which it is read by lexcial analyser */
          );
     /* append a new element to the end of the list */
    virtual void add_element(symbol_c *elem);
     /* insert a new element before position pos. */
     /* To insert into the begining of list, call with pos=0  */
     /* To insert into the end of list, call with pos=list->n */
    virtual void insert_element(symbol_c *elem, int pos = 0);
     /* remove element at position pos. */
    virtual void remove_element(int pos = 0);
};




#define SYM_LIST(class_name_c, ...)											\
class class_name_c:	public list_c {											\
  public:														\
    __VA_ARGS__														\
  public:														\
    class_name_c(													\
                 int fl = 0, int fc = 0, const char *ffile = NULL /* filename */, long int forder=0,			\
                 int ll = 0, int lc = 0, const char *lfile = NULL /* filename */, long int lorder=0);			\
    class_name_c(symbol_c *elem, 											\
                 int fl = 0, int fc = 0, const char *ffile = NULL /* filename */, long int forder=0,			\
                 int ll = 0, int lc = 0, const char *lfile = NULL /* filename */, long int lorder=0);			\
    virtual void *accept(visitor_c &visitor);										\
};


#define SYM_TOKEN(class_name_c, ...)											\
class class_name_c: 	public token_c {										\
  public:														\
    __VA_ARGS__														\
  public:														\
    class_name_c(const char *value, 											\
                 int fl = 0, int fc = 0, const char *ffile = NULL /* filename */, long int forder=0,			\
                 int ll = 0, int lc = 0, const char *lfile = NULL /* filename */, long int lorder=0);			\
    virtual void *accept(visitor_c &visitor);										\
};


#define SYM_REF0(class_name_c, ...)											\
class class_name_c: public symbol_c {											\
  public:														\
    __VA_ARGS__														\
  public:														\
    class_name_c(		 											\
                 int fl = 0, int fc = 0, const char *ffile = NULL /* filename */, long int forder=0,			\
                 int ll = 0, int lc = 0, const char *lfile = NULL /* filename */, long int lorder=0);			\
    virtual void *accept(visitor_c &visitor);										\
};


#define SYM_REF1(class_name_c, ref1, ...)										\
class class_name_c: public symbol_c {											\
  public:														\
    symbol_c *ref1;													\
    __VA_ARGS__														\
  public:														\
    class_name_c(symbol_c *ref1,											\
                 int fl = 0, int fc = 0, const char *ffile = NULL /* filename */, long int forder=0,			\
                 int ll = 0, int lc = 0, const char *lfile = NULL /* filename */, long int lorder=0);			\
    virtual void *accept(visitor_c &visitor);										\
};


#define SYM_REF2(class_name_c, ref1, ref2, ...)										\
class class_name_c: public symbol_c {											\
  public:														\
    symbol_c *ref1;													\
    symbol_c *ref2;													\
    __VA_ARGS__														\
  public:														\
    class_name_c(symbol_c *ref1,											\
		 symbol_c *ref2 = NULL,											\
                 int fl = 0, int fc = 0, const char *ffile = NULL /* filename */, long int forder=0,			\
                 int ll = 0, int lc = 0, const char *lfile = NULL /* filename */, long int lorder=0);			\
    virtual void *accept(visitor_c &visitor);										\
};


#define SYM_REF3(class_name_c, ref1, ref2, ref3, ...)									\
class class_name_c: public symbol_c {											\
  public:														\
    symbol_c *ref1;													\
    symbol_c *ref2;													\
    symbol_c *ref3;													\
    __VA_ARGS__														\
  public:														\
    class_name_c(symbol_c *ref1,											\
		 symbol_c *ref2,											\
		 symbol_c *ref3,											\
                 int fl = 0, int fc = 0, const char *ffile = NULL /* filename */, long int forder=0,			\
                 int ll = 0, int lc = 0, const char *lfile = NULL /* filename */, long int lorder=0);			\
    virtual void *accept(visitor_c &visitor);										\
};


#define SYM_REF4(class_name_c, ref1, ref2, ref3, ref4, ...)								\
class class_name_c: public symbol_c {											\
  public:														\
    symbol_c *ref1;													\
    symbol_c *ref2;													\
    symbol_c *ref3;													\
    symbol_c *ref4;													\
    __VA_ARGS__														\
  public:														\
    class_name_c(symbol_c *ref1,											\
		 symbol_c *ref2,											\
		 symbol_c *ref3,											\
		 symbol_c *ref4 = NULL,											\
                 int fl = 0, int fc = 0, const char *ffile = NULL /* filename */, long int forder=0,			\
                 int ll = 0, int lc = 0, const char *lfile = NULL /* filename */, long int lorder=0);			\
    virtual void *accept(visitor_c &visitor);										\
};


#define SYM_REF5(class_name_c, ref1, ref2, ref3, ref4, ref5, ...)							\
class class_name_c: public symbol_c {											\
  public:														\
    symbol_c *ref1;													\
    symbol_c *ref2;													\
    symbol_c *ref3;													\
    symbol_c *ref4;													\
    symbol_c *ref5;													\
    __VA_ARGS__														\
  public:														\
    class_name_c(symbol_c *ref1,											\
		 symbol_c *ref2,											\
		 symbol_c *ref3,											\
		 symbol_c *ref4,											\
		 symbol_c *ref5,											\
                 int fl = 0, int fc = 0, const char *ffile = NULL /* filename */, long int forder=0,			\
                 int ll = 0, int lc = 0, const char *lfile = NULL /* filename */, long int lorder=0);			\
    virtual void *accept(visitor_c &visitor);										\
};


#define SYM_REF6(class_name_c, ref1, ref2, ref3, ref4, ref5, ref6, ...)							\
class class_name_c: public symbol_c {											\
  public:														\
    symbol_c *ref1;													\
    symbol_c *ref2;													\
    symbol_c *ref3;													\
    symbol_c *ref4;													\
    symbol_c *ref5;													\
    symbol_c *ref6;													\
    __VA_ARGS__														\
  public:														\
    class_name_c(symbol_c *ref1,											\
		 symbol_c *ref2,											\
		 symbol_c *ref3,											\
		 symbol_c *ref4,											\
		 symbol_c *ref5,											\
		 symbol_c *ref6 = NULL,											\
                 int fl = 0, int fc = 0, const char *ffile = NULL /* filename */, long int forder=0,			\
                 int ll = 0, int lc = 0, const char *lfile = NULL /* filename */, long int lorder=0);			\
    virtual void *accept(visitor_c &visitor);										\
};


#include "absyntax.def"



#undef SYM_LIST
#undef SYM_TOKEN
#undef SYM_REF0
#undef SYM_REF1
#undef SYM_REF2
#undef SYM_REF3
#undef SYM_REF4
#undef SYM_REF5
#undef SYM_REF6

#endif /*  _ABSYNTAX_HH */
