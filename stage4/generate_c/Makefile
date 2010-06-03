# include the system specific Makefile
include ../../Makefile.$(shell uname)

default: all

all: generate_c.o

clean:
	echo > Makefile.depend
	-rm -f *.o */*.o

CXXFLAGS += -Wno-unused
CXXFLAGS += -I. -I../* -I../../absyntax

#how to make things from other directories if they are missing
../% /%:
	$(MAKE) -C $(@D) $(@F)

test_iec_std_lib: test_iec_std_lib.c iec_std_lib.h
	gcc -o test_iec_std_lib test_iec_std_lib.c
	
test: test_iec_std_lib

Makefile.depend depend:
	$(CXX) -MM -MG -I. *.cc \
	  | sed 's/:/ Makefile.depend:/' > Makefile.depend

include Makefile.depend
