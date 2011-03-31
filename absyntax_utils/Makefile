# include the system specific Makefile
include ../Makefile.$(shell uname)




SEARCH_UTIL_FILES  = absyntax_utils.o
SEARCH_UTIL_FILES += search_expression_type.o
SEARCH_UTIL_FILES += decompose_var_instance_name.o
SEARCH_UTIL_FILES += function_call_iterator.o
SEARCH_UTIL_FILES += function_call_param_iterator.o
SEARCH_UTIL_FILES += function_param_iterator.o
SEARCH_UTIL_FILES += search_base_type.o
SEARCH_UTIL_FILES += search_constant_type.o
SEARCH_UTIL_FILES += search_fb_instance_decl.o
SEARCH_UTIL_FILES += search_fb_typedecl.o
SEARCH_UTIL_FILES += search_il_operand_type.o
SEARCH_UTIL_FILES += search_varfb_instance_type.o
SEARCH_UTIL_FILES += search_var_instance_decl.o
SEARCH_UTIL_FILES += spec_init_separator.o
SEARCH_UTIL_FILES += type_initial_value.o
SEARCH_UTIL_FILES += add_en_eno_param_decl.o
SEARCH_UTIL_FILES += get_sizeof_datatype.o
SEARCH_UTIL_FILES += get_function_type.o


default: all

all: $(SEARCH_UTIL_FILES)



clean:
	rm -f *.o Makefile.depend


CXXFLAGS += -I. -I../*



Makefile.depend depend:
	$(CXX) -MM -MG -I. *.cc \
	  | sed 's/:/ Makefile.depend:/' > Makefile.depend

include Makefile.depend
