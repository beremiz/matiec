#ifndef __ACCESSOR_H
#define __ACCESSOR_H


// variable declaration macros
#define __DECLARE_VAR(type, name)\
	__IEC_##type##_t name;
#define __DECLARE_GLOBAL(type, resource, name)\
	__IEC_##type##_t resource##__##name;\
	static __IEC_##type##_t *GLOBAL__##name = &resource##__##name;\
	void __INIT_GLOBAL_##name(type value) {\
		(*GLOBAL__##name).value = value;\
	}\
	void __SET_GLOBAL_##name(type value) {\
		if (!((*GLOBAL__##name).flags & __IEC_FORCE_FLAG))\
			(*GLOBAL__##name).value = value;\
	}\
	type* __GET_GLOBAL_##name(void) {\
		return &((*GLOBAL__##name).value);\
	}
#define __DECLARE_GLOBAL_LOCATION(type, location)\
	extern type *location;
#define __DECLARE_GLOBAL_LOCATED(type, resource, name)\
	__IEC_##type##_p resource##__##name;\
	static __IEC_##type##_p *GLOBAL__##name = &resource##__##name;\
	void __INIT_GLOBAL_##name(type value) {\
		*((*GLOBAL__##name).value) = value;\
	}\
	void __SET_GLOBAL_##name(type value) {\
		if (!((*GLOBAL__##name).flags & __IEC_FORCE_FLAG))\
			*((*GLOBAL__##name).value) = value;\
	}\
	type* __GET_GLOBAL_##name(void) {\
		return (*GLOBAL__##name).value;\
	}
#define __DECLARE_EXTERNAL(type, name)\
	__IEC_##type##_p name;
#define __DECLARE_LOCATED(type, name)\
	__IEC_##type##_p name;


// variable initialization macros
#define __INIT_RETAIN(name, retained)\
    name.flags |= retained?__IEC_RETAIN_FLAG:0;
#define __INIT_VAR(name, initial, retained)\
	name.value = initial;\
	__INIT_RETAIN(name, retained)
#define __INIT_GLOBAL(name, initial, retained)\
	__INIT_GLOBAL_##name(initial);\
	__INIT_RETAIN((*GLOBAL__##name), retained)
#define __INIT_GLOBAL_LOCATED(resource, name, location, retained)\
	resource##__##name.value = location;\
	__INIT_RETAIN(resource##__##name, retained)
#define __INIT_EXTERNAL(type, global, name, retained)\
	name.value = __GET_GLOBAL_##global();\
    __INIT_RETAIN(name, retained)
#define __INIT_LOCATED(type, location, name, retained)\
	{extern type *location;\
	 name.value = location;\
	 __INIT_RETAIN(name, retained)}
#define __INIT_LOCATED_VALUE(name, initial)\
	*(name.value) = initial;


// variable getting macros
#define __GET_VAR(name, ...)\
	name.value __VA_ARGS__
#define __GET_EXTERNAL(name, ...)\
	((name.flags & __IEC_FORCE_FLAG) ? name.fvalue __VA_ARGS__ : *(name.value) __VA_ARGS__)
#define __GET_LOCATED(name, ...)\
	((name.flags & __IEC_FORCE_FLAG) ? name.fvalue __VA_ARGS__ : *(name.value) __VA_ARGS__)
#define __GET_VAR_BY_REF(name, ...)\
	((name.flags & __IEC_FORCE_FLAG) ? &(name.fvalue __VA_ARGS__) : &(name.value __VA_ARGS__))
#define __GET_EXTERNAL_BY_REF(name, ...)\
	((name.flags & __IEC_FORCE_FLAG) ? &(name.fvalue __VA_ARGS__) : &(*(name.value) __VA_ARGS__))
#define __GET_LOCATED_BY_REF(name, ...)\
	((name.flags & __IEC_FORCE_FLAG) ? &(name.fvalue __VA_ARGS__) : &(*(name.value) __VA_ARGS__))

// variable setting macros
#define __SET_VAR(name, new_value, ...)\
	if (!(name.flags & __IEC_FORCE_FLAG)) name.value __VA_ARGS__ = new_value
#define __SET_EXTERNAL(global, name, new_value)\
	if (!(name.flags & __IEC_FORCE_FLAG))\
		__SET_GLOBAL_##global(new_value)
#define __SET_COMPLEX_EXTERNAL(name, new_value, ...)\
	*(name.value) __VA_ARGS__ = new_value
#define __SET_LOCATED(name, new_value, ...)\
	if (!(name.flags & __IEC_FORCE_FLAG)) *(name.value) __VA_ARGS__ = new_value

#endif //__ACCESSOR_H
