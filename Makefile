TOPDIR := $(shell pwd)
SRCDIR := $(TOPDIR)/src
INCDIR := $(TOPDIR)/inc
BINDIR := $(TOPDIR)/bin

SOURCES  := $(shell find $(SRCDIR) -name "*.cpp")
INCLUDES := $(shell find $(INCDIR) -name "*.h")

INCDIRS := $(shell pwd)/inc

BIN_NAME := main

default: clean
	{ \
	set -e;\
	mkdir bin;\
	g++ -I$(INCDIRS) $(INCLUDES) $(SOURCES) -o $(BINDIR)/$(BIN_NAME);\
	}
clean:
	rm -f -r $(BINDIR)
run:
	./bin/$(BIN_NAME)
