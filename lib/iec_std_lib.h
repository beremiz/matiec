/****
 * IEC 61131-3 standard function lib
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

#include "iec_std_lib_generated.h"

#define __print_BOOL(name) printf("  %s = (BOOL) %s\n",#name, name?"TRUE":"FALSE");
#define __print_SINT(name) printf("  %s = (SINT) %d\n",#name, name);
#define __print_INT(name) printf("  %s = (INT) %d\n",#name, name);
#define __print_DINT(name) printf("  %s = (DINT) %d\n",#name, name);
#define __print_LINT(name) printf("  %s = (LINT) %d\n",#name, name);
#define __print_USINT(name) printf("  %s = (USINT) %u\n",#name, name);
#define __print_UINT(name) printf("  %s = (UINT) %u\n",#name, name);
#define __print_UDINT(name) printf("  %s = (UDINT) %u\n",#name, name);
#define __print_ULINT(name) printf("  %s = (ULINT) %lu\n",#name, name);
#define __print_REAL(name) printf("  %s = (REAL) %f\n",#name, (double)name);
#define __print_LREAL(name) printf("  %s = (LREAL) %f\n",#name, (double)name);
#define __print_TIME(name) {STRING __tmp = __time_to_string(name);__tmp.body[__tmp.len] = 0; printf("  %s = (TIME) %*s\n",#name, __tmp.len, &__tmp.body);}
#define __print_DATE(name) {STRING __tmp = __date_to_string(name);__tmp.body[__tmp.len] = 0; printf("  %s = (DATE) %*s\n",#name, __tmp.len, &__tmp.body);}
#define __print_TOD(name) {STRING __tmp = __tod_to_string(name);__tmp.body[__tmp.len] = 0; printf("  %s = (TOD) %*s\n",#name, __tmp.len, &__tmp.body);}
#define __print_DT(name) {STRING __tmp = __dt_to_string(name);__tmp.body[__tmp.len] = 0; printf("  %s = (DT) %*s\n",#name, __tmp.len, &__tmp.body);}
#define __print_STRING(name) printf("  %s = (STRING) {%d, \"%*s\"}\n",#name, name.len, name.len, &name.body);
#define __print_BYTE(name) printf("  %s = (BYTE) 0x%2.2x\n",#name, name);
#define __print_WORD(name) printf("  %s = (WORD) 0x%4.4x\n",#name, name);
#define __print_DWORD(name) printf("  %s = (DWORD) 0x%8.8x\n",#name, name);
#define __print_LWORD(name) printf("  %s = (LWORD) 0x%16.16lx\n",#name, name);

#ifdef DEBUG_IEC
#define DBG(...) printf(__VA_ARGS__);
#define DBG_TYPE(TYPENAME, name) __print_##TYPENAME(name);
#else
#define DBG(...)
#define DBG_TYPE(TYPENAME, name)
#endif

/*****************/
/*  Types defs   */
/*****************/

typedef uint8_t  BOOL;

#define TRUE 1
#define FALSE 0

typedef int8_t    SINT;
typedef int16_t   INT;
typedef int32_t   DINT;
typedef int64_t   LINT;

typedef uint8_t    USINT;
typedef uint16_t   UINT;
typedef uint32_t   UDINT;
typedef uint64_t   ULINT;

typedef uint8_t    BYTE;
typedef uint16_t   WORD;
typedef uint32_t   DWORD;
typedef uint64_t   LWORD;

typedef float    REAL;
typedef double   LREAL;


#if !defined __timespec_defined
# define __timespec_defined     1

struct timespec
  {
    long int tv_sec;            /* Seconds.  */
    long int tv_nsec;           /* Nanoseconds.  */
  };

#endif

typedef struct timespec TIME;
typedef struct timespec DATE;
typedef struct timespec DT;
typedef struct timespec TOD;

#define __TIME_CMP(t1, t2) (t2.tv_sec == t1.tv_sec ? t2.tv_nsec - t1.tv_nsec : t1.tv_sec - t2.tv_sec) 
extern TIME __CURRENT_TIME;

#define STR_MAX_LEN 40
typedef int8_t __strlen_t;
typedef struct {
    __strlen_t len;
    uint8_t body[STR_MAX_LEN];
} STRING;

#define __STR_CMP(str1, str2) memcmp((char*)&str1.body,(char*)&str2.body, str1.len < str2.len ? str1.len : str2.len)

/* TODO
typedef struct {
    __strlen_t len;
    u_int16_t body[STR_MAX_LEN];
} WSTRING;
*/

# if __WORDSIZE == 64
#define __32b_sufix
#define __64b_sufix L
#else
#define __32b_sufix L
#define __64b_sufix LL 
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
#define __STRING_LITERAL(value) __literal(STRING,value,)
#define __BYTE_LITERAL(value) __literal(BYTE,value,)
#define __WORD_LITERAL(value) __literal(WORD,value,)
#define __DWORD_LITERAL(value) __literal(DWORD,value,__32b_sufix)
#define __LWORD_LITERAL(value) __literal(LWORD,value,__32b_sufix)



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




/*****************/
/* Misc internal */
/*****************/

/* function that generates an IEC runtime error */
static inline void IEC_error(void) {
  /* TODO... */
  fprintf(stderr, "IEC 61131-3 runtime error.\n");
  /*exit(1);*/
}


static inline void __normalize_timespec (struct timespec *ts) {
  if( ts->tv_nsec < -1000000000 || (( ts->tv_sec > 0 ) && ( ts->tv_nsec < 0 ))){
    ts->tv_sec--;
    ts->tv_nsec += 1000000000;
  }
  if( ts->tv_nsec > 1000000000 || (( ts->tv_sec < 0 ) && ( ts->tv_nsec > 0 ))){
    ts->tv_sec++;
    ts->tv_nsec -= 1000000000;
  }
}

static inline struct timespec __time_to_timespec(int sign, double mseconds, double seconds, double minutes, double hours, double days) {
  struct timespec ts;
  
  /* sign is 1 for positive values, -1 for negative time... */
  long double total_sec = ((days*24 + hours)*60 + minutes)*60 + seconds + mseconds/1e3;
  if (sign >= 0) sign = 1; else sign = -1;
  ts.tv_sec = sign * (long int)total_sec;
  ts.tv_nsec = sign * (long int)((total_sec - ts.tv_sec)*1e9);

  return ts;
}


static inline struct timespec __tod_to_timespec(double seconds, double minutes, double hours) {
  struct timespec ts;
  
  long double total_sec = (hours*60 + minutes)*60 + seconds;
  ts.tv_sec = (long int)total_sec;
  ts.tv_nsec = (long int)((total_sec - ts.tv_sec)*1e9);
  
  return ts;
}

static inline struct timespec __date_to_timespec(int day, int month, int year) {
  struct timespec ts;
  struct tm broken_down_time;

  broken_down_time.tm_sec = 0;
  broken_down_time.tm_min = 0;
  broken_down_time.tm_hour = 0;
  broken_down_time.tm_mday = day;  /* day of month, from 1 to 31 */
  broken_down_time.tm_mon = month - 1;   /* month since January, in the range 0 to 11 */
  broken_down_time.tm_year = year - 1900;  /* number of years since 1900 */

  time_t epoch_seconds = mktime(&broken_down_time); /* determine number of seconds since the epoch, i.e. Jan 1st 1970 */

  if ((time_t)(-1) == epoch_seconds)
    IEC_error();

  ts.tv_sec = epoch_seconds;
  ts.tv_nsec = 0;
  
  return ts;
}

static inline struct timespec __dt_to_timespec(double seconds,  double minutes, double hours, int day, int month, int year) {
  struct timespec ts;
  
  long double total_sec = (hours*60 + minutes)*60 + seconds;
  ts.tv_sec = (long int)total_sec;
  ts.tv_nsec = (long int)((total_sec - ts.tv_sec)*1e9);

  struct tm broken_down_time;
  broken_down_time.tm_sec = 0;
  broken_down_time.tm_min = 0;
  broken_down_time.tm_hour = 0;
  broken_down_time.tm_mday = day;  /* day of month, from 1 to 31 */
  broken_down_time.tm_mon = month - 1;   /* month since January, in the range 0 to 11 */
  broken_down_time.tm_year = year - 1900;  /* number of years since 1900 */

  time_t epoch_seconds = mktime(&broken_down_time); /* determine number of seconds since the epoch, i.e. Jan 1st 1970 */
  if ((time_t)(-1) == epoch_seconds)
    IEC_error();

  ts.tv_sec += epoch_seconds;
  if (ts.tv_sec < epoch_seconds)
    /* since the TOD is always positive, if the above happens then we had an overflow */
    IEC_error();

  return ts;
}

/***************/
/*   Time ops  */
/***************/
static inline TIME __date_and_time_to_time_of_day(TIME IN){
  return (TIME){IN.tv_sec % 86400, IN.tv_nsec};
}
static inline TIME __date_and_time_to_date(TIME IN){
  return (TIME){IN.tv_sec - (IN.tv_sec % (24*60*60)), 0};
}
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
/* String ops  */
/***************/
static inline UINT __len(STRING IN){
    return IN.len;
}
static inline STRING __left(STRING IN, SINT L){
    STRING res = __INIT_STRING;
    L = L < IN.len ? L : IN.len;
    memcpy(&res.body, &IN.body, L);
    res.len = L;
    return res;
}
static inline STRING __right(STRING IN, SINT L){
    STRING res = __INIT_STRING;
    L = L < IN.len ? L : IN.len;
    memcpy(&res.body, &IN.body[IN.len - L], L);
    res.len = L;
    return res;
}
static inline STRING __mid(STRING IN, SINT L, SINT P){
    STRING res = __INIT_STRING;
    if(P <= IN.len){
	    P -= 1; /* now can be used as [index]*/
	    L = L + P <= IN.len ? L : IN.len - P;
	    memcpy(&res.body, &IN.body[P] , L);
        res.len = L;
    }
    return res;
}
static inline STRING __concat(SINT param_count, ...){
  va_list ap;
  UINT i;
  __strlen_t charcount = 0;
  STRING res = __INIT_STRING;

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
static inline STRING __insert(STRING IN1, STRING IN2, SINT P){
    STRING res = __INIT_STRING;
    __strlen_t to_copy;
    
    to_copy = P > IN1.len ? IN1.len : P - 1;
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
static inline STRING __delete(STRING IN, SINT L, SINT P){
    STRING res = __INIT_STRING;
    __strlen_t to_copy;
    
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
static inline STRING __replace(STRING IN1, STRING IN2, SINT L, SINT P){
    STRING res = __INIT_STRING;
    __strlen_t to_copy;
    
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



static inline UINT __pfind(STRING* IN1, STRING* IN2){
    UINT count1 = 0; /* offset of first matching char in IN1 */
    UINT count2 = 0; /* count of matching char */
    while(count1 + count2 < IN1->len && count2 < IN2->len)
    {
        if(IN1->body[count1 + count2] != IN2->body[count2++]){
            count1 += count2;
            count2 = 0;
        }        
    }
    return count2 == IN2->len -1 ? 0 : count1 + 1;
}
static inline UINT __find(STRING IN1, STRING IN2){
    return __pfind(&IN1, &IN2);
}

/***************/
/* Convertions */
/***************/
    /***************/
    /*  TO_STRING  */
    /***************/
static inline STRING __bool_to_string(BOOL IN)
{
    if(IN)
        return (STRING){4, "TRUE"};
    return (STRING){5,"FALSE"};
}
static inline STRING __bit_to_string(LWORD IN){
    STRING res = __INIT_STRING;
    res.len = snprintf(res.body, STR_MAX_LEN, "16#%llx", IN);
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
static inline STRING __real_to_string(LREAL IN){
    STRING res = __INIT_STRING;
    res.len = snprintf(res.body, STR_MAX_LEN, "%.10g", IN);
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
static inline STRING __sint_to_string(LINT IN){
    STRING res = __INIT_STRING;
    res.len = snprintf(res.body, STR_MAX_LEN, "%lld", IN);
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
static inline STRING __uint_to_string(ULINT IN){
    STRING res = __INIT_STRING;
    res.len = snprintf(res.body, STR_MAX_LEN, "%llu", IN);
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
    /***************/
    /* FROM_STRING */
    /***************/
static inline BOOL __string_to_bool(STRING IN){
    return IN.len == 5 ? !memcmp(&IN.body,"TRUE", IN.len) : 0;
}

static inline LINT __pstring_to_sint(STRING* IN){
    LINT res = 0;
    char tmp[STR_MAX_LEN];
    char tmp2[STR_MAX_LEN];
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
                fac = 1;
                shift = 0;
            }            
        }
    }
    return res;
}

static inline LINT __string_to_sint(STRING IN){
    return (LWORD)__pstring_to_sint(&IN);
}
static inline LWORD __string_to_bit(STRING IN){
    return (LWORD)__pstring_to_sint(&IN);
}
static inline ULINT __string_to_uint(STRING IN){
    return (ULINT)__pstring_to_sint(&IN);
}
static inline LREAL __string_to_real(STRING IN){
    /* search the dot */
    __strlen_t l = IN.len;
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
static inline TIME __int_to_time(LINT IN){
    return (TIME){IN, 0};
}

static inline TIME __real_to_time(LREAL IN){
    return (TIME){IN, (IN - (LINT)IN) * 1000000000};
}
static inline TIME __string_to_time(STRING IN){
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
    __strlen_t l = IN.len;
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
static inline LINT __time_to_int(TIME IN){
    return IN.tv_sec;
}
static inline STRING __time_to_string(TIME IN){
    /*t#5d14h12m18s3.5ms*/
    STRING res = __INIT_STRING;
    div_t days = div(IN.tv_sec ,86400);
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
    /* D#1984-06-25 */
    STRING res = __INIT_STRING;
    struct tm* broken_down_time;
    time_t seconds = IN.tv_sec;
    if (NULL == (broken_down_time = localtime(&seconds))){ /* get the UTC (GMT) broken down time */
        IEC_error();
        return (STRING){7,"D#ERROR"};
    }
    res.len = snprintf((char*)&res.body, STR_MAX_LEN, "D#%d-%2.2d-%2.2d", broken_down_time->tm_year + 1900, broken_down_time->tm_mon + 1, broken_down_time->tm_mday);
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
static inline STRING __tod_to_string(TOD IN){
    /* TOD#15:36:55.36 */
    STRING res = __INIT_STRING;
    struct tm* broken_down_time;
    time_t seconds = IN.tv_sec;
    if (NULL == (broken_down_time = localtime(&seconds))){ /* get the UTC (GMT) broken down time */
        IEC_error();
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
    /* DT#1984-06-25-15:36:55.36 */
    STRING res;
    struct tm* broken_down_time;
    time_t seconds = IN.tv_sec;
    if (NULL == (broken_down_time = localtime(&seconds))){ /* get the UTC (GMT) broken down time */
        IEC_error();
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
    /* BCD */
#define __bcd_digit(fac) 
static inline ULINT __bcd_to_uint(LWORD IN){
    return IN & 0xf +
           !(IN >>= 4) ? 0 : IN & 0xf * 10ULL + 
           !(IN >>= 4) ? 0 : IN & 0xf * 100ULL + 
           !(IN >>= 4) ? 0 : IN & 0xf * 1000ULL + 
           !(IN >>= 4) ? 0 : IN & 0xf * 10000ULL + 
           !(IN >>= 4) ? 0 : IN & 0xf * 100000ULL + 
           !(IN >>= 4) ? 0 : IN & 0xf * 1000000ULL + 
           !(IN >>= 4) ? 0 : IN & 0xf * 10000000ULL + 
           !(IN >>= 4) ? 0 : IN & 0xf * 100000000ULL + 
           !(IN >>= 4) ? 0 : IN & 0xf * 1000000000ULL + 
           !(IN >>= 4) ? 0 : IN & 0xf * 10000000000ULL + 
           !(IN >>= 4) ? 0 : IN & 0xf * 100000000000ULL + 
           !(IN >>= 4) ? 0 : IN & 0xf * 1000000000000ULL + 
           !(IN >>= 4) ? 0 : IN & 0xf * 10000000000000ULL + 
           !(IN >>= 4) ? 0 : IN & 0xf * 100000000000000ULL + 
           !(IN >>= 4) ? 0 : IN & 0xf * 1000000000000000ULL;
           
}
static inline LWORD __uint_to_bcd(ULINT IN){
    return (IN - (IN /= 10))|
           (IN - (IN /= 10)) << 4 |
           (IN - (IN /= 10)) << 8 |
           (IN - (IN /= 10)) << 12 |
           (IN - (IN /= 10)) << 16 |
           (IN - (IN /= 10)) << 20 |
           (IN - (IN /= 10)) << 24 |
           (IN - (IN /= 10)) << 28 |
           (IN - (IN /= 10)) << 32 |
           (IN - (IN /= 10)) << 36 |
           (IN - (IN /= 10)) << 40 |
           (IN - (IN /= 10)) << 44 |
           (IN - (IN /= 10)) << 48 |
           (IN - (IN /= 10)) << 52 |
           (IN - (IN /= 10)) << 56 |
           (IN - (IN /= 10)) << 60;
}

/**************/
/* Binary ops */
/**************/
#define __ror_(TYPENAME)\
static inline TYPENAME __ror_##TYPENAME( TYPENAME IN, USINT N){\
 N %= 8*sizeof(TYPENAME);\
 return (IN >> N) | (IN << 8*sizeof(TYPENAME)-N);\
}
/* Call previously defined macro for each ANY_NBIT */
ANY_NBIT(__ror_)

#define __rol_(TYPENAME)\
static inline TYPENAME __rol_##TYPENAME( TYPENAME IN, USINT N){\
 N %= 8*sizeof(TYPENAME);\
 return (IN << N) | (IN >> 8*sizeof(TYPENAME)-N);\
}
/* Call previously defined macro for each ANY_NBIT */
ANY_NBIT(__rol_)

/**************/
/* Selection  */
/**************/
	/**************/
	/*   limit    */
	/**************/

#define __limit_(TYPENAME)\
static inline TYPENAME __limit_##TYPENAME( TYPENAME MN, TYPENAME IN, TYPENAME MX){\
 return IN > MN ? IN < MX ? IN : MX : MN;\
}

/* Call previously defined macro for each concerned type */
ANY_NBIT(__limit_)
ANY_NUM(__limit_)

#define __limit_time(TYPENAME)\
static inline TIME __limit_##TYPENAME( TYPENAME MN, TYPENAME IN, TYPENAME MX){\
    return __TIME_CMP(IN, MN) > 0 ? /* IN>MN ?*/\
           __TIME_CMP(IN, MX) < 0 ? /* IN<MX ?*/\
           IN : MX : MN;\
}

/* Call previously defined macro for each concerned type */
ANY_DATE(__limit_time)
__limit_time(TIME)

static inline STRING __limit_STRING( STRING MN, STRING IN, STRING MX){
    return __STR_CMP(IN, MN) > 0 ? __STR_CMP(IN, MX) < 0 ? IN : MX : MN;
}

    /**************/
    /*     MAX    */
    /**************/
    
/* workaround for va-atgs limitation on shorter that int params */    
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

#define __extrem_(fname,TYPENAME, COND) \
static inline TYPENAME fname##TYPENAME( UINT param_count, TYPENAME op1, ...){\
  va_list ap;\
  UINT i;\
  \
  va_start (ap, op1);         /* Initialize the argument list.  */\
  \
  for (i = 0; i < param_count; i++){\
    TYPENAME tmp = va_arg (ap, VA_ARGS_##TYPENAME);\
    op1 = COND ? tmp : op1;\
  }\
  \
  va_end (ap);                  /* Clean up.  */\
  return op1;\
}

#define __max_num(TYPENAME) __extrem_(__max_,TYPENAME, op1 < tmp)
ANY_NBIT(__max_num)
ANY_NUM(__max_num)

__extrem_(__max_, STRING, __STR_CMP(op1,tmp) < 0)
#define __max_time(TYPENAME) __extrem_(__max_, TYPENAME, __TIME_CMP(op1, tmp) < 0)

/* Call previously defined macro for each concerned type */
ANY_DATE(__max_time)
__max_time(TIME)

    /**************/
    /*     MIN    */
    /**************/
#define __min_num(TYPENAME) __extrem_(__min, TYPENAME, op1 > tmp)
ANY_NBIT(__min_num)
ANY_NUM(__min_num)

__extrem_(__min, STRING, __STR_CMP(op1,tmp) > 0)

#define __min_time(TYPENAME) __extrem_(__min_, TYPENAME, __TIME_CMP(op1, tmp) > 0)

/* Call previously defined macro for each concerned type */
ANY_DATE(__min_time)
__min_time(TIME)

    /**************/
    /*     MUX    */
    /**************/
#define __mux_(TYPENAME) \
static inline TYPENAME __mux_##TYPENAME( UINT param_count, UINT K, ...){\
  va_list ap;\
  UINT i;\
  TYPENAME tmp = __INIT_##TYPENAME;\
  \
  va_start (ap, K);         /* Initialize the argument list.  */\
  \
  for (i = 0; i < param_count; i++){\
    if(K == i){\
        tmp = va_arg (ap, VA_ARGS_##TYPENAME);\
        va_end (ap);                  /* Clean up.  */\
        return tmp;\
    }else{\
        va_arg (ap, VA_ARGS_##TYPENAME);\
    }\
  }\
  \
  va_end (ap);                  /* Clean up.  */\
  return tmp;\
}

ANY(__mux_)

/**************/
/* Comparison */
/**************/

#define __compare_(fname,TYPENAME, COND) \
static inline BOOL fname##TYPENAME( UINT param_count, TYPENAME op1, ...){\
  va_list ap;\
  UINT i;\
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
#define __compare_time(fname, TYPENAME, TEST) __compare_(fname, TYPENAME, __TIME_CMP(op1, tmp) TEST 0)
#define __compare_string(fname, TEST) __compare_(fname, STRING, __STR_CMP(op1, tmp) TEST 0 )

    /**************/
    /*     GT     */
    /**************/

#define __gt_num(TYPENAME) __compare_num(__gt_, TYPENAME, > )
ANY_NBIT(__gt_num)
ANY_NUM(__gt_num)

#define __gt_time(TYPENAME) __compare_time(__gt_, TYPENAME, > )
ANY_DATE(__gt_time)
__gt_time(TIME)

__compare_string(__gt_, > )

    /**************/
    /*     GE     */
    /**************/

#define __ge_num(TYPENAME) __compare_num(__ge_, TYPENAME, >= )
ANY_BIT(__ge_num)
ANY_NUM(__ge_num)

#define __ge_time(TYPENAME) __compare_time(__ge_, TYPENAME, >= )
ANY_DATE(__ge_time)
__ge_time(TIME)

__compare_string(__ge_, >=)

    /**************/
    /*     EQ     */
    /**************/

#define __eq_num(TYPENAME) __compare_num(__eq_, TYPENAME, == )
ANY_BIT(__eq_num)
ANY_NUM(__eq_num)

#define __eq_time(TYPENAME) __compare_time(__eq_, TYPENAME, == )
ANY_DATE(__eq_time)
__eq_time(TIME)

__compare_string(__eq_, == )

    /**************/
    /*     LT     */
    /**************/

#define __lt_num(TYPENAME) __compare_num(__lt_, TYPENAME, < )
ANY_BIT(__lt_num)
ANY_NUM(__lt_num)

#define __lt_time(TYPENAME) __compare_time(__lt_, TYPENAME, < )
ANY_DATE(__lt_time)
__lt_time(TIME)

__compare_string(__lt_, < )

    /**************/
    /*     LE     */
    /**************/

#define __le_num(TYPENAME) __compare_num(__le_, TYPENAME, <= )
ANY_BIT(__le_num)
ANY_NUM(__le_num)

#define __le_time(TYPENAME) __compare_time(__le_, TYPENAME, <= )
ANY_DATE(__le_time)
__le_time(TIME)

__compare_string(__le_, <= )

    /**************/
    /*     NE     */
    /**************/

#define __ne_num(TYPENAME) __compare_num(__ne_, TYPENAME, != )
ANY_BIT(__ne_num)
ANY_NUM(__ne_num)

#define __ne_time(TYPENAME) __compare_time(__ne_, TYPENAME, != )
ANY_DATE(__ne_time)
__ne_time(TIME)

__compare_string(__ne_, != )


