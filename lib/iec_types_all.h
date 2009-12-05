#ifndef IEC_TYPES_ALL_H
#define IEC_TYPES_ALL_H

#include "iec_std_lib_generated.h"

/*********************/
/*  IEC Types defs   */
/*********************/

/* Include non windows.h clashing typedefs */
#include "iec_types.h"

#define TRUE 1
#define FALSE 0

#define __DEBUG_FLAG 1
#define __FORCE_FLAG 2
#define __RETAIN_FLAG 4

#define __DECLARE_IEC_TYPE(type)\
typedef IEC_##type type;\
\
typedef struct {\
  IEC_##type value;\
  IEC_BYTE flags;\
} __IEC_##type##_t;\
\
typedef struct {\
  IEC_##type *value;\
  IEC_BYTE flags;\
  IEC_##type fvalue;\
} __IEC_##type##_p;

#define __DECLARE_DERIVED_TYPE(base, type)\
typedef base type;\
typedef __IEC_##base##_t __IEC_##type##_t;

#define __DECLARE_COMPLEX_STRUCT(type)\
typedef struct {\
  type value;\
  IEC_BYTE flags;\
} __IEC_##type##_t;\
\
typedef struct {\
  type *value;\
  IEC_BYTE flags;\
} __IEC_##type##_p;

#define __DECLARE_ARRAY_TYPE(base, type, size)\
typedef base type size;\
__DECLARE_COMPLEX_STRUCT(type);

#define __DECLARE_STRUCT_TYPE(elements, type)\
typedef elements type;\
__DECLARE_COMPLEX_STRUCT(type);

/* Those typdefs clash with windows.h */
/* i.e. this file cannot be included aside windows.h */
ANY(__DECLARE_IEC_TYPE)


/*
typedef IEC_BOOL  BOOL;

typedef IEC_SINT    SINT;
typedef IEC_INT   INT;
typedef IEC_DINT   DINT;
typedef IEC_LINT   LINT;

typedef IEC_USINT    USINT;
typedef IEC_UINT   UINT;
typedef IEC_UDINT   UDINT;
typedef IEC_ULINT   ULINT;

typedef IEC_BYTE    BYTE;
typedef IEC_WORD   WORD;
typedef IEC_DWORD   DWORD;
typedef IEC_LWORD   LWORD;

typedef IEC_REAL    REAL;
typedef IEC_LREAL   LREAL;

typedef IEC_TIME TIME;
typedef IEC_DATE DATE;
typedef IEC_DT DT;
typedef IEC_TOD TOD;

typedef IEC_STRING STRING;
*/

typedef struct {
  __IEC_BOOL_t state;     // current step state. 0 : inative, 1: active
  BOOL prev_state;  // previous step state. 0 : inative, 1: active
  TIME elapsed_time;  // time since step is active
} STEP;

typedef struct {
  BOOL stored;  // action storing state. 0 : not stored, 1: stored
  BOOL state; // current action state. 0 : inative, 1: active
  BOOL set;   // set have been requested (reset each time the body is evaluated)
  BOOL reset; // reset have been requested (reset each time the body is evaluated)
  TIME set_remaining_time;    // time before set will be requested
  TIME reset_remaining_time;  // time before reset will be requested
} ACTION;

/* Extra debug types for SFC */
#define ANY_SFC(DO) DO(STEP) DO(TRANSITION) DO(ACTION)

/* Enumerate native types */
#define __decl_enum_type(TYPENAME) TYPENAME##_ENUM,
typedef enum{
  ANY(__decl_enum_type)
  ANY_SFC(__decl_enum_type)
  /*TODO handle custom types*/
} __IEC_types_enum;

/* Get size of type from its number */
#define __decl_size_case(TYPENAME) case TYPENAME##_ENUM: return sizeof(TYPENAME);
#define __decl_size_case_force_BOOL(TYPENAME) case TYPENAME##_ENUM: return sizeof(BOOL);
static inline USINT __get_type_enum_size(__IEC_types_enum t){
 switch(t){
  ANY(__decl_size_case)
  /* size do not correspond to real struct.
   * only a bool is used to represent state*/
  ANY_SFC(__decl_size_case_force_BOOL)
  /*TODO handle custom types*/
 }
 return 0;
}

/* Get name of type from its number */
#define __decl_typename_case(TYPENAME) case TYPENAME##_ENUM: return #TYPENAME ;
static inline const char* __get_type_enum_name(__IEC_types_enum t){
 switch(t){
  ANY(__decl_typename_case)
  /* size do not correspond to real struct.
   * only a bool is used to represent state*/
  ANY_SFC(__decl_typename_case)
  /*TODO handle custom types*/
 }
 return 0;
}


#endif /*IEC_TYPES_ALL_H*/
