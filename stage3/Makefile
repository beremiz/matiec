# include the system specific Makefile
include ../Makefile.$(shell uname)




STAGE3_FILES  = stage3.o
STAGE3_FILES += visit_expression_type.o

default: all

all: $(STAGE3_FILES)



clean:
	rm -f *.o Makefile.depend


CXXFLAGS += -I. -I../*



Makefile.depend depend:
	$(CXX) -MM -MG -I. *.cc \
	  | sed 's/:/ Makefile.depend:/' > Makefile.depend

include Makefile.depend
