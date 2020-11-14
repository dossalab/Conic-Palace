#
# Part of the Conic Palace - robot control center
#
# Main build makefile
#
# See LICENSE.md for licensing information
# Roman Luitko, 2020
#

outdir = out
native-exe = $(outdir)/native/conic-palace
windows-exe = $(outdir)/windows/conic-palace.exe

all: native windows

native:
	go build -o $(native-exe)

windows:
	sudo scripts/docker-build.sh windows $(windows-exe)

clean:
	rm -rf $(outdir)

.PHONY: all clean

