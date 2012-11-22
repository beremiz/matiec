#ifndef IEC_TYPES_H
#define IEC_TYPES_H

#include <limits.h>
#include <float.h>
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

typedef struct {
    long int tv_sec;            /* Seconds.  */
    long int tv_nsec;           /* Nanoseconds.  */
} /* __attribute__((packed)) */ IEC_TIMESPEC;  /* packed is gcc specific! */

typedef IEC_TIMESPEC IEC_TIME;
typedef IEC_TIMESPEC IEC_DATE;
typedef IEC_TIMESPEC IEC_DT;
typedef IEC_TIMESPEC IEC_TOD;

#ifndef STR_MAX_LEN
#define STR_MAX_LEN 126
#endif

#ifndef STR_LEN_TYPE
#define STR_LEN_TYPE int8_t
#endif

typedef STR_LEN_TYPE __strlen_t;
typedef struct {
    __strlen_t len;
    uint8_t body[STR_MAX_LEN];
} /* __attribute__((packed)) */ IEC_STRING;  /* packed is gcc specific! */

#endif /*IEC_TYPES_H*/
