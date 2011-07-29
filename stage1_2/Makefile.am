include ../common.mk

lib_LIBRARIES = libstage1_2.a

iec.y.cc: iec.y
	$(YACC) -d -v -o iec.y.cc iec.y

iec.flex.cc: iec.flex
	$(LEX) -o iec.flex.cc iec.flex

libstage1_2_a_SOURCES = \
	iec.flex.cc \
	iec.y.cc \
	stage1_2.cc 

libstage1_2_a_CPPFLAGS =  -DDEFAULT_LIBDIR='"lib"' -I../../absyntax

