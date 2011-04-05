#!/bin/sh

#/*
# *  matiec - a compiler for the programming languages defined in IEC 61131-3
# *  Copyright (C) 2003-2011  Mario de Sousa (msousa@fe.up.pt)
# *
# *  This program is free software: you can redistribute it and/or modify
# *  it under the terms of the GNU General Public License as published by
# *  the Free Software Foundation, either version 3 of the License, or
# *  (at your option) any later version.
# *
# *  This program is distributed in the hope that it will be useful,
# *  but WITHOUT ANY WARRANTY; without even the implied warranty of
# *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# *  GNU General Public License for more details.
# *
# *  You should have received a copy of the GNU General Public License
# *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
# *
# *
# * This code is made available on the understanding that it will not be
# * used in safety-critical situations without a full and competent review.
# */
#
#/*
# * An IEC 61131-3 compiler.
# *
# * Based on the
# * FINAL DRAFT - IEC 61131-3, 2nd Ed. (2001-12-10)
# *
# */
#
#
#  A shell script to create the library header file containing the 
#  standard functions defined in IEC 61131-3
#


print_usage()
{
  echo "usage: $0 {c | iec}"
  echo "   c -> produce c file with implementation of standard functions"
  echo " iec -> produce txt file with declaration of standard functions"
  exit 0
}


create_iec_beg()
{
echo
echo {disable code generation}
echo
}


create_iec_end()
{
echo
echo {enable code generation}
echo
}


create_iec()
{
echo
echo
echo FUNCTION $1 : $3
echo "  "VAR_INPUT   IN: $2";" END_VAR
echo "  "VAR_OUTPUT OUT: $3";" END_VAR
echo "  "LD TRUE
echo END_FUNCTION
}


create_c_beg()
{
echo  
}

create_c_end()
{
echo  
}


create_c()
{
echo 
echo inline
echo $1"("$2 IN, $3 *__OUT, BOOL EN, BOOL *__ENO")" 
echo { $4 }
} 
 

##################################
##################################
##                              ##
##    Main code starts here...  ##
##                              ##
##################################
##################################

if [ $# -ne 1 ] 
then
  print_usage
fi

if   [ $1 = "c" ] 
then
  create=create_c
  create_beg=create_c_beg
  create_end=create_c_end
elif [ $1 = "iec" ] 
then 
  create=create_iec
  create_beg=create_iec_beg
  create_end=create_iec_end
else
  print_usage
fi



$create_beg    



$create	BOOL_TO_BYTE	BOOL	BYTE	"*__OUT=(BYTE	)__move_BOOL	(EN,__ENO,IN);"	
$create	BOOL_TO_DINT	BOOL	DINT	"*__OUT=(DINT	)__move_BOOL	(EN,__ENO,IN);"	
$create	BOOL_TO_DWORD	BOOL	DWORD	"*__OUT=(DWORD	)__move_BOOL	(EN,__ENO,IN);"	
$create	BOOL_TO_INT	BOOL	INT	"*__OUT=(INT	)__move_BOOL	(EN,__ENO,IN);"	
$create	BOOL_TO_LINT	BOOL	LINT	"*__OUT=(LINT	)__move_BOOL	(EN,__ENO,IN);"	
$create	BOOL_TO_LREAL	BOOL	LREAL	"*__OUT=(LREAL	)__move_BOOL	(EN,__ENO,IN);"	
$create	BOOL_TO_LWORD	BOOL	LWORD	"*__OUT=(LWORD	)__move_BOOL	(EN,__ENO,IN);"	
$create	BOOL_TO_REAL	BOOL	REAL	"*__OUT=(REAL	)__move_BOOL	(EN,__ENO,IN);"	
$create	BOOL_TO_SINT	BOOL	SINT	"*__OUT=(SINT	)__move_BOOL	(EN,__ENO,IN);"	
$create	BOOL_TO_UDINT	BOOL	UDINT	"*__OUT=(UDINT	)__move_BOOL	(EN,__ENO,IN);"	
$create	BOOL_TO_UINT	BOOL	UINT	"*__OUT=(UINT	)__move_BOOL	(EN,__ENO,IN);"	
$create	BOOL_TO_ULINT	BOOL	ULINT	"*__OUT=(ULINT	)__move_BOOL	(EN,__ENO,IN);"	
$create	BOOL_TO_USINT	BOOL	USINT	"*__OUT=(USINT	)__move_BOOL	(EN,__ENO,IN);"	
$create	BOOL_TO_WORD	BOOL	WORD	"*__OUT=(WORD	)__move_BOOL	(EN,__ENO,IN);"	
$create	BYTE_TO_BOOL	BYTE	BOOL	"*__OUT=(BOOL	)__move_BYTE	(EN,__ENO,IN);"	
$create	BYTE_TO_DINT	BYTE	DINT	"*__OUT=(DINT	)__move_BYTE	(EN,__ENO,IN);"	
$create	BYTE_TO_DWORD	BYTE	DWORD	"*__OUT=(DWORD	)__move_BYTE	(EN,__ENO,IN);"	
$create	BYTE_TO_INT	BYTE	INT	"*__OUT=(INT	)__move_BYTE	(EN,__ENO,IN);"	
$create	BYTE_TO_LINT	BYTE	LINT	"*__OUT=(LINT	)__move_BYTE	(EN,__ENO,IN);"	
$create	BYTE_TO_LREAL	BYTE	LREAL	"*__OUT=(LREAL	)__move_BYTE	(EN,__ENO,IN);"	
$create	BYTE_TO_LWORD	BYTE	LWORD	"*__OUT=(LWORD	)__move_BYTE	(EN,__ENO,IN);"	
$create	BYTE_TO_REAL	BYTE	REAL	"*__OUT=(REAL	)__move_BYTE	(EN,__ENO,IN);"	
$create	BYTE_TO_SINT	BYTE	SINT	"*__OUT=(SINT	)__move_BYTE	(EN,__ENO,IN);"	
$create	BYTE_TO_UDINT	BYTE	UDINT	"*__OUT=(UDINT	)__move_BYTE	(EN,__ENO,IN);"	
$create	BYTE_TO_UINT	BYTE	UINT	"*__OUT=(UINT	)__move_BYTE	(EN,__ENO,IN);"	
$create	BYTE_TO_ULINT	BYTE	ULINT	"*__OUT=(ULINT	)__move_BYTE	(EN,__ENO,IN);"	
$create	BYTE_TO_USINT	BYTE	USINT	"*__OUT=(USINT	)__move_BYTE	(EN,__ENO,IN);"	
$create	BYTE_TO_WORD	BYTE	WORD	"*__OUT=(WORD	)__move_BYTE	(EN,__ENO,IN);"	
$create	DINT_TO_BOOL	DINT	BOOL	"*__OUT=(BOOL	)__move_DINT	(EN,__ENO,IN);"	
$create	DINT_TO_BYTE	DINT	BYTE	"*__OUT=(BYTE	)__move_DINT	(EN,__ENO,IN);"	
$create	DINT_TO_DWORD	DINT	DWORD	"*__OUT=(DWORD	)__move_DINT	(EN,__ENO,IN);"	
$create	DINT_TO_INT	DINT	INT	"*__OUT=(INT	)__move_DINT	(EN,__ENO,IN);"	
$create	DINT_TO_LINT	DINT	LINT	"*__OUT=(LINT	)__move_DINT	(EN,__ENO,IN);"	
$create	DINT_TO_LREAL	DINT	LREAL	"*__OUT=(LREAL	)__move_DINT	(EN,__ENO,IN);"	
$create	DINT_TO_LWORD	DINT	LWORD	"*__OUT=(LWORD	)__move_DINT	(EN,__ENO,IN);"	
$create	DINT_TO_REAL	DINT	REAL	"*__OUT=(REAL	)__move_DINT	(EN,__ENO,IN);"	
$create	DINT_TO_SINT	DINT	SINT	"*__OUT=(SINT	)__move_DINT	(EN,__ENO,IN);"	
$create	DINT_TO_UDINT	DINT	UDINT	"*__OUT=(UDINT	)__move_DINT	(EN,__ENO,IN);"	
$create	DINT_TO_UINT	DINT	UINT	"*__OUT=(UINT	)__move_DINT	(EN,__ENO,IN);"	
$create	DINT_TO_ULINT	DINT	ULINT	"*__OUT=(ULINT	)__move_DINT	(EN,__ENO,IN);"	
$create	DINT_TO_USINT	DINT	USINT	"*__OUT=(USINT	)__move_DINT	(EN,__ENO,IN);"	
$create	DINT_TO_WORD	DINT	WORD	"*__OUT=(WORD	)__move_DINT	(EN,__ENO,IN);"	
$create	DWORD_TO_BOOL	DWORD	BOOL	"*__OUT=(BOOL	)__move_DWORD	(EN,__ENO,IN);"	
$create	DWORD_TO_BYTE	DWORD	BYTE	"*__OUT=(BYTE	)__move_DWORD	(EN,__ENO,IN);"	
$create	DWORD_TO_DINT	DWORD	DINT	"*__OUT=(DINT	)__move_DWORD	(EN,__ENO,IN);"	
$create	DWORD_TO_INT	DWORD	INT	"*__OUT=(INT	)__move_DWORD	(EN,__ENO,IN);"	
$create	DWORD_TO_LINT	DWORD	LINT	"*__OUT=(LINT	)__move_DWORD	(EN,__ENO,IN);"	
$create	DWORD_TO_LREAL	DWORD	LREAL	"*__OUT=(LREAL	)__move_DWORD	(EN,__ENO,IN);"	
$create	DWORD_TO_LWORD	DWORD	LWORD	"*__OUT=(LWORD	)__move_DWORD	(EN,__ENO,IN);"	
$create	DWORD_TO_REAL	DWORD	REAL	"*__OUT=(REAL	)__move_DWORD	(EN,__ENO,IN);"	
$create	DWORD_TO_SINT	DWORD	SINT	"*__OUT=(SINT	)__move_DWORD	(EN,__ENO,IN);"	
$create	DWORD_TO_UDINT	DWORD	UDINT	"*__OUT=(UDINT	)__move_DWORD	(EN,__ENO,IN);"	
$create	DWORD_TO_UINT	DWORD	UINT	"*__OUT=(UINT	)__move_DWORD	(EN,__ENO,IN);"	
$create	DWORD_TO_ULINT	DWORD	ULINT	"*__OUT=(ULINT	)__move_DWORD	(EN,__ENO,IN);"	
$create	DWORD_TO_USINT	DWORD	USINT	"*__OUT=(USINT	)__move_DWORD	(EN,__ENO,IN);"	
$create	DWORD_TO_WORD	DWORD	WORD	"*__OUT=(WORD	)__move_DWORD	(EN,__ENO,IN);"	
$create	INT_TO_BOOL	INT	BOOL	"*__OUT=(BOOL	)__move_INT	(EN,__ENO,IN);"	
$create	INT_TO_BYTE	INT	BYTE	"*__OUT=(BYTE	)__move_INT	(EN,__ENO,IN);"	
$create	INT_TO_DINT	INT	DINT	"*__OUT=(DINT	)__move_INT	(EN,__ENO,IN);"	
$create	INT_TO_DWORD	INT	DWORD	"*__OUT=(DWORD	)__move_INT	(EN,__ENO,IN);"	
$create	INT_TO_LINT	INT	LINT	"*__OUT=(LINT	)__move_INT	(EN,__ENO,IN);"	
$create	INT_TO_LREAL	INT	LREAL	"*__OUT=(LREAL	)__move_INT	(EN,__ENO,IN);"	
$create	INT_TO_LWORD	INT	LWORD	"*__OUT=(LWORD	)__move_INT	(EN,__ENO,IN);"	
$create	INT_TO_REAL	INT	REAL	"*__OUT=(REAL	)__move_INT	(EN,__ENO,IN);"	
$create	INT_TO_SINT	INT	SINT	"*__OUT=(SINT	)__move_INT	(EN,__ENO,IN);"	
$create	INT_TO_UDINT	INT	UDINT	"*__OUT=(UDINT	)__move_INT	(EN,__ENO,IN);"	
$create	INT_TO_UINT	INT	UINT	"*__OUT=(UINT	)__move_INT	(EN,__ENO,IN);"	
$create	INT_TO_ULINT	INT	ULINT	"*__OUT=(ULINT	)__move_INT	(EN,__ENO,IN);"	
$create	INT_TO_USINT	INT	USINT	"*__OUT=(USINT	)__move_INT	(EN,__ENO,IN);"	
$create	INT_TO_WORD	INT	WORD	"*__OUT=(WORD	)__move_INT	(EN,__ENO,IN);"	
$create	LINT_TO_BOOL	LINT	BOOL	"*__OUT=(BOOL	)__move_LINT	(EN,__ENO,IN);"	
$create	LINT_TO_BYTE	LINT	BYTE	"*__OUT=(BYTE	)__move_LINT	(EN,__ENO,IN);"	
$create	LINT_TO_DINT	LINT	DINT	"*__OUT=(DINT	)__move_LINT	(EN,__ENO,IN);"	
$create	LINT_TO_DWORD	LINT	DWORD	"*__OUT=(DWORD	)__move_LINT	(EN,__ENO,IN);"	
$create	LINT_TO_INT	LINT	INT	"*__OUT=(INT	)__move_LINT	(EN,__ENO,IN);"	
$create	LINT_TO_LREAL	LINT	LREAL	"*__OUT=(LREAL	)__move_LINT	(EN,__ENO,IN);"	
$create	LINT_TO_LWORD	LINT	LWORD	"*__OUT=(LWORD	)__move_LINT	(EN,__ENO,IN);"	
$create	LINT_TO_REAL	LINT	REAL	"*__OUT=(REAL	)__move_LINT	(EN,__ENO,IN);"	
$create	LINT_TO_SINT	LINT	SINT	"*__OUT=(SINT	)__move_LINT	(EN,__ENO,IN);"	
$create	LINT_TO_UDINT	LINT	UDINT	"*__OUT=(UDINT	)__move_LINT	(EN,__ENO,IN);"	
$create	LINT_TO_UINT	LINT	UINT	"*__OUT=(UINT	)__move_LINT	(EN,__ENO,IN);"	
$create	LINT_TO_ULINT	LINT	ULINT	"*__OUT=(ULINT	)__move_LINT	(EN,__ENO,IN);"	
$create	LINT_TO_USINT	LINT	USINT	"*__OUT=(USINT	)__move_LINT	(EN,__ENO,IN);"	
$create	LINT_TO_WORD	LINT	WORD	"*__OUT=(WORD	)__move_LINT	(EN,__ENO,IN);"	
$create	LREAL_TO_BOOL	LREAL	BOOL	"*__OUT=(BOOL	)__move_LREAL	(EN,__ENO,IN);"	
$create	LREAL_TO_BYTE	LREAL	BYTE	"*__OUT=(BYTE	)__move_LREAL	(EN,__ENO,IN);"	
$create	LREAL_TO_DINT	LREAL	DINT	"*__OUT=(DINT	)__move_LREAL	(EN,__ENO,IN);"	
$create	LREAL_TO_DWORD	LREAL	DWORD	"*__OUT=(DWORD	)__move_LREAL	(EN,__ENO,IN);"	
$create	LREAL_TO_INT	LREAL	INT	"*__OUT=(INT	)__move_LREAL	(EN,__ENO,IN);"	
$create	LREAL_TO_LINT	LREAL	LINT	"*__OUT=(LINT	)__move_LREAL	(EN,__ENO,IN);"	
$create	LREAL_TO_LWORD	LREAL	LWORD	"*__OUT=(LWORD	)__move_LREAL	(EN,__ENO,IN);"	
$create	LREAL_TO_REAL	LREAL	REAL	"*__OUT=(REAL	)__move_LREAL	(EN,__ENO,IN);"	
$create	LREAL_TO_SINT	LREAL	SINT	"*__OUT=(SINT	)__move_LREAL	(EN,__ENO,IN);"	
$create	LREAL_TO_UDINT	LREAL	UDINT	"*__OUT=(UDINT	)__move_LREAL	(EN,__ENO,IN);"	
$create	LREAL_TO_UINT	LREAL	UINT	"*__OUT=(UINT	)__move_LREAL	(EN,__ENO,IN);"	
$create	LREAL_TO_ULINT	LREAL	ULINT	"*__OUT=(ULINT	)__move_LREAL	(EN,__ENO,IN);"	
$create	LREAL_TO_USINT	LREAL	USINT	"*__OUT=(USINT	)__move_LREAL	(EN,__ENO,IN);"	
$create	LREAL_TO_WORD	LREAL	WORD	"*__OUT=(WORD	)__move_LREAL	(EN,__ENO,IN);"	
$create	LWORD_TO_BOOL	LWORD	BOOL	"*__OUT=(BOOL	)__move_LWORD	(EN,__ENO,IN);"	
$create	LWORD_TO_BYTE	LWORD	BYTE	"*__OUT=(BYTE	)__move_LWORD	(EN,__ENO,IN);"	
$create	LWORD_TO_DINT	LWORD	DINT	"*__OUT=(DINT	)__move_LWORD	(EN,__ENO,IN);"	
$create	LWORD_TO_DWORD	LWORD	DWORD	"*__OUT=(DWORD	)__move_LWORD	(EN,__ENO,IN);"	
$create	LWORD_TO_INT	LWORD	INT	"*__OUT=(INT	)__move_LWORD	(EN,__ENO,IN);"	
$create	LWORD_TO_LINT	LWORD	LINT	"*__OUT=(LINT	)__move_LWORD	(EN,__ENO,IN);"	
$create	LWORD_TO_LREAL	LWORD	LREAL	"*__OUT=(LREAL	)__move_LWORD	(EN,__ENO,IN);"	
$create	LWORD_TO_REAL	LWORD	REAL	"*__OUT=(REAL	)__move_LWORD	(EN,__ENO,IN);"	
$create	LWORD_TO_SINT	LWORD	SINT	"*__OUT=(SINT	)__move_LWORD	(EN,__ENO,IN);"	
$create	LWORD_TO_UDINT	LWORD	UDINT	"*__OUT=(UDINT	)__move_LWORD	(EN,__ENO,IN);"	
$create	LWORD_TO_UINT	LWORD	UINT	"*__OUT=(UINT	)__move_LWORD	(EN,__ENO,IN);"	
$create	LWORD_TO_ULINT	LWORD	ULINT	"*__OUT=(ULINT	)__move_LWORD	(EN,__ENO,IN);"	
$create	LWORD_TO_USINT	LWORD	USINT	"*__OUT=(USINT	)__move_LWORD	(EN,__ENO,IN);"	
$create	LWORD_TO_WORD	LWORD	WORD	"*__OUT=(WORD	)__move_LWORD	(EN,__ENO,IN);"	
$create	REAL_TO_BOOL	REAL	BOOL	"*__OUT=(BOOL	)__move_REAL	(EN,__ENO,IN);"	
$create	REAL_TO_BYTE	REAL	BYTE	"*__OUT=(BYTE	)__move_REAL	(EN,__ENO,IN);"	
$create	REAL_TO_DINT	REAL	DINT	"*__OUT=(DINT	)__move_REAL	(EN,__ENO,IN);"	
$create	REAL_TO_DWORD	REAL	DWORD	"*__OUT=(DWORD	)__move_REAL	(EN,__ENO,IN);"	
$create	REAL_TO_INT	REAL	INT	"*__OUT=(INT	)__move_REAL	(EN,__ENO,IN);"	
$create	REAL_TO_LINT	REAL	LINT	"*__OUT=(LINT	)__move_REAL	(EN,__ENO,IN);"	
$create	REAL_TO_LREAL	REAL	LREAL	"*__OUT=(LREAL	)__move_REAL	(EN,__ENO,IN);"	
$create	REAL_TO_LWORD	REAL	LWORD	"*__OUT=(LWORD	)__move_REAL	(EN,__ENO,IN);"	
$create	REAL_TO_SINT	REAL	SINT	"*__OUT=(SINT	)__move_REAL	(EN,__ENO,IN);"	
$create	REAL_TO_UDINT	REAL	UDINT	"*__OUT=(UDINT	)__move_REAL	(EN,__ENO,IN);"	
$create	REAL_TO_UINT	REAL	UINT	"*__OUT=(UINT	)__move_REAL	(EN,__ENO,IN);"	
$create	REAL_TO_ULINT	REAL	ULINT	"*__OUT=(ULINT	)__move_REAL	(EN,__ENO,IN);"	
$create	REAL_TO_USINT	REAL	USINT	"*__OUT=(USINT	)__move_REAL	(EN,__ENO,IN);"	
$create	REAL_TO_WORD	REAL	WORD	"*__OUT=(WORD	)__move_REAL	(EN,__ENO,IN);"	
$create	SINT_TO_BOOL	SINT	BOOL	"*__OUT=(BOOL	)__move_SINT	(EN,__ENO,IN);"	
$create	SINT_TO_BYTE	SINT	BYTE	"*__OUT=(BYTE	)__move_SINT	(EN,__ENO,IN);"	
$create	SINT_TO_DINT	SINT	DINT	"*__OUT=(DINT	)__move_SINT	(EN,__ENO,IN);"	
$create	SINT_TO_DWORD	SINT	DWORD	"*__OUT=(DWORD	)__move_SINT	(EN,__ENO,IN);"	
$create	SINT_TO_INT	SINT	INT	"*__OUT=(INT	)__move_SINT	(EN,__ENO,IN);"	
$create	SINT_TO_LINT	SINT	LINT	"*__OUT=(LINT	)__move_SINT	(EN,__ENO,IN);"	
$create	SINT_TO_LREAL	SINT	LREAL	"*__OUT=(LREAL	)__move_SINT	(EN,__ENO,IN);"	
$create	SINT_TO_LWORD	SINT	LWORD	"*__OUT=(LWORD	)__move_SINT	(EN,__ENO,IN);"	
$create	SINT_TO_REAL	SINT	REAL	"*__OUT=(REAL	)__move_SINT	(EN,__ENO,IN);"	
$create	SINT_TO_UDINT	SINT	UDINT	"*__OUT=(UDINT	)__move_SINT	(EN,__ENO,IN);"	
$create	SINT_TO_UINT	SINT	UINT	"*__OUT=(UINT	)__move_SINT	(EN,__ENO,IN);"	
$create	SINT_TO_ULINT	SINT	ULINT	"*__OUT=(ULINT	)__move_SINT	(EN,__ENO,IN);"	
$create	SINT_TO_USINT	SINT	USINT	"*__OUT=(USINT	)__move_SINT	(EN,__ENO,IN);"	
$create	SINT_TO_WORD	SINT	WORD	"*__OUT=(WORD	)__move_SINT	(EN,__ENO,IN);"	
$create	UDINT_TO_BOOL	UDINT	BOOL	"*__OUT=(BOOL	)__move_UDINT	(EN,__ENO,IN);"	
$create	UDINT_TO_BYTE	UDINT	BYTE	"*__OUT=(BYTE	)__move_UDINT	(EN,__ENO,IN);"	
$create	UDINT_TO_DINT	UDINT	DINT	"*__OUT=(DINT	)__move_UDINT	(EN,__ENO,IN);"	
$create	UDINT_TO_DWORD	UDINT	DWORD	"*__OUT=(DWORD	)__move_UDINT	(EN,__ENO,IN);"	
$create	UDINT_TO_INT	UDINT	INT	"*__OUT=(INT	)__move_UDINT	(EN,__ENO,IN);"	
$create	UDINT_TO_LINT	UDINT	LINT	"*__OUT=(LINT	)__move_UDINT	(EN,__ENO,IN);"	
$create	UDINT_TO_LREAL	UDINT	LREAL	"*__OUT=(LREAL	)__move_UDINT	(EN,__ENO,IN);"	
$create	UDINT_TO_LWORD	UDINT	LWORD	"*__OUT=(LWORD	)__move_UDINT	(EN,__ENO,IN);"	
$create	UDINT_TO_REAL	UDINT	REAL	"*__OUT=(REAL	)__move_UDINT	(EN,__ENO,IN);"	
$create	UDINT_TO_SINT	UDINT	SINT	"*__OUT=(SINT	)__move_UDINT	(EN,__ENO,IN);"	
$create	UDINT_TO_UINT	UDINT	UINT	"*__OUT=(UINT	)__move_UDINT	(EN,__ENO,IN);"	
$create	UDINT_TO_ULINT	UDINT	ULINT	"*__OUT=(ULINT	)__move_UDINT	(EN,__ENO,IN);"	
$create	UDINT_TO_USINT	UDINT	USINT	"*__OUT=(USINT	)__move_UDINT	(EN,__ENO,IN);"	
$create	UDINT_TO_WORD	UDINT	WORD	"*__OUT=(WORD	)__move_UDINT	(EN,__ENO,IN);"	
$create	UINT_TO_BOOL	UINT	BOOL	"*__OUT=(BOOL	)__move_UINT	(EN,__ENO,IN);"	
$create	UINT_TO_BYTE	UINT	BYTE	"*__OUT=(BYTE	)__move_UINT	(EN,__ENO,IN);"	
$create	UINT_TO_DINT	UINT	DINT	"*__OUT=(DINT	)__move_UINT	(EN,__ENO,IN);"	
$create	UINT_TO_DWORD	UINT	DWORD	"*__OUT=(DWORD	)__move_UINT	(EN,__ENO,IN);"	
$create	UINT_TO_INT	UINT	INT	"*__OUT=(INT	)__move_UINT	(EN,__ENO,IN);"	
$create	UINT_TO_LINT	UINT	LINT	"*__OUT=(LINT	)__move_UINT	(EN,__ENO,IN);"	
$create	UINT_TO_LREAL	UINT	LREAL	"*__OUT=(LREAL	)__move_UINT	(EN,__ENO,IN);"	
$create	UINT_TO_LWORD	UINT	LWORD	"*__OUT=(LWORD	)__move_UINT	(EN,__ENO,IN);"	
$create	UINT_TO_REAL	UINT	REAL	"*__OUT=(REAL	)__move_UINT	(EN,__ENO,IN);"	
$create	UINT_TO_SINT	UINT	SINT	"*__OUT=(SINT	)__move_UINT	(EN,__ENO,IN);"	
$create	UINT_TO_UDINT	UINT	UDINT	"*__OUT=(UDINT	)__move_UINT	(EN,__ENO,IN);"	
$create	UINT_TO_ULINT	UINT	ULINT	"*__OUT=(ULINT	)__move_UINT	(EN,__ENO,IN);"	
$create	UINT_TO_USINT	UINT	USINT	"*__OUT=(USINT	)__move_UINT	(EN,__ENO,IN);"	
$create	UINT_TO_WORD	UINT	WORD	"*__OUT=(WORD	)__move_UINT	(EN,__ENO,IN);"	
$create	ULINT_TO_BOOL	ULINT	BOOL	"*__OUT=(BOOL	)__move_ULINT	(EN,__ENO,IN);"	
$create	ULINT_TO_BYTE	ULINT	BYTE	"*__OUT=(BYTE	)__move_ULINT	(EN,__ENO,IN);"	
$create	ULINT_TO_DINT	ULINT	DINT	"*__OUT=(DINT	)__move_ULINT	(EN,__ENO,IN);"	
$create	ULINT_TO_DWORD	ULINT	DWORD	"*__OUT=(DWORD	)__move_ULINT	(EN,__ENO,IN);"	
$create	ULINT_TO_INT	ULINT	INT	"*__OUT=(INT	)__move_ULINT	(EN,__ENO,IN);"	
$create	ULINT_TO_LINT	ULINT	LINT	"*__OUT=(LINT	)__move_ULINT	(EN,__ENO,IN);"	
$create	ULINT_TO_LREAL	ULINT	LREAL	"*__OUT=(LREAL	)__move_ULINT	(EN,__ENO,IN);"	
$create	ULINT_TO_LWORD	ULINT	LWORD	"*__OUT=(LWORD	)__move_ULINT	(EN,__ENO,IN);"	
$create	ULINT_TO_REAL	ULINT	REAL	"*__OUT=(REAL	)__move_ULINT	(EN,__ENO,IN);"	
$create	ULINT_TO_SINT	ULINT	SINT	"*__OUT=(SINT	)__move_ULINT	(EN,__ENO,IN);"	
$create	ULINT_TO_UDINT	ULINT	UDINT	"*__OUT=(UDINT	)__move_ULINT	(EN,__ENO,IN);"	
$create	ULINT_TO_UINT	ULINT	UINT	"*__OUT=(UINT	)__move_ULINT	(EN,__ENO,IN);"	
$create	ULINT_TO_USINT	ULINT	USINT	"*__OUT=(USINT	)__move_ULINT	(EN,__ENO,IN);"	
$create	ULINT_TO_WORD	ULINT	WORD	"*__OUT=(WORD	)__move_ULINT	(EN,__ENO,IN);"	
$create	USINT_TO_BOOL	USINT	BOOL	"*__OUT=(BOOL	)__move_USINT	(EN,__ENO,IN);"	
$create	USINT_TO_BYTE	USINT	BYTE	"*__OUT=(BYTE	)__move_USINT	(EN,__ENO,IN);"	
$create	USINT_TO_DINT	USINT	DINT	"*__OUT=(DINT	)__move_USINT	(EN,__ENO,IN);"	
$create	USINT_TO_DWORD	USINT	DWORD	"*__OUT=(DWORD	)__move_USINT	(EN,__ENO,IN);"	
$create	USINT_TO_INT	USINT	INT	"*__OUT=(INT	)__move_USINT	(EN,__ENO,IN);"	
$create	USINT_TO_LINT	USINT	LINT	"*__OUT=(LINT	)__move_USINT	(EN,__ENO,IN);"	
$create	USINT_TO_LREAL	USINT	LREAL	"*__OUT=(LREAL	)__move_USINT	(EN,__ENO,IN);"	
$create	USINT_TO_LWORD	USINT	LWORD	"*__OUT=(LWORD	)__move_USINT	(EN,__ENO,IN);"	
$create	USINT_TO_REAL	USINT	REAL	"*__OUT=(REAL	)__move_USINT	(EN,__ENO,IN);"	
$create	USINT_TO_SINT	USINT	SINT	"*__OUT=(SINT	)__move_USINT	(EN,__ENO,IN);"	
$create	USINT_TO_UDINT	USINT	UDINT	"*__OUT=(UDINT	)__move_USINT	(EN,__ENO,IN);"	
$create	USINT_TO_UINT	USINT	UINT	"*__OUT=(UINT	)__move_USINT	(EN,__ENO,IN);"	
$create	USINT_TO_ULINT	USINT	ULINT	"*__OUT=(ULINT	)__move_USINT	(EN,__ENO,IN);"	
$create	USINT_TO_WORD	USINT	WORD	"*__OUT=(WORD	)__move_USINT	(EN,__ENO,IN);"	
$create	WORD_TO_BOOL	WORD	BOOL	"*__OUT=(BOOL	)__move_WORD	(EN,__ENO,IN);"	
$create	WORD_TO_BYTE	WORD	BYTE	"*__OUT=(BYTE	)__move_WORD	(EN,__ENO,IN);"	
$create	WORD_TO_DINT	WORD	DINT	"*__OUT=(DINT	)__move_WORD	(EN,__ENO,IN);"	
$create	WORD_TO_DWORD	WORD	DWORD	"*__OUT=(DWORD	)__move_WORD	(EN,__ENO,IN);"	
$create	WORD_TO_INT	WORD	INT	"*__OUT=(INT	)__move_WORD	(EN,__ENO,IN);"	
$create	WORD_TO_LINT	WORD	LINT	"*__OUT=(LINT	)__move_WORD	(EN,__ENO,IN);"	
$create	WORD_TO_LREAL	WORD	LREAL	"*__OUT=(LREAL	)__move_WORD	(EN,__ENO,IN);"	
$create	WORD_TO_LWORD	WORD	LWORD	"*__OUT=(LWORD	)__move_WORD	(EN,__ENO,IN);"	
$create	WORD_TO_REAL	WORD	REAL	"*__OUT=(REAL	)__move_WORD	(EN,__ENO,IN);"	
$create	WORD_TO_SINT	WORD	SINT	"*__OUT=(SINT	)__move_WORD	(EN,__ENO,IN);"	
$create	WORD_TO_UDINT	WORD	UDINT	"*__OUT=(UDINT	)__move_WORD	(EN,__ENO,IN);"	
$create	WORD_TO_UINT	WORD	UINT	"*__OUT=(UINT	)__move_WORD	(EN,__ENO,IN);"	
$create	WORD_TO_ULINT	WORD	ULINT	"*__OUT=(ULINT	)__move_WORD	(EN,__ENO,IN);"	
$create	WORD_TO_USINT	WORD	USINT	"*__OUT=(USINT	)__move_WORD	(EN,__ENO,IN);"	


########################
# Handling strings...  #
########################
$create	STRING_TO_BOOL	STRING	BOOL	"*__OUT=(BOOL	)__string_to_bool	(EN,__ENO,IN);"	
$create	STRING_TO_BYTE	STRING	BYTE	"*__OUT=(BYTE	)__string_to_bit	(EN,__ENO,IN);"	
$create	STRING_TO_WORD	STRING	WORD	"*__OUT=(WORD	)__string_to_bit	(EN,__ENO,IN);"	
$create	STRING_TO_DWORD	STRING	DWORD	"*__OUT=(DWORD	)__string_to_bit	(EN,__ENO,IN);"	
$create	STRING_TO_LWORD	STRING	LWORD	"*__OUT=(LWORD	)__string_to_bit	(EN,__ENO,IN);"	
$create	STRING_TO_SINT	STRING	SINT	"*__OUT=(SINT	)__string_to_sint	(EN,__ENO,IN);"	
$create	STRING_TO_INT	STRING	INT	"*__OUT=(INT	)__string_to_sint	(EN,__ENO,IN);"	
$create	STRING_TO_DINT	STRING	DINT	"*__OUT=(DINT	)__string_to_sint	(EN,__ENO,IN);"	
$create	STRING_TO_LINT	STRING	LINT	"*__OUT=(LINT	)__string_to_sint	(EN,__ENO,IN);"	
$create	STRING_TO_USINT	STRING	USINT	"*__OUT=(USINT	)__string_to_uint	(EN,__ENO,IN);"	
$create	STRING_TO_UINT	STRING	UINT	"*__OUT=(UINT	)__string_to_uint	(EN,__ENO,IN);"	
$create	STRING_TO_UDINT	STRING	UDINT	"*__OUT=(UDINT	)__string_to_uint	(EN,__ENO,IN);"	
$create	STRING_TO_ULINT	STRING	ULINT	"*__OUT=(ULINT	)__string_to_uint	(EN,__ENO,IN);"	
$create	STRING_TO_REAL	STRING	REAL	"*__OUT=(REAL	)__string_to_real	(EN,__ENO,IN);"	
$create	STRING_TO_LREAL	STRING	LREAL	"*__OUT=(LREAL	)__string_to_real	(EN,__ENO,IN);"	
$create	STRING_TO_DATE	STRING	DATE	"*__OUT=(DATE	)__string_to_time	(EN,__ENO,IN);"
$create	STRING_TO_TIME	STRING	TIME	"*__OUT=(TIME	)__string_to_time	(EN,__ENO,IN);"
$create	STRING_TO_TOD	STRING	TOD	"*__OUT=(TOD	)__string_to_time	(EN,__ENO,IN);"
$create	STRING_TO_DT	STRING	DT	"*__OUT=(DT	)__string_to_time	(EN,__ENO,IN);"

$create	BOOL_TO_STRING	BOOL	STRING	"*__OUT=(STRING	)__bool_to_string	(EN,__ENO,IN);"
$create	BYTE_TO_STRING	BYTE	STRING	"*__OUT=(STRING	)__bit_to_string	(EN,__ENO,IN);"
$create	WORD_TO_STRING	WORD	STRING	"*__OUT=(STRING	)__bit_to_string	(EN,__ENO,IN);"
$create	DWORD_TO_STRING	DWORD	STRING	"*__OUT=(STRING	)__bit_to_string	(EN,__ENO,IN);"
$create	LWORD_TO_STRING	LWORD	STRING	"*__OUT=(STRING	)__bit_to_string	(EN,__ENO,IN);"
$create	INT_TO_STRING	INT	STRING	"*__OUT=(STRING	)__sint_to_string	(EN,__ENO,IN);"
$create	LINT_TO_STRING	LINT	STRING	"*__OUT=(STRING	)__sint_to_string	(EN,__ENO,IN);"
$create	DINT_TO_STRING	DINT	STRING	"*__OUT=(STRING	)__sint_to_string	(EN,__ENO,IN);"
$create	SINT_TO_STRING	SINT	STRING	"*__OUT=(STRING	)__sint_to_string	(EN,__ENO,IN);"
$create	USINT_TO_STRING	USINT	STRING	"*__OUT=(STRING	)__uint_to_string	(EN,__ENO,IN);"
$create	UINT_TO_STRING	UINT	STRING	"*__OUT=(STRING	)__uint_to_string	(EN,__ENO,IN);"
$create	UDINT_TO_STRING	UDINT	STRING	"*__OUT=(STRING	)__uint_to_string	(EN,__ENO,IN);"
$create	ULINT_TO_STRING	ULINT	STRING	"*__OUT=(STRING	)__uint_to_string	(EN,__ENO,IN);"
$create	REAL_TO_STRING	REAL	STRING	"*__OUT=(STRING	)__real_to_string	(EN,__ENO,IN);"
$create	LREAL_TO_STRING	LREAL	STRING	"*__OUT=(STRING	)__real_to_string	(EN,__ENO,IN);"
$create	DATE_TO_STRING	DATE	STRING	"*__OUT=(STRING	)__date_to_string	(EN,__ENO,IN);"
$create	DT_TO_STRING	DT	STRING	"*__OUT=(STRING	)__dt_to_string	(EN,__ENO,IN);"
$create	TIME_TO_STRING	TIME	STRING	"*__OUT=(STRING	)__time_to_string	(EN,__ENO,IN);"
$create	TOD_TO_STRING	TOD	STRING	"*__OUT=(STRING	)__tod_to_string	(EN,__ENO,IN);"

########################
# Handling of dates    #
########################
$create	BOOL_TO_DATE	BOOL	DATE	"*__OUT=(DATE	)__int_to_time	(EN,__ENO,IN);"
$create	BYTE_TO_DATE	BYTE	DATE	"*__OUT=(DATE	)__int_to_time	(EN,__ENO,IN);"
$create	WORD_TO_DATE	WORD	DATE	"*__OUT=(DATE	)__int_to_time	(EN,__ENO,IN);"
$create	DWORD_TO_DATE	DWORD	DATE	"*__OUT=(DATE	)__int_to_time	(EN,__ENO,IN);"
$create	LWORD_TO_DATE	LWORD	DATE	"*__OUT=(DATE	)__int_to_time	(EN,__ENO,IN);"
$create	SINT_TO_DATE	SINT	DATE	"*__OUT=(DATE	)__int_to_time	(EN,__ENO,IN);"
$create	INT_TO_DATE	INT	DATE	"*__OUT=(DATE	)__int_to_time	(EN,__ENO,IN);"
$create	DINT_TO_DATE	DINT	DATE	"*__OUT=(DATE	)__int_to_time	(EN,__ENO,IN);"
$create	LINT_TO_DATE	LINT	DATE	"*__OUT=(DATE	)__int_to_time	(EN,__ENO,IN);"
$create	USINT_TO_DATE	USINT	DATE	"*__OUT=(DATE	)__int_to_time	(EN,__ENO,IN);"
$create	UINT_TO_DATE	UINT	DATE	"*__OUT=(DATE	)__int_to_time	(EN,__ENO,IN);"
$create	UDINT_TO_DATE	UDINT	DATE	"*__OUT=(DATE	)__int_to_time	(EN,__ENO,IN);"
$create	ULINT_TO_DATE	ULINT	DATE	"*__OUT=(DATE	)__int_to_time	(EN,__ENO,IN);"
$create	REAL_TO_DATE	REAL	DATE	"*__OUT=(DATE	)__real_to_time	(EN,__ENO,IN);"
$create	LREAL_TO_DATE	LREAL	DATE	"*__OUT=(DATE	)__real_to_time	(EN,__ENO,IN);"

$create	DATE_TO_BYTE	DATE	BYTE	"*__OUT=(BYTE	)__time_to_int	(EN,__ENO,IN);"	
$create	DATE_TO_WORD	DATE	WORD	"*__OUT=(WORD	)__time_to_int	(EN,__ENO,IN);"	
$create	DATE_TO_DWORD	DATE	DWORD	"*__OUT=(DWORD	)__time_to_int	(EN,__ENO,IN);"	
$create	DATE_TO_LWORD	DATE	LWORD	"*__OUT=(LWORD	)__time_to_int	(EN,__ENO,IN);"	
$create	DATE_TO_SINT	DATE	SINT	"*__OUT=(SINT	)__time_to_int	(EN,__ENO,IN);"	
$create	DATE_TO_INT	DATE	INT	"*__OUT=(INT	)__time_to_int	(EN,__ENO,IN);"	
$create	DATE_TO_DINT	DATE	DINT	"*__OUT=(DINT	)__time_to_int	(EN,__ENO,IN);"	
$create	DATE_TO_LINT	DATE	LINT	"*__OUT=(LINT	)__time_to_int	(EN,__ENO,IN);"	
$create	DATE_TO_USINT	DATE	USINT	"*__OUT=(USINT	)__time_to_int	(EN,__ENO,IN);"	
$create	DATE_TO_UINT	DATE	UINT	"*__OUT=(UINT	)__time_to_int	(EN,__ENO,IN);"	
$create	DATE_TO_UDINT	DATE	UDINT	"*__OUT=(UDINT	)__time_to_int	(EN,__ENO,IN);"	
$create	DATE_TO_ULINT	DATE	ULINT	"*__OUT=(ULINT	)__time_to_int	(EN,__ENO,IN);"	
$create	DATE_TO_REAL	DATE	REAL	"*__OUT=(REAL	)__time_to_real	(EN,__ENO,IN);"	
$create	DATE_TO_LREAL	DATE	LREAL	"*__OUT=(LREAL	)__time_to_real	(EN,__ENO,IN);"	

########################
# Handling of TIME     #
########################
$create	BOOL_TO_TIME	BOOL	TIME	"*__OUT=(TIME	)__int_to_time	(EN,__ENO,IN);"
$create	BYTE_TO_TIME	BYTE	TIME	"*__OUT=(TIME	)__int_to_time	(EN,__ENO,IN);"
$create	WORD_TO_TIME	WORD	TIME	"*__OUT=(TIME	)__int_to_time	(EN,__ENO,IN);"
$create	DWORD_TO_TIME	DWORD	TIME	"*__OUT=(TIME	)__int_to_time	(EN,__ENO,IN);"
$create	LWORD_TO_TIME	LWORD	TIME	"*__OUT=(TIME	)__int_to_time	(EN,__ENO,IN);"
$create	SINT_TO_TIME	SINT	TIME	"*__OUT=(TIME	)__int_to_time	(EN,__ENO,IN);"
$create	INT_TO_TIME	INT	TIME	"*__OUT=(TIME	)__int_to_time	(EN,__ENO,IN);"
$create	DINT_TO_TIME	DINT	TIME	"*__OUT=(TIME	)__int_to_time	(EN,__ENO,IN);"
$create	LINT_TO_TIME	LINT	TIME	"*__OUT=(TIME	)__int_to_time	(EN,__ENO,IN);"
$create	USINT_TO_TIME	USINT	TIME	"*__OUT=(TIME	)__int_to_time	(EN,__ENO,IN);"
$create	UINT_TO_TIME	UINT	TIME	"*__OUT=(TIME	)__int_to_time	(EN,__ENO,IN);"
$create	UDINT_TO_TIME	UDINT	TIME	"*__OUT=(TIME	)__int_to_time	(EN,__ENO,IN);"
$create	ULINT_TO_TIME	ULINT	TIME	"*__OUT=(TIME	)__int_to_time	(EN,__ENO,IN);"
$create	REAL_TO_TIME	REAL	TIME	"*__OUT=(TIME	)__real_to_time	(EN,__ENO,IN);"
$create	LREAL_TO_TIME	LREAL	TIME	"*__OUT=(TIME	)__real_to_time	(EN,__ENO,IN);"

$create	TIME_TO_BYTE	TIME	BYTE	"*__OUT=(BYTE	)__time_to_int	(EN,__ENO,IN);"	
$create	TIME_TO_WORD	TIME	WORD	"*__OUT=(WORD	)__time_to_int	(EN,__ENO,IN);"	
$create	TIME_TO_DWORD	TIME	DWORD	"*__OUT=(DWORD	)__time_to_int	(EN,__ENO,IN);"	
$create	TIME_TO_LWORD	TIME	LWORD	"*__OUT=(LWORD	)__time_to_int	(EN,__ENO,IN);"	
$create	TIME_TO_SINT	TIME	SINT	"*__OUT=(SINT	)__time_to_int	(EN,__ENO,IN);"	
$create	TIME_TO_INT	TIME	INT	"*__OUT=(INT	)__time_to_int	(EN,__ENO,IN);"	
$create	TIME_TO_DINT	TIME	DINT	"*__OUT=(DINT	)__time_to_int	(EN,__ENO,IN);"	
$create	TIME_TO_LINT	TIME	LINT	"*__OUT=(LINT	)__time_to_int	(EN,__ENO,IN);"	
$create	TIME_TO_USINT	TIME	USINT	"*__OUT=(USINT	)__time_to_int	(EN,__ENO,IN);"	
$create	TIME_TO_UINT	TIME	UINT	"*__OUT=(UINT	)__time_to_int	(EN,__ENO,IN);"	
$create	TIME_TO_UDINT	TIME	UDINT	"*__OUT=(UDINT	)__time_to_int	(EN,__ENO,IN);"	
$create	TIME_TO_ULINT	TIME	ULINT	"*__OUT=(ULINT	)__time_to_int	(EN,__ENO,IN);"	
$create	TIME_TO_REAL	TIME	REAL	"*__OUT=(REAL	)__time_to_real	(EN,__ENO,IN);"	
$create	TIME_TO_LREAL	TIME	LREAL	"*__OUT=(LREAL	)__time_to_real	(EN,__ENO,IN);"	


##############################
# Handling of DATE_AND_TIME  #
##############################
$create	BOOL_TO_DT	BOOL	DT	"*__OUT=(DT	)__int_to_time	(EN,__ENO,IN);"
$create	BYTE_TO_DT	BYTE	DT	"*__OUT=(DT	)__int_to_time	(EN,__ENO,IN);"
$create	WORD_TO_DT	WORD	DT	"*__OUT=(DT	)__int_to_time	(EN,__ENO,IN);"
$create	DWORD_TO_DT	DWORD	DT	"*__OUT=(DT	)__int_to_time	(EN,__ENO,IN);"
$create	LWORD_TO_DT	LWORD	DT	"*__OUT=(DT	)__int_to_time	(EN,__ENO,IN);"
$create	SINT_TO_DT	SINT	DT	"*__OUT=(DT	)__int_to_time	(EN,__ENO,IN);"
$create	INT_TO_DT	INT	DT	"*__OUT=(DT	)__int_to_time	(EN,__ENO,IN);"
$create	DINT_TO_DT	DINT	DT	"*__OUT=(DT	)__int_to_time	(EN,__ENO,IN);"
$create	LINT_TO_DT	LINT	DT	"*__OUT=(DT	)__int_to_time	(EN,__ENO,IN);"
$create	USINT_TO_DT	USINT	DT	"*__OUT=(DT	)__int_to_time	(EN,__ENO,IN);"
$create	UINT_TO_DT	UINT	DT	"*__OUT=(DT	)__int_to_time	(EN,__ENO,IN);"
$create	UDINT_TO_DT	UDINT	DT	"*__OUT=(DT	)__int_to_time	(EN,__ENO,IN);"
$create	ULINT_TO_DT	ULINT	DT	"*__OUT=(DT	)__int_to_time	(EN,__ENO,IN);"
$create	REAL_TO_DT	REAL	DT	"*__OUT=(DT	)__real_to_time	(EN,__ENO,IN);"
$create	LREAL_TO_DT	LREAL	DT	"*__OUT=(DT	)__real_to_time	(EN,__ENO,IN);"

$create	DT_TO_BYTE	DT	BYTE	"*__OUT=(BYTE	)__time_to_int	(EN,__ENO,IN);"	
$create	DT_TO_WORD	DT	WORD	"*__OUT=(WORD	)__time_to_int	(EN,__ENO,IN);"	
$create	DT_TO_DWORD	DT	DWORD	"*__OUT=(DWORD	)__time_to_int	(EN,__ENO,IN);"	
$create	DT_TO_LWORD	DT	LWORD	"*__OUT=(LWORD	)__time_to_int	(EN,__ENO,IN);"	
$create	DT_TO_SINT	DT	SINT	"*__OUT=(SINT	)__time_to_int	(EN,__ENO,IN);"	
$create	DT_TO_INT	DT	INT	"*__OUT=(INT	)__time_to_int	(EN,__ENO,IN);"	
$create	DT_TO_DINT	DT	DINT	"*__OUT=(DINT	)__time_to_int	(EN,__ENO,IN);"	
$create	DT_TO_LINT	DT	LINT	"*__OUT=(LINT	)__time_to_int	(EN,__ENO,IN);"	
$create	DT_TO_USINT	DT	USINT	"*__OUT=(USINT	)__time_to_int	(EN,__ENO,IN);"	
$create	DT_TO_UINT	DT	UINT	"*__OUT=(UINT	)__time_to_int	(EN,__ENO,IN);"	
$create	DT_TO_UDINT	DT	UDINT	"*__OUT=(UDINT	)__time_to_int	(EN,__ENO,IN);"	
$create	DT_TO_ULINT	DT	ULINT	"*__OUT=(ULINT	)__time_to_int	(EN,__ENO,IN);"	
$create	DT_TO_REAL	DT	REAL	"*__OUT=(REAL	)__time_to_real	(EN,__ENO,IN);"	
$create	DT_TO_LREAL	DT	LREAL	"*__OUT=(LREAL	)__time_to_real	(EN,__ENO,IN);"	


####################
# Handling of TOD  #
####################

$create	BOOL_TO_TOD	BOOL	TOD	"*__OUT=(TOD	)__int_to_time	(EN,__ENO,IN);"
$create	BYTE_TO_TOD	BYTE	TOD	"*__OUT=(TOD	)__int_to_time	(EN,__ENO,IN);"
$create	WORD_TO_TOD	WORD	TOD	"*__OUT=(TOD	)__int_to_time	(EN,__ENO,IN);"
$create	DWORD_TO_TOD	DWORD	TOD	"*__OUT=(TOD	)__int_to_time	(EN,__ENO,IN);"
$create	LWORD_TO_TOD	LWORD	TOD	"*__OUT=(TOD	)__int_to_time	(EN,__ENO,IN);"
$create	SINT_TO_TOD	SINT	TOD	"*__OUT=(TOD	)__int_to_time	(EN,__ENO,IN);"
$create	INT_TO_TOD	INT	TOD	"*__OUT=(TOD	)__int_to_time	(EN,__ENO,IN);"
$create	DINT_TO_TOD	DINT	TOD	"*__OUT=(TOD	)__int_to_time	(EN,__ENO,IN);"
$create	LINT_TO_TOD	LINT	TOD	"*__OUT=(TOD	)__int_to_time	(EN,__ENO,IN);"
$create	USINT_TO_TOD	USINT	TOD	"*__OUT=(TOD	)__int_to_time	(EN,__ENO,IN);"
$create	UINT_TO_TOD	UINT	TOD	"*__OUT=(TOD	)__int_to_time	(EN,__ENO,IN);"
$create	UDINT_TO_TOD	UDINT	TOD	"*__OUT=(TOD	)__int_to_time	(EN,__ENO,IN);"
$create	ULINT_TO_TOD	ULINT	TOD	"*__OUT=(TOD	)__int_to_time	(EN,__ENO,IN);"
$create	REAL_TO_TOD	REAL	TOD	"*__OUT=(TOD	)__real_to_time	(EN,__ENO,IN);"
$create	LREAL_TO_TOD	LREAL	TOD	"*__OUT=(TOD	)__real_to_time	(EN,__ENO,IN);"

$create	TOD_TO_BYTE	TOD	BYTE	"*__OUT=(BYTE	)__time_to_int	(EN,__ENO,IN);"	
$create	TOD_TO_WORD	TOD	WORD	"*__OUT=(WORD	)__time_to_int	(EN,__ENO,IN);"	
$create	TOD_TO_DWORD	TOD	DWORD	"*__OUT=(DWORD	)__time_to_int	(EN,__ENO,IN);"	
$create	TOD_TO_LWORD	TOD	LWORD	"*__OUT=(LWORD	)__time_to_int	(EN,__ENO,IN);"	
$create	TOD_TO_SINT	TOD	SINT	"*__OUT=(SINT	)__time_to_int	(EN,__ENO,IN);"	
$create	TOD_TO_INT	TOD	INT	"*__OUT=(INT	)__time_to_int	(EN,__ENO,IN);"	
$create	TOD_TO_DINT	TOD	DINT	"*__OUT=(DINT	)__time_to_int	(EN,__ENO,IN);"	
$create	TOD_TO_LINT	TOD	LINT	"*__OUT=(LINT	)__time_to_int	(EN,__ENO,IN);"	
$create	TOD_TO_USINT	TOD	USINT	"*__OUT=(USINT	)__time_to_int	(EN,__ENO,IN);"	
$create	TOD_TO_UINT	TOD	UINT	"*__OUT=(UINT	)__time_to_int	(EN,__ENO,IN);"	
$create	TOD_TO_UDINT	TOD	UDINT	"*__OUT=(UDINT	)__time_to_int	(EN,__ENO,IN);"	
$create	TOD_TO_ULINT	TOD	ULINT	"*__OUT=(ULINT	)__time_to_int	(EN,__ENO,IN);"	
$create	TOD_TO_REAL	TOD	REAL	"*__OUT=(REAL	)__time_to_real	(EN,__ENO,IN);"	
$create	TOD_TO_LREAL	TOD	LREAL	"*__OUT=(LREAL	)__time_to_real	(EN,__ENO,IN);"	



                                                                                                                                                 
$create DATE_AND_TIME_TO_TIME_OF_DAY	DT       TOD	"*__OUT = (TOD	)__date_and_time_to_time_of_day(EN,__ENO,IN);" 
$create DATE_AND_TIME_TO_DATE	DT	DATE	"*__OUT = (DATE	)__date_and_time_to_date(EN,__ENO,IN);" 
                                                                                                                     



$create_end    

                                                                                          
# *BCD_TO_**   and   **_TO_BCD*     are not yet supported                        
# We comment them out for now...                                                  
exit 0                                                                                     
create   UDINT_TO_BCD_BYTE               UDINT                BYTE                             
create   UDINT_TO_BCD_WORD               UDINT                WORD                             
create   UDINT_TO_BCD_DWORD              UDINT                DWORD                            
create   UDINT_TO_BCD_LWORD              UDINT                LWORD                            
create    UINT_TO_BCD_BYTE                UINT                BYTE                             
create    UINT_TO_BCD_WORD                UINT                WORD                             
create    UINT_TO_BCD_DWORD               UINT                DWORD                            
create    UINT_TO_BCD_LWORD               UINT                LWORD                            
create   USINT_TO_BCD_BYTE               USINT                BYTE                             
create   USINT_TO_BCD_WORD               USINT                WORD                             
create   USINT_TO_BCD_DWORD              USINT                DWORD                            
create   USINT_TO_BCD_LWORD              USINT                LWORD               
create   ULINT_TO_BCD_BYTE               ULINT                BYTE                
create   ULINT_TO_BCD_WORD               ULINT                WORD                
create   ULINT_TO_BCD_DWORD              ULINT                DWORD               
create   ULINT_TO_BCD_LWORD              ULINT                LWORD               
                                                                                  
create   BYTE_BCD_TO_UDINT               BYTE                 UDINT                
create   WORD_BCD_TO_UDINT               WORD                 UDINT                
create  DWORD_BCD_TO_UDINT               DWORD                UDINT                
create  LWORD_BCD_TO_UDINT               LWORD                UDINT                
create   BYTE_BCD_TO_UINT                BYTE                 UINT                   
create   WORD_BCD_TO_UINT                WORD                 UINT                   
create  DWORD_BCD_TO_UINT                DWORD                UINT                   
create  LWORD_BCD_TO_UINT                LWORD                UINT                   
create   BYTE_BCD_TO_USINT               BYTE                 USINT                      
create   WORD_BCD_TO_USINT               WORD                 USINT                      
create  DWORD_BCD_TO_USINT               DWORD                USINT                      
create  LWORD_BCD_TO_USINT               LWORD                USINT                      
create   BYTE_BCD_TO_ULINT               BYTE                 ULINT                      
create   WORD_BCD_TO_ULINT               WORD                 ULINT                      
create  DWORD_BCD_TO_ULINT               DWORD                ULINT                      
create  LWORD_BCD_TO_ULINT               LWORD                ULINT                      



exit 0

    ABS             
    SQRT
    LN
    LOG
    EXP
    SIN
    COS
    TAN
    ASIN
    ACOS
    ATAN
    ADD
    MUL
    SUB
    DIV
    MOD
    EXPT
    MOVE
    SHL
    SHR
    ROR
    ROL
    AND
    OR
    XOR
    NOT
    SEL
    MAX
    MIN
    LIMIT
    MUX
    GT
    GE
    EQ
    LT
    LE
    NE
    LEN
    LEFT
    RIGHT
    MID
    CONCAT
    INSERT
    DELETE
    REPLACE
    FIND
    
    TRUNC
    
    
    
    
    
    
    
    
