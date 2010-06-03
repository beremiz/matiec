# include the system specific Makefile
include ../../Makefile.$(shell uname)

default: all

all: generate_iec.o

clean:
	echo > Makefile.depend
	-rm -f *.o */*.o 

#get warnings, debugging information and optimization
#CXXFLAGS  = -Wall -pedantic -Wpointer-arith -Wwrite-strings
# CXXFLAGS += -Werror
#CXXFLAGS += -ggdb -O3 -funroll-loops
# Note: if the optimizer crashes, we'll leave out the -O3 for those files

CXXFLAGS += -I. -I../* -I../../absyntax



#how to make things from other directories if they are missing
../% /%:
	$(MAKE) -C $(@D) $(@F)

Makefile.depend depend:
	$(CXX) -MM -MG -I. *.cc \
	  | sed 's/:/ Makefile.depend:/' > Makefile.depend

include Makefile.depend
