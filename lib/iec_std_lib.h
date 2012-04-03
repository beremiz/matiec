/*
 * copyright 2008 Edouard TISSERANT
 * copyright 2011 Mario de Sousa (msousa@fe.up.pt)
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

/****
 * IEC 61131-3 standard function library
 */

/* NOTE: This file is full of (what may seem at first) very strange macros.
 *       If you want to know what all these strange macros are doing,
 *       just parse this file through a C preprocessor (e.g. cpp), 
 *       and analyse the output!
 *       $gcc -E iec_std_lib.h 
 */

#include <limits.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef DEBUG_IEC
#define DBG(...) printf(__VA_ARGS__);
#define DBG_TYPE(TYPENAME, name) __print_##TYPENAME(name);
#else
#define DBG(...)
#define DBG_TYPE(TYPENAME, name)
#endif

/*
 * Include type defs.
 */
#include "iec_types_all.h"

extern TIME __CURRENT_TIME;
extern BOOL __DEBUG;

/* TODO
typedef struct {
    __strlen_t len;
    u_int16_t body[STR_MAX_LEN];
} WSTRING;
*/
/*
# if __WORDSIZE == 64
#define __32b_sufix
#define __64b_sufix L
#else
#define __32b_sufix L
#define __64b_sufix LL
#endif
*/

# if __WORDSIZE == 64
#define __32b_sufix
#define __64b_sufix L
#else
#define __32b_sufix L
/* changed this from LL to L temporarily. It was causing a bug when compiling resulting code with gcc.
 * I have other things to worry about at the moment.. 
 */
#define __64b_sufix L   
#endif


#define __lit(type,value,sfx) (type)value##sfx
// Keep this macro expention step to let sfx change into L or LL
#define __literal(type,value,sfx) __lit(type,value,sfx)

#define __BOOL_LITERAL(value) __literal(BOOL,value,)
#define __SINT_LITERAL(value) __literal(SINT,value,)
#define __INT_LITERAL(value) __literal(INT,value,)
#define __DINT_LITERAL(value) __literal(DINT,value,__32b_sufix)
#define __LINT_LITERAL(value) __literal(LINT,value,__64b_sufix)
#define __USINT_LITERAL(value) __literal(USINT,value,)
#define __UINT_LITERAL(value) __literal(UINT,value,)
#define __UDINT_LITERAL(value) __literal(UDINT,value,__32b_sufix)
#define __ULINT_LITERAL(value) __literal(ULINT,value,__64b_sufix)
#define __REAL_LITERAL(value) __literal(REAL,value,__32b_sufix)
#define __LREAL_LITERAL(value) __literal(LREAL,value,__64b_sufix)
#define __TIME_LITERAL(value) __literal(TIME,value,)
#define __DATE_LITERAL(value) __literal(DATE,value,)
#define __TOD_LITERAL(value) __literal(TOD,value,)
#define __DT_LITERAL(value) __literal(DT,value,)
#define __STRING_LITERAL(count,value) (STRING){count,value}
#define __BYTE_LITERAL(value) __literal(BYTE,value,)
#define __WORD_LITERAL(value) __literal(WORD,value,)
#define __DWORD_LITERAL(value) __literal(DWORD,value,__32b_sufix)
#define __LWORD_LITERAL(value) __literal(LWORD,value,__64b_sufix)



#define __INIT_REAL 0
#define __INIT_LREAL 0
#define __INIT_SINT 0
#define __INIT_INT 0
#define __INIT_DINT 0
#define __INIT_LINT 0
#define __INIT_USINT 0
#define __INIT_UINT 0
#define __INIT_UDINT 0
#define __INIT_ULINT 0
#define __INIT_TIME (TIME){0,0}
#define __INIT_BOOL 0
#define __INIT_BYTE 0
#define __INIT_WORD 0
#define __INIT_DWORD 0
#define __INIT_LWORD 0
#define __INIT_STRING (STRING){0,""}
//#define __INIT_WSTRING
#define __INIT_DATE (DATE){0,0}
#define __INIT_TOD (TOD){0,0}
#define __INIT_DT (DT){0,0}

typedef union __IL_DEFVAR_T {
    BOOL    BOOLvar;

    SINT    SINTvar;
    INT     INTvar;
    DINT    DINTvar;
    LINT    LINTvar;

    USINT   USINTvar;
    UINT    UINTvar;
    UDINT   UDINTvar;
    ULINT   ULINTvar;

    BYTE    BYTEvar;
    WORD    WORDvar;
    DWORD   DWORDvar;
    LWORD   LWORDvar;

    REAL    REALvar;
    LREAL   LREALvar;

    TIME    TIMEvar;
    TOD TODvar;
    DT  DTvar;
    DATE    DATEvar;
} __IL_DEFVAR_T;


/**********************************************************************/
/**********************************************************************/
/*****                                                            *****/
/*****      Some helper functions...                              *****/
/*****                     ...used later:                         *****/
/*****    - when declaring the IEC 61131-3 standard functions     *****/
/*****    - in the C source code itself in SFC and ST expressions *****/
/*****                                                            *****/
/**********************************************************************/
/**********************************************************************/


/****************************/
/* Notify IEC runtime error */
/****************************/

/* function that generates an IEC runtime error */
static inline void __iec_error(void) {
  /* TODO... */
  fprintf(stderr, "IEC 61131-3 runtime error.\n");
  /*exit(1);*/
}

/*******************************/
/* Time normalization function */
/*******************************/

static inline void __normalize_timespec (IEC_TIMESPEC *ts) {
  if( ts->tv_nsec < -1000000000 || (( ts->tv_sec > 0 ) && ( ts->tv_nsec < 0 ))){
    ts->tv_sec--;
    ts->tv_nsec += 1000000000;
  }
  if( ts->tv_nsec > 1000000000 || (( ts->tv_sec < 0 ) && ( ts->tv_nsec > 0 ))){
    ts->tv_sec++;
    ts->tv_nsec -= 1000000000;
  }
}

/**********************************************/
/* Time conversion to/from timespec functions */
/**********************************************/

static inline IEC_TIMESPEC __time_to_timespec(int sign, double mseconds, double seconds, double minutes, double hours, double days) {
  IEC_TIMESPEC ts;

  /* sign is 1 for positive values, -1 for negative time... */
  long double total_sec = ((days*24 + hours)*60 + minutes)*60 + seconds + mseconds/1e3;
  if (sign >= 0) sign = 1; else sign = -1;
  ts.tv_sec = sign * (long int)total_sec;
  ts.tv_nsec = sign * (long int)((total_sec - ts.tv_sec)*1e9);

  return ts;
}


static inline IEC_TIMESPEC __tod_to_timespec(double seconds, double minutes, double hours) {
  IEC_TIMESPEC ts;

  long double total_sec = (hours*60 + minutes)*60 + seconds;
  ts.tv_sec = (long int)total_sec;
  ts.tv_nsec = (long int)((total_sec - ts.tv_sec)*1e9);

  return ts;
}

static inline IEC_TIMESPEC __date_to_timespec(int day, int month, int year) {
  IEC_TIMESPEC ts;
  struct tm broken_down_time;
  time_t epoch_seconds;

  broken_down_time.tm_sec = 0;
  broken_down_time.tm_min = 0;
  broken_down_time.tm_hour = 0;
  broken_down_time.tm_mday = day;  /* day of month, from 1 to 31 */
  broken_down_time.tm_mon = month - 1;   /* month since January, in the range 0 to 11 */
  broken_down_time.tm_year = year - 1900;  /* number of years since 1900 */

  epoch_seconds = mktime(&broken_down_time); /* determine number of seconds since the epoch, i.e. Jan 1st 1970 */

  if ((time_t)(-1) == epoch_seconds)
    __iec_error();

  ts.tv_sec = epoch_seconds;
  ts.tv_nsec = 0;

  return ts;
}

static inline IEC_TIMESPEC __dt_to_timespec(double seconds,  double minutes, double hours, int day, int month, int year) {
  IEC_TIMESPEC ts;
  struct tm broken_down_time;
  time_t epoch_seconds;

  long double total_sec = (hours*60 + minutes)*60 + seconds;
  ts.tv_sec = (long int)total_sec;
  ts.tv_nsec = (long int)((total_sec - ts.tv_sec)*1e9);

  broken_down_time.tm_sec = 0;
  broken_down_time.tm_min = 0;
  broken_down_time.tm_hour = 0;
  broken_down_time.tm_mday = day;  /* day of month, from 1 to 31 */
  broken_down_time.tm_mon = month - 1;   /* month since January, in the range 0 to 11 */
  broken_down_time.tm_year = year - 1900;  /* number of years since 1900 */

  epoch_seconds = mktime(&broken_down_time); /* determine number of seconds since the epoch, i.e. Jan 1st 1970 */
  if ((time_t)(-1) == epoch_seconds)
    __iec_error();

  ts.tv_sec += epoch_seconds;
  if (ts.tv_sec < epoch_seconds)
    /* since the TOD is always positive, if the above happens then we had an overflow */
    __iec_error();

  return ts;
}

/*******************/
/* Time operations */
/*******************/

#define __time_cmp(t1, t2) (t2.tv_sec == t1.tv_sec ? t1.tv_nsec - t2.tv_nsec : t1.tv_sec - t2.tv_sec)

static inline TIME __time_add(TIME IN1, TIME IN2){
  TIME res ={IN1.tv_sec + IN2.tv_sec,
             IN1.tv_nsec + IN2.tv_nsec };
  __normalize_timespec(&res);
  return res;
}
static inline TIME __time_sub(TIME IN1, TIME IN2){
  TIME res ={IN1.tv_sec - IN2.tv_sec,
             IN1.tv_nsec - IN2.tv_nsec };
  __normalize_timespec(&res);
  return res;
}
static inline TIME __time_mul(TIME IN1, LREAL IN2){
  LREAL s_f = IN1.tv_sec * IN2;
  time_t s = s_f;
  div_t ns = div((LREAL)IN1.tv_nsec * IN2, 1000000000);
  TIME res = {s + ns.quot,
              ns.rem + (s_f - s) * 1000000000 };
  __normalize_timespec(&res);
  return res;
}
static inline TIME __time_div(TIME IN1, LREAL IN2){
  LREAL s_f = IN1.tv_sec / IN2;
  time_t s = s_f;
  TIME res = {s,
              IN1.tv_nsec / IN2 + (s_f - s) * 1000000000 };
  __normalize_timespec(&res);
  return res;
}


/***************/
/* Convertions */
/***************/
    /*****************/
    /*  REAL_TO_INT  */
    /*****************/
static inline LINT __real_round(LREAL IN) {
	return fmod(IN, 1) == 0 ? ((LINT)IN / 2) * 2 : (LINT)IN;
}
static inline LINT __preal_to_sint(LREAL IN) {
   return IN >= 0 ? __real_round(IN + 0.5) : __real_round(IN - 0.5);
}
static inline LINT __preal_to_uint(LREAL IN) {
   return IN >= 0 ? __real_round(IN + 0.5) : 0;
}
static inline LINT __real_to_sint(LREAL IN)  {return (LINT)__preal_to_sint(IN);}
static inline LWORD __real_to_bit(LREAL IN)  {return (LWORD)__preal_to_uint(IN);}
static inline ULINT __real_to_uint(LREAL IN) {return (ULINT)__preal_to_uint(IN);}

    /***************/
    /*  TO_STRING  */
    /***************/
static inline STRING __bool_to_string(BOOL IN) {
    if(IN) return (STRING){4, "TRUE"};
    return (STRING){5,"FALSE"};
}
static inline STRING __bit_to_string(LWORD IN) {
    STRING res;
    res = __INIT_STRING;
    res.len = snprintf((char*)res.body, STR_MAX_LEN, "16#%llx",(long long unsigned int)IN);
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
static inline STRING __real_to_string(LREAL IN) {
    STRING res;
    res = __INIT_STRING;
    res.len = snprintf((char*)res.body, STR_MAX_LEN, "%.10g", IN);
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
static inline STRING __sint_to_string(LINT IN) {
    STRING res;
    res = __INIT_STRING;
    res.len = snprintf((char*)res.body, STR_MAX_LEN, "%lld", (long long int)IN);
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
static inline STRING __uint_to_string(ULINT IN) {
    STRING res;
    res = __INIT_STRING;
    res.len = snprintf((char*)res.body, STR_MAX_LEN, "%llu", (long long unsigned int)IN);
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
    /***************/
    /* FROM_STRING */
    /***************/
static inline BOOL __string_to_bool(STRING IN) {
    return IN.len == 5 ? !memcmp(&IN.body,"TRUE", IN.len) : 0;
}

static inline LINT __pstring_to_sint(STRING* IN) {
    LINT res = 0;
    __strlen_t l;
    unsigned int shift = 0;

    if(IN->body[0]=='2' && IN->body[1]=='#'){
        /* 2#0101_1010_1011_1111 */
        for(l = IN->len - 1; l >= 2 && shift < 64; l--)
        {
            char c = IN->body[l];
            if( c >= '0' && c <= '1'){
                res |= ( c - '0') << shift;
                shift += 1;
            }
        }
    }else if(IN->body[0]=='8' && IN->body[1]=='#'){
        /* 8#1234_5665_4321 */
        for(l = IN->len - 1; l >= 2 && shift < 64; l--)
        {
            char c = IN->body[l];
            if( c >= '0' && c <= '7'){
                res |= ( c - '0') << shift;
                shift += 3;
            }
        }
    }else if(IN->body[0]=='1' && IN->body[1]=='6' && IN->body[2]=='#'){
        /* 16#1234_5678_9abc_DEFG */
        for(l = IN->len - 1; l >= 3 && shift < 64; l--)
        {
            char c = IN->body[l];
            if( c >= '0' && c <= '9'){
                res |= (LWORD)( c - '0') << shift;
                shift += 4;
            }else if( c >= 'a' && c <= 'f'){
                res |= (LWORD)( c - 'a' + 10 ) << shift;
                shift += 4;
            }else if( c >= 'A' && c <= 'F'){
                res |= (LWORD)( c - 'A' + 10 ) << shift;
                shift += 4;
            }
        }
    }else{
        /* -123456789 */
        LINT fac = IN->body[0] == '-' ? -1 : 1;
        for(l = IN->len - 1; l >= 0 && shift < 20; l--)
        {
            char c = IN->body[l];
            if( c >= '0' && c <= '9'){
                res += ( c - '0') * fac;
                fac *= 10;
                shift += 1;
            }else if( c >= '.' ){ /* reset value */
                res = 0;
                fac = IN->body[0] == '-' ? -1 : 1;
                shift = 0;
            }
        }
    }
    return res;
}

static inline LINT  __string_to_sint(STRING IN) {return (LINT)__pstring_to_sint(&IN);}
static inline LWORD __string_to_bit (STRING IN) {return (LWORD)__pstring_to_sint(&IN);}
static inline ULINT __string_to_uint(STRING IN) {return (ULINT)__pstring_to_sint(&IN);}
static inline LREAL __string_to_real(STRING IN) {
    __strlen_t l;
    l = IN.len;
    /* search the dot */
    while(--l > 0 && IN.body[l] != '.');
    if(l != 0){
        return atof((const char *)&IN.body);
    }else{
        return (LREAL)__pstring_to_sint(&IN);
    }
}

    /***************/
    /*   TO_TIME   */
    /***************/
static inline TIME    __int_to_time(LINT IN)  {return (TIME){IN, 0};}
static inline TIME   __real_to_time(LREAL IN) {return (TIME){IN, (IN - (LINT)IN) * 1000000000};}
static inline TIME __string_to_time(STRING IN){
    __strlen_t l;
    /* TODO :
     *
     *  Duration literals without underlines: T#14ms    T#-14ms   T#14.7s   T#14.7m
     *                short prefix            T#14.7h    t#14.7d   t#25h15m
     *                                        t#5d14h12m18s3.5ms
     *                long prefix             TIME#14ms    TIME#-14ms   time#14.7s
     *  Duration literals with underlines:
     *                short prefix            t#25h_15m t#5d_14h_12m_18s_3.5ms
     *                long prefix             TIME#25h_15m
     *                                        time#5d_14h_12m_18s_3.5ms
     *
     *  Long prefix notation                 Short prefix notation
     *  DATE#1984-06-25                      D#1984-06-25
     *  date#1984-06-25                      d#1984-06-25
     *  TIME_OF_DAY#15:36:55.36              TOD#15:36:55.36
     *  time_of_day#15:36:55.36              tod#15:36:55.36
     *  DATE_AND_TIME#1984-06-25-15:36:55.36 DT#1984-06-25-15:36:55.36
     *  date_and_time#1984-06-25-15:36:55.36 dt#1984-06-25-15:36:55.36
     *
     */
    /* Quick hack : only transform seconds */
    /* search the dot */
    l = IN.len;
    while(--l > 0 && IN.body[l] != '.');
    if(l != 0){
        LREAL IN_val = atof((const char *)&IN.body);
        return  (TIME){IN_val, (IN_val - (LINT)IN_val)*1000000000};
    }else{
        return  (TIME){__pstring_to_sint(&IN), 0};
    }
}

    /***************/
    /*  FROM_TIME  */
    /***************/
static inline LREAL __time_to_real(TIME IN){
    return (LREAL)IN.tv_sec + ((LREAL)IN.tv_nsec/1000000000);
}
static inline LINT __time_to_int(TIME IN) {return IN.tv_sec;}
static inline STRING __time_to_string(TIME IN){
    STRING res;
    div_t days;
    /*t#5d14h12m18s3.5ms*/
    res = __INIT_STRING;
    days = div(IN.tv_sec ,86400);
    if(!days.rem && IN.tv_nsec == 0){
        res.len = snprintf((char*)&res.body, STR_MAX_LEN, "T#%dd", days.quot);
    }else{
        div_t hours = div(days.rem, 3600);
        if(!hours.rem && IN.tv_nsec == 0){
            res.len = snprintf((char*)&res.body, STR_MAX_LEN, "T#%dd%dh", days.quot, hours.quot);
        }else{
            div_t minuts = div(hours.rem, 60);
            if(!minuts.rem && IN.tv_nsec == 0){
                res.len = snprintf((char*)&res.body, STR_MAX_LEN, "T#%dd%dh%dm", days.quot, hours.quot, minuts.quot);
            }else{
                if(IN.tv_nsec == 0){
                    res.len = snprintf((char*)&res.body, STR_MAX_LEN, "T#%dd%dh%dm%ds", days.quot, hours.quot, minuts.quot, minuts.rem);
                }else{
                    res.len = snprintf((char*)&res.body, STR_MAX_LEN, "T#%dd%dh%dm%ds%gms", days.quot, hours.quot, minuts.quot, minuts.rem, (LREAL)IN.tv_nsec / 1000000);
                }
            }
        }
    }
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
static inline STRING __date_to_string(DATE IN){
    STRING res;
    struct tm* broken_down_time;
    time_t seconds;
    /* D#1984-06-25 */
    res = __INIT_STRING;
    seconds = IN.tv_sec;
    if (NULL == (broken_down_time = localtime(&seconds))){ /* get the UTC (GMT) broken down time */
        __iec_error();
        return (STRING){7,"D#ERROR"};
    }
    res.len = snprintf((char*)&res.body, STR_MAX_LEN, "D#%d-%2.2d-%2.2d", broken_down_time->tm_year + 1900, broken_down_time->tm_mon + 1, broken_down_time->tm_mday);
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
static inline STRING __tod_to_string(TOD IN){
    STRING res;
    struct tm* broken_down_time;
    time_t seconds;
    /* TOD#15:36:55.36 */
    res = __INIT_STRING;
    seconds = IN.tv_sec;
    if (NULL == (broken_down_time = localtime(&seconds))){ /* get the UTC (GMT) broken down time */
        __iec_error();
        return (STRING){9,"TOD#ERROR"};
    }
    if(IN.tv_nsec == 0){
        res.len = snprintf((char*)&res.body, STR_MAX_LEN, "TOD#%2.2d:%2.2d:%d", broken_down_time->tm_hour, broken_down_time->tm_min, broken_down_time->tm_sec);
    }else{
        res.len = snprintf((char*)&res.body, STR_MAX_LEN, "TOD#%2.2d:%2.2d:%g", broken_down_time->tm_hour, broken_down_time->tm_min, (LREAL)broken_down_time->tm_sec + (LREAL)IN.tv_nsec / 1e9);
    }
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
static inline STRING __dt_to_string(DT IN){
    STRING res;
    struct tm* broken_down_time;
    time_t seconds;
    /* DT#1984-06-25-15:36:55.36 */
    seconds = IN.tv_sec;
    if (NULL == (broken_down_time = localtime(&seconds))){ /* get the UTC (GMT) broken down time */
        __iec_error();
        return (STRING){8,"DT#ERROR"};
    }
    if(IN.tv_nsec == 0){
        res.len = snprintf((char*)&res.body, STR_MAX_LEN, "DT#%d-%2.2d-%2.2d-%2.2d:%2.2d:%d",
                 broken_down_time->tm_year,
                 broken_down_time->tm_mon,
                 broken_down_time->tm_mday,
                 broken_down_time->tm_hour,
                 broken_down_time->tm_min,
                 broken_down_time->tm_sec);
    }else{
        res.len = snprintf((char*)&res.body, STR_MAX_LEN, "DT#%d-%2.2d-%2.2d-%2.2d:%2.2d:%g",
                 broken_down_time->tm_year,
                 broken_down_time->tm_mon,
                 broken_down_time->tm_mday,
                 broken_down_time->tm_hour,
                 broken_down_time->tm_min,
                 (LREAL)broken_down_time->tm_sec + ((LREAL)IN.tv_nsec / 1e9));
    }
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}

    /**********************************************/
    /*  [ANY_DATE | TIME] _TO_ [ANY_DATE | TIME]  */
    /**********************************************/

static inline TOD __date_and_time_to_time_of_day(DT IN) {return (TOD){IN.tv_sec % 86400, IN.tv_nsec};}
static inline DATE __date_and_time_to_date(DT IN){return (DATE){IN.tv_sec - (IN.tv_sec % (24*60*60)), 0};}

    /*****************/
    /*  FROM/TO BCD  */
    /*****************/
#define __bcd_digit(fac)
static inline ULINT __bcd_to_uint(LWORD IN){
    ULINT res;
    ULINT i;

    res = IN & 0xf;
    for(i = 10ULL; i <= 1000000000000000ULL; i *= 10){
        if(!(IN >>= 4))
            break;
        res += (IN & 0xf) * i;
    }
    return res;
}

static inline LWORD __uint_to_bcd(ULINT IN){
    LWORD res;
    USINT i;

    res = IN % 10;
    for(i = 4; i<=60; i += 4){
        if(!(IN /= 10))
            break;
        res |= (IN % 10) << i;
    }
    return res;
}


    /************/
    /*  MOVE_*  */
    /************/

/* some helpful __move_[ANY] functions, used in the *_TO_** and MOVE  standard functions */
/* e.g. __move_BOOL, __move_BYTE, __move_REAL, __move_TIME, ... */
#define __move_(TYPENAME)\
static inline TYPENAME __move_##TYPENAME(TYPENAME op1) {return op1;}
__ANY(__move_)



/*****************************************************************/
/*****************************************************************/
/*****                                                       *****/
/*****                 IEC 61131-3                           *****/
/*****      S T A N D A R D     F U N C T I O N S            *****/
/*****                                                       *****/
/*****************************************************************/
/*****************************************************************/

/* NOTE: If you want to know what all these strange macros are doing,
 *       just parse this file through a C preprocessor, and analyse the output!
 *       $gcc -E iec_std_lib.h 
 */

/* NOTE: We only define and declare the explicitly typed standard functions
 *       (e.g., SIN_REAL, SIN_LREAL, ..., ADD_SINT, ADD_INT, ADD_LINT, ...)
 *       We do not declare/define the overloaded functions
 *       (SIN, ADD, ...). 
 *       When handling a call to an overloaded function, the iec2c compiler 
 *       will determine in stage3 the data type of the parameter being passed, 
 *       and in stage4 generate the C code to call the correct
 *       typed standard function.
 */

/* NOTE on explicit typing of:
 *           - Table 25 - Standard bit shift functions
 *           - Table 29 - Character string Functions
 *
 *  In section 2.5.1.4 (Typing, overloading, and type conversion) of the IEC 61131-3 (version 2)
 *  of the standard, it is stated:
 * "A standard function, [...] is said to be overloaded when it
 * can operate on input data elements of various types within a generic type designator as defined in
 * 2.3.2. For instance, an overloaded addition function on generic type ANY_NUM can operate on data
 * of types LREAL, REAL, DINT, INT, and SINT."
 * [...]
 * "When a function which normally represents an overloaded operator is to be typed, i.e., the types
 * of its inputs and outputs restricted to a particular elementary or derived data type as defined in
 * 2.3, this shall be done by appending an "underline" character followed by the required type, as
 * shown in table 21."
 *
 * However, this explanation (as well as the example in table 21) only refers to functions where the same
 * generic data type is used for the single input and the output parameter.
 * How can we create explicitly types functions when this is not the case?
 * It does not seem to be covered by the standard.
 *
 * For this reason, we do not define the LEN_SINT, LEN_INT, LEN_STRING, LEN_[ANY_INT], LEN_[ANY_STRING] functions...
 */
 

/********************/
/*   EN/ENO PARAMS  */
/********************/

#define EN_ENO_PARAMS BOOL EN, BOOL *ENO
#define EN_ENO EN, ENO

#define TEST_EN(TYPENAME)\
  if (!EN) {\
    if (ENO != NULL)\
      *ENO = __BOOL_LITERAL(FALSE);\
    return __INIT_##TYPENAME;\
  }\
  else if (ENO != NULL)\
    *ENO = __BOOL_LITERAL(TRUE);

#define TEST_EN_COND(TYPENAME, COND)\
  if (!EN || (COND)) {\
    if (ENO != NULL)\
      *ENO = __BOOL_LITERAL(FALSE);\
    return __INIT_##TYPENAME;\
  }\
  else if (ENO != NULL)\
    *ENO = __BOOL_LITERAL(TRUE);

  
  
/*****************************************/  
/*****************************************/  
/*  2.5.1.5.1 Type Conversion Functions  */
/*****************************************/  
/*****************************************/  

#define __convert_type(from_TYPENAME,to_TYPENAME, oper) \
static inline to_TYPENAME from_TYPENAME##_TO_##to_TYPENAME(EN_ENO_PARAMS, from_TYPENAME op){\
  TEST_EN(to_TYPENAME)\
  return (to_TYPENAME)oper(op);\
}

/******** [ANY_NUM | ANY_NBIT]_TO_BOOL   ************/
#define __convert_num_to_bool(TYPENAME) \
static inline BOOL TYPENAME##_TO_BOOL(EN_ENO_PARAMS, TYPENAME op){\
  TEST_EN(BOOL)\
  return op == 0 ? 0 : 1;\
}
__ANY_NUM(__convert_num_to_bool)
__ANY_NBIT(__convert_num_to_bool)

/******** [TIME | ANY_DATE]_TO_BOOL   ************/
#define __convert_time_to_bool(TYPENAME) \
static inline BOOL TYPENAME##_TO_BOOL(EN_ENO_PARAMS, TYPENAME op){\
  TEST_EN(BOOL)\
  return op.tv_sec == 0 && op.tv_nsec == 0 ? 0 : 1;\
}
__convert_time_to_bool(TIME)
__ANY_DATE(__convert_time_to_bool)

#define __to_anynum_(from_TYPENAME)   __ANY_NUM_1(__iec_,from_TYPENAME)
#define __to_anyint_(from_TYPENAME)   __ANY_INT_1(__iec_,from_TYPENAME)
#define __to_anybit_(from_TYPENAME)   __ANY_BIT_1(__iec_,from_TYPENAME)
#define __to_anynbit_(from_TYPENAME) __ANY_NBIT_1(__iec_,from_TYPENAME)
#define __to_anysint_(from_TYPENAME) __ANY_SINT_1(__iec_,from_TYPENAME)
#define __to_anyuint_(from_TYPENAME) __ANY_UINT_1(__iec_,from_TYPENAME)
#define __to_anyreal_(from_TYPENAME) __ANY_REAL_1(__iec_,from_TYPENAME)
#define __to_anydate_(from_TYPENAME) __ANY_DATE_1(__iec_,from_TYPENAME)

/******** [ANY_BIT]_TO_[ANY_NUM | ANT_NBIT]   ************/
#define __iec_(to_TYPENAME,from_TYPENAME) __convert_type(from_TYPENAME, to_TYPENAME, __move_##to_TYPENAME)
__ANY_BIT(__to_anynum_)
__ANY_BIT(__to_anynbit_)
#undef __iec_

/******** [ANY_INT]_TO_[ANY_NUM | ANT_NBIT]   ************/
#define __iec_(to_TYPENAME,from_TYPENAME) __convert_type(from_TYPENAME, to_TYPENAME, __move_##to_TYPENAME)
__ANY_INT(__to_anynum_)
__ANY_INT(__to_anynbit_)
#undef __iec_

/******** [ANY_REAL]_TO_[ANY_NBIT]   ************/
#define __iec_(to_TYPENAME,from_TYPENAME) __convert_type(from_TYPENAME, to_TYPENAME, __real_to_bit)
__ANY_REAL(__to_anynbit_)
#undef __iec_

/******** [ANY_REAL]_TO_[ANY_NINT]   ************/
#define __iec_(to_TYPENAME,from_TYPENAME) __convert_type(from_TYPENAME, to_TYPENAME, __real_to_sint)
__ANY_REAL(__to_anysint_)
#undef __iec_
#define __iec_(to_TYPENAME,from_TYPENAME) __convert_type(from_TYPENAME, to_TYPENAME, __real_to_uint)
__ANY_REAL(__to_anyuint_)
#undef __iec_

/******** [ANY_REAL]_TO_[ANY_REAL]   ************/ 
#define __iec_(to_TYPENAME,from_TYPENAME) __convert_type(from_TYPENAME, to_TYPENAME, __move_##to_TYPENAME)
__ANY_REAL(__to_anyreal_)
#undef __iec_

/******** [ANY_BIT | ANY_INT]_TO_[TIME | ANY_DATE]   ************/ 
#define __iec_(from_TYPENAME) __convert_type(from_TYPENAME, TIME, __int_to_time)
__ANY_BIT(__iec_)
__ANY_INT(__iec_)
#undef __iec_
#define __iec_(to_TYPENAME,from_TYPENAME) __convert_type(from_TYPENAME, to_TYPENAME, __int_to_time)
__ANY_BIT(__to_anydate_)
__ANY_INT(__to_anydate_)
#undef __iec_

/******** [ANY_REAL]_TO_[TIME | ANY_DATE]   ************/ 
#define __iec_(from_TYPENAME) __convert_type(from_TYPENAME, TIME, __real_to_time)
__ANY_REAL(__iec_)
#undef __iec_
#define __iec_(to_TYPENAME,from_TYPENAME) __convert_type(from_TYPENAME, to_TYPENAME, __real_to_time)
__ANY_REAL(__to_anydate_)
#undef __iec_

/******** [TIME | ANY_DATE]_TO_[ANY_BIT | ANY_INT]   ************/ 
#define __iec_(to_TYPENAME,from_TYPENAME) __convert_type(from_TYPENAME, to_TYPENAME, __time_to_int)
__to_anyint_(TIME)
__to_anynbit_(TIME)
__ANY_DATE(__to_anyint_)
__ANY_DATE(__to_anynbit_)
#undef __iec_

/******** [TIME | ANY_DATE]_TO_[ANY_REAL]   ************/ 
#define __iec_(to_TYPENAME,from_TYPENAME) __convert_type(from_TYPENAME, to_TYPENAME, __time_to_real)
__to_anyreal_(TIME)
__ANY_DATE(__to_anyreal_)
#undef __iec_


/******** [ANY_DATE]_TO_[ANY_DATE | TIME]   ************/ 
/* Not supported: DT_TO_TIME */
__convert_type(DT, DATE,  __date_and_time_to_date)
__convert_type(DT, DT,    __move_DT)
__convert_type(DT, TOD,   __date_and_time_to_time_of_day)
/* Not supported: DATE_TO_TIME */
__convert_type(DATE, DATE, __move_DATE)
/* Not supported: DATE_TO_DT */
/* Not supported: DATE_TO_TOD */
/* Not supported: TOD_TO_TIME */
/* Not supported: TOD_TO_DATE */
/* Not supported: TOD_TO_DT */
__convert_type(TOD, TOD, __move_TOD)


/******** TIME_TO_[ANY_DATE]   ************/ 
/* Not supported: TIME_TO_DATE */
/* Not supported: TIME_TO_DT */
/* Not supported: TIME_TO_TOD */

/******** TIME_TO_TIME   ************/ 
__convert_type(TIME, TIME, __move_TIME)


/******** [ANY_BIT]_TO_STRING   ************/ 
__convert_type(BOOL, STRING, __bool_to_string)
#define __iec_(from_TYPENAME) __convert_type(from_TYPENAME, STRING, __bit_to_string)
__ANY_NBIT(__iec_)
#undef __iec_

/******** [ANY_INT]_TO_STRING   ************/ 
#define __iec_(from_TYPENAME) __convert_type(from_TYPENAME, STRING, __sint_to_string)
__ANY_SINT(__iec_)
#undef __iec_
#define __iec_(from_TYPENAME) __convert_type(from_TYPENAME, STRING, __uint_to_string)
__ANY_UINT(__iec_)
#undef __iec_

/******** [ANY_REAL]_TO_STRING   ************/ 
#define __iec_(from_TYPENAME) __convert_type(from_TYPENAME, STRING, __real_to_string)
__ANY_REAL(__iec_)
#undef __iec_

/******** [ANY_DATE]_TO_STRING   ************/ 
__convert_type(DATE, STRING, __date_to_string)
__convert_type(DT,   STRING, __dt_to_string)
__convert_type(TOD,  STRING, __tod_to_string)

/******** TIME_TO_STRING   ************/ 
__convert_type(TIME, STRING, __time_to_string)


/******** STRING_TO_[ANY_BIT]   ************/ 
__convert_type(STRING, BOOL, __string_to_bool)
#define __iec_(to_TYPENAME) __convert_type(STRING, to_TYPENAME, __string_to_bit)
__ANY_NBIT(__iec_)
#undef __iec_

/******** STRING_TO_[ANY_INT]   ************/ 
#define __iec_(to_TYPENAME) __convert_type(STRING, to_TYPENAME, __string_to_sint)
__ANY_SINT(__iec_)
#undef __iec_
#define __iec_(to_TYPENAME) __convert_type(STRING, to_TYPENAME, __string_to_uint)
__ANY_UINT(__iec_)
#undef __iec_

/******** STRING_TO_[ANY_REAL]   ************/ 
#define __iec_(to_TYPENAME) __convert_type(STRING, to_TYPENAME, __string_to_real)
__ANY_REAL(__iec_)
#undef __iec_

/******** STRING_TO_[ANY_DATE]   ************/ 
#define __iec_(to_TYPENAME) __convert_type(STRING, to_TYPENAME, __string_to_time)
__ANY_DATE(__iec_)
#undef __iec_
                                   
/******** STRING_TO_TIME   ************/ 
__convert_type(STRING, TIME, __string_to_time)


/********   TRUNC   ************/ 
#define __iec_(to_TYPENAME,from_TYPENAME) \
static inline to_TYPENAME TRUNC__##to_TYPENAME##__##from_TYPENAME(EN_ENO_PARAMS, from_TYPENAME op){\
  TEST_EN(to_TYPENAME)\
  return (to_TYPENAME)__move_##to_TYPENAME(op);\
}
__ANY_REAL(__to_anyint_)
#undef __iec_


/********   _TO_BCD   ************/ 
#define __iec_(to_TYPENAME,from_TYPENAME) \
static inline to_TYPENAME from_TYPENAME##_TO_BCD_##to_TYPENAME(EN_ENO_PARAMS, from_TYPENAME op){\
  TEST_EN(to_TYPENAME)\
  return (to_TYPENAME)__uint_to_bcd(op);\
}
__ANY_UINT(__to_anynbit_)
#undef __iec_


/********   BCD_TO_   ************/ 
#define __iec_(to_TYPENAME,from_TYPENAME) \
static inline to_TYPENAME from_TYPENAME##_BCD_TO_##to_TYPENAME(EN_ENO_PARAMS, from_TYPENAME op){\
  TEST_EN(to_TYPENAME)\
  return (to_TYPENAME)__bcd_to_uint(op);\
}
__ANY_NBIT(__to_anyuint_)
#undef __iec_


/***********************************/  
/***********************************/  
/*  2.5.1.5.2 Numerical Functions  */
/***********************************/  
/***********************************/  

/* workaround for va-args limitation on shorter than int params */
#define VA_ARGS_REAL LREAL
#define VA_ARGS_LREAL LREAL
#define VA_ARGS_SINT DINT
#define VA_ARGS_INT DINT
#define VA_ARGS_DINT DINT
#define VA_ARGS_LINT LINT
#define VA_ARGS_USINT UDINT
#define VA_ARGS_UINT UDINT
#define VA_ARGS_UDINT UDINT
#define VA_ARGS_ULINT ULINT
#define VA_ARGS_TIME TIME
#define VA_ARGS_BOOL DWORD
#define VA_ARGS_BYTE DWORD
#define VA_ARGS_WORD DWORD
#define VA_ARGS_DWORD DWORD
#define VA_ARGS_LWORD LWORD
#define VA_ARGS_STRING STRING
#define VA_ARGS_WSTRING WSTRING
#define VA_ARGS_DATE DATE
#define VA_ARGS_TOD TOD
#define VA_ARGS_DT DT


#define __numeric(fname,TYPENAME, FUNC) \
/* explicitly typed function */\
static inline TYPENAME fname##TYPENAME(EN_ENO_PARAMS, TYPENAME op){\
  TEST_EN(TYPENAME)\
  return FUNC(op);\
}\
/* overloaded function */\
static inline TYPENAME fname##_##TYPENAME##__##TYPENAME(EN_ENO_PARAMS, TYPENAME op) {\
  return fname##TYPENAME(EN_ENO, op);\
}

/******************************************************************/
/***   Table 23 - Standard functions of one numeric variable    ***/
/******************************************************************/

  /**************/
  /*    ABS     */
  /**************/
#define __abs_signed(TYPENAME) \
/* explicitly typed function */\
static inline TYPENAME ABS_##TYPENAME(EN_ENO_PARAMS, TYPENAME op){\
  TEST_EN(TYPENAME)\
  if (op < 0)\
    return -op;\
  return op;\
}\
/* overloaded function */\
static inline TYPENAME ABS__##TYPENAME##__##TYPENAME(EN_ENO_PARAMS, TYPENAME op) {\
  return ABS_##TYPENAME(EN_ENO, op);\
}

#define __abs_unsigned(TYPENAME) \
/* explicitly typed function */\
static inline TYPENAME ABS_##TYPENAME(EN_ENO_PARAMS, TYPENAME op){\
  TEST_EN(TYPENAME)\
  return op;\
}\
/* overloaded function */\
static inline TYPENAME ABS__##TYPENAME##__##TYPENAME(EN_ENO_PARAMS, TYPENAME op) {\
  return ABS_##TYPENAME(EN_ENO, op);\
}

__ANY_REAL(__abs_signed)
__ANY_SINT(__abs_signed)
__ANY_UINT(__abs_unsigned)


  /**************/
  /*    SQRT    */
  /**************/
#define __sqrt(TYPENAME) __numeric(SQRT_, TYPENAME, sqrt)
__ANY_REAL(__sqrt)


/**************/
  /*     LN     */
  /**************/
#define __ln(TYPENAME) __numeric(LN_, TYPENAME, log)
__ANY_REAL(__ln)


  /**************/
  /*     LOG    */
  /**************/
#define __log(TYPENAME) __numeric(LOG_, TYPENAME, log10)
__ANY_REAL(__log)


  /**************/
  /*     EXP    */
  /**************/
#define __exp(TYPENAME) __numeric(EXP_, TYPENAME, exp)
__ANY_REAL(__exp)


  /**************/
  /*     SIN    */
  /**************/
#define __sin(TYPENAME) __numeric(SIN_, TYPENAME, sin)
__ANY_REAL(__sin)


  /**************/
  /*     COS    */
  /**************/
#define __cos(TYPENAME) __numeric(COS_, TYPENAME, cos)
__ANY_REAL(__cos)

  /**************/
  /*     TAN    */
  /**************/
#define __tan(TYPENAME) __numeric(TAN_, TYPENAME, tan)
__ANY_REAL(__tan)


  /**************/
  /*    ASIN    */
  /**************/
#define __asin(TYPENAME) __numeric(ASIN_, TYPENAME, asin)
__ANY_REAL(__asin)

  /**************/
  /*    ACOS    */
  /**************/
#define __acos(TYPENAME) __numeric(ACOS_, TYPENAME, acos)
__ANY_REAL(__acos)

  /**************/
  /*    ATAN    */
  /**************/
#define __atan(TYPENAME) __numeric(ATAN_, TYPENAME, atan)
__ANY_REAL(__atan)



/*****************************************************/
/***   Table 24 - Standard arithmetic functions    ***/
/*****************************************************/

#define __arith_expand(fname,TYPENAME, OP)\
static inline TYPENAME fname(EN_ENO_PARAMS, UINT param_count, TYPENAME op1, ...){\
  va_list ap;\
  UINT i;\
  TEST_EN(TYPENAME)\
  \
  va_start (ap, op1);         /* Initialize the argument list.  */\
  \
  for (i = 0; i < param_count - 1; i++){\
    op1 = op1 OP va_arg (ap, VA_ARGS_##TYPENAME);\
  }\
  \
  va_end (ap);                  /* Clean up.  */\
  return op1;\
}

#define __arith_static(fname,TYPENAME, OP)\
/* explicitly typed function */\
static inline TYPENAME fname##TYPENAME(EN_ENO_PARAMS, TYPENAME op1, TYPENAME op2){\
  TEST_EN(TYPENAME)\
  return op1 OP op2;\
}\
/* overloaded function */\
static inline TYPENAME fname##_##TYPENAME##__##TYPENAME##__##TYPENAME(EN_ENO_PARAMS, TYPENAME op1, TYPENAME op2){\
  return fname##TYPENAME(EN_ENO, op1, op2);\
}

  /**************/
  /*     ADD    */
  /**************/
#define __add(TYPENAME) \
__arith_expand(ADD_##TYPENAME, TYPENAME, +) 			 /* explicitly typed function */\
__arith_expand(ADD__##TYPENAME##__##TYPENAME, TYPENAME, +)	 /* overloaded function */
__ANY_NUM(__add)


  /**************/
  /*     MUL    */
  /**************/
#define __mul(TYPENAME) \
__arith_expand(MUL_##TYPENAME, TYPENAME, *) 			 /* explicitly typed function */\
__arith_expand(MUL__##TYPENAME##__##TYPENAME, TYPENAME, *)	 /* overloaded function */
__ANY_NUM(__mul)


  /**************/
  /*     SUB    */
  /**************/
#define __sub(TYPENAME) __arith_static(SUB_, TYPENAME, -)
__ANY_NUM(__sub)


  /**************/
  /*     DIV    */
  /**************/
#define __div(TYPENAME)\
/* The explicitly typed standard functions */\
static inline TYPENAME DIV_##TYPENAME(EN_ENO_PARAMS, TYPENAME op1, TYPENAME op2){\
  TEST_EN_COND(TYPENAME, op2 == 0)\
  return op1 / op2;\
}\
/* The overloaded standard functions */\
static inline TYPENAME DIV__##TYPENAME##__##TYPENAME##__##TYPENAME(EN_ENO_PARAMS, TYPENAME op1, TYPENAME op2){\
  return DIV_##TYPENAME(EN_ENO, op1, op2);\
}
__ANY_NUM(__div)


  /**************/
  /*     MOD    */
  /**************/
#define __mod(TYPENAME)\
/* The explicitly typed standard functions */\
static inline TYPENAME MOD_##TYPENAME(EN_ENO_PARAMS, TYPENAME op1, TYPENAME op2){\
  TEST_EN(TYPENAME)\
  if (op2 == 0) return 0;\
  return op1 % op2;\
}\
/* The overloaded standard functions */\
static inline TYPENAME MOD__##TYPENAME##__##TYPENAME##__##TYPENAME(EN_ENO_PARAMS, TYPENAME op1, TYPENAME op2){\
  return MOD_##TYPENAME(EN_ENO, op1, op2);\
}
__ANY_INT(__mod)

  /**************/
  /*    EXPT    */
  /**************/
/* overloaded function */
#define __iec_(in1_TYPENAME,in2_TYPENAME) \
static inline in1_TYPENAME EXPT__##in1_TYPENAME##__##in1_TYPENAME##__##in2_TYPENAME\
  (EN_ENO_PARAMS, in1_TYPENAME IN1, in2_TYPENAME IN2){\
  TEST_EN(in1_TYPENAME)\
  return pow(IN1, IN2);\
}
#define __in1_anyreal_(in2_TYPENAME)   __ANY_REAL_1(__iec_,in2_TYPENAME)
__ANY_NUM(__in1_anyreal_)
#undef __iec_

  

  /***************/
  /*     MOVE    */
  /***************/
/* The explicitly typed standard functions */
#define __iec_(TYPENAME)\
static inline TYPENAME MOVE_##TYPENAME(EN_ENO_PARAMS, TYPENAME op1){\
  TEST_EN(TYPENAME)\
  return op1;\
}
__ANY(__iec_)
#undef __iec_

/* Overloaded function */
#define __iec_(TYPENAME)\
static inline TYPENAME MOVE__##TYPENAME##__##TYPENAME(EN_ENO_PARAMS, TYPENAME op1){\
  TEST_EN(TYPENAME)\
  return op1;\
}
__ANY(__iec_)
#undef __iec_






/***********************************/  
/***********************************/  
/*  2.5.1.5.3 Bit String Functions */
/***********************************/  
/***********************************/  

/****************************************************/
/***   Table 25 - Standard bit shift functions    ***/
/****************************************************/

/* We do not delcare explcitly typed versions of the functions in table 25.
 * See note above regarding explicitly typed functions for more details.
 */
#define __in1_anynbit_(in2_TYPENAME)   __ANY_NBIT_1(__iec_,in2_TYPENAME)

#define __shift_(fname, in1_TYPENAME, in2_TYPENAME, OP)\
static inline in1_TYPENAME fname(EN_ENO_PARAMS, in1_TYPENAME IN, in2_TYPENAME N) {\
  TEST_EN(in1_TYPENAME)\
  return IN OP N;\
}

  /**************/
  /*     SHL    */
  /**************/
#define __iec_(TYPENAME) \
/* Overloaded function */\
static inline BOOL SHL__BOOL__##TYPENAME(EN_ENO_PARAMS, BOOL IN, TYPENAME N) { \
  TEST_EN(BOOL);\
  return (N==0)? IN : __INIT_BOOL;  /* shifting by N>1 will always introduce a 0 */\
}
__ANY_INT(__iec_)
#undef __iec_


#define __iec_(in1_TYPENAME,in2_TYPENAME) \
__shift_(SHL__##in1_TYPENAME##__##in1_TYPENAME##__##in2_TYPENAME, in1_TYPENAME, in2_TYPENAME, << )/* Overloaded function */
__ANY_INT(__in1_anynbit_)
#undef __iec_


  /**************/
  /*     SHR    */
  /**************/
#define __iec_(TYPENAME) \
/* Overloaded function */\
static inline BOOL SHR__BOOL__##TYPENAME(EN_ENO_PARAMS, BOOL IN, TYPENAME N) { \
  TEST_EN(BOOL);\
  return (N==0)? IN : __INIT_BOOL;  /* shifting by N>1 will always introduce a 0 */\
}
__ANY_INT(__iec_)
#undef __iec_


#define __iec_(in1_TYPENAME,in2_TYPENAME) \
__shift_(SHR__##in1_TYPENAME##__##in1_TYPENAME##__##in2_TYPENAME, in1_TYPENAME, in2_TYPENAME, >> )/* Overloaded function */
__ANY_INT(__in1_anynbit_)
#undef __iec_


  /**************/
  /*     ROR    */
  /**************/
#define __iec_(TYPENAME) \
/* Overloaded function */\
static inline BOOL ROR__BOOL__##TYPENAME(EN_ENO_PARAMS, BOOL IN, TYPENAME N) { \
  TEST_EN(BOOL);\
  return IN; /* rotating a single bit by any value N will not change that bit! */\
}
__ANY_INT(__iec_)
#undef __iec_


#define __iec_(in1_TYPENAME,in2_TYPENAME) \
static inline in1_TYPENAME ROR__##in1_TYPENAME##__##in1_TYPENAME##__##in2_TYPENAME(EN_ENO_PARAMS, in1_TYPENAME IN, in2_TYPENAME N){\
  TEST_EN(in1_TYPENAME)\
  N %= 8*sizeof(in1_TYPENAME);\
  return (IN >> N) | (IN << (8*sizeof(in1_TYPENAME)-N));\
}
__ANY_INT(__in1_anynbit_)
#undef __iec_


  /**************/
  /*     ROL    */
  /**************/
#define __iec_(TYPENAME) \
/* Overloaded function */\
static inline BOOL ROL__BOOL__##TYPENAME(EN_ENO_PARAMS, BOOL IN, TYPENAME N) { \
  TEST_EN(BOOL);\
  return IN; /* rotating a single bit by any value N will not change that bit! */\
}
__ANY_INT(__iec_)
#undef __iec_


#define __iec_(in1_TYPENAME,in2_TYPENAME) \
static inline in1_TYPENAME ROL__##in1_TYPENAME##__##in1_TYPENAME##__##in2_TYPENAME(EN_ENO_PARAMS, in1_TYPENAME IN, in2_TYPENAME N){\
  TEST_EN(in1_TYPENAME)\
  N %= 8*sizeof(in1_TYPENAME);\
  return (IN << N) | (IN >> (8*sizeof(in1_TYPENAME)-N));\
}
__ANY_INT(__in1_anynbit_)
#undef __iec_



/*********************/
/***   Table 26    ***/
/*********************/

  /**************/
  /*     AND    */
  /**************/
__arith_expand(AND_BOOL, BOOL, && )         /* The explicitly typed standard functions */
__arith_expand(AND__BOOL__BOOL, BOOL, && )  /* Overloaded function */

#define __iec_(TYPENAME) \
__arith_expand(AND_##TYPENAME, TYPENAME, &)  /* The explicitly typed standard functions */\
__arith_expand(AND__##TYPENAME##__##TYPENAME, TYPENAME, &)  /* Overloaded function */
__ANY_NBIT(__iec_)
#undef __iec_

  /*************/
  /*     OR    */
  /*************/
__arith_expand(OR_BOOL, BOOL, || )         /* The explicitly typed standard functions */
__arith_expand(OR__BOOL__BOOL, BOOL, || )  /* Overloaded function */

#define __iec_(TYPENAME) \
__arith_expand(OR_##TYPENAME, TYPENAME, |)  /* The explicitly typed standard functions */\
__arith_expand(OR__##TYPENAME##__##TYPENAME, TYPENAME, |)  /* Overloaded function */
__ANY_NBIT(__iec_)
#undef __iec_

  /**************/
  /*     XOR    */
  /**************/
#define __xorbool_expand(fname) \
static inline BOOL fname(EN_ENO_PARAMS, UINT param_count, BOOL op1, ...){ \
  va_list ap; \
  UINT i; \
  TEST_EN(BOOL) \
\
  va_start (ap, op1);         /* Initialize the argument list.  */ \
\
  for (i = 0; i < param_count - 1; i++){ \
    BOOL tmp = va_arg (ap, VA_ARGS_BOOL); \
    op1 = (op1 && !tmp) || (!op1 && tmp); \
  } \
\
  va_end (ap);                  /* Clean up.  */ \
  return op1; \
}

__xorbool_expand(XOR_BOOL) /* The explicitly typed standard functions */
__xorbool_expand(XOR__BOOL__BOOL) /* Overloaded function */

#define __iec_(TYPENAME) \
__arith_expand(XOR_##TYPENAME, TYPENAME, ^) /* The explicitly typed standard functions */\
__arith_expand(XOR__##TYPENAME##__##TYPENAME, TYPENAME, ^) /* Overloaded function */\
__ANY_NBIT(__iec_)
#undef __iec_


  /**************/
  /*     NOT    */
  /**************/
/* The explicitly typed standard functions */
static inline BOOL NOT_BOOL(EN_ENO_PARAMS, BOOL op1){
  TEST_EN(BOOL)
  return !op1;
}

/* Overloaded function */
static inline BOOL NOT__BOOL__BOOL(EN_ENO_PARAMS, BOOL op1){
  TEST_EN(BOOL)
  return !op1;
}

/* The explicitly typed standard functions */
#define __iec_(TYPENAME)\
static inline TYPENAME NOT_##TYPENAME(EN_ENO_PARAMS, TYPENAME op1){\
  TEST_EN(TYPENAME)\
  return ~op1;\
}
__ANY_NBIT(__iec_)
#undef __iec_

/* Overloaded function */
#define __iec_(TYPENAME)\
static inline TYPENAME NOT__##TYPENAME##__##TYPENAME(EN_ENO_PARAMS, TYPENAME op1){\
  TEST_EN(TYPENAME)\
  return ~op1;\
}
__ANY_NBIT(__iec_)
#undef __iec_






/***************************************************/  
/***************************************************/  
/*  2.5.1.5.4  Selection and comparison Functions  */
/***************************************************/  
/***************************************************/  

/*********************/
/***   Table 27    ***/
/*********************/


    /**************/
    /*    SEL     */
    /**************/

/* The explicitly typed standard functions */
#define __iec_(TYPENAME)\
static inline TYPENAME SEL_##TYPENAME(EN_ENO_PARAMS, BOOL G, TYPENAME op0, TYPENAME op1){\
  TEST_EN(TYPENAME)\
  return G ? op1 : op0;\
}
__ANY(__iec_)
#undef __iec_

/* Overloaded function */
#define __iec_(TYPENAME)\
static inline TYPENAME SEL__##TYPENAME##__BOOL__##TYPENAME##__##TYPENAME(EN_ENO_PARAMS, BOOL G, TYPENAME op0, TYPENAME op1){\
  TEST_EN(TYPENAME)\
  return G ? op1 : op0;\
}
__ANY(__iec_)
#undef __iec_


    /**************/
    /*     MAX    */
    /**************/

#define __extrem_(fname,TYPENAME, COND) \
static inline TYPENAME fname(EN_ENO_PARAMS, UINT param_count, TYPENAME op1, ...){\
  va_list ap;\
  UINT i;\
  TEST_EN(TYPENAME)\
  \
  va_start (ap, op1);         /* Initialize the argument list.  */\
  \
  for (i = 0; i < param_count - 1; i++){\
    TYPENAME tmp = va_arg (ap, VA_ARGS_##TYPENAME);\
    op1 = COND ? tmp : op1;\
  }\
  \
  va_end (ap);                  /* Clean up.  */\
  return op1;\
}

/* Max for numerical data types */	
#define __iec_(TYPENAME) \
__extrem_(MAX_##TYPENAME,TYPENAME, op1 < tmp) /* The explicitly typed standard functions */\
__extrem_(MAX__##TYPENAME##__##TYPENAME,TYPENAME, op1 < tmp) /* Overloaded function */
__ANY_BIT(__iec_)
__ANY_NUM(__iec_)
#undef __iec_

/* Max for time data types */	
#define __iec_(TYPENAME) \
__extrem_(MAX_##TYPENAME, TYPENAME, __time_cmp(op1, tmp) < 0) /* The explicitly typed standard functions */\
__extrem_(MAX__##TYPENAME##__##TYPENAME, TYPENAME, __time_cmp(op1, tmp) < 0) /* Overloaded function */
__ANY_DATE(__iec_)
__iec_(TIME)
#undef __iec_

#define __STR_CMP(str1, str2) memcmp((char*)&str1.body,(char*)&str2.body, str1.len < str2.len ? str1.len : str2.len)

/* Max for string data types */	
__extrem_(MAX_STRING, STRING, __STR_CMP(op1,tmp) < 0) /* The explicitly typed standard functions */
__extrem_(MAX__STRING__STRING, STRING, __STR_CMP(op1,tmp) < 0) /* Overloaded function */

    /**************/
    /*     MIN    */
    /**************/
/* Min for numerical data types */	
#define __iec_(TYPENAME) \
__extrem_(MIN_##TYPENAME, TYPENAME, op1 > tmp) /* The explicitly typed standard functions */\
__extrem_(MIN__##TYPENAME##__##TYPENAME, TYPENAME, op1 > tmp) /* Overloaded function */
__ANY_NBIT(__iec_)
__ANY_NUM(__iec_)
#undef __iec_

/* Min for time data types */	
#define __iec_(TYPENAME) \
__extrem_(MIN_##TYPENAME, TYPENAME, __time_cmp(op1, tmp) > 0) /* The explicitly typed standard functions */\
__extrem_(MIN__##TYPENAME##__##TYPENAME, TYPENAME, __time_cmp(op1, tmp) > 0) /* Overloaded function */
__ANY_DATE(__iec_)
__iec_(TIME)
#undef __iec_

/* Min for string data types */
__extrem_(MIN_STRING, STRING, __STR_CMP(op1,tmp) > 0) /* The explicitly typed standard functions */
__extrem_(MIN__STRING__STRING, STRING, __STR_CMP(op1,tmp) > 0) /* Overloaded function */

    /**************/
    /*   LIMIT    */
    /**************/

/* Limit for numerical data types */
#define __iec_(TYPENAME)\
/* The explicitly typed standard functions */\
static inline TYPENAME LIMIT_##TYPENAME(EN_ENO_PARAMS, TYPENAME MN, TYPENAME IN, TYPENAME MX){\
  TEST_EN(TYPENAME)\
  return IN > MN ? IN < MX ? IN : MX : MN;\
}\
/* Overloaded function */\
static inline TYPENAME LIMIT__##TYPENAME##__##TYPENAME##__##TYPENAME##__##TYPENAME(EN_ENO_PARAMS, TYPENAME MN, TYPENAME IN, TYPENAME MX){\
  TEST_EN(TYPENAME)\
  return IN > MN ? IN < MX ? IN : MX : MN;\
}
__ANY_NBIT(__iec_)
__ANY_NUM(__iec_)
#undef __iec_


/* Limit for time data types */	
#define __iec_(TYPENAME)\
/* The explicitly typed standard functions */\
static inline TYPENAME LIMIT_##TYPENAME(EN_ENO_PARAMS, TYPENAME MN, TYPENAME IN, TYPENAME MX){\
    TEST_EN(TYPENAME)\
    return __time_cmp(IN, MN) > 0 ? /* IN>MN ?*/\
           __time_cmp(IN, MX) < 0 ? /* IN<MX ?*/\
           IN : MX : MN;\
}\
/* Overloaded function */\
static inline TYPENAME LIMIT__##TYPENAME##__##TYPENAME##__##TYPENAME##__##TYPENAME(EN_ENO_PARAMS, TYPENAME MN, TYPENAME IN, TYPENAME MX){\
    TEST_EN(TYPENAME)\
    return __time_cmp(IN, MN) > 0 ? /* IN>MN ?*/\
           __time_cmp(IN, MX) < 0 ? /* IN<MX ?*/\
           IN : MX : MN;\
}

__ANY_DATE(__iec_)
__iec_(TIME)
#undef __iec_

/* Limit for string data types */	
/* The explicitly typed standard functions */
static inline STRING LIMIT_STRING(EN_ENO_PARAMS, STRING MN, STRING IN, STRING MX){
    TEST_EN(STRING)
    return __STR_CMP(IN, MN) > 0 ? __STR_CMP(IN, MX) < 0 ? IN : MX : MN;
}

/* Overloaded function */
static inline STRING LIMIT__STRING__STRING__STRING__STRING(EN_ENO_PARAMS, STRING MN, STRING IN, STRING MX){
    TEST_EN(STRING)
    return __STR_CMP(IN, MN) > 0 ? __STR_CMP(IN, MX) < 0 ? IN : MX : MN;
}


    /**************/
    /*     MUX    */
    /**************/
/* The standard states that the inputs for SEL and MUX must be named starting off from 0,
 * unlike remaining functions, that start off at 1.
 */    
/* The explicitly typed standard functions */
#define __in1_anyint_(in2_TYPENAME)   __ANY_INT_1(__iec_,in2_TYPENAME)
#define __iec_(in1_TYPENAME,in2_TYPENAME) \
static inline in2_TYPENAME MUX__##in2_TYPENAME##__##in1_TYPENAME##__##in2_TYPENAME(EN_ENO_PARAMS, in1_TYPENAME K, UINT param_count, ...){\
  va_list ap;\
  UINT i;\
  in2_TYPENAME tmp;\
  TEST_EN_COND(in2_TYPENAME, K >= param_count)\
  tmp = __INIT_##in2_TYPENAME;\
  \
  va_start (ap, param_count);         /* Initialize the argument list.  */\
  \
  for (i = 0; i < param_count; i++){\
    if(K == i){\
        tmp = va_arg (ap, VA_ARGS_##in2_TYPENAME);\
        va_end (ap);                  /* Clean up.  */\
        return tmp;\
    }else{\
        va_arg (ap, VA_ARGS_##in2_TYPENAME);\
    }\
  }\
  \
  va_end (ap);                  /* Clean up.  */\
  return tmp;\
}

__ANY(__in1_anyint_)
#undef __iec_


/******************************************/
/***             Table 28               ***/
/***   Standard comparison functions    ***/
/******************************************/

#define __compare_(fname,TYPENAME, COND) \
static inline BOOL fname(EN_ENO_PARAMS, UINT param_count, TYPENAME op1, ...){\
  va_list ap;\
  UINT i;\
  TEST_EN(BOOL)\
  \
  va_start (ap, op1);         /* Initialize the argument list.  */\
  DBG(#fname #TYPENAME "\n")\
  DBG_TYPE(TYPENAME, op1)\
  \
  for (i = 0; i < param_count - 1; i++){\
    TYPENAME tmp = va_arg (ap, VA_ARGS_##TYPENAME);\
    DBG_TYPE(TYPENAME, tmp)\
    if(COND){\
        op1 = tmp;\
    }else{\
        va_end (ap);                  /* Clean up.  */\
        return 0;\
    }\
  }\
  \
  va_end (ap);                  /* Clean up.  */\
  return 1;\
}

#define __compare_num(fname, TYPENAME, TEST) __compare_(fname, TYPENAME, op1 TEST tmp )
#define __compare_time(fname, TYPENAME, TEST) __compare_(fname, TYPENAME, __time_cmp(op1, tmp) TEST 0)
#define __compare_string(fname, TEST) __compare_(fname, STRING, __STR_CMP(op1, tmp) TEST 0 )


    /**************/
    /*     GT     */
    /**************/
/* Comparison for numerical data types */
#define __iec_(TYPENAME) \
__compare_num(GT_##TYPENAME, TYPENAME, > ) /* The explicitly typed standard functions */\
__compare_num(GT__BOOL__##TYPENAME, TYPENAME, > ) /* Overloaded function */
__ANY_NBIT(__iec_)
__ANY_NUM(__iec_)
#undef __iec_

/* Comparison for time data types */	
#define __iec_(TYPENAME) \
__compare_time(GT_##TYPENAME, TYPENAME, > ) /* The explicitly typed standard functions */\
__compare_time(GT__BOOL__##TYPENAME, TYPENAME, > ) /* Overloaded function */
__ANY_DATE(__iec_)
__iec_(TIME)
#undef __iec_

/* Comparison for string data types */	
__compare_string(GT_STRING, > ) /* The explicitly typed standard functions */
__compare_string(GT__BOOL__STRING, > ) /* Overloaded function */

    /**************/
    /*     GE     */
    /**************/
/* Comparison for numerical data types */
#define __iec_(TYPENAME) \
__compare_num(GE_##TYPENAME, TYPENAME, >= ) /* The explicitly typed standard functions */\
__compare_num(GE__BOOL__##TYPENAME, TYPENAME, >= ) /* Overloaded function */
__ANY_NBIT(__iec_)
__ANY_NUM(__iec_)
#undef __iec_

/* Comparison for time data types */	
#define __iec_(TYPENAME) \
__compare_time(GE_##TYPENAME, TYPENAME, >= ) /* The explicitly typed standard functions */\
__compare_time(GE__BOOL__##TYPENAME, TYPENAME, >= ) /* Overloaded function */
__ANY_DATE(__iec_)
__iec_(TIME)
#undef __iec_

/* Comparison for string data types */	
__compare_string(GE_STRING, >= ) /* The explicitly typed standard functions */
__compare_string(GE__BOOL__STRING, >= ) /* Overloaded function */



    /**************/
    /*     EQ     */
    /**************/
/* Comparison for numerical data types */
#define __iec_(TYPENAME) \
__compare_num(EQ_##TYPENAME, TYPENAME, == ) /* The explicitly typed standard functions */\
__compare_num(EQ__BOOL__##TYPENAME, TYPENAME, == ) /* Overloaded function */
__ANY_NBIT(__iec_)
__ANY_NUM(__iec_)
#undef __iec_

/* Comparison for time data types */	
#define __iec_(TYPENAME) \
__compare_time(EQ_##TYPENAME, TYPENAME, == ) /* The explicitly typed standard functions */\
__compare_time(EQ__BOOL__##TYPENAME, TYPENAME, == ) /* Overloaded function */
__ANY_DATE(__iec_)
__iec_(TIME)
#undef __iec_

/* Comparison for string data types */	
__compare_string(EQ_STRING, == ) /* The explicitly typed standard functions */
__compare_string(EQ__BOOL__STRING, == ) /* Overloaded function */


    /**************/
    /*     LT     */
    /**************/
/* Comparison for numerical data types */
#define __iec_(TYPENAME) \
__compare_num(LT_##TYPENAME, TYPENAME, < ) /* The explicitly typed standard functions */\
__compare_num(LT__BOOL__##TYPENAME, TYPENAME, < ) /* Overloaded function */
__ANY_NBIT(__iec_)
__ANY_NUM(__iec_)
#undef __iec_

/* Comparison for time data types */	
#define __iec_(TYPENAME) \
__compare_time(LT_##TYPENAME, TYPENAME, < ) /* The explicitly typed standard functions */\
__compare_time(LT__BOOL__##TYPENAME, TYPENAME, < ) /* Overloaded function */
__ANY_DATE(__iec_)
__iec_(TIME)
#undef __iec_

/* Comparison for string data types */	
__compare_string(LT_STRING, < ) /* The explicitly typed standard functions */
__compare_string(LT__BOOL__STRING, < ) /* Overloaded function */


    /**************/
    /*     LE     */
    /**************/
/* Comparison for numerical data types */
#define __iec_(TYPENAME) \
__compare_num(LE_##TYPENAME, TYPENAME, <= ) /* The explicitly typed standard functions */\
__compare_num(LE__BOOL__##TYPENAME, TYPENAME, <= ) /* Overloaded function */
__ANY_NBIT(__iec_)
__ANY_NUM(__iec_)
#undef __iec_

/* Comparison for time data types */	
#define __iec_(TYPENAME) \
__compare_time(LE_##TYPENAME, TYPENAME, <= ) /* The explicitly typed standard functions */\
__compare_time(LE__BOOL__##TYPENAME, TYPENAME, <= ) /* Overloaded function */
__ANY_DATE(__iec_)
__iec_(TIME)
#undef __iec_

/* Comparison for string data types */	
__compare_string(LE_STRING, <= ) /* The explicitly typed standard functions */
__compare_string(LE__BOOL__STRING, <= ) /* Overloaded function */


    /**************/
    /*     NE     */
    /**************/
#define __ne_num(fname, TYPENAME) \
static inline BOOL fname(EN_ENO_PARAMS, TYPENAME op1, TYPENAME op2){\
  TEST_EN(BOOL)\
  return op1 != op2 ? 1 : 0;\
}

#define __ne_time(fname, TYPENAME) \
static inline BOOL fname(EN_ENO_PARAMS, TYPENAME op1, TYPENAME op2){\
  TEST_EN(BOOL)\
  return __time_cmp(op1, op2) != 0 ? 1 : 0;\
}


/* Comparison for numerical data types */
#define __iec_(TYPENAME) \
__ne_num(NE_##TYPENAME, TYPENAME) /* The explicitly typed standard functions */\
__ne_num(NE__BOOL__##TYPENAME##__##TYPENAME, TYPENAME) /* Overloaded function */
__ANY_NBIT(__iec_)
__ANY_NUM(__iec_)
#undef __iec_

/* Comparison for time data types */	
#define __iec_(TYPENAME) \
__ne_time(NE_##TYPENAME, TYPENAME) /* The explicitly typed standard functions */\
__ne_time(NE__BOOL__##TYPENAME##__##TYPENAME, TYPENAME) /* Overloaded function */
__ANY_DATE(__iec_)
__iec_(TIME)
#undef __iec_

/* Comparison for string data types */	
__compare_string(NE_STRING, != ) /* The explicitly typed standard functions */
__compare_string(NE__BOOL__STRING__STRING, != ) /* Overloaded function */






/*********************************************/  
/*********************************************/  
/*  2.5.1.5.5   Character string  Functions  */
/*********************************************/  
/*********************************************/  

/*************************************/
/***           Table 29            ***/
/***  Character string  Functions  ***/
/*************************************/

/* We do not delcare explcitly typed versions of the functions in table 29.
 * See note above regarding explicitly typed functions for more details.
 */
 



    /***************/
    /*     LEN     */
    /***************/
static inline __strlen_t __len(STRING IN) {return IN.len;}

/* A function, with 1 input paramter, implementing a generic OPERATION */
#define __genoper_1p_(fname,ret_TYPENAME, par_TYPENAME, OPERATION) \
static inline ret_TYPENAME fname(EN_ENO_PARAMS, par_TYPENAME par1){\
  TEST_EN(ret_TYPENAME)\
  return (ret_TYPENAME)OPERATION(par1);\
}

#define __iec_(TYPENAME) __genoper_1p_(LEN__##TYPENAME##__STRING, TYPENAME, STRING, __len)
__ANY_INT(__iec_)
#undef __iec_


    /****************/
    /*     LEFT     */
    /****************/

#define __left(TYPENAME) \
static inline STRING LEFT__STRING__STRING__##TYPENAME(EN_ENO_PARAMS, STRING IN, TYPENAME L){\
    STRING res;\
    TEST_EN_COND(STRING, L < 0)\
    res = __INIT_STRING;\
    L = L < (TYPENAME)IN.len ? L : (TYPENAME)IN.len;\
    memcpy(&res.body, &IN.body, L);\
    res.len = L;\
    return res;\
}
__ANY_INT(__left)


    /*****************/
    /*     RIGHT     */
    /*****************/

#define __right(TYPENAME) \
static inline STRING RIGHT__STRING__STRING__##TYPENAME(EN_ENO_PARAMS, STRING IN, TYPENAME L){\
  STRING res;\
  TEST_EN_COND(STRING, L < 0)\
  res = __INIT_STRING;\
  L = L < (TYPENAME)IN.len ? L : (TYPENAME)IN.len;\
  memcpy(&res.body, &IN.body[(TYPENAME)IN.len - L], L);\
  res.len = L;\
  return res;\
}
__ANY_INT(__right)


    /***************/
    /*     MID     */
    /***************/

#define __mid(TYPENAME) \
static inline STRING MID__STRING__STRING__##TYPENAME##__##TYPENAME(EN_ENO_PARAMS, STRING IN, TYPENAME L, TYPENAME P){\
  STRING res;\
  TEST_EN_COND(STRING, L < 0 || P < 0)\
  res = __INIT_STRING;\
  if(P <= (TYPENAME)IN.len){\
	P -= 1; /* now can be used as [index]*/\
	L = L + P <= (TYPENAME)IN.len ? L : (TYPENAME)IN.len - P;\
	memcpy(&res.body, &IN.body[P] , L);\
	res.len = L;\
  }\
  return res;\
}
__ANY_INT(__mid)


    /******************/
    /*     CONCAT     */
    /******************/

static inline STRING CONCAT(EN_ENO_PARAMS, UINT param_count, ...){
  UINT i;
  STRING res;
  va_list ap;
  __strlen_t charcount;
  TEST_EN(STRING)
  charcount = 0;
  res = __INIT_STRING;

  va_start (ap, param_count);         /* Initialize the argument list.  */

  for (i = 0; i < param_count && charcount < STR_MAX_LEN; i++)
  {
    STRING tmp = va_arg(ap, STRING);
    __strlen_t charrem = STR_MAX_LEN - charcount;
    __strlen_t to_write = tmp.len > charrem ? charrem : tmp.len;
    memcpy(&res.body[charcount], &tmp.body , to_write);
    charcount += to_write;
  }

  res.len = charcount;

  va_end (ap);                  /* Clean up.  */
  return res;
}

    /******************/
    /*     INSERT     */
    /******************/

static inline STRING __insert(STRING IN1, STRING IN2, __strlen_t P){
    STRING res;
    __strlen_t to_copy;
    res = __INIT_STRING;

    to_copy = P > IN1.len ? IN1.len : P;
    memcpy(&res.body, &IN1.body , to_copy);
    P = res.len = to_copy;

    to_copy = IN2.len + res.len > STR_MAX_LEN ? STR_MAX_LEN - res.len : IN2.len;
    memcpy(&res.body[res.len], &IN2.body , to_copy);
    res.len += to_copy;

    to_copy = IN1.len - P < STR_MAX_LEN - res.len ? IN1.len - P : STR_MAX_LEN - res.len ;
    memcpy(&res.body[res.len], &IN1.body[P] , to_copy);
    res.len += to_copy;

    return res;
}

#define __iec_(TYPENAME) \
static inline STRING INSERT__STRING__STRING__STRING__##TYPENAME(EN_ENO_PARAMS, STRING str1, STRING str2, TYPENAME P){\
  TEST_EN_COND(STRING, P < 0)\
  return (STRING)__insert(str1,str2,P);\
}
__ANY_INT(__iec_)
#undef __iec_


    /******************/
    /*     DELETE     */
    /******************/

static inline STRING __delete(STRING IN, __strlen_t L, __strlen_t P){
    STRING res;
    __strlen_t to_copy;
    res = __INIT_STRING;

    to_copy = P > IN.len ? IN.len : P-1;
    memcpy(&res.body, &IN.body , to_copy);
    P = res.len = to_copy;

    if( IN.len > P + L ){
        to_copy = IN.len - P - L;
        memcpy(&res.body[res.len], &IN.body[P + L], to_copy);
        res.len += to_copy;
    }

    return res;
}

#define __iec_(TYPENAME) \
static inline STRING DELETE__STRING__STRING__##TYPENAME##__##TYPENAME(EN_ENO_PARAMS, STRING str, TYPENAME L, TYPENAME P){\
  TEST_EN_COND(STRING, L < 0 || P < 0)\
  return (STRING)__delete(str,L,P);\
}
__ANY_INT(__iec_)
#undef __iec_


    /*******************/
    /*     REPLACE     */
    /*******************/

static inline STRING __replace(STRING IN1, STRING IN2, __strlen_t L, __strlen_t P){
    STRING res;
    __strlen_t to_copy;
    res = __INIT_STRING;

    to_copy = P > IN1.len ? IN1.len : P-1;
    memcpy(&res.body, &IN1.body , to_copy);
    P = res.len = to_copy;

    to_copy = IN2.len < L ? IN2.len : L;

    if( to_copy + res.len > STR_MAX_LEN )
       to_copy = STR_MAX_LEN - res.len;

    memcpy(&res.body[res.len], &IN2.body , to_copy);
    res.len += to_copy;

    P += L;
    if( res.len <  STR_MAX_LEN && P < IN1.len)
    {
        to_copy = IN1.len - P;
        memcpy(&res.body[res.len], &IN1.body[P] , to_copy);
        res.len += to_copy;
    }

    return res;
}

#define __iec_(TYPENAME) \
static inline STRING REPLACE__STRING__STRING__STRING__##TYPENAME##__##TYPENAME(EN_ENO_PARAMS, STRING str1, STRING str2, TYPENAME L, TYPENAME P){\
  TEST_EN_COND(STRING, L < 0 || P < 0)\
  return (STRING)__replace(str1,str2,L,P);\
}
__ANY_INT(__iec_)
#undef __iec_

    /****************/
    /*     FIND     */
    /****************/

static inline __strlen_t __pfind(STRING* IN1, STRING* IN2){
    UINT count1 = 0; /* offset of first matching char in IN1 */
    UINT count2 = 0; /* count of matching char */
    while(count1 + count2 < IN1->len && count2 < IN2->len)
    {
        if(IN1->body[count1 + count2] != IN2->body[count2]){
            count1 += count2 + 1;
            count2 = 0;
        }
        else {
            count2++;
        }
    }
    return count2 == IN2->len -1 ? 0 : count1 + 1;
}

#define __iec_(TYPENAME) \
static inline TYPENAME FIND__##TYPENAME##__STRING__STRING(EN_ENO_PARAMS, STRING str1, STRING str2){\
  TEST_EN(TYPENAME)\
  return (TYPENAME)__pfind(&str1,&str2);\
}
__ANY_INT(__iec_)
#undef __iec_


/*********************************************/  
/*********************************************/  
/*  2.5.1.5.6  Functions of time data types  */
/*********************************************/  
/*********************************************/  

/**************************************/
/***           Table 30             ***/
/***  Functions of time data types  ***/
/**************************************/


static inline TIME ADD_TIME(EN_ENO_PARAMS, TIME IN1, TIME IN2){
  TEST_EN(TIME)
  return __time_add(IN1, IN2);
}

static inline TOD ADD_TOD_TIME(EN_ENO_PARAMS, TOD IN1, TIME IN2){
  TEST_EN(TOD)
  return __time_add(IN1, IN2);
}

static inline DT ADD_DT_TIME(EN_ENO_PARAMS, DT IN1, TIME IN2){
  TEST_EN(DT)
  return __time_add(IN1, IN2);
}

static inline TIME SUB_TIME(EN_ENO_PARAMS, TIME IN1, TIME IN2){
  TEST_EN(TIME)
  return __time_sub(IN1, IN2);
}

static inline TIME SUB_DATE_DATE(EN_ENO_PARAMS, DATE IN1, DATE IN2){
  TEST_EN(TIME)
  return __time_sub(IN1, IN2);
}

static inline TOD SUB_TOD_TIME(EN_ENO_PARAMS, TOD IN1, TIME IN2){
  TEST_EN(TOD)
  return __time_sub(IN1, IN2);
}

static inline TIME SUB_TOD_TOD(EN_ENO_PARAMS, TOD IN1, TOD IN2){
  TEST_EN(TIME)
  return __time_sub(IN1, IN2);
}

static inline DT SUB_DT_TIME(EN_ENO_PARAMS, DT IN1, TIME IN2){
  TEST_EN(DT)
  return __time_sub(IN1, IN2);
}

static inline TIME SUB_DT_DT(EN_ENO_PARAMS, DT IN1, DT IN2){
  TEST_EN(TIME)
  return __time_sub(IN1, IN2);
}


/***  MULTIME  ***/
#define __iec_(TYPENAME)\
static inline TIME MULTIME__TIME__TIME__##TYPENAME(EN_ENO_PARAMS, TIME IN1, TYPENAME IN2){\
  TEST_EN(TIME)\
  return __time_mul(IN1, IN2);\
}
__ANY_NUM(__iec_)
#undef __iec_

/***  MUL  ***/
#define __iec_(TYPENAME)\
static inline TIME MUL__TIME__TIME__##TYPENAME(EN_ENO_PARAMS, TIME IN1, TYPENAME IN2){\
  TEST_EN(TIME)\
  return __time_mul(IN1, IN2);\
}
__ANY_NUM(__iec_)
#undef __iec_

/***  DIVTIME  ***/
#define __iec_(TYPENAME)\
static inline TIME DIVTIME__TIME__TIME__##TYPENAME(EN_ENO_PARAMS, TIME IN1, TYPENAME IN2){\
  TEST_EN(TIME)\
  return __time_div(IN1, IN2);\
}
__ANY_NUM(__iec_)
#undef __iec_

/***  DIV  ***/
#define __iec_(TYPENAME)\
static inline TIME DIV__TIME__TIME__##TYPENAME(EN_ENO_PARAMS, TIME IN1, TYPENAME IN2){\
  TEST_EN(TIME)\
  return __time_div(IN1, IN2);\
}
__ANY_NUM(__iec_)
#undef __iec_

/*** CONCAT_DATE_TOD ***/
static inline DT CONCAT_DATE_TOD(EN_ENO_PARAMS, DATE IN1, TOD IN2){
  TEST_EN(DT)
  return __time_add(IN1, IN2);
}



/****************************************************/  
/****************************************************/  
/*  2.5.1.5.6   Functions of enumerated data types  */
/****************************************************/  
/****************************************************/  

/********************************************/
/***              Table 31                ***/
/***  Functions of enumerated data types  ***/
/********************************************/

/* Do we support this? */
