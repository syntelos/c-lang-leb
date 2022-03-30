#
# COMPILER
#
CC := clang
#
# REPRESENTATION [600] SUSv3 / UNIX 03 / POSIX.1-2001
#
PORTABILITY := -D_XOPEN_SOURCE=600
#
# CONSISTENCY
#
WARNINGS := #-Wno-long-long -Wall -pedantic -Werror
#
# INSPECTION
#
DEBUG := -g -ggdb
#
# STRUCTURE
#
CCFLAGS := $(PORTABILITY) -Ic-lang-bix/c-endian-bint/inc -Ic-lang-bix/inc -Iinc $(WARNINGS) $(DEBUG)

LDFLAGS := -lm #-lpthread
#
# DEPENDENCIES
#
HEADERS := inc/*.h

SOURCES := src/*.c
#
# SUBMODULE BINT
#
BIX_HEADERS := c-lang-bix/inc/*.h

BIX_SOURCES := c-lang-bix/src/*.c

leb: $(HEADERS) $(BIX_HEADERS) $(SOURCES) $(BIX_SOURCES) main/leb.c
	$(CC) $(CCFLAGS) -o $@ $(SOURCES) $(BIX_SOURCES) main/leb.c $(LDFLAGS)

clean:
	rm -f leb core
