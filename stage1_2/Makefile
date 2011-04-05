# matiec - a compiler for the programming languages defined in IEC 61131-3
#
# Copyright (C) 2003-2011  Mario de Sousa (msousa@fe.up.pt)
# Copyright (C) 2007-2011  Laurent Bessard and Edouard Tisserant
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# include the system specific Makefile
include ../Makefile.$(shell uname)



default: all

all: iec.flex.o iec.y.o stage1_2.o

clean:
	echo > Makefile.depend
	-rm -f iec.flex.c iec.y.cc iec.y.hh iec.y.output
	-rm -f iec.noerrorcheck.y
	-rm -f test_flex
	-rm -f stage1_2.o
	-rm -f iec.y.o
	-rm -f iec.flex.o
	-rm -f Makefile.depend


CFLAGS += -I. -I../* -I../../absyntax

iec.flex.c: iec.flex
	flex -oiec.flex.c iec.flex

stage1_2.cc: iec.y.hh 
stage1_2.o: stage1_2.cc

iec.flex.o: iec.y.hh iec.flex.c
	$(CXX) -c iec.flex.c -D DEFAULT_LIBDIR='"$(IECLIBDIR)"' $(CFLAGS)

iec.y.hh iec.y.cc: iec.y
	bison -d -v -o iec.y.cc iec.y

iec.y.o: iec.y.cc iec.y.hh
	$(CXX) -c iec.y.cc $(CFLAGS)

noerrorcheck: iec.y
	sed '/ERROR_CHECK_BEGIN/,/ERROR_CHECK_END/ d' iec.y > iec.noerrorcheck.y
	flex -oiec.flex.c iec.flex
	$(CXX) -c iec.flex.c -D DEFAULT_LIBDIR='"$(IECLIBDIR)"' $(CFLAGS)
	bison -d -v -o iec.y.cc iec.noerrorcheck.y
	$(CXX) -c iec.y.cc $(CFLAGS)

#how to make things from other directories if they are missing
../% /%:
	$(MAKE) -C $(@D) $(@F)


Makefile.depend depend:
	$(CXX) -MM -MG -I. *.cc \
	  | sed 's/:/ Makefile.depend:/' > Makefile.depend

include Makefile.depend


