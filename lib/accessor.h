#ifndef __ACCESSOR_H
#define __ACCESSOR_H


// variable declaration macros
#define __DECLARE_VAR(type, name)\
	__IEC_##type##_t name;
#define __DECLARE_GLOBAL(type, resource, name)\
	__IEC_##type##_t resource##__##name;\
	static __IEC_##type##_t *GLOBAL__##name = &resource##__##name;
#define __DECLARE_GLOBAL_LOCATION(type, location)\
	extern type *location;
#define __DECLARE_GLOBAL_LOCATED(type, resource, name)\
	__IEC_##type##_p resource##__##name;\
	static __IEC_##type##_p *GLOBAL__##name;
#define __DECLARE_EXTERNAL(type, name)\
	__IEC_##type##_p name;
#define __DECLARE_LOCATED(type, name)\
	__IEC_##type##_p name;


// variable initialization macros
#define __INIT_STRUCT(name, initial, retained)\
    name.value = initial;\
	name.flags |= retained?RETAIN_FLAG:0;
#define __INIT_VAR(name, initial, retained)\
	__INIT_STRUCT(name, initial, retained)
#define __INIT_GLOBAL(name, initial, retained)\
	__INIT_STRUCT((*GLOBAL__##name), initial, retained)
#define __INIT_GLOBAL_LOCATED(resource, name, location, retained)\
	__INIT_STRUCT(resource##__##name, location, retained)
#define __INIT_EXTERNAL(type, global, name, retained)\
	{extern __IEC_##type##_t *GLOBAL__##global;\
	 __INIT_STRUCT(name, &((*GLOBAL__##global).value), retained)}
#define __INIT_LOCATED(type, location, name, retained)\
	{extern type *location;\
	 __INIT_STRUCT(name, location, retained)}
#define __INIT_LOCATED_VALUE(name, initial)\
	*(name.value) = initial;


// variable getting macros
#define __GET_VAR(name, ...)\
	name.value __VA_ARGS__
#define __GET_EXTERNAL(name)\
	name.flags & FORCE_FLAG ? name.fvalue : *(name.value)
#define __GET_LOCATED(name)\
	name.flags & FORCE_FLAG ? name.fvalue : *(name.value)
#define __GET_VAR_BY_REF(name)\
	&(name)
#define __GET_EXTERNAL_BY_REF(name)\
	name.value
#define __GET_LOCATED_BY_REF(name)\
	name.value

// variable setting macros
#define __SET_VAR(name, new_value, ...)\
	if (!(name.flags & FORCE_FLAG)) name.value __VA_ARGS__ = new_value
#define __SET_EXTERNAL(name, new_value)\
	if (!(name.flags & FORCE_FLAG)) *(name.value) = new_value
#define __SET_LOCATED(name, new_value)\
	if (!(name.flags & FORCE_FLAG)) *(name.value) = new_value

#endif //__ACCESSOR_H
