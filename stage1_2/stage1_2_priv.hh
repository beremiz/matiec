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
 * The private interface to stage1_2.cc 
 */



/* !!! WARNING !!!
 *
 *       Whoever includes this file (stage1_2_priv.hh) will need
 *       to first inlcude iec.y.hh !!
 *
 *       Read other comments further down to understand why we don't
 *       include iec.y.hh in this file.
 */



/* file with the declarations of symbol tables... */
#include "../util/symtable.hh"



/*
 * This file includes the interface through which the lexical parser (stage 1 - flex)
 * and the syntax analyser (stage 2 - bison) interact between themselves.
 *
 * This is mostly through direct access to shared global variables, however some
 * of the global variables will only be accessed through some accessor functions.
 *
 * This file also includes some utility functions (strdupX() ) that are both used
 * in the lexical and syntax analysers.
 */





/*********************************************/
/* print the include file stack to stderr... */
/*********************************************/
/* This is a service that flex provides to bison... */
void print_include_stack(void);



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
extern const char *current_filename;



/****************************************************/
/* Controlling the entry to the body_state in flex. */
/****************************************************/
void cmd_goto_body_state(void);
int  get_goto_body_state(void);
void rst_goto_body_state(void);


/*************************************************************/
/* Controlling the entry to the sfc_qualifier_state in flex. */
/*************************************************************/
void cmd_goto_sfc_qualifier_state(void);
int  get_goto_sfc_qualifier_state(void);
void rst_goto_sfc_qualifier_state(void);


/*********************************************************/
/* Controlling the entry to the task_init_state in flex. */
/*********************************************************/
void cmd_goto_task_init_state(void);
int  get_goto_task_init_state(void);
void rst_goto_task_init_state(void);


/****************************************************************/
/* Returning to state in flex previously pushed onto the stack. */
/****************************************************************/
void cmd_pop_state(void);
int  get_pop_state(void);
void rst_pop_state(void);



/*********************************/
/* The global symbol tables...   */
/*********************************/
/* NOTE: only accessed indirectly by the lexical parser (flex)
 *       through the function get_identifier_token()
 */
/* NOTE: BOGUS_TOKEN_ID is defined in the bison generated file iec.y.hh.
 *       We need this constant defined before we can declare the symbol tables.
 *       However, we cannot #include "iec.y.hh" in this file (stage1_2_priv.hh) directly
 *       because of the way bison ver. 2.3 is copying all declarations in the prologue
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
extern symtable_c<int, BOGUS_TOKEN_ID> library_element_symtable;

/* A symbol table to store the declared variables of
 * the function currently being parsed...
 */
extern symtable_c<int, BOGUS_TOKEN_ID> variable_name_symtable;

/* Function only called from within flex!
 *
 * search for a symbol in either of the two symbol tables
 * declared above, and return the token id of the first
 * symbol found.
 * Searches first in the variables, and only if not found
 * does it continue searching in the library elements
 */
int get_identifier_token(const char *identifier_str);



/************************/
/* Utility Functions... */
/************************/

/* Join two strings together. Allocate space with malloc(3). */
char *strdup2(const char *a, const char *b);

/* Join three strings together. Allocate space with malloc(3). */
char *strdup3(const char *a, const char *b, const char *c);



