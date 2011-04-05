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
 * A generic symbol table.
 *
 * This is used to create symbol tables such as a list of
 * variables currently in scope, etc...
 * Note that the list of previously defined funstions uses the
 * dsymtable_c instead, as it requires the table to store duplicate values.
 */


#include <iostream>
#include "symtable.hh"



/* A macro for printing out internal parser errors... */
#define ERROR error_exit(__FILE__,__LINE__)
/* function defined in main.cc */
extern void error_exit(const char *file_name, int line_no);




template<typename value_type, value_type null_value>
symtable_c<value_type, null_value>::symtable_c(void) {inner_scope = NULL;}


 /* clear all entries... */
template<typename value_type, value_type null_value>
void symtable_c<value_type, null_value>::reset(void) {
  _base.clear();
}

 /* create new inner scope */
template<typename value_type, value_type null_value>
void symtable_c<value_type, null_value>::push(void) {
  if (inner_scope != NULL) {
    inner_scope->push();
  } else {
    inner_scope = new symtable_c();
  }
}

  /* clear most inner scope */
  /* returns 1 if this is the inner most scope	*/
  /*         0 otherwise			*/
template<typename value_type, value_type null_value>
int symtable_c<value_type, null_value>::pop(void) {
  if (inner_scope != NULL) {
    if (inner_scope->pop() == 1) {
      delete inner_scope;
      inner_scope = NULL;
    }
    return 0;
  } else {
    _base.clear();
    return 1;
  }
}

template<typename value_type, value_type null_value>
void symtable_c<value_type, null_value>::set(const symbol_c *symbol, value_t new_value) {
  if (inner_scope != NULL) {
    inner_scope->set(symbol, new_value);
    return;
  }

  const token_c *name = dynamic_cast<const token_c *>(symbol);
  if (name == NULL)
    ERROR;
  set(name->value, new_value);
}


template<typename value_type, value_type null_value>
void symtable_c<value_type, null_value>::set(const char *identifier_str, value_t new_value) {
  if (inner_scope != NULL) {
    inner_scope->set(identifier_str, new_value);
    return;
  }

  // std::cout << "set_identifier(" << identifier_str << "): \n";
  iterator i = _base.find(identifier_str);
  if (i == _base.end())
    /* identifier not already in map! */
    ERROR;

  _base[identifier_str] = new_value;
}

template<typename value_type, value_type null_value>
void symtable_c<value_type, null_value>::insert(const char *identifier_str, value_t new_value) {
  if (inner_scope != NULL) {
    inner_scope->insert(identifier_str, new_value);
    return;
  }

  // std::cout << "store_identifier(" << identifier_str << "): \n";
  std::pair<const char *, value_t> new_element(identifier_str, new_value);
  std::pair<iterator, bool> res = _base.insert(new_element);
  if (!res.second)
    /* error inserting new identifier... */
    /* identifier already in map?        */
    ERROR;
}

template<typename value_type, value_type null_value>
void symtable_c<value_type, null_value>::insert(const symbol_c *symbol, value_t new_value) {
/*
// not required...
  if (inner_scope != NULL) {
    inner_scope->insert(symbol, new_value);
    return;
  }
*/
  const token_c *name = dynamic_cast<const token_c *>(symbol);
  if (name == NULL)
    ERROR;
  insert(name->value, new_value);
}



/* returns null_value if not found! */
template<typename value_type, value_type null_value>
value_type symtable_c<value_type, null_value>::find_value(const char *identifier_str) {
  if (inner_scope != NULL) {
    value_t token = inner_scope->find_value(identifier_str);
    if (token != null_value)
      /* found in the lower level */
      return token;
  }

  /* if no lower level, or not found in lower level... */
  iterator i = _base.find(identifier_str);

  if (i == _base.end())
    return null_value;
  else
    return i->second;
}


template<typename value_type, value_type null_value>
value_type symtable_c<value_type, null_value>::find_value(const symbol_c *symbol) {
  const token_c *name = dynamic_cast<const token_c *>(symbol);
  if (name == NULL)
    ERROR;
  return find_value(name->value);
}


/* debuging function... */
template<typename value_type, value_type null_value>
void symtable_c<value_type, null_value>::print(void) {
  for(iterator i = _base.begin();
      i != _base.end();
      i++)
    std::cout << i->second << ":" << i->first << "\n";
  std::cout << "=====================\n";

  if (inner_scope != NULL) {
    inner_scope->print();
  }
}









