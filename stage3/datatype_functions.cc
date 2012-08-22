/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2009-2012  Mario de Sousa (msousa@fe.up.pt)
 *  Copyright (C) 2012       Manuele Conti  (conti.ma@alice.it)
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

#include "datatype_functions.hh"
#include "../absyntax_utils/absyntax_utils.hh"
#include <vector>






elementary_type_c *elementary_type_c::singleton = NULL;

const char *elementary_type_c::to_string(symbol_c *symbol) {
  if (NULL == singleton)    singleton = new elementary_type_c;
  if (NULL == singleton)    ERROR;
  const char *res           = (const char *)symbol->accept(*singleton);
  if (NULL == res)          ERROR;
  return res;
}





/* Macro that expand to subtypes */
/* copied from matiec/lib/create_standard_functions_txt.sh */
#define __ANY(DO)                 __ANY_DERIVED(DO) __ANY_ELEMENTARY(DO)
#define __ANY_DERIVED(DO)
#define __ANY_ELEMENTARY(DO)      __ANY_MAGNITUDE(DO) __ANY_BIT(DO) __ANY_STRING(DO) __ANY_DATE(DO)
#define __ANY_MAGNITUDE(DO)       __ANY_NUM(DO) DO(time)
#define __ANY_BIT(DO)             __ANY_NBIT(DO) DO(bool)
#define __ANY_NBIT(DO)            DO(byte) DO(word) DO(dword) DO(lword)
//#define __ANY_STRING(DO)          DO(string) DO(wstring)
#define __ANY_STRING(DO)          DO(string)
#define __ANY_DATE(DO)            DO(date) DO(tod) DO(dt)
#define __ANY_NUM(DO)             __ANY_REAL(DO) __ANY_INT(DO)
#define __ANY_REAL(DO)            DO(real) DO(lreal)
#define __ANY_INT(DO)             __ANY_SINT(DO) __ANY_UINT(DO)
#define __ANY_SINT(DO)            DO(sint) DO(int) DO(dint) DO(lint)
#define __ANY_UINT(DO)            DO(usint) DO(uint) DO(udint) DO(ulint)

#define __ANY_1(DO,P1)            __ANY_DERIVED_1(DO,P1) __ANY_ELEMENTARY_1(DO,P1)
#define __ANY_DERIVED_1(DO,P1)
#define __ANY_ELEMENTARY_1(DO,P1) __ANY_MAGNITUDE_1(DO,P1) __ANY_BIT_1(DO,P1) __ANY_STRING_1(DO,P1) __ANY_DATE_1(DO,P1)
#define __ANY_MAGNITUDE_1(DO,P1)  __ANY_NUM_1(DO,P1) DO(time,P1)
#define __ANY_BIT_1(DO,P1)        __ANY_NBIT_1(DO,P1) DO(bool,P1)
#define __ANY_NBIT_1(DO,P1)       DO(byte,P1) DO(word,P1) DO(dword,P1) DO(lword,P1)
// #define __ANY_STRING_1(DO,P1)     DO(string,P1) DO(wstring,P1)
#define __ANY_STRING_1(DO,P1)     DO(string,P1)
#define __ANY_DATE_1(DO,P1)       DO(date,P1) DO(tod,P1) DO(dt,P1)
#define __ANY_NUM_1(DO,P1)        __ANY_REAL_1(DO,P1) __ANY_INT_1(DO,P1)
#define __ANY_REAL_1(DO,P1)       DO(real,P1) DO(lreal,P1)
#define __ANY_INT_1(DO,P1)        __ANY_SINT_1(DO,P1) __ANY_UINT_1(DO,P1)
#define __ANY_SINT_1(DO,P1)       DO(sint,P1) DO(int,P1) DO(dint,P1) DO(lint,P1)
#define __ANY_UINT_1(DO,P1)       DO(usint,P1) DO(uint,P1) DO(udint,P1) DO(ulint,P1)


/**************************************************************/
/**************************************************************/
/**************************************************************/
/*******  TABLE 24: Standard arithmetic functions       *******/
/*******    merged with                                 *******/
/*******  TABLE 30: Functions of time data types        *******/
/**************************************************************/
/**************************************************************/
/**************************************************************/

/* NOTE: IEC 61131-3 v2 declares that using implicit operations ('+', '-', '*', '/') on ANYTIME data types is
 *       valid, but deprecated, suposedly meaning that they will be removed in the following version of the standard.
 *       However, the current draft version of IEC 61131-3 v3 still allows this use, and no longer declares these
 *       implicit operations as deprecated.
 *       Because of this, and although we are implementing v2 of the standard, we will no longer mark these 
 *       operations as deprecated.
 */
  #define ANYTIME_OPER_DEPRECATION_STATUS widen_entry::ok
//#define ANYTIME_OPER_DEPRECATION_STATUS widen_entry::deprecated


const struct widen_entry widen_ADD_table[] = {
#define __add(TYPE)       \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::safe##TYPE##_type_name, widen_entry::ok                 },
    __ANY_NUM(__add)
#undef __add

    /*******************************************/
    /*******************************************/
    /*** Operations with TIME, DT and TOD... ***/
    /*******************************************/
    /*******************************************/ 
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::time_type_name,            &search_constant_type_c::time_type_name,         widen_entry::ok                 },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::time_type_name,            &search_constant_type_c::tod_type_name,          ANYTIME_OPER_DEPRECATION_STATUS },
    /* NOTE: the standard des not explicitly support the following semantics. However, since 'addition' is supposed to be commutative, we add it anyway... */
    /* not currently supported by stage4, so it is best no tto add it for now... */
//  { &search_constant_type_c::time_type_name,          &search_constant_type_c::tod_type_name,             &search_constant_type_c::tod_type_name,          ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::time_type_name,            &search_constant_type_c::dt_type_name,           ANYTIME_OPER_DEPRECATION_STATUS },         
    /* NOTE: the standard des not explicitly support the following semantics. However, since 'addition' is supposed to be commutative, we add it anyway... */
    /* not currently supported by stage4, so it is best no tto add it for now... */
//  { &search_constant_type_c::time_type_name,          &search_constant_type_c::dt_type_name,              &search_constant_type_c::dt_type_name,           ANYTIME_OPER_DEPRECATION_STATUS },         

    /*******************************/
    /* SAFE version on the left... */
    /*******************************/
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::time_type_name,            &search_constant_type_c::time_type_name,         widen_entry::ok                 },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::time_type_name,            &search_constant_type_c::tod_type_name,          ANYTIME_OPER_DEPRECATION_STATUS },
    /* NOTE: the standard des not explicitly support the following semantics. However, since 'addition' is supposed to be commutative, we add it anyway... */
    /* not currently supported by stage4, so it is best no tto add it for now... */
//  { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::tod_type_name,             &search_constant_type_c::tod_type_name,          ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::time_type_name,            &search_constant_type_c::dt_type_name,           ANYTIME_OPER_DEPRECATION_STATUS },         
    /* NOTE: the standard des not explicitly support the following semantics. However, since 'addition' is supposed to be commutative, we add it anyway... */
    /* not currently supported by stage4, so it is best no tto add it for now... */
//  { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::dt_type_name,              &search_constant_type_c::dt_type_name,           ANYTIME_OPER_DEPRECATION_STATUS },         

    /********************************/
    /* SAFE version on the right... */
    /********************************/
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::safetime_type_name,        &search_constant_type_c::time_type_name,         widen_entry::ok         },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::safetime_type_name,        &search_constant_type_c::tod_type_name,          ANYTIME_OPER_DEPRECATION_STATUS },
    /* NOTE: the standard des not explicitly support the following semantics. However, since 'addition' is supposed to be commutative, we add it anyway... */
    /* not currently supported by stage4, so it is best no tto add it for now... */
//  { &search_constant_type_c::time_type_name,          &search_constant_type_c::safetod_type_name,         &search_constant_type_c::tod_type_name,          ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::safetime_type_name,        &search_constant_type_c::dt_type_name,           ANYTIME_OPER_DEPRECATION_STATUS },         
    /* NOTE: the standard des not explicitly support the following semantics. However, since 'addition' is supposed to be commutative, we add it anyway... */
    /* not currently supported by stage4, so it is best no tto add it for now... */
//  { &search_constant_type_c::time_type_name,          &search_constant_type_c::safedt_type_name,          &search_constant_type_c::dt_type_name,           ANYTIME_OPER_DEPRECATION_STATUS },         

    /*************************************/
    /* SAFE version on left and right... */
    /*************************************/
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safetime_type_name,     widen_entry::ok                 },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safetod_type_name,      ANYTIME_OPER_DEPRECATION_STATUS },
    /* NOTE: the standard des not explicitly support the following semantics. However, since 'addition' is supposed to be commutative, we add it anyway... */
    /* not currently supported by stage4, so it is best no tto add it for now... */
//  { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safetod_type_name,         &search_constant_type_c::safetod_type_name,      ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safedt_type_name,       ANYTIME_OPER_DEPRECATION_STATUS },         
    /* NOTE: the standard des not explicitly support the following semantics. However, since 'addition' is supposed to be commutative, we add it anyway... */
    /* not currently supported by stage4, so it is best no tto add it for now... */
//  { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safedt_type_name,          &search_constant_type_c::safedt_type_name,       ANYTIME_OPER_DEPRECATION_STATUS },
   
    { NULL, NULL, NULL, widen_entry::ok },
};







const struct widen_entry widen_SUB_table[] = {
#define __sub(TYPE)       \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::safe##TYPE##_type_name, widen_entry::ok                 },
    __ANY_NUM(__sub)
#undef __sub

    /*******************************************/
    /*******************************************/
    /*** Operations with TIME, DT and TOD... ***/
    /*******************************************/
    /*******************************************/ 
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::time_type_name,            &search_constant_type_c::time_type_name,         widen_entry::ok                 },
    { &search_constant_type_c::date_type_name,          &search_constant_type_c::date_type_name,            &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::time_type_name,            &search_constant_type_c::tod_type_name,          ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::tod_type_name,             &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::time_type_name,            &search_constant_type_c::dt_type_name,           ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::dt_type_name,              &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS },        

    /*******************************/
    /* SAFE version on the left... */
    /*******************************/
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::time_type_name,            &search_constant_type_c::time_type_name,         widen_entry::ok                 },
    { &search_constant_type_c::safedate_type_name,      &search_constant_type_c::date_type_name,            &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::time_type_name,            &search_constant_type_c::tod_type_name,          ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::tod_type_name,             &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::time_type_name,            &search_constant_type_c::dt_type_name,           ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::dt_type_name,              &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS },        

    /********************************/
    /* SAFE version on the right... */
    /********************************/
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::safetime_type_name,        &search_constant_type_c::time_type_name,         widen_entry::ok                 },
    { &search_constant_type_c::date_type_name,          &search_constant_type_c::safedate_type_name,        &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::safetime_type_name,        &search_constant_type_c::tod_type_name,          ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::tod_type_name,           &search_constant_type_c::safetod_type_name,         &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::safetime_type_name,        &search_constant_type_c::dt_type_name,           ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::dt_type_name,            &search_constant_type_c::safedt_type_name,          &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS },        

    /*************************************/
    /* SAFE version on left and right... */
    /*************************************/
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safetime_type_name,     widen_entry::ok                 },
    { &search_constant_type_c::safedate_type_name,      &search_constant_type_c::safedate_type_name,        &search_constant_type_c::safetime_type_name,     ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safetod_type_name,      ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::safetod_type_name,       &search_constant_type_c::safetod_type_name,         &search_constant_type_c::safetime_type_name,     ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safedt_type_name,       ANYTIME_OPER_DEPRECATION_STATUS },
    { &search_constant_type_c::safedt_type_name,        &search_constant_type_c::safedt_type_name,          &search_constant_type_c::safetime_type_name,     ANYTIME_OPER_DEPRECATION_STATUS },        

    { NULL, NULL, NULL, widen_entry::ok },
};







const struct widen_entry widen_MUL_table[] = {
#define __mul(TYPE)       \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::safe##TYPE##_type_name, widen_entry::ok                 },
    __ANY_NUM(__mul)
#undef __mul

    /*******************************************/
    /*******************************************/
    /*** Operations with TIME, DT and TOD... ***/
    /*******************************************/
    /*******************************************/ 
#define __multime(TYPE)       \
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS }, \
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS }, \
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS }, \
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::safetime_type_name,     ANYTIME_OPER_DEPRECATION_STATUS }, \
    /* NOTE: the standard des not explicitly support the following semantics. However, since 'multiplication' is supposed to be commutative, we add it anyway... */                 \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::time_type_name,            &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::time_type_name,            &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS }, \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::safetime_type_name,        &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::safetime_type_name,        &search_constant_type_c::safetime_type_name,     ANYTIME_OPER_DEPRECATION_STATUS },
    __ANY_NUM(__multime)
#undef __multime

    { NULL, NULL, NULL, widen_entry::ok },
};





const struct widen_entry widen_DIV_table[] = {
#define __div(TYPE)       \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::safe##TYPE##_type_name, widen_entry::ok                 },
    __ANY_NUM(__div)
#undef __div

    /*******************************************/
    /*******************************************/
    /*** Operations with TIME, DT and TOD... ***/
    /*******************************************/
    /*******************************************/ 
#define __divtime(TYPE)       \
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS }, \
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS }, \
    { &search_constant_type_c::time_type_name,          &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::time_type_name,         ANYTIME_OPER_DEPRECATION_STATUS }, \
    { &search_constant_type_c::safetime_type_name,      &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::safetime_type_name,     ANYTIME_OPER_DEPRECATION_STATUS },
    __ANY_NUM(__divtime)
#undef __divtime

    { NULL, NULL, NULL, widen_entry::ok },
 };

 


const struct widen_entry widen_MOD_table[] = {
#define __mod(TYPE)       \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::safe##TYPE##_type_name, widen_entry::ok                 },
    __ANY_NUM(__mod)
#undef __mod

    { NULL, NULL, NULL, widen_entry::ok },
};
 
 


const struct widen_entry widen_EXPT_table[] = {
#define __expt(IN2TYPE, IN1TYPE)       \
    { &search_constant_type_c::IN1TYPE##_type_name,        &search_constant_type_c::IN2TYPE##_type_name,          &search_constant_type_c::IN1TYPE##_type_name,       widen_entry::ok        }, \
    { &search_constant_type_c::safe##IN1TYPE##_type_name,  &search_constant_type_c::IN2TYPE##_type_name,          &search_constant_type_c::IN1TYPE##_type_name,       widen_entry::ok        }, \
    { &search_constant_type_c::IN1TYPE##_type_name,        &search_constant_type_c::safe##IN2TYPE##_type_name,    &search_constant_type_c::IN1TYPE##_type_name,       widen_entry::ok        }, \
    { &search_constant_type_c::safe##IN1TYPE##_type_name,  &search_constant_type_c::safe##IN2TYPE##_type_name,    &search_constant_type_c::safe##IN1TYPE##_type_name, widen_entry::ok        },
#define __IN2_anynum_(IN1_TYPENAME)   __ANY_NUM_1(__expt,IN1_TYPENAME)
    __ANY_REAL(__IN2_anynum_)
#undef __expt
#undef __IN2_anynum_
    { NULL, NULL, NULL, widen_entry::ok },
};



/**************************************************************/
/**************************************************************/
/**************************************************************/
/*******                                                *******/
/*******  TABLE 26: Standard bitwise Boolean functions  *******/
/*******                                                *******/
/**************************************************************/
/**************************************************************/
/**************************************************************/
/* table used by AND and ANDN operators, and and_expression */
const struct widen_entry widen_AND_table[] = {
#define __and(TYPE)       \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::safe##TYPE##_type_name, widen_entry::ok                 },
    __ANY_BIT(__and)
#undef __and

    { NULL, NULL, NULL, widen_entry::ok },
};

/* table used by OR and ORN operators, and or_expression */
const struct widen_entry widen_OR_table[] = {
#define __or(TYPE)       \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::safe##TYPE##_type_name, widen_entry::ok                 },
    __ANY_BIT(__or)
#undef __or

    { NULL, NULL, NULL, widen_entry::ok },
};


/* table used by XOR and XORN operators, and xor_expression */
const struct widen_entry widen_XOR_table[] = {
#define __xor(TYPE)       \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::TYPE##_type_name,       widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::safe##TYPE##_type_name, widen_entry::ok                 },
    __ANY_BIT(__xor)
#undef __xor

    { NULL, NULL, NULL, widen_entry::ok },
};

/**************************************************************/
/**************************************************************/
/**************************************************************/
/*******                                                *******/
/*******  TABLE 28: Standard comparison functions       *******/
/*******                                                *******/
/**************************************************************/
/**************************************************************/
/**************************************************************/
/* table used by GT, GE, EQ, LE, LT, and NE  operators, and equivalent ST expressions. */
const struct widen_entry widen_CMP_table[] = {
#define __cmp(TYPE)       \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::bool_type_name,         widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::TYPE##_type_name,          &search_constant_type_c::bool_type_name,         widen_entry::ok                 }, \
    { &search_constant_type_c::TYPE##_type_name,        &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::bool_type_name,         widen_entry::ok                 }, \
    { &search_constant_type_c::safe##TYPE##_type_name,  &search_constant_type_c::safe##TYPE##_type_name,    &search_constant_type_c::safebool_type_name,     widen_entry::ok                 },
    __ANY_ELEMENTARY(__cmp)
#undef __cmp

    { NULL, NULL, NULL, widen_entry::ok },
};


/* Search for a datatype inside a candidate_datatypes list.
 * Returns: position of datatype in the list, or -1 if not found.
 */
int search_in_candidate_datatype_list(symbol_c *datatype, const std::vector <symbol_c *> &candidate_datatypes) {
	if (NULL == datatype) 
		return -1;

	for(unsigned int i = 0; i < candidate_datatypes.size(); i++)
		if (is_type_equal(datatype, candidate_datatypes[i]))
			return i;
	/* Not found ! */
	return -1;
}

/* Remove a datatype inside a candidate_datatypes list.
 * Returns: If successful it returns true, false otherwise.
 */
bool remove_from_candidate_datatype_list(symbol_c *datatype, std::vector <symbol_c *> &candidate_datatypes) {
	int pos = search_in_candidate_datatype_list(datatype, candidate_datatypes);
	if (pos < 0)
		return false;
	
	candidate_datatypes.erase(candidate_datatypes.begin() + pos);
	return true;
}



/* Intersect two candidate_datatype_lists.
 * Remove from list1 (origin, dest.) all elements that are not found in list2 (with).
 * In essence, list1 will contain the result of the intersection of list1 with list2.
 * In other words, modify list1 so it only contains the elelements that are simultaneously in list1 and list2!
 */
void intersect_candidate_datatype_list(symbol_c *list1 /*origin, dest.*/, symbol_c *list2 /*with*/) {
	if ((NULL == list1) || (NULL == list2))
		/* In principle, we should never call it with NULL values. Best to abort the compiler just in case! */
		return;

	for(std::vector<symbol_c *>::iterator i = list1->candidate_datatypes.begin(); i < list1->candidate_datatypes.end(); ) {
		/* Note that we do _not_ increment i in the for() loop!
		 * When we erase an element from position i, a new element will take it's place, that must also be tested! 
		 */
		if (search_in_candidate_datatype_list(*i, list2->candidate_datatypes) < 0)
			/* remove this element! This will change the value of candidate_datatypes.size() */
			list1->candidate_datatypes.erase(i);
		else i++;
	}
}




/* intersect the candidate_datatype lists of all prev_il_intructions, and set the local candidate_datatype list to the result! */
void intersect_prev_candidate_datatype_lists(il_instruction_c *symbol) {
	if (symbol->prev_il_instruction.empty())
		return;
	
	symbol->candidate_datatypes = symbol->prev_il_instruction[0]->candidate_datatypes;
	for (unsigned int i = 1; i < symbol->prev_il_instruction.size(); i++) {
		intersect_candidate_datatype_list(symbol /*origin, dest.*/, symbol->prev_il_instruction[i] /*with*/);
	}  
}




/* A helper function... */
bool is_ANY_ELEMENTARY_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  return is_ANY_MAGNITUDE_type(type_symbol)
      || is_ANY_BIT_type      (type_symbol)
      || is_ANY_STRING_type   (type_symbol)
      || is_ANY_DATE_type     (type_symbol);
}

/* A helper function... */
bool is_ANY_SAFEELEMENTARY_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  return is_ANY_SAFEMAGNITUDE_type(type_symbol)
      || is_ANY_SAFEBIT_type      (type_symbol)
      || is_ANY_SAFESTRING_type   (type_symbol)
      || is_ANY_SAFEDATE_type     (type_symbol);
}

/* A helper function... */
bool is_ANY_ELEMENTARY_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  /* NOTE: doing
   *          return is_ANY_SAFEELEMENTARY_type() || is_ANY_ELEMENTARY_type()
   *       is incorrect, as the literals would never be considered compatible...
   */
  return is_ANY_MAGNITUDE_compatible(type_symbol)
      || is_ANY_BIT_compatible      (type_symbol)
      || is_ANY_STRING_compatible   (type_symbol)
      || is_ANY_DATE_compatible     (type_symbol);
}


/* A helper function... */
bool is_ANY_MAGNITUDE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(time_type_name_c)) {return true;}
  return is_ANY_NUM_type(type_symbol);
}

/* A helper function... */
bool is_ANY_signed_MAGNITUDE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(time_type_name_c)) {return true;}
  return is_ANY_signed_NUM_type(type_symbol);
}

/* A helper function... */
bool is_ANY_SAFEMAGNITUDE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safetime_type_name_c)) {return true;}
  return is_ANY_SAFENUM_type(type_symbol);
}

/* A helper function... */
bool is_ANY_signed_SAFEMAGNITUDE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safetime_type_name_c)) {return true;}
  return is_ANY_signed_SAFENUM_type(type_symbol);
}

/* A helper function... */
bool is_ANY_MAGNITUDE_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_MAGNITUDE_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEMAGNITUDE_type(type_symbol))              {return true;}
  return is_ANY_NUM_compatible(type_symbol);
}

/* A helper function... */
bool is_ANY_signed_MAGNITUDE_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_signed_MAGNITUDE_type    (type_symbol))       {return true;}
  if (is_ANY_signed_SAFEMAGNITUDE_type(type_symbol))       {return true;}
  return is_ANY_signed_NUM_compatible(type_symbol);
}

/* A helper function... */
bool is_ANY_NUM_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_type(type_symbol))                       {return true;}
  if (is_ANY_INT_type(type_symbol))                        {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_signed_NUM_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_type(type_symbol))                       {return true;}
  if (is_ANY_signed_INT_type(type_symbol))                 {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFENUM_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  return is_ANY_SAFEREAL_type(type_symbol)
      || is_ANY_SAFEINT_type (type_symbol);
}

/* A helper function... */
bool is_ANY_signed_SAFENUM_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  return is_ANY_SAFEREAL_type(type_symbol)
      || is_ANY_signed_SAFEINT_type (type_symbol);
}

/* A helper function... */
bool is_ANY_NUM_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_compatible(type_symbol))                       {return true;}
  if (is_ANY_INT_compatible(type_symbol))                        {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_signed_NUM_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_compatible(type_symbol))                       {return true;}
  if (is_ANY_signed_INT_compatible(type_symbol))                 {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_DATE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(date_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(tod_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(dt_type_name_c))   {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFEDATE_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safedate_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safetod_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safedt_type_name_c))   {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_DATE_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_DATE_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEDATE_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_STRING_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(string_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(wstring_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFESTRING_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safestring_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safewstring_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_STRING_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_STRING_type    (type_symbol))              {return true;}
  if (is_ANY_SAFESTRING_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_INT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(sint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(int_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(dint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(lint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(usint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(uint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(udint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(ulint_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_signed_INT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(sint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(int_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(dint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(lint_type_name_c))  {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_signed_SAFEINT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safesint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safeint_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(safedint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safelint_type_name_c))  {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFEINT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safesint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safeint_type_name_c))   {return true;}
  if (typeid(*type_symbol) == typeid(safedint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safelint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safeusint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safeuint_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safeudint_type_name_c)) {return true;}
  if (typeid(*type_symbol) == typeid(safeulint_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_signed_INT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_signed_INT_type    (type_symbol))              {return true;}
  if (is_ANY_signed_SAFEINT_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_INT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_INT_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEINT_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_REAL_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(real_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(lreal_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFEREAL_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safereal_type_name_c))  {return true;}
  if (typeid(*type_symbol) == typeid(safelreal_type_name_c)) {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_REAL_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_REAL_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEREAL_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_BIT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(bool_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(byte_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(word_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(dword_type_name_c))    {return true;}
  if (typeid(*type_symbol) == typeid(lword_type_name_c))    {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_SAFEBIT_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safebool_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(safebyte_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(safeword_type_name_c))     {return true;}
  if (typeid(*type_symbol) == typeid(safedword_type_name_c))    {return true;}
  if (typeid(*type_symbol) == typeid(safelword_type_name_c))    {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_BIT_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_ANY_BIT_type    (type_symbol))              {return true;}
  if (is_ANY_SAFEBIT_type(type_symbol))              {return true;}
  return false;
}

/* A helper function... */
bool is_BOOL_type(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(bool_type_name_c))      {return true;}
  return false;
}

/* A helper function... */
bool is_SAFEBOOL_type(symbol_c *type_symbol){
  if (type_symbol == NULL) {return false;}
  if (typeid(*type_symbol) == typeid(safebool_type_name_c))  {return true;}
  return false;
}

/* A helper function... */
bool is_ANY_BOOL_compatible(symbol_c *type_symbol) {
  if (type_symbol == NULL) {return false;}
  if (is_BOOL_type    (type_symbol))              {return true;}
  if (is_SAFEBOOL_type(type_symbol))              {return true;}
  return false;
}





bool is_type_equal(symbol_c *first_type, symbol_c *second_type) {
  if ((NULL == first_type) || (NULL == second_type))
      return false;
  if (typeid(* first_type) == typeid(invalid_type_name_c))
      return false;
  if (typeid(*second_type) == typeid(invalid_type_name_c))
      return false;
    
  if (is_ANY_ELEMENTARY_type(first_type)) {
      if (typeid(*first_type) == typeid(*second_type))
          return true;
  } else   /* ANY_DERIVED */
      return (first_type == second_type);

  return false;
}



bool is_type_valid(symbol_c *type) {
  if (NULL == type)
      return false;
  if (typeid(*type) == typeid(invalid_type_name_c))
      return false;

  return true;
}
