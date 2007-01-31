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



/* Determine the data type of a specific constant or variable.
 * A reference to the relevant type definition is returned.
 *
 * For example:
 *       22          -> returns reference to a int_type_name_c object.
 *       22.2        -> returns reference to a real_type_name_c object.
 *       LREAL#22.2  -> returns reference to a lreal_type_name_c object.
 *       etc...
 */
class search_constant_type_c: public search_visitor_c {

  public:
/**********************/
/* B.1.3 - Data types */
/**********************/
/***********************************/
/* B 1.3.1 - Elementary Data Types */
/***********************************/
  static real_type_name_c     real_type_name;
  static int_type_name_c      int_type_name;
  static string_type_name_c   string_type_name;
  static wstring_type_name_c  wstring_type_name;
  static time_type_name_c     time_type_name;
  static date_type_name_c     date_type_name;
  static dt_type_name_c       dt_type_name;
  static tod_type_name_c      tod_type_name;


  public:
    symbol_c *get_type(symbol_c *constant) {
      return (symbol_c *)constant->accept(*this);
    }

  public:
/*********************/
/* B 1.2 - Constants */
/*********************/

/******************************/
/* B 1.2.1 - Numeric Literals */
/******************************/
    void *visit(real_c *symbol) {return (void *)&real_type_name;}
    void *visit(integer_c *symbol) {return (void *)&int_type_name;}
    void *visit(binary_integer_c *symbol) {return (void *)&int_type_name;}
    void *visit(octal_integer_c *symbol) {return (void *)&int_type_name;}
    void *visit(hex_integer_c *symbol) {return (void *)&int_type_name;}

    void *visit(numeric_literal_c *symbol)
      {return (void *)((symbol->type!=NULL)?symbol->type:symbol->value->accept(*this));}
    void *visit(integer_literal_c *symbol)
      {return (void *)((symbol->type!=NULL)?symbol->type:symbol->value->accept(*this));}
    void *visit(real_literal_c *symbol)
      {return (void *)((symbol->type!=NULL)?symbol->type:symbol->value->accept(*this));}
    void *visit(bit_string_literal_c *symbol)
      {return (void *)((symbol->type!=NULL)?symbol->type:symbol->value->accept(*this));}
    void *visit(boolean_literal_c *symbol)
      {return (void *)((symbol->type!=NULL)?symbol->type:symbol->value->accept(*this));}

/*******************************/
/* B.1.2.2   Character Strings */
/*******************************/
    void *visit(double_byte_character_string_c *symbol) {return (void *)&wstring_type_name;}
    void *visit(single_byte_character_string_c *symbol) {return (void *)&string_type_name;}

/***************************/
/* B 1.2.3 - Time Literals */
/***************************/
/************************/
/* B 1.2.3.1 - Duration */
/************************/
    void *visit(neg_time_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
    void *visit(duration_c *symbol) {return (void *)&time_type_name;}
    void *visit(fixed_point_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
    void *visit(days_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
    void *visit(hours_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
    void *visit(minutes_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
    void *visit(seconds_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
    void *visit(milliseconds_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */

/************************************/
/* B 1.2.3.2 - Time of day and Date */
/************************************/
    void *visit(time_of_day_c *symbol) {return (void *)&tod_type_name;}
    void *visit(daytime_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
    void *visit(date_c *symbol) {return (void *)&date_type_name;}
    void *visit(date_literal_c *symbol) {ERROR; return NULL;}  /* this member function should never be called. */
    void *visit(date_and_time_c *symbol) {return (void *)&dt_type_name;}
};

real_type_name_c     search_constant_type_c::real_type_name;
int_type_name_c      search_constant_type_c::int_type_name;
string_type_name_c   search_constant_type_c::string_type_name;
wstring_type_name_c  search_constant_type_c::wstring_type_name;
time_type_name_c     search_constant_type_c::time_type_name;
date_type_name_c     search_constant_type_c::date_type_name;
dt_type_name_c       search_constant_type_c::dt_type_name;
tod_type_name_c      search_constant_type_c::tod_type_name;







