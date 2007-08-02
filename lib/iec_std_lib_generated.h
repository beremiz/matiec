/*
 * (c) 2003 Mario de Sousa
 *
 * Offered to the public under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
 * General Public License for more details.
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
 
 
/****
 * IEC 61131-3 standard function lib
 * generated code, do not edit by hand
 */

/* Macro that expand to subtypes */
#define ANY(DO) ANY_DERIVED(DO) ANY_ELEMENTARY(DO)
#define ANY_DERIVED(DO)
#define ANY_ELEMENTARY(DO) ANY_MAGNITUDE(DO) ANY_BIT(DO) ANY_STRING(DO) ANY_DATE(DO)
#define ANY_MAGNITUDE(DO) ANY_NUM(DO) DO(TIME)
#define ANY_BIT(DO) ANY_NBIT(DO) DO(BOOL)
#define ANY_NBIT(DO) DO(BYTE) DO(WORD) DO(DWORD) DO(LWORD)
#define ANY_STRING(DO) DO(STRING)
#define ANY_DATE(DO) DO(DATE) DO(TOD) DO(DT)
#define ANY_NUM(DO) ANY_REAL(DO) ANY_INT(DO)
#define ANY_REAL(DO) DO(REAL) DO(LREAL)
#define ANY_INT(DO) ANY_SINT(DO) ANY_UINT(DO)
#define ANY_SINT(DO) DO(SINT) DO(INT) DO(DINT) DO(LINT)
#define ANY_UINT(DO) DO(USINT) DO(UINT) DO(UDINT) DO(ULINT)
