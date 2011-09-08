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

/*
 * A generic symbol table that allows duplicate values.
 *
 * This is used to create a symbol table of previously defined
 * functions. Duplicate are allowed since the standard permits function\
 * overloading in the standard library.
 */


#include <iostream>
#include "symtable.hh"



/* A macro for printing out internal parser errors... */
#define ERROR error_exit(__FILE__,__LINE__)
/* function defined in main.cc */
extern void error_exit(const char *file_name, int line_no);




 /* clear all entries... */
template<typename value_type, value_type null_value>
void dsymtable_c<value_type, null_value>::reset(void) {
  _base.clear();
}


template<typename value_type, value_type null_value>
void dsymtable_c<value_type, null_value>::insert(const char *identifier_str, value_t new_value) {
  // std::cout << "store_identifier(" << identifier_str << "): \n";
  std::pair<const char *, value_t> new_element(identifier_str, new_value);
  /* iterator res = */ _base.insert(new_element);
}


template<typename value_type, value_type null_value>
void dsymtable_c<value_type, null_value>::insert(const symbol_c *symbol, value_t new_value) {
  const token_c *name = dynamic_cast<const token_c *>(symbol);
  if (name == NULL)
    ERROR;
  insert(name->value, new_value);
}


#if 0
template<typename value_type, value_type null_value>
void dsymtable_c<value_type, null_value>::insert_noduplicate(const char *identifier_str, value_t new_value) {
  if (find_value(identifier_str) != null_value)
    /* already present in the set! */
    ERROR;

  // std::cout << "store_identifier(" << identifier_str << "): \n";
  std::pair<const char *, value_t> new_element(identifier_str, new_value);
  /* iterator res = */ _base.insert(new_element);
}


template<typename value_type, value_type null_value>
void dsymtable_c<value_type, null_value>::insert_noduplicate(const symbol_c *symbol, value_t new_value) {
  const token_c *name = dynamic_cast<const token_c *>(symbol);
  if (name == NULL)
    ERROR;
  insert_noduplicate(name->value, new_value);
}
#endif



/* Determine how many entries are associated to key identifier_str */ 
/* returns:
 *         0: if no entry is found
 *         1: if 1 entry is found
 *         2: if more than 1 entry is found 
 */
template<typename value_type, value_type null_value>
int dsymtable_c<value_type, null_value>::multiplicity(const char *identifier_str) {
  iterator lower = _base.lower_bound(identifier_str);
  if (lower == _base.end()) return 0;

  iterator upper = _base.upper_bound(identifier_str);
  iterator second = lower;
  second++;
  
  if (second == upper) return 1;
  
  return 2;
}


/* returns null_value if not found! */
template<typename value_type, value_type null_value>
value_type dsymtable_c<value_type, null_value>::find_value(const char *identifier_str) {
  iterator i = _base.find(identifier_str);

  if (i == _base.end())
    return null_value;
  else
    return i->second;
}


template<typename value_type, value_type null_value>
const char * dsymtable_c<value_type, null_value>::symbol_to_string(const symbol_c *symbol) {
  const token_c *name = dynamic_cast<const token_c *>(symbol);
  if (name == NULL)
    ERROR;
  return name->value;
}


/* debuging function... */
template<typename value_type, value_type null_value>
void dsymtable_c<value_type, null_value>::print(void) {
  for(iterator i = _base.begin();
      i != _base.end();
      i++)
    std::cout << i->second << ":" << i->first << "\n";
  std::cout << "=====================\n";
}









