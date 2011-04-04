# include the system specific Makefile
include ../Makefile.$(shell uname)




default: all

all: stage4.o

clean:
	rm -f *.o
	find . -depth -mindepth 2 -maxdepth 2 -name Makefile | sed 's/Makefile//g' | xargs -I {} make -C{} clean


CXXFLAGS += -I. -I../*

#how to make things in subdirectories etc
../% /% absyntax/% stage1_2/% stage3/% stage4/% util/%:
	        $(MAKE) -C $(@D) $(@F)

Makefile.depend depend:
	$(CXX) -MM -MG -I. *.cc \
	  | sed 's/:/ Makefile.depend:/' > Makefile.depend

include Makefile.depend
