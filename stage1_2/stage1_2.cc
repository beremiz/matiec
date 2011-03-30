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

#include <string.h>
#include <stdlib.h>

/* file with declaration of absyntax classes... */
#include "../absyntax/absyntax.hh"


#include "stage1_2.hh"
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


/******************************************************/
/* whether we are suporting safe extensions           */
/* as defined in PLCopen - Technical Committee 5      */
/* Safety Software Technical Specification,           */
/* Part 1: Concepts and Function Blocks,              */
/* Version 1.0 – Official Release                     */
/******************************************************/
bool safe_extensions_ = false;
bool get_opt_safe_extensions() {return safe_extensions_;}

/****************************************************/
/* Controlling the entry to the body_state in flex. */
/****************************************************/
static int goto_body_state__ = 0;

void cmd_goto_body_state(void) {goto_body_state__ = 1;}
int  get_goto_body_state(void) {return goto_body_state__;}
void rst_goto_body_state(void) {goto_body_state__ = 0;}

/*************************************************************/
/* Controlling the entry to the sfc_qualifier_state in flex. */
/*************************************************************/
static int goto_sfc_qualifier_state__ = 0;

void cmd_goto_sfc_qualifier_state(void) {goto_sfc_qualifier_state__ = 1;}
int  get_goto_sfc_qualifier_state(void) {return goto_sfc_qualifier_state__;}
void rst_goto_sfc_qualifier_state(void) {goto_sfc_qualifier_state__ = 0;}

/*************************************************************/
/* Controlling the entry to the sfc_priority_state in flex.  */
/*************************************************************/
static int goto_sfc_priority_state__ = 0;

void cmd_goto_sfc_priority_state(void) {goto_sfc_priority_state__ = 1;}
int  get_goto_sfc_priority_state(void) {return goto_sfc_priority_state__;}
void rst_goto_sfc_priority_state(void) {goto_sfc_priority_state__ = 0;}

/*************************************************************/
/* Controlling the entry to the sfc_qualifier_state in flex. */
/*************************************************************/
static int goto_task_init_state__ = 0;

void cmd_goto_task_init_state(void) {goto_task_init_state__ = 1;}
int  get_goto_task_init_state(void) {return goto_task_init_state__;}
void rst_goto_task_init_state(void) {goto_task_init_state__ = 0;}

/****************************************************************/
/* Returning to state in flex previously pushed onto the stack. */
/****************************************************************/
static int pop_state__ = 0;

void cmd_pop_state(void) {pop_state__ = 1;}
int  get_pop_state(void) {return pop_state__;}
void rst_pop_state(void) {pop_state__ = 0;}


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

/* A symbol table to store the declared direct variables of
 * the function currently being parsed...
 */
/* static */ symtable_c<int, BOGUS_TOKEN_ID> direct_variable_symtable;

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

/* Function only called from within flex!
 *
 * search for a symbol in direct variables symbol table
 * declared above, and return the token id of the first
 * symbol found.
 */
int get_direct_variable_token(const char *direct_variable_str) {
  int token_id;

  if ((token_id = direct_variable_symtable.find_value(direct_variable_str)) == direct_variable_symtable.end_value())
    return direct_variable_token;
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

/*************************/
/* Tracking Functions... */
/*************************/

extern tracking_t* current_tracking;

/*--------------------------------------------------------------------
 * GetNextChar
 * 
 * reads a character from input for flex
 *------------------------------------------------------------------*/
int GetNextChar(char *b, int maxBuffer) {
  char *p;
  
  if (  current_tracking->eof  )
    return 0;
  
  while (  current_tracking->currentChar >= current_tracking->lineLength  ) {
    current_tracking->currentChar = 0;
    current_tracking->currentTokenStart = 1;
    current_tracking->eof = false;
    
    p = fgets(current_tracking->buffer, MAX_BUFFER_LENGTH, current_tracking->in_file);
    if (  p == NULL  ) {
      if (  ferror(current_tracking->in_file)  )
        return 0;
      current_tracking->eof = true;
      return 0;
    }
    
    current_tracking->lineNumber++;
    current_tracking->lineLength = strlen(current_tracking->buffer);
  }
  
  b[0] = current_tracking->buffer[current_tracking->currentChar];
  if (b[0] == ' ' || b[0] == '\t')
    current_tracking->currentTokenStart++;
  current_tracking->currentChar++;

  return b[0]==0?0:1;
}

tracking_t* GetNewTracking(FILE* in_file) {
  tracking_t* new_env = new tracking_t;
  new_env->eof = 0;
  new_env->lineNumber = 0;
  new_env->currentChar = 0;
  new_env->lineLength = 0;
  new_env->currentTokenStart = 0;
  new_env->buffer = (char*)malloc(MAX_BUFFER_LENGTH);
  new_env->in_file = in_file;
  return new_env;
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


int stage2__(const char *filename, 
             const char *includedir,     /* Include directory, where included files will be searched for... */
             symbol_c **tree_root_ref,
             bool full_token_loc         /* error messages specify full token location */
            );


int stage1_2(const char *filename, symbol_c **tree_root_ref, stage1_2_options_t options) {
      /* NOTE: we only call stage2 (bison - syntax analysis) directly, as stage 2 will itself call stage1 (flex - lexical analysis)
       *       automatically as needed
       */

      /* NOTE: Since we do not call stage1__ (flex) directly, we cannot directly pass any parameters to that function either.
       *       In this case, we use callback functions, i.e. stage1__ (i.e. flex) will call functions defined in this file
       *       whenever it needs info/parameters coming from stage1_2().
       *       These callback functions will get their data from local (to this file) global variables...
       *       We now set those variables...
       */
  safe_extensions_ = options.safe_extensions;
  
  return stage2__(filename, options.includedir, tree_root_ref, options.full_token_loc);
}

