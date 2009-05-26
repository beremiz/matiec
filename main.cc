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




#include "stage1_2/stage1_2.hh"
#include "search_utils/search_utils.hh"

//int stage3(symbol_c *tree_root);
int stage4(symbol_c *tree_root, const char *builddir);


static void printusage(const char *cmd) {
  printf("syntax: %s [-h] [-f] [-s] [-I <include_directory>] [-T <target_directory>] <input_file>\n", cmd);
  printf("  h : show this help message\n");
  printf("  f : full token location on error messages\n");
      /******************************************************/
      /* whether we are suporting safe extensions           */
      /* as defined in PLCopen - Technical Committee 5      */
      /* Safety Software Technical Specification,           */
      /* Part 1: Concepts and Function Blocks,              */
      /* Version 1.0 – Official Release                     */
      /******************************************************/
  printf("  s : allow use of safe extensions\n");
}



int main(int argc, char **argv) {
  symbol_c *tree_root;
  char * builddir = NULL;
  stage1_2_options_t stage1_2_options = {false, false, NULL};
  int optres, errflg = 0;
/*
  extern char *optarg;
  extern int optind, optopt;
*/

  while ((optres = getopt(argc, argv, ":hfsI:T:")) != -1) {
    switch(optres) {
    case 'h':
      printusage(argv[0]);
      return 0;
      break;
    case 'f':
      stage1_2_options.full_token_loc = true;
      break;
    case 's':
      stage1_2_options.safe_extensions = true;
      break;
    case 'I':
      stage1_2_options.includedir = optarg;
      break;
    case ':':       /* -I or -T without operand */
      fprintf(stderr, "Option -%c requires an operand\n", optopt);
      errflg++;
      break;
    case '?':
    default:
      fprintf(stderr, "Unrecognized option: -%c\n", optopt);
      errflg++;
      break;
    }
  }

  if (optind == argc) {
    fprintf(stderr, "Missing input file\n");
    errflg++;
  }

  if (optind > argc) {
    fprintf(stderr, "Too many input files\n");
    errflg++;
  }

  if (errflg) {
      printusage(argv[0]);
      return EXIT_FAILURE;
  }


  /* 1st Pass */
  if (stage1_2(argv[optind], &tree_root, stage1_2_options) < 0)
    return EXIT_FAILURE;

  /* 2nd Pass */
printf("loading symbol tables...\n");
  search_utils_init(tree_root);
printf("loading symbol tables... DONE!\n");
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


