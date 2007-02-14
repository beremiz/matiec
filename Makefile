# include the system specific Makefile
#include ../../Makefile.$(shell uname)
 
default: all

all: iec2cc iec2iec

install: all
	install -d $(INSTALL_PREDIR)/$(INSTALL_BINDIR)/ 
	install -d $(INSTALL_PREDIR)/$(IECLIBDIR)/
	install iec2cc    $(INSTALL_PREDIR)/$(INSTALL_BINDIR)/
	install lib/*.txt $(INSTALL_PREDIR)/$(IECLIBDIR)/
#	install iec2iec   $(INSTALL_PREDIR)/$(INSTALL_BINDIR)/


uninstall:
	rm -f $(INSTALL_PREDIR)/$(INSTALL_BINDIR)/iec2cc
	rm -f $(INSTALL_PREDIR)/$(INSTALL_BINDIR)/iec2iec
	for ff in `cd lib; ls *.txt; cd ..` do echo $$ff done
#	for ff in `cd lib; ls *.txt; cd ..` do rm -f $(INSTALL_PREDIR)/$(IECLIBDIR)/$$ff done


clean:
	-rm -f iec2iec iec2cc *.o absyntax/*.o Makefile.depend
# make something everywhere (ie, in all Makefiles that have that target)
	find . -depth -mindepth 2 -maxdepth 2 -name Makefile -printf %h\\n | xargs -i make -C{} $@



#get warnings, debugging information and optimization
CXXFLAGS  = -Wall -pedantic -Wpointer-arith -Wwrite-strings
# CXXFLAGS += -Werror
CXXFLAGS += -ggdb -O3 -funroll-loops
# Note: if the optimizer crashes, we'll leave out the -O3 for those files

CXXFLAGS += -I.



LIBS  = absyntax/absyntax.o absyntax/visitor.o
LIBS += stage1_2/stage1_2.o stage1_2/iec.y.o stage1_2/iec.flex.o 

iec2cc: main.o stage4/generate_cc/generate_cc.o stage4/stage4.o $(LIBS)
	$(CXX) -o iec2cc main.o stage4/stage4.o stage4/generate_cc/generate_cc.o $(LIBS)


iec2iec: main.o stage4/generate_iec/generate_iec.o stage4/stage4.o $(LIBS)
	$(CXX) -o iec2iec main.o stage4/stage4.o stage4/generate_iec/generate_iec.o $(LIBS)


#how to make things in subdirectories etc
../% /% absyntax/% stage1_2/% stage3/% stage4/% util/%:
	$(MAKE) -C $(@D) $(@F)

Makefile.depend depend:
	$(CXX) -MM -MG -I. *.cc \
	  | perl -pe 's/:/ Makefile.depend:/' > Makefile.depend

include Makefile.depend




