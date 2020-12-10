CC=gcc
LD=gcc

libs := gtk+-3.0 libconic librobot

ECHO	:= printf "[%s]\t%s\n"

CFLAGS := $(shell pkg-config --cflags $(libs)) -I. -Wall
LDFLAGS := -lm $(shell pkg-config --libs $(libs))

app := app
objects := \
	src/main.o \
	util/i18n.o \
	src/connman.o \
	widgets/viewport.o \
	views/header.o \
	views/main.o

all: $(app)
	./app

%.o : %.c
	@ $(ECHO) CC "$@"
	@ $(CC) $(CFLAGS) -c $< -o $@

$(app): $(objects)
	@ $(ECHO) LD "$@"
	@ $(LD) $(LDFLAGS) $^ -o $@

clean:
	$(RM) $(objects) $(app)

.PHONY: all clean

