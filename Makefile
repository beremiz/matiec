# include the system specific Makefile
include Makefile.$(shell uname)

default: all

all: iec2c iec2iec

install: all
	install -d $(INSTALL_PREDIR)/$(INSTALL_BINDIR)/ 
	install -d $(INSTALL_PREDIR)/$(IECLIBDIR)/
	install iec2c    $(INSTALL_PREDIR)/$(INSTALL_BINDIR)/
	install lib/*.txt $(INSTALL_PREDIR)/$(IECLIBDIR)/
#	install iec2iec   $(INSTALL_PREDIR)/$(INSTALL_BINDIR)/


uninstall:
	rm -f $(INSTALL_PREDIR)/$(INSTALL_BINDIR)/iec2c
	rm -f $(INSTALL_PREDIR)/$(INSTALL_BINDIR)/iec2iec
	for ff in `cd lib; ls *.txt; cd ..` do echo $$ff done
#	for ff in `cd lib; ls *.txt; cd ..` do rm -f $(INSTALL_PREDIR)/$(IECLIBDIR)/$$ff done


clean:
	-rm -f iec2iec iec2c *.o absyntax/*.o
	echo > Makefile.depend
# make something everywhere (ie, in all Makefiles that have that target)
	find . -depth -mindepth 2 -maxdepth 2 -name Makefile -printf %h\\n | xargs -i make -C{} $@

CXXFLAGS += -I.

LIBS  = absyntax/absyntax.o absyntax/visitor.o
LIBS += stage1_2/stage1_2.o stage1_2/iec.y.o stage1_2/iec.flex.o
LIBS += stage3/stage3.o
LIBS += stage3/visit_expression_type.o
LIBS += absyntax_utils/absyntax_utils.o
LIBS += absyntax_utils/search_expression_type.o
LIBS += absyntax_utils/decompose_var_instance_name.o
LIBS += absyntax_utils/function_call_iterator.o
LIBS += absyntax_utils/function_call_param_iterator.o
LIBS += absyntax_utils/function_param_iterator.o
LIBS += absyntax_utils/search_base_type.o
LIBS += absyntax_utils/search_constant_type.o
LIBS += absyntax_utils/search_fb_instance_decl.o
LIBS += absyntax_utils/search_fb_typedecl.o
LIBS += absyntax_utils/search_varfb_instance_type.o
LIBS += absyntax_utils/search_var_instance_decl.o
LIBS += absyntax_utils/spec_init_separator.o
LIBS += absyntax_utils/type_initial_value.o
LIBS += absyntax_utils/add_en_eno_param_decl.o
LIBS += absyntax_utils/get_sizeof_datatype.o
LIBS += absyntax_utils/get_function_type.o



iec2c: main.o stage4/generate_c/generate_c.o stage4/stage4.o $(LIBS)
	$(CXX) -o iec2c main.o stage4/stage4.o stage4/generate_c/generate_c.o $(LIBS)


iec2iec: main.o stage4/generate_iec/generate_iec.o stage4/stage4.o $(LIBS)
	$(CXX) -o iec2iec main.o stage4/stage4.o stage4/generate_iec/generate_iec.o $(LIBS)


#how to make things in subdirectories etc
../% /% absyntax/% stage1_2/% stage3/% stage4/% util/%:
	$(MAKE) -C $(@D) $(@F)

Makefile.depend depend:
	$(CXX) -MM -MG -I. *.cc \
	  | perl -pe 's/:/ Makefile.depend:/' > Makefile.depend

include Makefile.depend



