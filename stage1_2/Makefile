# include the system specific Makefile
#include ../../../Makefile.$(shell uname)



default:	all

.PHONY: iec.flex

all: iec.flex.o iec.y.o stage1_2.o


clean:
	-rm -f *.o Makefile.depend
	-rm -f iec.flex.c iec.y.cc iec.y.hh iec.y.output
	-rm -f test_flex

#get warnings, debugging information and optimization
CFLAGS  = -Wall -pedantic -Wpointer-arith -Wwrite-strings
# CFLAGS += -Werror

CFLAGS += -ggdb -O3 -funroll-loops
# Note: if the optimizer crashes, we'll leave out the -O3 for those files

CFLAGS += -I. -I../* -I../../absyntax

test_flex: iec.flex.c iec.y.hh
	$(CXX) -o test_flex.o -c iec.flex.c -DTEST_MAIN $(CFLAGS)
	$(CXX) -o test_flex test_flex.o
#	$(CXX) -o test_flex test_flex.o ../util/symtable.o -DTEST_MAIN

iec.flex.c: iec.flex
	flex -oiec.flex.c iec.flex

iec.flex.o: iec.y.hh iec.flex.c
	$(CXX) -c iec.flex.c -D LIBDIRECTORY='"$(IECLIBDIR)"' $(CFLAGS)

iec.y.hh iec.y.cc: iec.y
	bison -d -v -o iec.y.cc iec.y

iec.y.o: iec.y.cc iec.y.hh
	$(CXX) -c iec.y.cc -D LIBDIRECTORY='"$(IECLIBDIR)"' $(CFLAGS)





#how to make things from other directories if they are missing
../% /%:
	$(MAKE) -C $(@D) $(@F)


Makefile.depend depend:
	$(CXX) -MM -MG -I. *.cc \
	  | perl -pe 's/:/ Makefile.depend:/' > Makefile.depend

include Makefile.depend

