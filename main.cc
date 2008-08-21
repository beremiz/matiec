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

/*
 ****************************************************************
 ****************************************************************
 ****************************************************************
 *********                                              *********
 *********                                              *********
 *********   O V E R A L L    A R C H I T E C T U R E   *********
 *********                                              *********
 *********                                              *********
 ****************************************************************
 ****************************************************************
 ****************************************************************

 The compiler works in 4(+1) stages:
 Stage 1   - Lexical analyser      - implemented with flex (iec.flex)
 Stage 2   - Syntax parser         - implemented with bison (iec.y)
 Stage 3   - Semantics analyser    - not yet implemented
 Stage 4   - Code generator        - implemented in C++
 Stage 4+1 - Binary code generator - gcc, javac, etc...


 Data structures passed between stages, in global variables:
 1->2   : tokens (int), and token values (char *)
 2->1   : symbol tables (defined in symtable.hh)
 2->3   : abstract syntax tree (tree of C++ classes, in absyntax.hh file)
 3->4   : Same as 2->3
 4->4+1 : file with program in c, java, etc...


 The compiler works in several passes:
 Pass 1: executes stages 1 and 2 simultaneously
 Pass 2: executes stage 3
 Pass 3: executes stage 4
 Pass 4: executes stage 4+1
*/



//#include <stdio.h>   // printf()
#include <string.h>
#include <stdlib.h>  // EXIT_FAILURE
#include "absyntax/absyntax.hh"  // symbol_c type




/* A macro for printing out internal parser errors... */
#include <iostream> // required for std::cerr
#define ERROR error_exit(__FILE__,__LINE__)
void error_exit(const char *file_name, int line_no) {
  std::cerr << "\nInternal program error in file " << file_name
            << " at line " << line_no << "\n\n\n";
  exit(EXIT_FAILURE);
}



/* forward declarations... */
int stage1_2(const char *filename, const char *includedir, symbol_c **tree_root, bool full);
//int stage3(symbol_c *tree_root);
int stage4(symbol_c *tree_root, const char *builddir);


static void printusage(const char *cmd) {
  printf("syntaxe: %s [-fh] <input_file> [-I <include_directory>] [<target_directory>]\n", cmd);
  printf("  f : full token location on error messages\n");
  printf("  h : show this help message\n");
}



int main(int argc, char **argv) {
  symbol_c *tree_root;
  char * includedir = NULL;
  char * builddir = NULL;
  bool full = false;
  int offset = 0; 

  if (argc < 2 || argc > 6) {
    printusage(argv[0]);
    return EXIT_FAILURE;
  }

  if (strcmp(argv[1], "-h") == 0) {
    printusage(argv[0]);
    return 0;
  }

  if (strcmp(argv[1], "-f") == 0) {
    if (argc == 2) {
      printusage(argv[0]);
      return EXIT_FAILURE;
    }
    full = true;
    offset = 1;
  }
    
  if (argc == (5 + offset)) {
    builddir = argv[4 + offset];
    argc = 4 + offset;
  }

  if (argc == (4 + offset)) {
    if (strcmp(argv[2 + offset], "-I") != 0) {
      printusage(argv[0]);
      return EXIT_FAILURE;
    }
    includedir = argv[3 + offset];
    argc = 2 + offset;
  }

  if (argc == (3 + offset)) {
    builddir = argv[2 + offset];
    argc = 2 + offset;
  }    

  /* 1st Pass */
  if (stage1_2(argv[1 + offset], includedir, &tree_root, full) < 0)
    return EXIT_FAILURE;

  /* 2nd Pass */
  /* not yet implemented... */
  /*
  if (stage3(tree_root) < 0)
    return EXIT_FAILURE;
  */

  /* 3rd Pass */
  if (stage4(tree_root, builddir) < 0)
    return EXIT_FAILURE;

  /* 4th Pass */
  /* Currently implemented in the Makefile! */

  return 0;
}


