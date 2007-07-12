/****
 * IEC 61131-3 standard function lib
 */

#include <limits.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "iec_std_lib_generated.h"

/*****************/
/*  Types defs   */
/*****************/

typedef u_int8_t  BOOL;

#define TRUE 1
#define FALSE 0

typedef int8_t    SINT;
typedef int16_t   INT;
typedef int32_t   DINT;
typedef int64_t   LINT;

typedef u_int8_t    USINT;
typedef u_int16_t   UINT;
typedef u_int32_t   UDINT;
typedef u_int64_t   ULINT;

typedef u_int8_t    BYTE;
typedef u_int16_t   WORD;
typedef u_int32_t   DWORD;
typedef u_int64_t   LWORD;

typedef float    REAL;
typedef double   LREAL;

typedef struct timespec TIME;
typedef struct timespec DATE;
typedef struct timespec DT;
typedef struct timespec TOD;

#define __TIME_CMP(t1, t2) (t2.tv_sec == t1.tv_sec ? t2.tv_nsec - t1.tv_nsec : t1.tv_sec - t2.tv_sec) 

#define STR_MAX_LEN 40
typedef int8_t __strlen_t;
typedef struct {
    __strlen_t len;
    u_int8_t body[STR_MAX_LEN];
} STRING;

#define __STR_CMP(str1, str2) memcmp((char*)&str1.body,(char*)&str2.body, str1.len < str2.len ? str1.len : str2.len)


/* TODO
typedef struct {
    __strlen_t len;
    u_int16_t body[STR_MAX_LEN];
} WSTRING;
*/

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
void IEC_error(void) {
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
inline TIME __date_and_time_to_time_of_day(TIME IN){
  return (TIME){IN.tv_sec % 86400, IN.tv_nsec};
}
inline TIME __date_and_time_to_date(TIME IN){
  return (TIME){IN.tv_sec - (IN.tv_sec % (24*60*60)), 0};
}
inline TIME __time_add(TIME IN1, TIME IN2){
  TIME res ={IN1.tv_sec + IN2.tv_sec,
             IN1.tv_nsec + IN2.tv_nsec };
  __normalize_timespec(&res);
  return res;
}
inline TIME __time_sub(TIME IN1, TIME IN2){
  TIME res ={IN1.tv_sec - IN2.tv_sec,
             IN1.tv_nsec - IN2.tv_nsec };
  __normalize_timespec(&res);
  return res;
}
inline TIME __time_mul(TIME IN1, LREAL IN2){
  LREAL s_f = IN1.tv_sec * IN2;
  time_t s = s_f;
  div_t ns = div((LREAL)IN1.tv_nsec * IN2, 1000000000);
  TIME res = {s + ns.quot,
              ns.rem + (s_f - s) * 1000000000 };
  __normalize_timespec(&res);
  return res;
}
inline TIME __time_div(TIME IN1, LREAL IN2){
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
inline UINT __len(STRING IN){
    return IN.len;
}
inline STRING __left(STRING IN, SINT L){
    STRING res = {0,};
    memcpy(&res.body, &IN.body, L < res.len ? L : res.len);
    return res;
}
inline STRING __right(STRING IN, SINT L){
    STRING res = {0,};
    L = L < IN.len ? L : IN.len;
    memcpy(&res, &IN.body[IN.len - L], L);
    res.len = L;
    return res;
}
inline STRING __mid(STRING IN, SINT L, SINT P){
    STRING res = {0,};
    if(P <= IN.len){
	    P -= 1; /* now can be used as [index]*/
	    L = L + P <= IN.len ? L : IN.len - P;
	    memcpy(&res, &IN.body[P] , L);
        res.len = L;
    }
    return res;
}
inline STRING __concat(SINT param_count, ...){
  va_list ap;
  UINT i;
  __strlen_t charcount = 0;
  STRING res = {0,};

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
inline STRING __insert(STRING IN1, STRING IN2, SINT P){
    STRING res = {0,};
    __strlen_t to_copy;
    
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
inline STRING __delete(STRING IN, SINT L_value, SINT P){
    STRING res = {0,};
    __strlen_t to_copy;
    
    to_copy = P > IN.len ? IN.len : P;
    memcpy(&res.body, &IN.body , to_copy);
    P = res.len = to_copy;

    to_copy = IN.len - P;
    memcpy(&res.body[res.len], &IN.body[P] , to_copy);
    res.len += to_copy;

    return res;
}
inline STRING __replace(STRING IN1, STRING IN2, SINT L, SINT P){
    STRING res = {0,};
    __strlen_t to_copy;
    
    to_copy = P > IN1.len ? IN1.len : P;
    memcpy(&res.body, &IN1.body , to_copy);
    P = res.len = to_copy;
    
    to_copy = IN2.len + res.len > STR_MAX_LEN ? STR_MAX_LEN - res.len : IN2.len;
    memcpy(&res.body[res.len], &IN2.body , to_copy);
    res.len += to_copy;

    to_copy = res.len < IN1.len ? IN1.len - res.len : 0;
    memcpy(&res.body[res.len], &IN1.body[res.len] , to_copy);
    res.len += to_copy;

    return res;
}



inline UINT __pfind(STRING* IN1, STRING* IN2){
    UINT count1 = 0;
    UINT count2 = 0;
    while(count1 + count2 < IN1->len && count2 < IN2->len)
    {
        if(IN1->body[count1 + count2] != IN2->body[count2++]){
            count1 += count2;
            count2 = 0;
        }        
    }
    return count2 == IN2->len ? 0 : count1;
}
inline UINT __find(STRING IN1, STRING IN2){
    return __pfind(&IN1, &IN2);
}

/***************/
/* Convertions */
/***************/
    /***************/
    /*  TO_STRING  */
    /***************/
inline STRING __bool_to_string(BOOL IN)
{
    if(IN)
        return (STRING){4, "TRUE"};
    return (STRING){5,"FALSE"};
}
inline STRING __bit_to_string(LWORD IN){
    STRING res = {0,};
    res.len = snprintf(res.body, STR_MAX_LEN, "16#%llx", IN);
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
inline STRING __real_to_string(LREAL IN){
    STRING res = {0,};
    res.len = snprintf(res.body, STR_MAX_LEN, "%g", IN);
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
inline STRING __sint_to_string(LINT IN){
    STRING res = {0,};
    res.len = snprintf(res.body, STR_MAX_LEN, "%lld", IN);
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
inline STRING __uint_to_string(ULINT IN){
    STRING res = {0,};
    res.len = snprintf(res.body, STR_MAX_LEN, "16#%llu", IN);
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
    /***************/
    /* FROM_STRING */
    /***************/
inline BOOL __string_to_bool(STRING IN){
    return IN.len == 5 ? !memcmp(&IN.body,"TRUE", IN.len) : 0;
}

inline LINT __pstring_to_sint(STRING* IN){
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
    }else if(IN->body[0]=='1' && IN->body[1]=='6' && IN->body[1]=='#'){
        /* 16#1234_5678_9abc_DEFG */
        for(l = IN->len - 1; l >= 3 && shift < 64; l--)
        {
            char c = IN->body[l];
            if( c >= '0' && c <= '9'){
                res |= ( c - '0') << shift;
                shift += 4;
            }else if( c >= 'a' && c <= 'f'){
                res |= ( c - 'a' + 10 ) << shift;
                shift += 4;
            }else if( c >= 'A' && c <= 'F'){
                res |= ( c - 'A' + 10 ) << shift;
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
            }
        }
    }
    return res;
}

inline LINT __string_to_sint(STRING IN){
    return (LWORD)__pstring_to_sint(&IN);
}
inline LWORD __string_to_bit(STRING IN){
    return (LWORD)__pstring_to_sint(&IN);
}
inline ULINT __string_to_uint(STRING IN){
    return (ULINT)__pstring_to_sint(&IN);
}
inline LREAL __string_to_real(STRING IN){
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
inline TIME __int_to_time(LINT IN){
    return (TIME){IN, 0};
}

inline TIME __real_to_time(LREAL IN){
    return (TIME){IN, (IN - (LINT)IN) * 1000000000};
}
inline TIME __string_to_time(STRING IN){
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
inline LREAL __time_to_real(TIME IN){
    return (LREAL)IN.tv_sec + ((LREAL)IN.tv_nsec/1000000000);
}
inline LINT __time_to_int(TIME IN){
    return IN.tv_sec;
}
inline STRING __time_to_string(TIME IN){
    /*t#5d14h12m18s3.5ms*/
    STRING res = {0,};
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
                    res.len = snprintf((char*)&res.body, STR_MAX_LEN, "T#%dd%dh%dm%ds%gms", days.quot, hours.quot, minuts.quot, minuts.rem, IN.tv_nsec / 1000000);
                }
            }
        }
    }
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
inline STRING __date_to_string(DATE IN){
    /* D#1984-06-25 */
    STRING res = {0,};
    struct tm broken_down_time;
    time_t seconds = IN.tv_sec;
    if (NULL == gmtime_r(&seconds, &broken_down_time)){ /* get the UTC (GMT) broken down time */
        IEC_error();
        return (STRING){7,"D#ERROR"};
    }
    res.len = snprintf((char*)&res.body, STR_MAX_LEN, "D#%d-%2.2d-%2.2d", broken_down_time.tm_year, broken_down_time.tm_mon, broken_down_time.tm_mday);
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
inline STRING __tod_to_string(TOD IN){
    /* TOD#15:36:55.36 */
    STRING res = {0,};
    struct tm broken_down_time;
    time_t seconds = IN.tv_sec;
    if (NULL == gmtime_r(&seconds, &broken_down_time)){ /* get the UTC (GMT) broken down time */
        IEC_error();
        return (STRING){9,"TOD#ERROR"};
    }
    if(IN.tv_nsec == 0){
        res.len = snprintf((char*)&res.body, STR_MAX_LEN, "TOD#%2.2d:%2.2d:%d", broken_down_time.tm_hour, broken_down_time.tm_min, broken_down_time.tm_sec);
    }else{
        res.len = snprintf((char*)&res.body, STR_MAX_LEN, "TOD#%2.2d:%2.2d:%g", broken_down_time.tm_hour, broken_down_time.tm_min, (LREAL)broken_down_time.tm_sec + (LREAL)IN.tv_nsec / 1000000);
    }
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
inline STRING __dt_to_string(DT IN){
    /* DT#1984-06-25-15:36:55.36 */
    STRING res;
    struct tm broken_down_time;
    time_t seconds = IN.tv_sec;
    if (NULL == gmtime_r(&seconds, &broken_down_time)){ /* get the UTC (GMT) broken down time */
        IEC_error();
        return (STRING){8,"DT#ERROR"};
    }
    if(IN.tv_nsec == 0){
        res.len = snprintf((char*)&res.body, STR_MAX_LEN, "DT#%d-%2.2d-%2.2d-%2.2d:%2.2d:%d",
                 broken_down_time.tm_year,
                 broken_down_time.tm_mon,
                 broken_down_time.tm_mday,
                 broken_down_time.tm_hour,
                 broken_down_time.tm_min,
                 broken_down_time.tm_sec);
    }else{
        res.len = snprintf((char*)&res.body, STR_MAX_LEN, "DT#%d-%2.2d-%2.2d-%2.2d:%2.2d:%d",
                 broken_down_time.tm_year,
                 broken_down_time.tm_mon,
                 broken_down_time.tm_mday,
                 broken_down_time.tm_hour,
                 broken_down_time.tm_min,
                 (LREAL)broken_down_time.tm_sec + ((LREAL)IN.tv_nsec / 1000000));
    }
    if(res.len > STR_MAX_LEN) res.len = STR_MAX_LEN;
    return res;
}
    /* BCD */
inline ULINT __bcd_to_uint(LWORD IN){
    return IN & 0xf +
           ((IN >>= 4) & 0xf) * 10 + 
           ((IN >>= 4) & 0xf) * 100 + 
           ((IN >>= 4) & 0xf) * 1000 + 
           ((IN >>= 4) & 0xf) * 10000 + 
           ((IN >>= 4) & 0xf) * 100000 + 
           ((IN >>= 4) & 0xf) * 1000000 + 
           ((IN >>= 4) & 0xf) * 10000000 + 
           ((IN >>= 4) & 0xf) * 100000000 + 
           ((IN >>= 4) & 0xf) * 1000000000 + 
           ((IN >>= 4) & 0xf) * 10000000000 + 
           ((IN >>= 4) & 0xf) * 100000000000 + 
           ((IN >>= 4) & 0xf) * 1000000000000 + 
           ((IN >>= 4) & 0xf) * 10000000000000 + 
           ((IN >>= 4) & 0xf) * 100000000000000 + 
           ((IN >>= 4) & 0xf) * 1000000000000000;
}
inline LWORD __uint_to_bcd(ULINT IN){
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
inline TYPENAME __ror_##TYPENAME( TYPENAME IN, USINT N){\
 N %= 8*sizeof(TYPENAME);\
 return (IN >> N) | (IN << 8*sizeof(TYPENAME)-N);\
}
/* Call previously defined macro for each ANY_NBIT */
ANY_NBIT(__ror_)

#define __rol_(TYPENAME)\
inline TYPENAME __rol_##TYPENAME( TYPENAME IN, USINT N){\
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
inline TYPENAME __limit_##TYPENAME( TYPENAME MN, TYPENAME IN, TYPENAME MX){\
 return IN > MN ? IN < MX ? IN : MX : MN;\
}

/* Call previously defined macro for each concerned type */
ANY_NBIT(__limit_)
ANY_NUM(__limit_)

#define __limit_time(TYPENAME)\
inline TIME __limit_##TYPENAME( TYPENAME MN, TYPENAME IN, TYPENAME MX){\
    return __TIME_CMP(IN, MN) > 0 ? /* IN>MN ?*/\
           __TIME_CMP(IN, MX) < 0 ? /* IN<MX ?*/\
           IN : MX : MN;\
}

/* Call previously defined macro for each concerned type */
ANY_DATE(__limit_time)
__limit_time(TIME)

inline STRING __limit_STRING( STRING MN, STRING IN, STRING MX){
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
inline TYPENAME fname##TYPENAME( UINT param_count, TYPENAME op1, ...){\
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
inline TYPENAME __mux_##TYPENAME( UINT param_count, UINT K, TYPENAME op1, ...){\
  va_list ap;\
  UINT i;\
  \
  va_start (ap, op1);         /* Initialize the argument list.  */\
  \
  for (i = 0; i < param_count; i++){\
    if(K == i){\
        TYPENAME tmp = va_arg (ap, VA_ARGS_##TYPENAME);\
        va_end (ap);                  /* Clean up.  */\
        return tmp;\
    }else{\
        va_arg (ap, VA_ARGS_##TYPENAME);\
    }\
  }\
  \
  va_end (ap);                  /* Clean up.  */\
  return op1;\
}

ANY(__mux_)

/**************/
/* Comparison */
/**************/

#define __compare_(fname,TYPENAME, COND) \
inline BOOL fname##TYPENAME( UINT param_count, TYPENAME op1, ...){\
  va_list ap;\
  UINT i;\
  \
  va_start (ap, op1);         /* Initialize the argument list.  */\
  \
  for (i = 0; i < param_count; i++){\
    TYPENAME tmp = va_arg (ap, VA_ARGS_##TYPENAME);\
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
ANY_NBIT(__ge_num)
ANY_NUM(__ge_num)

#define __ge_time(TYPENAME) __compare_time(__ge_, TYPENAME, >= )
ANY_DATE(__ge_time)
__ge_time(TIME)

__compare_string(__ge_, >=)

    /**************/
    /*     EQ     */
    /**************/

#define __eq_num(TYPENAME) __compare_num(__eq_, TYPENAME, == )
ANY_NBIT(__eq_num)
ANY_NUM(__eq_num)

#define __eq_time(TYPENAME) __compare_time(__eq_, TYPENAME, == )
ANY_DATE(__eq_time)
__eq_time(TIME)

__compare_string(__eq_, == )

    /**************/
    /*     LT     */
    /**************/

#define __lt_num(TYPENAME) __compare_num(__lt_, TYPENAME, < )
ANY_NBIT(__lt_num)
ANY_NUM(__lt_num)

#define __lt_time(TYPENAME) __compare_time(__lt_, TYPENAME, < )
ANY_DATE(__lt_time)
__lt_time(TIME)

__compare_string(__lt_, < )

    /**************/
    /*     LE     */
    /**************/

#define __le_num(TYPENAME) __compare_num(__le_, TYPENAME, <= )
ANY_NBIT(__le_num)
ANY_NUM(__le_num)

#define __le_time(TYPENAME) __compare_time(__le_, TYPENAME, <= )
ANY_DATE(__le_time)
__le_time(TIME)

__compare_string(__le_, <= )

    /**************/
    /*     NE     */
    /**************/

#define __ne_num(TYPENAME) __compare_num(__ne_, TYPENAME, != )
ANY_NBIT(__ne_num)
ANY_NUM(__ne_num)

#define __ne_time(TYPENAME) __compare_time(__ne_, TYPENAME, != )
ANY_DATE(__ne_time)
__ne_time(TIME)

__compare_string(__ne_, != )


