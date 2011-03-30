/*
 * (c) 2009 Mario de Sousa
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
		/* error messages specify full token location */
	bool full_token_loc; 
		/* Include directory, where included files will be searched for... */
	const char *includedir;
} stage1_2_options_t;


int stage1_2(const char *filename, symbol_c **tree_root, stage1_2_options_t options);





#endif   /* _STAGE1_2_HH */
