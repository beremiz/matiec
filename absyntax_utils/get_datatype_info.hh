/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2003-2012  Mario de Sousa (msousa@fe.up.pt)
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

/* Determine the characteristics of a specific data type
 *  e.g., is it an enumeration, is it an array, is it ANY_INT, etc...
 *
 * The methods of this class may be passed either:
 *  - a data type declaration symbol_c, 
 *   OR
 *  - the name of a data type (identifier_c)
 *    In this case, we shall first serach for the basetype declaration using search_base_type_c, and then 
 *    run the normal process.
 */
#include "absyntax_utils.hh"

#include "../main.hh" // required for ERROR() and ERROR_MSG() macros.






class get_datatype_info_c { 


  private: // this is a purely static class. No need for constructors!
     get_datatype_info_c(void) {};
    ~get_datatype_info_c(void) {};

 
  public:
    static bool is_type_equal(symbol_c *first_type, symbol_c *second_type);
    static bool is_type_valid(symbol_c *type);
      
    static bool is_ANY_REAL_literal(symbol_c *type_symbol); /* Can't we do away with this?? */
    static bool is_ANY_INT_literal (symbol_c *type_symbol); /* Can't we do away with this?? */

    static bool is_sfc_initstep                    (symbol_c *type_symbol);
    static bool is_sfc_step                        (symbol_c *type_symbol);
    static bool is_function_block                  (symbol_c *type_symbol);
    static bool is_subrange                        (symbol_c *type_symbol);
    static bool is_enumerated                      (symbol_c *type_symbol);
    static bool is_array                           (symbol_c *type_symbol);
    static bool is_structure                       (symbol_c *type_symbol);

  
  
    static bool is_ANY_ELEMENTARY                  (symbol_c *type_symbol);
    static bool is_ANY_SAFEELEMENTARY              (symbol_c *type_symbol);
    static bool is_ANY_ELEMENTARY_compatible       (symbol_c *type_symbol);

    static bool is_ANY_MAGNITUDE                   (symbol_c *type_symbol);
    static bool is_ANY_SAFEMAGNITUDE               (symbol_c *type_symbol);
    static bool is_ANY_MAGNITUDE_compatible        (symbol_c *type_symbol);

    static bool is_ANY_signed_MAGNITUDE            (symbol_c *type_symbol);
    static bool is_ANY_signed_SAFEMAGNITUDE        (symbol_c *type_symbol);
    static bool is_ANY_signed_MAGNITUDE_compatible (symbol_c *type_symbol);

    static bool is_ANY_NUM                         (symbol_c *type_symbol);
    static bool is_ANY_SAFENUM                     (symbol_c *type_symbol);
    static bool is_ANY_NUM_compatible              (symbol_c *type_symbol);

    static bool is_ANY_signed_NUM                  (symbol_c *type_symbol);
    static bool is_ANY_signed_SAFENUM              (symbol_c *type_symbol);
    static bool is_ANY_signed_NUM_compatible       (symbol_c *type_symbol);

    static bool is_ANY_INT                         (symbol_c *type_symbol);
    static bool is_ANY_SAFEINT                     (symbol_c *type_symbol);
    static bool is_ANY_INT_compatible              (symbol_c *type_symbol);

    static bool is_ANY_signed_INT                  (symbol_c *type_symbol);
    static bool is_ANY_signed_SAFEINT              (symbol_c *type_symbol);
    static bool is_ANY_signed_INT_compatible       (symbol_c *type_symbol);

    static bool is_ANY_unsigned_INT                (symbol_c *type_symbol);
    static bool is_ANY_unsigned_SAFEINT            (symbol_c *type_symbol);
    static bool is_ANY_unsigned_INT_compatible     (symbol_c *type_symbol);

    static bool is_ANY_REAL                        (symbol_c *type_symbol);
    static bool is_ANY_SAFEREAL                    (symbol_c *type_symbol);
    static bool is_ANY_REAL_compatible             (symbol_c *type_symbol);

    static bool is_ANY_nBIT                        (symbol_c *type_symbol);
    static bool is_ANY_SAFEnBIT                    (symbol_c *type_symbol);
    static bool is_ANY_nBIT_compatible             (symbol_c *type_symbol);

    static bool is_BOOL                            (symbol_c *type_symbol);
    static bool is_SAFEBOOL                        (symbol_c *type_symbol);
    static bool is_BOOL_compatible                 (symbol_c *type_symbol);

    static bool is_ANY_BIT                         (symbol_c *type_symbol);
    static bool is_ANY_SAFEBIT                     (symbol_c *type_symbol);
    static bool is_ANY_BIT_compatible              (symbol_c *type_symbol);

    static bool is_ANY_DATE                        (symbol_c *type_symbol);
    static bool is_ANY_SAFEDATE                    (symbol_c *type_symbol);
    static bool is_ANY_DATE_compatible             (symbol_c *type_symbol);

    static bool is_TIME                            (symbol_c *type_symbol);
    static bool is_SAFETIME                        (symbol_c *type_symbol);
    static bool is_TIME_compatible                 (symbol_c *type_symbol);

    static bool is_ANY_STRING                      (symbol_c *type_symbol);
    static bool is_ANY_SAFESTRING                  (symbol_c *type_symbol);
    static bool is_ANY_STRING_compatible           (symbol_c *type_symbol);

};

