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
 * An IEC 61131-3 compiler.
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


#include "../absyntax/visitor.hh"


class search_constant_type_c: public search_visitor_c {

  public:
  /**********************/
  /* B.1.3 - Data types */
  /**********************/
  /***********************************/
  /* B 1.3.1 - Elementary Data Types */
  /***********************************/
  static real_type_name_c     real_type_name;
  static sint_type_name_c     sint_type_name;
  static lint_type_name_c     lint_type_name;
  static dint_type_name_c     dint_type_name;
  static date_type_name_c     date_type_name;
  static dword_type_name_c    dword_type_name;
  static dt_type_name_c       dt_type_name;
  static tod_type_name_c      tod_type_name;
  static udint_type_name_c    udint_type_name;
  static word_type_name_c     word_type_name;
  static wstring_type_name_c  wstring_type_name;
  static string_type_name_c   string_type_name;
  static lword_type_name_c    lword_type_name;
  static uint_type_name_c     uint_type_name;
  static lreal_type_name_c    lreal_type_name;
  static byte_type_name_c     byte_type_name;
  static usint_type_name_c    usint_type_name;
  static ulint_type_name_c    ulint_type_name;
  static bool_type_name_c     bool_type_name;
  static time_type_name_c     time_type_name;
  static int_type_name_c      int_type_name;

/* temporarily here until we remove the st_code_gen.c and il_code_gen.c files... */
  static integer_c      integer;

  /******************************************************/
  /* Extensions to the base standard as defined in      */
  /* "Safety Software Technical Specification,          */
  /*  Part 1: Concepts and Function Blocks,             */
  /*  Version 1.0 – Official Release"                   */
  /* by PLCopen - Technical Committee 5 - 2006-01-31    */
  /******************************************************/
 
//  static safebool_type_name_c          safebool_type_name;
  /* The following is required because the expression (TOD_var - TOD_var) will result in a data type
   *  (in this case, TIME) that is neither of the expression elements...
   */
  static safetime_type_name_c     safetime_type_name;
  static safetod_type_name_c      safetod_type_name;
  static safedt_type_name_c       safedt_type_name;



  public:
    symbol_c *get_type(symbol_c *constant);


  private:
    /*********************/
    /* B 1.2 - Constants */
    /*********************/

    /******************************/
    /* B 1.2.1 - Numeric Literals */
    /******************************/
    void *visit(real_c *symbol);
    void *visit(neg_real_c *symbol);
    void *visit(integer_c *symbol);
    void *visit(neg_integer_c *symbol);
    void *visit(binary_integer_c *symbol);
    void *visit(octal_integer_c *symbol);
    void *visit(hex_integer_c *symbol);

    void *visit(integer_literal_c *symbol);
    void *visit(real_literal_c *symbol);
    void *visit(bit_string_literal_c *symbol);
    void *visit(boolean_literal_c *symbol);

    void *visit(boolean_true_c *symbol);
    void *visit(boolean_false_c *symbol);

    /*******************************/
    /* B.1.2.2   Character Strings */
    /*******************************/
    void *visit(double_byte_character_string_c *symbol);
    void *visit(single_byte_character_string_c *symbol);

    /***************************/
    /* B 1.2.3 - Time Literals */
    /***************************/
    /************************/
    /* B 1.2.3.1 - Duration */
    /************************/
    void *visit(neg_time_c *symbol);
    void *visit(duration_c *symbol);
    void *visit(fixed_point_c *symbol);
    void *visit(days_c *symbol);
    void *visit(hours_c *symbol);
    void *visit(minutes_c *symbol);
    void *visit(seconds_c *symbol);
    void *visit(milliseconds_c *symbol);

    /************************************/
    /* B 1.2.3.2 - Time of day and Date */
    /************************************/
    void *visit(time_of_day_c *symbol);
    void *visit(daytime_c *symbol);
    void *visit(date_c *symbol);
    void *visit(date_literal_c *symbol);
    void *visit(date_and_time_c *symbol);

    /********************************/
    /* B 1.3.3 - Derived data types */
    /********************************/
    void *visit(enumerated_value_c *symbol);
};  // search_constant_type_c



