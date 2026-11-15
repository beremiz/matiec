#define __INITIAL_VALUE(...) __VA_ARGS__

// Types declaration macros

#define __DECLARE_DERIVED_TYPE(type, base)\
typedef base type;\
typedef __IEC_##base##_t __IEC_##type##_t;\
typedef __IEC_##base##_p __IEC_##type##_p;

#define __DECLARE_COMPLEX_STRUCT(type)\
typedef struct {\
  IEC_BYTE flags;\
  type value;\
} __IEC_##type##_t;\
\
typedef struct {\
  IEC_BYTE flags;\
  type *value;\
} __IEC_##type##_p;

#define __DECLARE_ENUMERATED_TYPE(type, ...)\
typedef enum {\
  __VA_ARGS__\
} type;\
__DECLARE_COMPLEX_STRUCT(type)

#define __DIM(...) [__VA_ARGS__]

#define __DECLARE_ARRAY_TYPE(type, base, dims)\
typedef struct {\
  __IEC_##base##_t table dims;\
} type;\
__DECLARE_COMPLEX_STRUCT(type)

#define __DECLARE_ARRAY_OF_COMPLEX_TYPE(type, base, dims)\
typedef struct {\
  base table dims;\
} type;\
__DECLARE_COMPLEX_STRUCT(type)

/* Alias an explicitly named IEC array type (e.g. MC_REAL_ARRAY) onto its structural
 * array datatype (e.g. __ARRAY_OF_LREAL_6), so it keeps the IEC name while remaining
 * the very same underlying C type (and thus assignment-compatible). */
#define __DECLARE_ARRAY_DERIVED_TYPE(type, base)\
typedef base type;\
typedef __IEC_##base##_t __IEC_##type##_t;\
typedef __IEC_##base##_p __IEC_##type##_p;

#define __DECLARE_STRUCT_TYPE(type, elements)\
typedef struct {\
  elements\
} type;\
__DECLARE_COMPLEX_STRUCT(type)

#define __DECLARE_REFTO_TYPE(type, name)\
typedef name type;\
__DECLARE_COMPLEX_STRUCT(type)

// variable declaration macros
#define __DECLARE_VAR(type, name)\
	__IEC_##type##_t name;
#define __DECLARE_COMPLEX_VAR(type, name)\
	type name;
#define __DECLARE_ARRAY_VAR(type, name)\
	__IEC_##type##_t name;
#define __DECLARE_STRUCT_VAR(type, name)\
	__IEC_##type##_t name;
#define __DECLARE_FB(type, name)\
	type##_data__ name;
#define __DECLARE_FB_TYPE(name, members)\
	typedef struct {\
	  members\
	} name##_data__;
#define __DECLARE_PROGRAM_TYPE(name, members)\
	typedef struct {\
	  members\
	} name##_data__;
#define __DECLARE_GLOBAL(type, domain, name)\
	__IEC_##type##_t domain##__##name;\
	static __IEC_##type##_t* GLOBAL__##name = &(domain##__##name);\
	GLOBAL_CAST void __INIT_GLOBAL_##name(type value) {\
		(*GLOBAL__##name).value = value;\
	}\
	GLOBAL_CAST IEC_BYTE __IS_GLOBAL_##name##_FORCED(void) {\
		return (*GLOBAL__##name).flags & __IEC_FORCE_FLAG;\
	}\
	GLOBAL_CAST type* __GET_GLOBAL_##name(void) {\
		return &((*GLOBAL__##name).value);\
	}
#define __DECLARE_GLOBAL_ARRAY(type, domain, name)\
	__DECLARE_GLOBAL(type, domain, name)
#define __DECLARE_GLOBAL_STRUCT(type, domain, name)\
	__DECLARE_GLOBAL(type, domain, name)
#define __DECLARE_GLOBAL_FB(type, domain, name)\
	type##_data__ domain##__##name;\
	static type##_data__* GLOBAL__##name = &(domain##__##name);\
	GLOBAL_CAST type##_data__* __GET_GLOBAL_##name(void) {\
		return &(*GLOBAL__##name);\
	}
#define __DECLARE_GLOBAL_LOCATION(type, location)\
	extern type *location;
#define __DECLARE_GLOBAL_LOCATED(type, resource, name)\
	__IEC_##type##_p resource##__##name;\
	static __IEC_##type##_p* GLOBAL__##name = &(resource##__##name);\
	GLOBAL_CAST void __INIT_GLOBAL_##name(type value) {\
		*((*GLOBAL__##name).value) = value;\
	}\
	GLOBAL_CAST IEC_BYTE __IS_GLOBAL_##name##_FORCED(void) {\
		return (*GLOBAL__##name).flags & __IEC_FORCE_FLAG;\
	}\
	GLOBAL_CAST type* __GET_GLOBAL_##name(void) {\
		return (*GLOBAL__##name).value;\
	}
#define __DECLARE_GLOBAL_LOCATED_ARRAY(type, resource, name)\
	__DECLARE_GLOBAL_LOCATED(type, resource, name)
#define __DECLARE_GLOBAL_LOCATED_STRUCT(type, resource, name)\
	__DECLARE_GLOBAL_LOCATED(type, resource, name)
#define __DECLARE_GLOBAL_PROTOTYPE(type, name)\
    extern type* __GET_GLOBAL_##name(void);
#define __DECLARE_GLOBAL_PROTOTYPE_FB(type, name)\
    extern type##_data__* __GET_GLOBAL_##name(void);
#define __DECLARE_EXTERNAL(type, name)\
	__IEC_##type##_p name;
#define __DECLARE_EXTERNAL_ARRAY(type, name)\
	__IEC_##type##_p name;
#define __DECLARE_EXTERNAL_STRUCT(type, name)\
	__IEC_##type##_p name;
#define __DECLARE_EXTERNAL_FB(type, name)\
	type##_data__* name;
#define __DECLARE_LOCATED(type, name)\
	__IEC_##type##_p name;
#define __DECLARE_LOCATED_ARRAY(type, name)\
	__IEC_##type##_p name;
#define __DECLARE_LOCATED_STRUCT(type, name)\
	__IEC_##type##_p name;
#define __DECLARE_PROGRAM_INSTANCE(type, resource, name)\
	type##_data__ resource##__##name;
#define __DECLARE_CONFIGURATION(configuration_name, tick_time)


// variable initialization macros
#define __INIT_RETAIN(name, retained)\
    name.flags |= retained?__IEC_RETAIN_FLAG:0;
#define __INIT_VAR(name, initial, retained)\
	name.value = initial;\
	__INIT_RETAIN(name, retained)
#define __INIT_GLOBAL(type, name, initial, retained)\
    {\
	    type temp = initial;\
	    __INIT_GLOBAL_##name(temp);\
	    __INIT_RETAIN((*GLOBAL__##name), retained)\
    }
#define __INIT_GLOBAL_FB(type, name, retained)\
	type##_init__(&(*GLOBAL__##name), retained);
#define __INIT_GLOBAL_LOCATED(domain, name, location, retained)\
	domain##__##name.value = location;\
	__INIT_RETAIN(domain##__##name, retained)
// Getter of the global is declared here, as POUs are also compiled where it
// isn't, e.g. config.c for globals of resources
#define __INIT_EXTERNAL(type, global, name, retained)\
    {\
		extern type* __GET_GLOBAL_##global(void);\
		name.value = __GET_GLOBAL_##global();\
		__INIT_RETAIN(name, retained)\
    }
#define __INIT_EXTERNAL_FB(type, global, name, retained)\
	{extern type##_data__* __GET_GLOBAL_##global(void);\
	name = __GET_GLOBAL_##global();}
#define __INIT_LOCATED(type, location, name, retained)\
	{\
		extern type *location;\
		name.value = location;\
		__INIT_RETAIN(name, retained)\
    }
#define __INIT_LOCATED_VALUE(name, initial)\
	*(name.value) = initial;


// variable getting macros
#define __GET_VAR(name, ...)\
	name.value __VA_ARGS__
#define __GET_EXTERNAL(name, ...)\
	((*(name.value)) __VA_ARGS__)
#define __GET_EXTERNAL_FB(name, ...)\
	__GET_VAR(((*name##_data__) __VA_ARGS__))
#define __GET_LOCATED(name, ...)\
	((*(name.value)) __VA_ARGS__)

#define __GET_VAR_BY_REF(name, ...)\
	(&(name.value __VA_ARGS__))
#define __GET_EXTERNAL_BY_REF(name, ...)\
	(&((*(name.value)) __VA_ARGS__))
#define __GET_EXTERNAL_FB_BY_REF(name, ...)\
	__GET_EXTERNAL_BY_REF(((*name##_data__) __VA_ARGS__))
#define __GET_LOCATED_BY_REF(name, ...)\
	(&((*(name.value)) __VA_ARGS__))

#define __GET_VAR_REF(name, ...)\
	(&(name.value __VA_ARGS__))
#define __GET_EXTERNAL_REF(name, ...)\
	(&((*(name.value)) __VA_ARGS__))
#define __GET_EXTERNAL_FB_REF(name, ...)\
	(&(__GET_VAR(((*name##_data__) __VA_ARGS__))))
#define __GET_LOCATED_REF(name, ...)\
	(&((*(name.value)) __VA_ARGS__))

#define __GET_VAR_DREF(name, ...)\
	(*(name.value __VA_ARGS__))
#define __GET_EXTERNAL_DREF(name, ...)\
	(*((*(name.value)) __VA_ARGS__))
#define __GET_EXTERNAL_FB_DREF(name, ...)\
	(*(__GET_VAR(((*name##_data__) __VA_ARGS__))))
#define __GET_LOCATED_DREF(name, ...)\
	(*((*(name.value)) __VA_ARGS__))


// variable setting macros
#define __SET_VAR(prefix, name, suffix, new_value)\
	if (!(prefix name.flags & __IEC_FORCE_FLAG)) prefix name.value suffix = new_value
#define __SET_EXTERNAL(prefix, name, suffix, new_value)\
	{extern IEC_BYTE __IS_GLOBAL_##name##_FORCED(void);\
    if (!(prefix name.flags & __IEC_FORCE_FLAG || __IS_GLOBAL_##name##_FORCED()))\
		(*(prefix name.value)) suffix = new_value;}
#define __SET_EXTERNAL_FB(prefix, name, suffix, new_value)\
	__SET_VAR(prefix, name, suffix, new_value)
#define __SET_LOCATED(prefix, name, suffix, new_value)\
	if (!(prefix name.flags & __IEC_FORCE_FLAG)) (*(prefix name.value)) suffix = new_value

