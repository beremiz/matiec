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
