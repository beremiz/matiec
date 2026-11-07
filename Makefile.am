include common.mk

bin_PROGRAMS = iec2c iec2iec

SUBDIRS = absyntax absyntax_utils stage1_2 stage3 stage4 

ACLOCAL_AMFLAGS=-I config

HGVERSION= $(shell hg -R $(top_srcdir) parents --template '{node|short}' 2> /dev/null || grep node $(top_srcdir)/.hg_archival.txt 2> /dev/null || true )
AM_CXXFLAGS += -DHGVERSION="\"${HGVERSION}\""

iec2c_LDADD = stage1_2/libstage1_2.a \
	stage3/libstage3.a \
	stage4/generate_c/libstage4_c.a \
	absyntax/libabsyntax.a \
	absyntax_utils/libabsyntax_utils.a 

iec2iec_LDADD = stage1_2/libstage1_2.a \
	stage3/libstage3.a \
	stage4/generate_iec/libstage4_iec.a \
	absyntax/libabsyntax.a \
	absyntax_utils/libabsyntax_utils.a 

iec2c_SOURCES = main.cc

iec2iec_SOURCES = main.cc

# 'make check', or its alias 'make test', runs the runtests script of each test
# suite, from the suite's directory, against the compilers just built.
# tests/syntax is not listed: its test cases predate the semantic checks of
# stage 3, and the current compiler rejects all of them.
TEST_SUITES = tests/initialization tests/stdlib

check-local:
	@failed=; \
	for suite in $(TEST_SUITES); do \
	  echo "*** $$suite"; \
	  (cd "$(srcdir)/$$suite" && \
	   IEC2C="$(abs_top_builddir)/iec2c" CC="$(CC)" ./runtests) || failed="$$failed $$suite"; \
	done; \
	if test -n "$$failed"; then echo "FAILED test suites:$$failed"; exit 1; fi

test: check
.PHONY: test
