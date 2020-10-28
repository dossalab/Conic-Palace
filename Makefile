#
# Part of the Conic Palace - robot control center
#
# See LICENSE.md for licensing information
# Roman Luitko, 2020
#

CC	:= gcc
LD	:= gcc
ECHO	:= printf "[%s]\t%s\n"

appname	:= conic_palace
objects	:= \
	src/app.o

pkglibs	:= gtk+-3.0

CFLAGS	:= $(shell pkg-config --cflags $(pkglibs))
LDFLAGS	:= $(shell pkg-config --libs $(pkglibs))

%.o : %.c
	@ $(ECHO) CC "$@"
	@ $(CC) $(CFLAGS) -c $< -o $@

all: $(appname)

$(appname): $(objects)
	@ $(ECHO) LD "$@"
	@ $(LD) $(LDFLAGS) $^ -o $@

clean:
	$(RM) $(objects) $(appname)

.PHONY: all clean

