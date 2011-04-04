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


create()
{
echo
echo
echo FUNCTION $1 : $3
echo "  "VAR_INPUT   IN: $2";" END_VAR
echo "  "VAR_OUTPUT OUT: $3";" END_VAR
echo "  "LD TRUE
echo END_FUNCTION
}




echo
echo {disable code generation}
echo
echo

create    REAL_TO_SINT                    REAL                SINT      
create    REAL_TO_LINT                    REAL                LINT      
create    REAL_TO_DINT                    REAL                DINT      
create    REAL_TO_DATE                    REAL                DATE      
create    REAL_TO_DWORD                   REAL                DWORD     
create    REAL_TO_DT                      REAL                DT        
create    REAL_TO_TOD                     REAL                TOD       
create    REAL_TO_UDINT                   REAL                UDINT     
create    REAL_TO_WORD                    REAL                WORD      
create    REAL_TO_STRING                  REAL                STRING    
create    REAL_TO_LWORD                   REAL                LWORD     
create    REAL_TO_UINT                    REAL                UINT      
create    REAL_TO_LREAL                   REAL                LREAL     
create    REAL_TO_BYTE                    REAL                BYTE      
create    REAL_TO_USINT                   REAL                USINT     
create    REAL_TO_ULINT                   REAL                ULINT     
create    REAL_TO_BOOL                    REAL                BOOL      
create    REAL_TO_TIME                    REAL                TIME      
create    REAL_TO_INT                     REAL                INT       
create    SINT_TO_REAL                    SINT                REAL      
create    SINT_TO_LINT                    SINT                LINT      
create    SINT_TO_DINT                    SINT                DINT      
create    SINT_TO_DATE                    SINT                DATE      
create    SINT_TO_DWORD                   SINT                DWORD     
create    SINT_TO_DT                      SINT                DT        
create    SINT_TO_TOD                     SINT                TOD       
create    SINT_TO_UDINT                   SINT                UDINT     
create    SINT_TO_WORD                    SINT                WORD      
create    SINT_TO_STRING                  SINT                STRING    
create    SINT_TO_LWORD                   SINT                LWORD     
create    SINT_TO_UINT                    SINT                UINT      
create    SINT_TO_LREAL                   SINT                LREAL     
create    SINT_TO_BYTE                    SINT                BYTE      
create    SINT_TO_USINT                   SINT                USINT     
create    SINT_TO_ULINT                   SINT                ULINT     
create    SINT_TO_BOOL                    SINT                BOOL      
create    SINT_TO_TIME                    SINT                TIME      
create    SINT_TO_INT                     SINT                INT       
create    LINT_TO_REAL                    LINT                REAL      
create    LINT_TO_SINT                    LINT                SINT      
create    LINT_TO_DINT                    LINT                DINT      
create    LINT_TO_DATE                    LINT                DATE      
create    LINT_TO_DWORD                   LINT                DWORD     
create    LINT_TO_DT                      LINT                DT        
create    LINT_TO_TOD                     LINT                TOD       
create    LINT_TO_UDINT                   LINT                UDINT     
create    LINT_TO_WORD                    LINT                WORD      
create    LINT_TO_STRING                  LINT                STRING    
create    LINT_TO_LWORD                   LINT                LWORD     
create    LINT_TO_UINT                    LINT                UINT      
create    LINT_TO_LREAL                   LINT                LREAL     
create    LINT_TO_BYTE                    LINT                BYTE      
create    LINT_TO_USINT                   LINT                USINT     
create    LINT_TO_ULINT                   LINT                ULINT     
create    LINT_TO_BOOL                    LINT                BOOL      
create    LINT_TO_TIME                    LINT                TIME      
create    LINT_TO_INT                     LINT                INT       
create    DINT_TO_REAL                    DINT                REAL      
create    DINT_TO_SINT                    DINT                SINT      
create    DINT_TO_LINT                    DINT                LINT      
create    DINT_TO_DATE                    DINT                DATE      
create    DINT_TO_DWORD                   DINT                DWORD     
create    DINT_TO_DT                      DINT                DT        
create    DINT_TO_TOD                     DINT                TOD       
create    DINT_TO_UDINT                   DINT                UDINT     
create    DINT_TO_WORD                    DINT                WORD      
create    DINT_TO_STRING                  DINT                STRING    
create    DINT_TO_LWORD                   DINT                LWORD     
create    DINT_TO_UINT                    DINT                UINT      
create    DINT_TO_LREAL                   DINT                LREAL     
create    DINT_TO_BYTE                    DINT                BYTE      
create    DINT_TO_USINT                   DINT                USINT     
create    DINT_TO_ULINT                   DINT                ULINT     
create    DINT_TO_BOOL                    DINT                BOOL      
create    DINT_TO_TIME                    DINT                TIME      
create    DINT_TO_INT                     DINT                INT       
create    DATE_TO_REAL                    DATE                REAL      
create    DATE_TO_SINT                    DATE                SINT      
create    DATE_TO_LINT                    DATE                LINT      
create    DATE_TO_DINT                    DATE                DINT      
create    DATE_TO_DWORD                   DATE                DWORD     
create    DATE_TO_UDINT                   DATE                UDINT     
create    DATE_TO_WORD                    DATE                WORD      
create    DATE_TO_STRING                  DATE                STRING    
create    DATE_TO_LWORD                   DATE                LWORD     
create    DATE_TO_UINT                    DATE                UINT      
create    DATE_TO_LREAL                   DATE                LREAL     
create    DATE_TO_BYTE                    DATE                BYTE      
create    DATE_TO_USINT                   DATE                USINT     
create    DATE_TO_ULINT                   DATE                ULINT     
create    DATE_TO_INT                     DATE                INT       
create   DWORD_TO_REAL                   DWORD                REAL      
create   DWORD_TO_SINT                   DWORD                SINT      
create   DWORD_TO_LINT                   DWORD                LINT      
create   DWORD_TO_DINT                   DWORD                DINT      
create   DWORD_TO_DATE                   DWORD                DATE      
create   DWORD_TO_DT                     DWORD                DT        
create   DWORD_TO_TOD                    DWORD                TOD       
create   DWORD_TO_UDINT                  DWORD                UDINT     
create   DWORD_TO_WORD                   DWORD                WORD      
create   DWORD_TO_STRING                 DWORD                STRING    
create   DWORD_TO_LWORD                  DWORD                LWORD     
create   DWORD_TO_UINT                   DWORD                UINT      
create   DWORD_TO_LREAL                  DWORD                LREAL     
create   DWORD_TO_BYTE                   DWORD                BYTE      
create   DWORD_TO_USINT                  DWORD                USINT     
create   DWORD_TO_ULINT                  DWORD                ULINT     
create   DWORD_TO_BOOL                   DWORD                BOOL      
create   DWORD_TO_TIME                   DWORD                TIME      
create   DWORD_TO_INT                    DWORD                INT       
create      DT_TO_REAL                      DT                REAL      
create      DT_TO_SINT                      DT                SINT      
create      DT_TO_LINT                      DT                LINT      
create      DT_TO_DINT                      DT                DINT      
create      DT_TO_DWORD                     DT                DWORD     
create      DT_TO_UDINT                     DT                UDINT     
create      DT_TO_WORD                      DT                WORD      
create      DT_TO_STRING                    DT                STRING    
create      DT_TO_LWORD                     DT                LWORD     
create      DT_TO_UINT                      DT                UINT      
create      DT_TO_LREAL                     DT                LREAL     
create      DT_TO_BYTE                      DT                BYTE      
create      DT_TO_USINT                     DT                USINT     
create      DT_TO_ULINT                     DT                ULINT     
create      DT_TO_INT                       DT                INT       
create     TOD_TO_REAL                     TOD                REAL      
create     TOD_TO_SINT                     TOD                SINT      
create     TOD_TO_LINT                     TOD                LINT      
create     TOD_TO_DINT                     TOD                DINT      
create     TOD_TO_DWORD                    TOD                DWORD     
create     TOD_TO_UDINT                    TOD                UDINT     
create     TOD_TO_WORD                     TOD                WORD      
create     TOD_TO_STRING                   TOD                STRING    
create     TOD_TO_LWORD                    TOD                LWORD     
create     TOD_TO_UINT                     TOD                UINT      
create     TOD_TO_LREAL                    TOD                LREAL     
create     TOD_TO_BYTE                     TOD                BYTE      
create     TOD_TO_USINT                    TOD                USINT     
create     TOD_TO_ULINT                    TOD                ULINT     
create     TOD_TO_INT                      TOD                INT       
create   UDINT_TO_REAL                   UDINT                REAL      
create   UDINT_TO_SINT                   UDINT                SINT      
create   UDINT_TO_LINT                   UDINT                LINT      
create   UDINT_TO_DINT                   UDINT                DINT      
create   UDINT_TO_DATE                   UDINT                DATE      
create   UDINT_TO_DWORD                  UDINT                DWORD     
create   UDINT_TO_DT                     UDINT                DT        
create   UDINT_TO_TOD                    UDINT                TOD       
create   UDINT_TO_WORD                   UDINT                WORD      
create   UDINT_TO_STRING                 UDINT                STRING    
create   UDINT_TO_LWORD                  UDINT                LWORD     
create   UDINT_TO_UINT                   UDINT                UINT      
create   UDINT_TO_LREAL                  UDINT                LREAL     
create   UDINT_TO_BYTE                   UDINT                BYTE      
create   UDINT_TO_USINT                  UDINT                USINT     
create   UDINT_TO_ULINT                  UDINT                ULINT     
create   UDINT_TO_BOOL                   UDINT                BOOL      
create   UDINT_TO_TIME                   UDINT                TIME      
create   UDINT_TO_INT                    UDINT                INT       
create    WORD_TO_REAL                    WORD                REAL      
create    WORD_TO_SINT                    WORD                SINT      
create    WORD_TO_LINT                    WORD                LINT      
create    WORD_TO_DINT                    WORD                DINT      
create    WORD_TO_DATE                    WORD                DATE      
create    WORD_TO_DWORD                   WORD                DWORD     
create    WORD_TO_DT                      WORD                DT        
create    WORD_TO_TOD                     WORD                TOD       
create    WORD_TO_UDINT                   WORD                UDINT     
create    WORD_TO_STRING                  WORD                STRING    
create    WORD_TO_LWORD                   WORD                LWORD     
create    WORD_TO_UINT                    WORD                UINT      
create    WORD_TO_LREAL                   WORD                LREAL     
create    WORD_TO_BYTE                    WORD                BYTE      
create    WORD_TO_USINT                   WORD                USINT     
create    WORD_TO_ULINT                   WORD                ULINT     
create    WORD_TO_BOOL                    WORD                BOOL      
create    WORD_TO_TIME                    WORD                TIME      
create    WORD_TO_INT                     WORD                INT       
create  STRING_TO_REAL                  STRING                REAL      
create  STRING_TO_SINT                  STRING                SINT      
create  STRING_TO_LINT                  STRING                LINT      
create  STRING_TO_DINT                  STRING                DINT      
create  STRING_TO_DATE                  STRING                DATE      
create  STRING_TO_DWORD                 STRING                DWORD     
create  STRING_TO_DT                    STRING                DT        
create  STRING_TO_TOD                   STRING                TOD       
create  STRING_TO_UDINT                 STRING                UDINT     
create  STRING_TO_WORD                  STRING                WORD      
create  STRING_TO_LWORD                 STRING                LWORD     
create  STRING_TO_UINT                  STRING                UINT      
create  STRING_TO_LREAL                 STRING                LREAL     
create  STRING_TO_BYTE                  STRING                BYTE      
create  STRING_TO_USINT                 STRING                USINT     
create  STRING_TO_ULINT                 STRING                ULINT     
create  STRING_TO_BOOL                  STRING                BOOL      
create  STRING_TO_TIME                  STRING                TIME      
create  STRING_TO_INT                   STRING                INT       
create   LWORD_TO_REAL                   LWORD                REAL      
create   LWORD_TO_SINT                   LWORD                SINT      
create   LWORD_TO_LINT                   LWORD                LINT      
create   LWORD_TO_DINT                   LWORD                DINT      
create   LWORD_TO_DATE                   LWORD                DATE      
create   LWORD_TO_DWORD                  LWORD                DWORD     
create   LWORD_TO_DT                     LWORD                DT        
create   LWORD_TO_TOD                    LWORD                TOD       
create   LWORD_TO_UDINT                  LWORD                UDINT     
create   LWORD_TO_WORD                   LWORD                WORD      
create   LWORD_TO_STRING                 LWORD                STRING    
create   LWORD_TO_UINT                   LWORD                UINT      
create   LWORD_TO_LREAL                  LWORD                LREAL     
create   LWORD_TO_BYTE                   LWORD                BYTE      
create   LWORD_TO_USINT                  LWORD                USINT     
create   LWORD_TO_ULINT                  LWORD                ULINT     
create   LWORD_TO_BOOL                   LWORD                BOOL      
create   LWORD_TO_TIME                   LWORD                TIME      
create   LWORD_TO_INT                    LWORD                INT       
create    UINT_TO_REAL                    UINT                REAL      
create    UINT_TO_SINT                    UINT                SINT      
create    UINT_TO_LINT                    UINT                LINT      
create    UINT_TO_DINT                    UINT                DINT      
create    UINT_TO_DATE                    UINT                DATE      
create    UINT_TO_DWORD                   UINT                DWORD     
create    UINT_TO_DT                      UINT                DT        
create    UINT_TO_TOD                     UINT                TOD       
create    UINT_TO_UDINT                   UINT                UDINT     
create    UINT_TO_WORD                    UINT                WORD      
create    UINT_TO_STRING                  UINT                STRING    
create    UINT_TO_LWORD                   UINT                LWORD     
create    UINT_TO_LREAL                   UINT                LREAL     
create    UINT_TO_BYTE                    UINT                BYTE      
create    UINT_TO_USINT                   UINT                USINT     
create    UINT_TO_ULINT                   UINT                ULINT     
create    UINT_TO_BOOL                    UINT                BOOL      
create    UINT_TO_TIME                    UINT                TIME      
create    UINT_TO_INT                     UINT                INT       
create   LREAL_TO_REAL                   LREAL                REAL      
create   LREAL_TO_SINT                   LREAL                SINT      
create   LREAL_TO_LINT                   LREAL                LINT      
create   LREAL_TO_DINT                   LREAL                DINT      
create   LREAL_TO_DATE                   LREAL                DATE      
create   LREAL_TO_DWORD                  LREAL                DWORD     
create   LREAL_TO_DT                     LREAL                DT        
create   LREAL_TO_TOD                    LREAL                TOD       
create   LREAL_TO_UDINT                  LREAL                UDINT     
create   LREAL_TO_WORD                   LREAL                WORD      
create   LREAL_TO_STRING                 LREAL                STRING    
create   LREAL_TO_LWORD                  LREAL                LWORD     
create   LREAL_TO_UINT                   LREAL                UINT      
create   LREAL_TO_BYTE                   LREAL                BYTE      
create   LREAL_TO_USINT                  LREAL                USINT     
create   LREAL_TO_ULINT                  LREAL                ULINT     
create   LREAL_TO_BOOL                   LREAL                BOOL      
create   LREAL_TO_TIME                   LREAL                TIME      
create   LREAL_TO_INT                    LREAL                INT       
create    BYTE_TO_REAL                    BYTE                REAL      
create    BYTE_TO_SINT                    BYTE                SINT      
create    BYTE_TO_LINT                    BYTE                LINT      
create    BYTE_TO_DINT                    BYTE                DINT      
create    BYTE_TO_DATE                    BYTE                DATE      
create    BYTE_TO_DWORD                   BYTE                DWORD     
create    BYTE_TO_DT                      BYTE                DT        
create    BYTE_TO_TOD                     BYTE                TOD       
create    BYTE_TO_UDINT                   BYTE                UDINT     
create    BYTE_TO_WORD                    BYTE                WORD      
create    BYTE_TO_STRING                  BYTE                STRING    
create    BYTE_TO_LWORD                   BYTE                LWORD     
create    BYTE_TO_UINT                    BYTE                UINT      
create    BYTE_TO_LREAL                   BYTE                LREAL     
create    BYTE_TO_USINT                   BYTE                USINT     
create    BYTE_TO_ULINT                   BYTE                ULINT     
create    BYTE_TO_BOOL                    BYTE                BOOL      
create    BYTE_TO_TIME                    BYTE                TIME      
create    BYTE_TO_INT                     BYTE                INT       
create   USINT_TO_REAL                   USINT                REAL      
create   USINT_TO_SINT                   USINT                SINT      
create   USINT_TO_LINT                   USINT                LINT      
create   USINT_TO_DINT                   USINT                DINT      
create   USINT_TO_DATE                   USINT                DATE      
create   USINT_TO_DWORD                  USINT                DWORD     
create   USINT_TO_DT                     USINT                DT        
create   USINT_TO_TOD                    USINT                TOD       
create   USINT_TO_UDINT                  USINT                UDINT     
create   USINT_TO_WORD                   USINT                WORD      
create   USINT_TO_STRING                 USINT                STRING    
create   USINT_TO_LWORD                  USINT                LWORD     
create   USINT_TO_UINT                   USINT                UINT      
create   USINT_TO_LREAL                  USINT                LREAL     
create   USINT_TO_BYTE                   USINT                BYTE      
create   USINT_TO_ULINT                  USINT                ULINT     
create   USINT_TO_BOOL                   USINT                BOOL      
create   USINT_TO_TIME                   USINT                TIME      
create   USINT_TO_INT                    USINT                INT       
create   ULINT_TO_REAL                   ULINT                REAL      
create   ULINT_TO_SINT                   ULINT                SINT      
create   ULINT_TO_LINT                   ULINT                LINT      
create   ULINT_TO_DINT                   ULINT                DINT      
create   ULINT_TO_DATE                   ULINT                DATE      
create   ULINT_TO_DWORD                  ULINT                DWORD     
create   ULINT_TO_DT                     ULINT                DT        
create   ULINT_TO_TOD                    ULINT                TOD       
create   ULINT_TO_UDINT                  ULINT                UDINT     
create   ULINT_TO_WORD                   ULINT                WORD      
create   ULINT_TO_STRING                 ULINT                STRING    
create   ULINT_TO_LWORD                  ULINT                LWORD     
create   ULINT_TO_UINT                   ULINT                UINT      
create   ULINT_TO_LREAL                  ULINT                LREAL     
create   ULINT_TO_BYTE                   ULINT                BYTE      
create   ULINT_TO_USINT                  ULINT                USINT     
create   ULINT_TO_BOOL                   ULINT                BOOL      
create   ULINT_TO_TIME                   ULINT                TIME      
create   ULINT_TO_INT                    ULINT                INT       
create    BOOL_TO_REAL                    BOOL                REAL      
create    BOOL_TO_SINT                    BOOL                SINT      
create    BOOL_TO_LINT                    BOOL                LINT      
create    BOOL_TO_DINT                    BOOL                DINT      
create    BOOL_TO_DATE                    BOOL                DATE      
create    BOOL_TO_DWORD                   BOOL                DWORD     
create    BOOL_TO_DT                      BOOL                DT        
create    BOOL_TO_TOD                     BOOL                TOD       
create    BOOL_TO_UDINT                   BOOL                UDINT     
create    BOOL_TO_WORD                    BOOL                WORD      
create    BOOL_TO_STRING                  BOOL                STRING    
create    BOOL_TO_LWORD                   BOOL                LWORD     
create    BOOL_TO_UINT                    BOOL                UINT      
create    BOOL_TO_LREAL                   BOOL                LREAL     
create    BOOL_TO_BYTE                    BOOL                BYTE      
create    BOOL_TO_USINT                   BOOL                USINT     
create    BOOL_TO_ULINT                   BOOL                ULINT     
create    BOOL_TO_TIME                    BOOL                TIME      
create    BOOL_TO_INT                     BOOL                INT       
create    TIME_TO_REAL                    TIME                REAL      
create    TIME_TO_SINT                    TIME                SINT      
create    TIME_TO_LINT                    TIME                LINT      
create    TIME_TO_DINT                    TIME                DINT      
create    TIME_TO_DWORD                   TIME                DWORD     
create    TIME_TO_UDINT                   TIME                UDINT     
create    TIME_TO_WORD                    TIME                WORD      
create    TIME_TO_STRING                  TIME                STRING    
create    TIME_TO_LWORD                   TIME                LWORD     
create    TIME_TO_UINT                    TIME                UINT      
create    TIME_TO_LREAL                   TIME                LREAL     
create    TIME_TO_BYTE                    TIME                BYTE      
create    TIME_TO_USINT                   TIME                USINT     
create    TIME_TO_ULINT                   TIME                ULINT     
create    TIME_TO_INT                     TIME                INT       
create     INT_TO_REAL                     INT                REAL      
create     INT_TO_SINT                     INT                SINT      
create     INT_TO_LINT                     INT                LINT      
create     INT_TO_DINT                     INT                DINT      
create     INT_TO_DATE                     INT                DATE      
create     INT_TO_DWORD                    INT                DWORD     
create     INT_TO_DT                       INT                DT        
create     INT_TO_TOD                      INT                TOD       
create     INT_TO_UDINT                    INT                UDINT     
create     INT_TO_WORD                     INT                WORD      
create     INT_TO_STRING                   INT                STRING    
create     INT_TO_LWORD                    INT                LWORD     
create     INT_TO_UINT                     INT                UINT      
create     INT_TO_LREAL                    INT                LREAL     
create     INT_TO_BYTE                     INT                BYTE      
create     INT_TO_USINT                    INT                USINT     
create     INT_TO_ULINT                    INT                ULINT     
create     INT_TO_BOOL                     INT                BOOL      
create     INT_TO_TIME                     INT                TIME      

create DATE_AND_TIME_TO_TIME_OF_DAY     DATE_AND_TIME       TIME_OF_DAY  
create DATE_AND_TIME_TO_DATE            DATE_AND_TIME       DATE         

echo
echo
echo  "(*   *BCD_TO_**   and   **_TO_BCD*     are not yet supported  *)"
echo  "(*  We comment them out for now...                            *)"
echo  "(*"
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
echo  "*)"


echo
echo {disable code generation}

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
    
    
    
    
    
    
    
    
