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

/* Forward declaration of the visitor interface
 * dclared in the visitor.hh file
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
     * Line number for the purposes of error checking
     */
    int first_line;
    int first_column;
    int last_line;
    int last_column;

  public:
    /* default constructor */
    symbol_c(void);
    symbol_c(int fl     /* first_line   */, 
             int fc     /* first_column */,
             int ll = 0 /* last_line    */,
             int lc = 0 /* last_column  */
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
    token_c(const char *value, int fl = 0, int fc = 0, int ll = 0, int lc = 0);
};


 /* a list of symbols... */
class list_c: public symbol_c {
  public:
    int n;
    symbol_c **elements;

  public:
    list_c(int fl = 0, int fc = 0, int ll = 0, int lc = 0);
    list_c(symbol_c *elem, int fl = 0, int fc = 0, int ll = 0, int lc = 0);
     /* insert a new element */
    virtual void add_element(symbol_c *elem);
};




#define SYM_LIST(class_name_c)								\
class class_name_c:	public list_c {							\
  public:										\
    class_name_c(int fl = 0, int fc = 0, int ll = 0, int lc = 0);			\
    class_name_c(symbol_c *elem, int fl = 0, int fc = 0, int ll = 0, int lc = 0);	\
    virtual void *accept(visitor_c &visitor);						\
};


#define SYM_TOKEN(class_name_c)								\
class class_name_c: 	public token_c {						\
  public:										\
    class_name_c(const char *value, int fl = 0, int fc = 0, int ll = 0, int lc = 0);	\
    virtual void *accept(visitor_c &visitor);						\
};


#define SYM_REF0(class_name_c)			\
class class_name_c: public symbol_c {		\
  public:					\
    class_name_c(int fl = 0, int fc = 0, 	\
		 int ll = 0, int lc = 0);	\
    virtual void *accept(visitor_c &visitor);	\
};


#define SYM_REF1(class_name_c, ref1)			\
class class_name_c: public symbol_c {			\
  public:						\
    symbol_c *ref1;					\
  public:						\
    class_name_c(symbol_c *ref1,			\
		 int fl = 0, int fc = 0, 		\
		 int ll = 0, int lc = 0);		\
    virtual void *accept(visitor_c &visitor);		\
};


#define SYM_REF2(class_name_c, ref1, ref2)		\
class class_name_c: public symbol_c {			\
  public:						\
    symbol_c *ref1;					\
    symbol_c *ref2;					\
  public:						\
    class_name_c(symbol_c *ref1,			\
		 symbol_c *ref2 = NULL,			\
		 int fl = 0, int fc = 0, 		\
		 int ll = 0, int lc = 0);		\
    virtual void *accept(visitor_c &visitor);		\
};


#define SYM_REF3(class_name_c, ref1, ref2, ref3)	\
class class_name_c: public symbol_c {			\
  public:						\
    symbol_c *ref1;					\
    symbol_c *ref2;					\
    symbol_c *ref3;					\
  public:						\
    class_name_c(symbol_c *ref1,			\
		 symbol_c *ref2,			\
		 symbol_c *ref3,			\
		 int fl = 0, int fc = 0, 		\
		 int ll = 0, int lc = 0);		\
    virtual void *accept(visitor_c &visitor);		\
};


#define SYM_REF4(class_name_c, ref1, ref2, ref3, ref4)	\
class class_name_c: public symbol_c {			\
  public:						\
    symbol_c *ref1;					\
    symbol_c *ref2;					\
    symbol_c *ref3;					\
    symbol_c *ref4;					\
  public:						\
    class_name_c(symbol_c *ref1,			\
		 symbol_c *ref2,			\
		 symbol_c *ref3,			\
		 symbol_c *ref4 = NULL,			\
		 int fl = 0, int fc = 0, 		\
		 int ll = 0, int lc = 0);		\
    virtual void *accept(visitor_c &visitor);		\
};


#define SYM_REF5(class_name_c, ref1, ref2, ref3, ref4, ref5)		\
class class_name_c: public symbol_c {					\
  public:								\
    symbol_c *ref1;							\
    symbol_c *ref2;							\
    symbol_c *ref3;							\
    symbol_c *ref4;							\
    symbol_c *ref5;							\
  public:								\
    class_name_c(symbol_c *ref1,					\
		 symbol_c *ref2,					\
		 symbol_c *ref3,					\
		 symbol_c *ref4,					\
		 symbol_c *ref5,					\
		 int fl = 0, int fc = 0, 				\
		 int ll = 0, int lc = 0);				\
    virtual void *accept(visitor_c &visitor);				\
};


#define SYM_REF6(class_name_c, ref1, ref2, ref3, ref4, ref5, ref6)	\
class class_name_c: public symbol_c {					\
  public:								\
    symbol_c *ref1;							\
    symbol_c *ref2;							\
    symbol_c *ref3;							\
    symbol_c *ref4;							\
    symbol_c *ref5;							\
    symbol_c *ref6;							\
  public:								\
    class_name_c(symbol_c *ref1,					\
		 symbol_c *ref2,					\
		 symbol_c *ref3,					\
		 symbol_c *ref4,					\
		 symbol_c *ref5,					\
		 symbol_c *ref6 = NULL,					\
		 int fl = 0, int fc = 0, 				\
		 int ll = 0, int lc = 0);				\
    virtual void *accept(visitor_c &visitor);				\
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
