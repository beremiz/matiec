# include the system specific Makefile
include ../Makefile.$(shell uname)




default: all

all: stage4.o

clean:
	rm -f *.o
	find . -depth -mindepth 2 -maxdepth 2 -name Makefile -printf %h\\n | xargs -i make -C{} $@


CXXFLAGS += -I. -I../*

#how to make things in subdirectories etc
../% /% absyntax/% stage1_2/% stage3/% stage4/% util/%:
	        $(MAKE) -C $(@D) $(@F)

