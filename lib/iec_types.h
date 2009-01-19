#ifndef IEC_TYPES_H
#define IEC_TYPES_H

#include <limits.h>
#include <float.h>
#include <time.h>
#include <stdint.h>

/*********************/
/*  IEC Types defs   */
/*********************/

typedef uint8_t  IEC_BOOL;

typedef int8_t    IEC_SINT;
typedef int16_t   IEC_INT;
typedef int32_t   IEC_DINT;
typedef int64_t   IEC_LINT;

typedef uint8_t    IEC_USINT;
typedef uint16_t   IEC_UINT;
typedef uint32_t   IEC_UDINT;
typedef uint64_t   IEC_ULINT;

typedef uint8_t    IEC_BYTE;
typedef uint16_t   IEC_WORD;
typedef uint32_t   IEC_DWORD;
typedef uint64_t   IEC_LWORD;

typedef float    IEC_REAL;
typedef double   IEC_LREAL;


#if !defined __timespec_defined
# define __timespec_defined     1

struct timespec
  {
    long int tv_sec;            /* Seconds.  */
    long int tv_nsec;           /* Nanoseconds.  */
  };

#endif

typedef struct timespec IEC_TIME;
typedef struct timespec IEC_DATE;
typedef struct timespec IEC_DT;
typedef struct timespec IEC_TOD;

#ifndef STR_MAX_LEN
#define STR_MAX_LEN 127
#endif

#ifndef STR_LEN_TYPE
#define STR_LEN_TYPE int8_t
#endif

typedef STR_LEN_TYPE __strlen_t;
typedef struct {
    __strlen_t len;
    uint8_t body[STR_MAX_LEN];
} IEC_STRING;

#endif /*IEC_TYPES_H*/
