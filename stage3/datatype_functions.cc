/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2009-2012  Mario de Sousa (msousa@fe.up.pt)
 *  Copyright (C) 2012       Manuele Conti  (conti.ma@alice.it)
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

#include "datatype_functions.hh"
#include "../absyntax_utils/absyntax_utils.hh"





elementary_type_c *elementary_type_c::singleton = NULL;

const char *elementary_type_c::to_string(symbol_c *symbol) {
  if (NULL == singleton)    singleton = new elementary_type_c;
  if (NULL == singleton)    ERROR;
  const char *res           = (const char *)symbol->accept(*singleton);
  if (NULL == res) {
	  int i = 1;
  }
  return res;
}





/*
 * 2.5.1.5.6 Functions of time data types
 * Table 30 - page 64
 */

const struct widen_entry widen_ADD_table[] = {
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::time_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::tod_type_name,             &search_constant_type_c::tod_type_name      },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::dt_type_name,              &search_constant_type_c::dt_type_name       },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::safetod_type_name,         &search_constant_type_c::safetod_type_name  },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::safedt_type_name,          &search_constant_type_c::safedt_type_name   },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::time_type_name,            &search_constant_type_c::tod_type_name      },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::time_type_name,            &search_constant_type_c::tod_type_name      },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::safetime_type_name,        &search_constant_type_c::tod_type_name      },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safetod_type_name  },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::time_type_name,            &search_constant_type_c::dt_type_name       },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::time_type_name,            &search_constant_type_c::dt_type_name       },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::safetime_type_name,        &search_constant_type_c::dt_type_name       },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safedt_type_name   },
    { NULL, NULL, NULL },
};


const struct widen_entry widen_SUB_table[] = {
	{ &search_constant_type_c::time_type_name,          &search_constant_type_c::time_type_name,            &search_constant_type_c::time_type_name     },
	{ &search_constant_type_c::tod_type_name,           &search_constant_type_c::tod_type_name,             &search_constant_type_c::tod_type_name      },
	{ &search_constant_type_c::dt_type_name,            &search_constant_type_c::dt_type_name,              &search_constant_type_c::dt_type_name       },
	{ &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safetime_type_name },
	{ &search_constant_type_c::safetod_type_name,       &search_constant_type_c::safetod_type_name,         &search_constant_type_c::safetod_type_name  },
	{ &search_constant_type_c::safedt_type_name,        &search_constant_type_c::safedt_type_name,          &search_constant_type_c::safedt_type_name   },

	{ &search_constant_type_c::tod_type_name,           &search_constant_type_c::time_type_name,            &search_constant_type_c::tod_type_name      },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::time_type_name,            &search_constant_type_c::tod_type_name      },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::safetime_type_name,        &search_constant_type_c::tod_type_name      },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safetod_type_name  },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::time_type_name,            &search_constant_type_c::dt_type_name       },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::time_type_name,            &search_constant_type_c::dt_type_name       },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::safetime_type_name,        &search_constant_type_c::dt_type_name       },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safedt_type_name   },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::tod_type_name,             &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::tod_type_name,             &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::safetod_type_name,         &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::safetod_type_name,         &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::date_type_name,          &search_constant_type_c::date_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::safedate_type_name,      &search_constant_type_c::date_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::date_type_name,          &search_constant_type_c::safedate_type_name,        &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::safedate_type_name,      &search_constant_type_c::safedate_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::dt_type_name,              &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::dt_type_name,              &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::safedt_type_name,          &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::safedt_type_name,          &search_constant_type_c::safetime_type_name },
    { NULL, NULL, NULL },
};

const struct widen_entry widen_MUL_table[] = {
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::lreal_type_name,           &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::real_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::dint_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::int_type_name,             &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::sint_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::ulint_type_name,           &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::udint_type_name,           &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::uint_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::usint_type_name,           &search_constant_type_c::time_type_name     },

    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::lreal_type_name,           &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::real_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::dint_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::int_type_name,             &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::sint_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::ulint_type_name,           &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::udint_type_name,           &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::uint_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::usint_type_name,           &search_constant_type_c::safetime_type_name },

    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safelreal_type_name,       &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safereal_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safedint_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeint_type_name,         &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safesint_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeulint_type_name,       &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeudint_type_name,       &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeuint_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeusint_type_name,       &search_constant_type_c::safetime_type_name },

    { NULL, NULL, NULL },
};

const struct widen_entry widen_DIV_table[] = {
	{ &search_constant_type_c::time_type_name,          &search_constant_type_c::lreal_type_name,           &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::real_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::dint_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::int_type_name,             &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::sint_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::ulint_type_name,           &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::udint_type_name,           &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::uint_type_name,            &search_constant_type_c::time_type_name     },
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::usint_type_name,           &search_constant_type_c::time_type_name     },

    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::lreal_type_name,           &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::real_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::dint_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::int_type_name,             &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::sint_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::ulint_type_name,           &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::udint_type_name,           &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::uint_type_name,            &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::usint_type_name,           &search_constant_type_c::safetime_type_name },

    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safelreal_type_name,       &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safereal_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safedint_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeint_type_name,         &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safesint_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeulint_type_name,       &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeudint_type_name,       &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeuint_type_name,        &search_constant_type_c::safetime_type_name },
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safeusint_type_name,       &search_constant_type_c::safetime_type_name },

    { NULL, NULL, NULL },
};

/* Search for a datatype inside a candidate_datatypes list.
 * Returns: position of datatype in the list, or -1 if not found.
 */
int search_in_datatype_list(symbol_c *datatype, std::vector <symbol_c *> candidate_datatypes) {
	for(unsigned int i = 0; i < candidate_datatypes.size(); i++)
		if (is_type_equal(datatype, candidate_datatypes[i]))
			return i;
	/* Not found ! */
	return -1;
}


/* A helper function... */
bool is_ANY_ELEMENTARY_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  return is_ANY_MAGNITUDE_type(type_symbol)
      || is_ANY_BIT_type      (type_symbol)
      || is_ANY_STRING_type   (type_symbol)
      || is_ANY_DATE_type     (type_symbol);
}

/* A helper function... */
bool is_ANY_SAFEELEMENTARY_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  return is_ANY_SAFEMAGNITUDE_type(type_symbol)
      || is_ANY_SAFEBIT_type      (type_symbol)
      || is_ANY_SAFESTRING_type   (type_symbol)
      || is_ANY_SAFEDATE_type     (type_symbol);
}

/* A helper function... */
bool is_ANY_ELEMENTARY_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  /* NOTE: doing
   *          return is_ANY_SAFEELEMENTARY_type() || is_ANY_ELEMENTARY_type()
   *       is incorrect, as the literals would never be considered compatible...
   */
  return is_ANY_MAGNITUDE_compatible(type_symbol)
      || is_ANY_BIT_compatible      (type_symbol)
      || is_ANY_STRING_compatible   (type_symbol)
      || is_ANY_DATE_compatible     (type_symbol);
}


/* A helper function... */
bool is_ANY_MAGNITUDE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(time_type_name_c)) {return true;}
  return is_ANY_NUM_type(type_symbol);
}

/* A helper function... */
bool is_ANY_signed_MAGNITUDE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(time_type_name_c)) {return true;}
  return is_ANY_signed_NUM_type(type_symbol);
}

/* A helper function... */
bool is_ANY_SAFEMAGNITUDE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safetime_type_name_c)) {return true;}
  return is_ANY_SAFENUM_type(type_symbol);
}

/* A helper function... */
bool is_ANY_signed_SAFEMAGNITUDE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safetime_type_name_c)) {return true;}
  return is_ANY_signed_SAFENUM_type(type_symbol);
}

/* A helper function... */
bool is_ANY_MAGNITUDE_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_MAGNITUDE_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEMAGNITUDE_type(type_symbol))              {return true;}
  return is_ANY_NUM_compatible(type_symbol);
}

/* A helper function... */
bool is_ANY_signed_MAGNITUDE_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_signed_MAGNITUDE_type    (type_symbol))       {return true;}
  if (is_ANY_signed_SAFEMAGNITUDE_type(type_symbol))       {return true;}
  return is_ANY_signed_NUM_compatible(type_symbol);
}

/* A helper function... */
bool is_ANY_NUM_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_type(type_symbol))                       {return true;}
  if (is_ANY_INT_type(type_symbol))                        {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_signed_NUM_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_type(type_symbol))                       {return true;}
  if (is_ANY_signed_INT_type(type_symbol))                 {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFENUM_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  return is_ANY_SAFEREAL_type(type_symbol)
      || is_ANY_SAFEINT_type (type_symbol);
}

/* A helper function... */
bool is_ANY_signed_SAFENUM_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  return is_ANY_SAFEREAL_type(type_symbol)
      || is_ANY_signed_SAFEINT_type (type_symbol);
}

/* A helper function... */
bool is_ANY_NUM_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_compatible(type_symbol))                       {return true;}
  if (is_ANY_INT_compatible(type_symbol))                        {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_signed_NUM_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_compatible(type_symbol))                       {return true;}
  if (is_ANY_signed_INT_compatible(type_symbol))                 {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_DATE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(date_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(tod_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(dt_type_name_c))   {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFEDATE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safedate_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safetod_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safedt_type_name_c))   {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_DATE_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_DATE_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEDATE_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_STRING_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(string_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(wstring_type_name_c)) {return true;}
// TODO literal_string ???
  return false;
}

/* A helper function... */
bool is_ANY_SAFESTRING_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safestring_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safewstring_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_STRING_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_STRING_type    (type_symbol))              {return true;}
  if (is_ANY_SAFESTRING_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_INT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(sint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(int_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(dint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(lint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(usint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(uint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(udint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(ulint_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_signed_INT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(sint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(int_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(dint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(lint_type_name_c))  {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_signed_SAFEINT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safesint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safeint_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(safedint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safelint_type_name_c))  {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFEINT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safesint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safeint_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(safedint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safelint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safeusint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safeuint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safeudint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safeulint_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_signed_INT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_signed_INT_type    (type_symbol))              {return true;}
  if (is_ANY_signed_SAFEINT_type(type_symbol))              {return true;}
//   if (is_literal_integer_type(type_symbol))          {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_INT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_INT_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEINT_type(type_symbol))              {return true;}
//   if (is_literal_integer_type(type_symbol))          {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_REAL_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(real_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(lreal_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFEREAL_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safereal_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safelreal_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_REAL_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEREAL_type(type_symbol))              {return true;}
//   if (is_literal_real_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_BIT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(bool_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(byte_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(word_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(dword_type_name_c))    {return true;}
  if (typeid(*type_symbol) == typeid(lword_type_name_c))    {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFEBIT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safebool_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(safebyte_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(safeword_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(safedword_type_name_c))    {return true;}
  if (typeid(*type_symbol) == typeid(safelword_type_name_c))    {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_BIT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_BIT_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEBIT_type(type_symbol))              {return true;}
//   if (is_nonneg_literal_integer_type(type_symbol))   {return true;}
//   if (is_literal_bool_type(type_symbol))             {return true;}
  return false;
}

/* A helper function... */
bool is_BOOL_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(bool_type_name_c))      {return true;}
  return false;
}

/* A helper function... */
bool is_SAFEBOOL_type(symbol_c *type_symbol){
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safebool_type_name_c))  {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_BOOL_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_BOOL_type    (type_symbol))              {return true;}
  if (is_SAFEBOOL_type(type_symbol))              {return true;}
//   if (is_literal_bool_type(type_symbol))              {return true;}
  return false;
}



#if 0
/* A helper function... */
bool is_literal_integer_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(neg_integer_c))        {return true;}
  return is_nonneg_literal_integer_type(type_symbol);
}


/* A helper function... */
bool is_nonneg_literal_integer_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(integer_c))        {return true;}
  if (typeid(*type_symbol) == typeid(binary_integer_c)) {return true;}
  if (typeid(*type_symbol) == typeid(octal_integer_c))  {return true;}
  if (typeid(*type_symbol) == typeid(hex_integer_c))    {return true;}
  return false;
}


/* A helper function... */
bool is_literal_real_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(real_c))     {return true;}
  if (typeid(*type_symbol) == typeid(neg_real_c)) {return true;}
  return false;
}


/* A helper function... */
bool is_literal_bool_type(symbol_c *type_symbol) {
  bool_type_name_c bool_t;

  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(boolean_true_c))    {return true;}
  if (typeid(*type_symbol) == typeid(boolean_false_c))   {return true;}
  if (is_nonneg_literal_integer_type(type_symbol))
    if (sizeoftype(&bool_t) >= sizeoftype(type_symbol))  {return true;}
  return false;
}

/* Determine the common data type between two data types.
 * If no common data type found, return NULL.
 *
 * If data types are identical, return the first (actually any would do...).
 * If any of the data types is a literal, we confirm that
 *   the literal uses less bits than the fixed size data type.
 *   e.g. BYTE and 1024 returns NULL
 *        BYTE and 255  returns BYTE
 *
 * If two literals, then return the literal that requires more bits...
 */

symbol_c *common_type(symbol_c *first_type, symbol_c *second_type) {
  if (first_type == NULL && second_type == NULL) {return NULL;}
  if (first_type == NULL)  {return second_type;}
  if (second_type == NULL) {return first_type;}

  if (is_literal_integer_type(first_type) && is_literal_integer_type(second_type))
    {return ((sizeoftype(first_type) > sizeoftype(second_type))? first_type:second_type);}

  if (is_literal_real_type(first_type) && is_literal_real_type(second_type))
    {return ((sizeoftype(first_type) > sizeoftype(second_type))? first_type:second_type);}

  if (is_literal_bool_type(first_type) && is_literal_bool_type(second_type))
    {return first_type;}

  /* The following check can only be made after the is_literal_XXXX checks */
  /* When two literals of the same type, with identical typeid's are checked,
   * we must return the one that occupies more bits... This is done above.
   */
  if (typeid(*first_type) == typeid(*second_type)) {return first_type;}

  /* NOTE Although a BOOL is also an ANY_BIT, we must check it explicitly since some
   *       literal bool values are not literal integers...
   */
  if (is_BOOL_type(first_type)        && is_literal_bool_type(second_type))    {return first_type;}
  if (is_BOOL_type(second_type)       && is_literal_bool_type(first_type))     {return second_type;}

  if (is_SAFEBOOL_type(first_type)    && is_literal_bool_type(second_type))    {return first_type;}
  if (is_SAFEBOOL_type(second_type)   && is_literal_bool_type(first_type))     {return second_type;}

  if (is_SAFEBOOL_type(first_type)    && is_BOOL_type(second_type))            {return second_type;}
  if (is_SAFEBOOL_type(second_type)   && is_BOOL_type(first_type))             {return first_type;}

  if (is_ANY_BIT_type(first_type)     && is_nonneg_literal_integer_type(second_type))
    {return ((sizeoftype(first_type)  >= sizeoftype(second_type))? first_type :NULL);}
  if (is_ANY_BIT_type(second_type)    && is_nonneg_literal_integer_type(first_type))
    {return ((sizeoftype(second_type) >= sizeoftype(first_type)) ? second_type:NULL);}

  if (is_ANY_SAFEBIT_type(first_type)     && is_nonneg_literal_integer_type(second_type))
    {return ((sizeoftype(first_type)  >= sizeoftype(second_type))? first_type :NULL);}
  if (is_ANY_SAFEBIT_type(second_type)    && is_nonneg_literal_integer_type(first_type))
    {return ((sizeoftype(second_type) >= sizeoftype(first_type)) ? second_type:NULL);}

  if  (is_ANY_SAFEBIT_type(first_type)    && is_ANY_BIT_type(second_type))
    {return ((sizeoftype(first_type) == sizeoftype(second_type))? second_type:NULL);}
  if  (is_ANY_SAFEBIT_type(second_type)   && is_ANY_BIT_type(first_type))
    {return ((sizeoftype(first_type) == sizeoftype(second_type))? first_type :NULL);}

  if (is_ANY_INT_type(first_type)     && is_literal_integer_type(second_type))
    {return ((sizeoftype(first_type)  >= sizeoftype(second_type))? first_type :NULL);}
  if (is_ANY_INT_type(second_type)    && is_literal_integer_type(first_type))
    {return ((sizeoftype(second_type) >= sizeoftype(first_type)) ? second_type:NULL);}

  if (is_ANY_SAFEINT_type(first_type)     && is_literal_integer_type(second_type))
    {return ((sizeoftype(first_type)  >= sizeoftype(second_type))? first_type :NULL);}
  if (is_ANY_SAFEINT_type(second_type)    && is_literal_integer_type(first_type))
    {return ((sizeoftype(second_type) >= sizeoftype(first_type)) ? second_type:NULL);}

  if  (is_ANY_SAFEINT_type(first_type)    && is_ANY_INT_type(second_type))
    {return ((sizeoftype(first_type) == sizeoftype(second_type))? second_type:NULL);}
  if  (is_ANY_SAFEINT_type(second_type)   && is_ANY_INT_type(first_type))
    {return ((sizeoftype(first_type) == sizeoftype(second_type))? first_type :NULL);}

  if (is_ANY_REAL_type(first_type)    && is_literal_real_type(second_type))
    {return ((sizeoftype(first_type)  >= sizeoftype(second_type))? first_type :NULL);}
  if (is_ANY_REAL_type(second_type)   && is_literal_real_type(first_type))
    {return ((sizeoftype(second_type) >= sizeoftype(first_type)) ? second_type:NULL);}

  if (is_ANY_SAFEREAL_type(first_type)    && is_literal_real_type(second_type))
    {return ((sizeoftype(first_type)  >= sizeoftype(second_type))? first_type :NULL);}
  if (is_ANY_SAFEREAL_type(second_type)   && is_literal_real_type(first_type))
    {return ((sizeoftype(second_type) >= sizeoftype(first_type)) ? second_type:NULL);}

  if  (is_ANY_SAFEREAL_type(first_type)    && is_ANY_REAL_type(second_type))
    {return ((sizeoftype(first_type) == sizeoftype(second_type))? second_type:NULL);}
  if  (is_ANY_SAFEREAL_type(second_type)   && is_ANY_REAL_type(first_type))
    {return ((sizeoftype(first_type) == sizeoftype(second_type))? first_type :NULL);}

  /* the Time and Date types... */
  if (is_type(first_type,  safetime_type_name_c) && is_type(second_type, time_type_name_c))  {return second_type;}
  if (is_type(second_type, safetime_type_name_c) && is_type( first_type, time_type_name_c))  {return  first_type;}

  if (is_type(first_type,  safedate_type_name_c) && is_type(second_type, date_type_name_c))  {return second_type;}
  if (is_type(second_type, safedate_type_name_c) && is_type( first_type, date_type_name_c))  {return  first_type;}

  if (is_type(first_type,  safedt_type_name_c)   && is_type(second_type, dt_type_name_c))    {return second_type;}
  if (is_type(second_type, safedt_type_name_c)   && is_type( first_type, dt_type_name_c))    {return  first_type;}

  if (is_type(first_type,  safetod_type_name_c)  && is_type(second_type, tod_type_name_c))   {return second_type;}
  if (is_type(second_type, safetod_type_name_c)  && is_type( first_type, tod_type_name_c))   {return  first_type;}

  /* no common type */
  return NULL;
}

/* Return TRUE if the second (value) data type may be assigned to a variable of the first (variable) data type
 * such as:
 *     var_type     value_type
 *    BOOL           BYTE#7     -> returns false
 *    INT            INT#7      -> returns true
 *    INT            7          -> returns true
 *    REAL           7.89       -> returns true
 *    REAL           7          -> returns true
 *    INT            7.89       -> returns false
 *    SAFEBOOL       BOOL#1     -> returns false   !!!
 *   etc...
 *
 * NOTE: It is assumed that the var_type is the data type of an lvalue
 */
bool is_valid_assignment(symbol_c *var_type, symbol_c *value_type) {
  if (var_type == NULL)   {/* STAGE3_ERROR(value_type, value_type, "Var_type   == NULL"); */ return false;}
  if (value_type == NULL) {/* STAGE3_ERROR(var_type,   var_type,   "Value_type == NULL"); */ return false;}

  symbol_c *common_type_symbol = common_type(var_type, value_type);
  if (NULL == common_type_symbol)
    return false;
  return (typeid(*var_type) == typeid(*common_type_symbol));
}


/* Return TRUE if there is a common data type, otherwise return FALSE
 * i.e., return TRUE if both data types may be used simultaneously in an expression
 * such as:
 *    BOOL#0     AND BYTE#7  -> returns false
 *    0          AND BYTE#7  -> returns true
 *    INT#10     AND INT#7   -> returns true
 *    INT#10     AND 7       -> returns true
 *    REAL#34.3  AND 7.89    -> returns true
 *    REAL#34.3  AND 7       -> returns true
 *    INT#10     AND 7.89    -> returns false
 *    SAFEBOOL#0 AND BOOL#1  -> returns true   !!!
 *   etc...
 */
bool is_compatible_type(symbol_c *first_type, symbol_c *second_type) {
  if (first_type == NULL || second_type == NULL) {return false;}
  return (NULL != common_type(first_type, second_type));
}
#endif

bool is_type_equal(symbol_c *first_type, symbol_c *second_type)
{
    if (first_type == NULL || second_type == NULL) {
        return false;
    }
    if (is_ANY_ELEMENTARY_type(first_type)) {
        if (typeid(*first_type) == typeid(*second_type))
            return true;
    } else   /* ANY_DERIVED */
        return (first_type == second_type);

    return false;
}
