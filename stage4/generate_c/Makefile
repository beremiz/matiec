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
