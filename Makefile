TOPDIR := $(shell pwd)
SRCDIR := $(TOPDIR)/src
INCDIR := $(TOPDIR)/inc
BINDIR := $(TOPDIR)/bin

SOURCES  := $(shell find $(SRCDIR) -name "*.cpp")
INCLUDES := $(shell find $(INCDIR) -name "*.h")

BIN_NAME := main

default:
	{ \
	set -e;\
	mkdir bin;\
	g++ $(INCLUDES) $(SOURCES) -o $(BINDIR)/$(BIN_NAME);\
	}
clean:
	rm -f -r $(BINDIR)
run:
	./bin/$(BIN_NAME)
