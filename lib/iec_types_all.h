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

#define __IEC_DEBUG_FLAG 0x01
#define __IEC_FORCE_FLAG 0x02
#define __IEC_RETAIN_FLAG 0x04

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
typedef struct {\
  base table size;\
} type;\
__DECLARE_COMPLEX_STRUCT(type);

#define __DECLARE_STRUCT_TYPE(elements, type)\
typedef elements type;\
__DECLARE_COMPLEX_STRUCT(type);

/* Those typdefs clash with windows.h */
/* i.e. this file cannot be included aside windows.h */
ANY(__DECLARE_IEC_TYPE)

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
#define __decl_enum_pointer(TYPENAME) TYPENAME##_P_ENUM,
#define __decl_enum_output(TYPENAME) TYPENAME##_O_ENUM,
typedef enum{
  ANY(__decl_enum_type)
  ANY(__decl_enum_pointer)
  ANY(__decl_enum_output)
  /* SFC specific types are never external or global */
  UNKNOWN_ENUM
} __IEC_types_enum;

/* Get size of type from its number */
#define __decl_size_case(TYPENAME) \
	case TYPENAME##_ENUM:\
	case TYPENAME##_O_ENUM:\
	case TYPENAME##_P_ENUM:\
		return sizeof(TYPENAME);
static inline USINT __get_type_enum_size(__IEC_types_enum t){
 switch(t){
  ANY(__decl_size_case)
  /* size do not correspond to real struct.
   * only a bool is used to represent state*/
  default:
	  return 0;
 }
 return 0;
}

#endif /*IEC_TYPES_ALL_H*/
