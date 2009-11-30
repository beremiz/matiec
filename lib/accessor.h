#ifndef __ACCESSOR_H
#define __ACCESSOR_H

// variable declaration macros
#define __DECLARE_VAR(type, name)\
	type name;
#define __DECLARE_GLOBAL(type, resource, name)\
	type resource##__##name;\
	static type *GLOBAL__##name = &resource##__##name;\
	type __GET_GLOBAL_##name(void) {return *GLOBAL__##name;}\
	void __SET_GLOBAL_##name(type value) {*GLOBAL__##name = value;}
#define __DECLARE_GLOBAL_LOCATION(type, location)\
	extern type *location;
#define __DECLARE_GLOBAL_LOCATED(type, resource, name)\
	type *resource##__##name;\
	static type *GLOBAL__##name;\
	type __GET_GLOBAL_##name(void) {return *GLOBAL__##name;}\
	void __SET_GLOBAL_##name(type value) {*GLOBAL__##name = value;}
#define __DECLARE_EXTERNAL(type, name)\
	type *name;
#define __DECLARE_LOCATED(type, name)\
	type *name;


// variable initialization macros
#define __INIT_VAR(name, initial)\
	name = initial;
#define __INIT_GLOBAL(name, initial)\
	*GLOBAL__##name = initial;
#define __INIT_GLOBAL_LOCATED(resource, name, location)\
	resource##__##name = location;\
    GLOBAL__##name = location;
#define __INIT_EXTERNAL(type, global, name)\
	{extern type *GLOBAL__##global;\
	 name = GLOBAL__##global;}
#define __INIT_LOCATED(type, location, name)\
	{extern type *location;\
	 name = location;}
#define __INIT_LOCATED_VALUE(name, initial)\
	*name = initial;


// variable getting macros
#define __GET_VAR(name)\
	name
#define __GET_EXTERNAL(name)\
	__GET_GLOBAL_##name()
#define __GET_LOCATED(name)\
	*(name)
#define __GET_VAR_BY_REF(name)\
	&(name)
#define __GET_EXTERNAL_BY_REF(name)\
	GLOBAL__##name
#define __GET_LOCATED_BY_REF(name)\
	name

// variable setting macros
#define __SET_VAR(name, new_value)\
	name = new_value
#define __SET_EXTERNAL(name, new_value)\
	__SET_GLOBAL_##name(value)
#define __SET_LOCATED(name, new_value)\
	*(name) = value

#endif //__ACCESSOR_H
