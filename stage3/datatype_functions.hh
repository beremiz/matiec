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

#ifndef _HELPER_FUNCTIONS_HH_
#define _HELPER_FUNCTIONS_HH_

#include "../absyntax/visitor.hh"
#include <typeinfo>





typedef struct {
  symbol_c *function_name;
  symbol_c *nonformal_operand_list;
  symbol_c *   formal_operand_list;

  enum {POU_FB, POU_function} POU_type;
//symbol_c &*datatype;
//std::vector <symbol_c *> &candidate_datatypes;
  std::vector <symbol_c *> &candidate_functions;
  symbol_c *&called_function_declaration;
  int      &extensible_param_count;
} generic_function_call_t;



/* A small helper class, to transform elementary data type to string.
 * this allows us to generate more relevant error messages...
 */

class elementary_type_c: public null_visitor_c {
  protected:
    elementary_type_c(void)  {};
    ~elementary_type_c(void) {};

  private:
    /* singleton class! */
    static elementary_type_c *singleton;

  public:
    static const char * to_string(symbol_c *symbol);


    /***********************************/
    /* B 1.3.1 - Elementary Data Types */
    /***********************************/
    void *visit(time_type_name_c        *symbol) {return (void *)"TIME";        };
    void *visit(bool_type_name_c        *symbol) {return (void *)"BOOL";        };
    void *visit(sint_type_name_c        *symbol) {return (void *)"SINT";        };
    void *visit(int_type_name_c         *symbol) {return (void *)"INT";         };
    void *visit(dint_type_name_c        *symbol) {return (void *)"DINT";        };
    void *visit(lint_type_name_c        *symbol) {return (void *)"LINT";        };
    void *visit(usint_type_name_c       *symbol) {return (void *)"USINT";       };
    void *visit(uint_type_name_c        *symbol) {return (void *)"UINT";        };
    void *visit(udint_type_name_c       *symbol) {return (void *)"UDINT";       };
    void *visit(ulint_type_name_c       *symbol) {return (void *)"ULINT";       };
    void *visit(real_type_name_c        *symbol) {return (void *)"REAL";        };
    void *visit(lreal_type_name_c       *symbol) {return (void *)"LREAL";       };
    void *visit(date_type_name_c        *symbol) {return (void *)"DATE";        };
    void *visit(tod_type_name_c         *symbol) {return (void *)"TOD";         };
    void *visit(dt_type_name_c          *symbol) {return (void *)"DT";          };
    void *visit(byte_type_name_c        *symbol) {return (void *)"BYTE";        };
    void *visit(word_type_name_c        *symbol) {return (void *)"WORD";        };
    void *visit(lword_type_name_c       *symbol) {return (void *)"LWORD";       };
    void *visit(dword_type_name_c       *symbol) {return (void *)"DWORD";       };
    void *visit(string_type_name_c      *symbol) {return (void *)"STRING";      };
    void *visit(wstring_type_name_c     *symbol) {return (void *)"WSTRING";     };

    void *visit(safetime_type_name_c    *symbol) {return (void *)"SAFETIME";    };
    void *visit(safebool_type_name_c    *symbol) {return (void *)"SAFEBOOL";    };
    void *visit(safesint_type_name_c    *symbol) {return (void *)"SAFESINT";    };
    void *visit(safeint_type_name_c     *symbol) {return (void *)"SAFEINT";     };
    void *visit(safedint_type_name_c    *symbol) {return (void *)"SAFEDINT";    };
    void *visit(safelint_type_name_c    *symbol) {return (void *)"SAFELINT";    };
    void *visit(safeusint_type_name_c   *symbol) {return (void *)"SAFEUSINT";   };
    void *visit(safeuint_type_name_c    *symbol) {return (void *)"SAFEUINT";    };
    void *visit(safeudint_type_name_c   *symbol) {return (void *)"SAFEUDINT";   };
    void *visit(safeulint_type_name_c   *symbol) {return (void *)"SAFEULINT";   };
    void *visit(safereal_type_name_c    *symbol) {return (void *)"SAFEREAL";    };
    void *visit(safelreal_type_name_c   *symbol) {return (void *)"SAFELREAL";   };
    void *visit(safedate_type_name_c    *symbol) {return (void *)"SAFEDATE";    };
    void *visit(safetod_type_name_c     *symbol) {return (void *)"SAFETOD";     };
    void *visit(safedt_type_name_c      *symbol) {return (void *)"SAFEDT";      };
    void *visit(safebyte_type_name_c    *symbol) {return (void *)"SAFEBYTE";    };
    void *visit(safeword_type_name_c    *symbol) {return (void *)"SAFEWORD";    };
    void *visit(safelword_type_name_c   *symbol) {return (void *)"SAFELWORD";   };
    void *visit(safedword_type_name_c   *symbol) {return (void *)"SAFEDWORD";   };
    void *visit(safestring_type_name_c  *symbol) {return (void *)"SAFESTRING";  };
    void *visit(safewstring_type_name_c *symbol) {return (void *)"SAFEWSTRING"; };
};






/* Widening Primitive Conversion */
struct widen_entry {
	symbol_c *left;
	symbol_c *right;
	symbol_c *result;
	enum {ok, deprecated} status;
};
/*
 * 2.5.1.5.6 Functions of time data types
 * Table 30 - page 64
 */
extern const struct widen_entry widen_ADD_table[];
extern const struct widen_entry widen_SUB_table[];
extern const struct widen_entry widen_MUL_table[];
extern const struct widen_entry widen_DIV_table[];
extern const struct widen_entry widen_MOD_table[];
extern const struct widen_entry widen_EXPT_table[];
extern const struct widen_entry widen_AND_table[];
extern const struct widen_entry widen_OR_table[];
extern const struct widen_entry widen_XOR_table[];
extern const struct widen_entry widen_CMP_table[];

/* Search for a datatype inside a candidate_datatypes list.
 * Returns: position of datatype in the list, or -1 if not found.
 */
int search_in_candidate_datatype_list(symbol_c *datatype, std::vector <symbol_c *> candidate_datatypes);

/* Intersect two candidate_datatype_lists.
 * Remove from list1 (origin, dest.) all elements that are not found in list2 (with).
 * In essence, list1 will contain the result of the intersection of list1 with list2.
 * In other words, modify list1 so it only contains the elelements that are simultaneously in list1 and list2!
 */
void intersect_candidate_datatype_list(symbol_c *list1 /*origin, dest.*/, symbol_c *list2 /*with*/);

/* intersect the candidate_datatype lists of all prev_il_intructions, and set the local candidate_datatype list to the result! */
void intersect_prev_candidate_datatype_lists(il_instruction_c *symbol);



/* A helper function... */
bool is_ANY_ELEMENTARY_type                (symbol_c *type_symbol);
bool is_ANY_SAFEELEMENTARY_type            (symbol_c *type_symbol);
bool is_ANY_ELEMENTARY_compatible          (symbol_c *type_symbol);

bool is_ANY_MAGNITUDE_type                 (symbol_c *type_symbol);
bool is_ANY_SAFEMAGNITUDE_type             (symbol_c *type_symbol);
bool is_ANY_MAGNITUDE_compatible           (symbol_c *type_symbol);

bool is_ANY_signed_MAGNITUDE_type          (symbol_c *type_symbol);
bool is_ANY_signed_SAFEMAGNITUDE_type      (symbol_c *type_symbol);
bool is_ANY_signed_MAGNITUDE_compatible    (symbol_c *type_symbol);

bool is_ANY_DATE_type                      (symbol_c *type_symbol);
bool is_ANY_SAFEDATE_type                  (symbol_c *type_symbol);
bool is_ANY_DATE_compatible                (symbol_c *type_symbol);

bool is_ANY_STRING_type                    (symbol_c *type_symbol);
bool is_ANY_SAFESTRING_type                (symbol_c *type_symbol);
bool is_ANY_STRING_compatible              (symbol_c *type_symbol);

bool is_ANY_INT_type                       (symbol_c *type_symbol);
bool is_ANY_SAFEINT_type                   (symbol_c *type_symbol);
bool is_ANY_INT_compatible                 (symbol_c *type_symbol);

bool is_ANY_signed_INT_type                (symbol_c *type_symbol);
bool is_ANY_signed_SAFEINT_type            (symbol_c *type_symbol);
bool is_ANY_signed_INT_compatible          (symbol_c *type_symbol);

bool is_ANY_REAL_type                      (symbol_c *type_symbol);
bool is_ANY_SAFEREAL_type                  (symbol_c *type_symbol);
bool is_ANY_REAL_compatible                (symbol_c *type_symbol);

bool is_ANY_NUM_type                       (symbol_c *type_symbol);
bool is_ANY_SAFENUM_type                   (symbol_c *type_symbol);
bool is_ANY_NUM_compatible                 (symbol_c *type_symbol);

bool is_ANY_signed_NUM_type                (symbol_c *type_symbol);
bool is_ANY_signed_SAFENUM_type            (symbol_c *type_symbol);
bool is_ANY_signed_NUM_compatible          (symbol_c *type_symbol);

bool is_ANY_BIT_type                       (symbol_c *type_symbol);
bool is_ANY_SAFEBIT_type                   (symbol_c *type_symbol);
bool is_ANY_BIT_compatible                 (symbol_c *type_symbol);

bool is_BOOL_type                          (symbol_c *type_symbol);
bool is_SAFEBOOL_type                      (symbol_c *type_symbol);
bool is_ANY_BOOL_compatible                (symbol_c *type_symbol);


bool is_type_equal(symbol_c *first_type, symbol_c *second_type);
bool is_type_valid(symbol_c *type);




#endif /* _HELPER_FUNCTIONS_HH_ */
