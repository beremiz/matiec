# include the system specific Makefile
include ../Makefile.$(shell uname)




default: all

all: absyntax.o visitor.o

clean:
	rm -f *.o
	find . -depth -mindepth 2 -maxdepth 2 -name Makefile -printf %h\\n | xargs -i make -C{} $@


#get warnings, debugging information and optimization
#CXXFLAGS  = -Wall -pedantic -Wpointer-arith -Wwrite-strings
# CXXFLAGS += -Werror

#CXXFLAGS += -ggdb -O3 -funroll-loops
# Note: if the optimizer crashes, we'll leave out the -O3 for those files

CXXFLAGS += -I. -I../* -I../../absyntax



#how to make things in subdirectories etc
../% /% absyntax/% stage1_2/% stage3/% stage4/% util/%:
	        $(MAKE) -C $(@D) $(@F)

