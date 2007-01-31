/*
 * (c) 2005 Mario de Sousa
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
 * A generic symbol table that allows duplicate values.
 *
 * This is used to create a symbol table of previously defined
 * functions. Duplicate are allowed since the standard permits function\
 * overloading in the standard library.
 */



#ifndef _DSYMTABLE_HH
#define _DSYMTABLE_HH

#include "../absyntax/absyntax.hh"

#include <map>
#include <string>




template<typename value_type, value_type null_value> class dsymtable_c {
  /* Case insensitive string compare copied from
   * "The C++ Programming Language" - 3rd Edition
   * by Bjarne Stroustrup, ISBN 0201889544.
   */
  class nocase_c {
    public:
      bool operator() (const std::string& x, const std::string& y) const {
        std::string::const_iterator ix = x.begin();
        std::string::const_iterator iy = y.begin();

        for(; (ix != x.end()) && (iy != y.end()) && (toupper(*ix) == toupper(*iy)); ++ix, ++iy);
        if (ix == x.end()) return (iy != y.end());
        if (iy == y.end()) return false;
        return (toupper(*ix) < toupper(*iy));
      };
  };

  public:
    typedef value_type value_t;

  private:
    /* Comparison between identifiers must ignore case, therefore the use of nocase_c */
    typedef std::multimap<std::string, value_t, nocase_c> base_t;
    base_t _base;

  public:
  typedef typename base_t::iterator iterator;
  typedef typename base_t::const_iterator const_iterator;
  typedef typename base_t::reverse_iterator reverse_iterator;
  typedef typename base_t::const_reverse_iterator const_reverse_iterator;

  private:
    void reset(void); /* clear all entries... */

  public:
    dsymtable_c(void) {};

    void insert(const char *identifier_str, value_t value);
    void insert(const symbol_c *symbol, value_t value);

    /* Search for an entry. Will return end_value() if not found */
    value_t end_value(void) {return null_value;}
    value_t find_value(const char *identifier_str);
    value_t find_value(const symbol_c *symbol);

    iterator find(const char *identifier_str) {return _base.find(identifier_str);}

  /* iterators pointing to beg/end of map... */
    iterator begin() 			{return _base.begin();}
    const_iterator begin() const	{return _base.begin();}
    iterator end()			{return _base.end();}
    const_iterator end() const 		{return _base.end();}
    reverse_iterator rbegin()		{return _base.rbegin();}
    const_reverse_iterator rbegin() const {return _base.rbegin();}
    reverse_iterator rend() 		{return _base.rend();}
    const_reverse_iterator rend() const	{return _base.rend();}

    /* debuging function... */
    void print(void);
};



/* Templates must include the source into the code! */
#include "dsymtable.cc"

#endif /*  _DSYMTABLE_HH */
