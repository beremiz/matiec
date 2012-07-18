/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
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



#ifndef _MAIN_HH
#define _MAIN_HH


 /* Get the definition of INT16_MAX, INT16_MIN, UINT64_MAX, INT64_MAX, INT64_MIN, ... */

#define __STDC_LIMIT_MACROS /* required when including from C++ source code. */
#include <stdint.h>         

#ifndef   UINT64_MAX 
  #define UINT64_MAX (std::numeric_limits< uint64_t >::max())
#endif
#ifndef    INT64_MAX 
  #define  INT64_MAX (std::numeric_limits<  int64_t >::max())
#endif
#ifndef    INT64_MIN
  #define  INT64_MIN (std::numeric_limits<  int64_t >::min()) 
#endif

#if    (real64_t  == float)
  #define HUGE_VAL64  HUGE_VALF
#elif  (real64_t  == double)
  #define HUGE_VAL64  HUGE_VAL
#elif  (real64_t  == long_double)
  #define HUGE_VAL64  HUGE_VALL
#else 
  #error Could not determine which data type is being used for real64_t (defined in absyntax.hh). Aborting!
#endif




 /* Function used throughout the code --> used to report failed assertions (i.e. internal compiler errors)! */
#include <stddef.h>  /* required for NULL */
 
#define ERROR               error_exit(__FILE__,__LINE__)
#define ERROR_MSG(msg, ...) error_exit(__FILE__,__LINE__, msg)
// #define ERROR_MSG(msg, ...) error_exit(__FILE__,__LINE__, msg, __VA_ARGS__)

extern void error_exit(const char *file_name, int line_no, const char *errmsg = NULL, ...);




#endif // #ifndef _MAIN_HH