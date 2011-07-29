include common.mk

bin_PROGRAMS = iec2c

SUBDIRS = absyntax absyntax_utils stage1_2 stage3 stage4 

ACLOCAL_AMFLAGS=-I config

LDADD = stage1_2/libstage1_2.a \
	stage3/libstage3.a \
	stage4/libstage4.a \
	absyntax/libabsyntax.a \
	absyntax_utils/libabsyntax_utils.a 

iec2c_SOURCES = main.cc 

