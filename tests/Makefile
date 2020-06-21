# Tests require
# 1. <https://pkg-config.freedesktop.org>
#    (or <https://github.com/pkgconf/pkgconf>)
# 2. <https://libcheck.github.io/check/>

SHELL=/bin/sh

default: it

.PHONY: clean default it test

TESTBINS = unittest_stralloc unittest_cdb

CHECK_INCLUDES := `pkg-config --cflags check`
CHECK_LIBS := `pkg-config --libs check`

clean:
	rm -f $(TESTBINS) *.o

it: $(TESTBINS)

test: it
	@for tbin in $(TESTBINS); do \
		./$$tbin || exit 1 ; \
	done

%.o: %.c ../compile
	../compile $< -I.. $(CHECK_INCLUDES)

unittest_stralloc: \
../load unittest_stralloc.o ../stralloc.a ../str.a ../error.a
	../load unittest_stralloc ../stralloc.a ../str.a ../error.a \
	$(CHECK_LIBS)

unittest_stralloc.o: \
../alloc.h ../stralloc.h

unittest_cdb: \
../load unittest_cdb.o ../cdb.a
	../load unittest_cdb ../cdb.a \
	$(CHECK_LIBS)

unittest_cdb.o: \
../cdb.h ../uint32.h
