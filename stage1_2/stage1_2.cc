/*
 * (c) 2007 Mario de Sousa
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
 * This file contains the code that calls the stage 1 (lexical anayser) 
 * and stage 2 (syntax parser) during the first pass.
 */



// #include "stage1_2.hh"
#include "iec.y.hh"
#include "stage1_2_priv.hh"





/**************************************/
/* The name of the file being parsed. */
/**************************************/
/* The name of the file currently being parsed...
 * Note that flex accesses and updates this global variable
 * apropriately whenever it comes across an (*#include <filename> *)
 * directive...
 * ... and bison will use it when producing error messages.
 * Note that bison also sets this variable correctly to the first
 * file being parsed.
 */
const char *current_filename = NULL;




/*****************************************************/
/* Controlling the entry to the st_il_state in flex. */
/*****************************************************/

static int goto_body_state__ = 0;

void cmd_goto_body_state(void) {goto_body_state__ = 1;}
int  get_goto_body_state(void) {return goto_body_state__;}
void rst_goto_body_state(void) {goto_body_state__ = 0;}



/*********************************/
/* The global symbol tables...   */
/*********************************/
/* NOTE: only accessed indirectly by the lexical parser (flex)
 *       through the function get_identifier_token()
 */
/* NOTE: BOGUS_TOKEN_ID is defined in the bison generated file iec.y.hh.
 *       We need this constant defined before we can declare the symbol tables.
 *       However, we cannot #include "iec.y.hh" in this file (stage1_2_priv.hh) directly
 *       because of the way bison ver. 3.2 is copying all declarations in the prologue
 *       of iec.y to the iec.y.hh file (including an #include stage1_2_priv.hh).
 *       So, if we were to include "iec.y.hh" here, we would get a circular include.
 *       All this means that whoever includes this file (stage1_2_priv.hh) will need
 *       to take care to first inlcude iec.y.hh !!
 */ 
/* A symbol table to store all the library elements */
/* e.g.: <function_name , function_decl>
 *       <fb_name , fb_decl>
 *       <type_name , type_decl>
 *       <program_name , program_decl>
 *       <configuration_name , configuration_decl>
 */
/* static */ symtable_c<int, BOGUS_TOKEN_ID> library_element_symtable;

/* A symbol table to store the declared variables of
 * the function currently being parsed...
 */
/* static */ symtable_c<int, BOGUS_TOKEN_ID> variable_name_symtable;


/* Function only called from within flex!
 *
 * search for a symbol in either of the two symbol tables
 * declared above, and return the token id of the first
 * symbol found.
 * Searches first in the variables, and only if not found
 * does it continue searching in the library elements
 */
int get_identifier_token(const char *identifier_str) {
//  std::cout << "get_identifier_token(" << identifier_str << "): \n";
  int token_id;

  if ((token_id = variable_name_symtable.find_value(identifier_str)) == variable_name_symtable.end_value())
    if ((token_id = library_element_symtable.find_value(identifier_str)) == library_element_symtable.end_value())
      return identifier_token;
  return token_id;
}


/************************/
/* Utility Functions... */
/************************/

/*
 * Join two strings together. Allocate space with malloc(3).
 */
char *strdup2(const char *a, const char *b) {
  char *res = (char *)malloc(strlen(a) + strlen(b) + 1);

  if (!res)
    return NULL;
  return strcat(strcpy(res, a), b);  /* safe, actually */
}

/*
 * Join three strings together. Allocate space with malloc(3).
 */
char *strdup3(const char *a, const char *b, const char *c) {
  char *res = (char *)malloc(strlen(a) + strlen(b) + strlen(c) + 1);

  if (!res)
    return NULL;
  return strcat(strcat(strcpy(res, a), b), c);  /* safe, actually */
}






/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


int stage1_2__(const char *filename, const char *includedir, symbol_c **tree_root_ref);


int stage1_2(const char *filename, const char *includedir, symbol_c **tree_root_ref) {
  return stage1_2__(filename, includedir, tree_root_ref);
}

