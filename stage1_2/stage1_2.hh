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


/*
 * The public interface to stage1_2.cc 
 */



#ifndef _STAGE1_2_HH
#define _STAGE1_2_HH



/*
 * This file includes the interface through which the main function accesses the stage1_2 services 
 */



typedef struct {
		/******************************************************/
		/* whether we are suporting safe extensions           */
		/* as defined in PLCopen - Technical Committee 5      */
		/* Safety Software Technical Specification,           */
		/* Part 1: Concepts and Function Blocks,              */
		/* Version 1.0 – Official Release                     */
		/******************************************************/
	bool safe_extensions;
	bool full_token_loc;       /* error messages specify full token location */
	bool conversion_functions; /* Create a conversion function for derived datatype */
	bool nested_comments;      /* Allow the use of nested comments. */
	const char *includedir;    /* Include directory, where included files will be searched for... */
} stage1_2_options_t;


int stage1_2(const char *filename, symbol_c **tree_root, stage1_2_options_t options);





#endif   /* _STAGE1_2_HH */
