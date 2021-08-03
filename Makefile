#
# Makefile
#

.PHONY: all clean library

CC=gcc
LIBRARY=CIEDE2000
SOURCE=$(LIBRARY).c
OBJECT=$(SOURCE:%.c=%.o)
DISPOSABLE_FILES=lib$(LIBRARY).so lib$(LIBRARY).dylib $(LIBRARY).dll $(OBJECT)
DISPOSABLE_DIRS=*dSYM
OS=$(shell uname)

CFLAGS=-Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC

all: library

library: $(LIBRARY).c
ifeq ($(findstring Darwin,$(OS)),Darwin)
	$(CC) -dynamiclib $(CFLAGS) $^ -o lib$(LIBRARY).dylib
else
ifeq ($(findstring MINGW,$(OS)),MINGW)
	$(CC) -shared $(CFLAGS) $^ -o lib$(LIBRARY).dll
else
	$(CC) -shared $(CFLAGS) $^ -o lib$(LIBRARY).so
endif
endif

clean:
	$(RM) $(DISPOSABLE_FILES)
	$(RM) -r $(DISPOSABLE_DIRS)

