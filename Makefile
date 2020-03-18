TOPDIR := $(shell pwd)
SRCDIR := $(TOPDIR)/src
INCDIR := $(TOPDIR)/inc
BINDIR := $(TOPDIR)/bin

SOURCES  := $(shell find $(SRCDIR) -name "*.cpp")
INCLUDES := $(shell find $(INCDIR) -name "*.h")

INCDIRS := $(shell pwd)/inc

BIN_NAME := main
BIN_NAME_ARM := main_arm

default: clean
	{ \
	set -e;\
	mkdir bin;\
	g++ -I$(INCDIRS) $(INCLUDES) $(SOURCES) -o $(BINDIR)/$(BIN_NAME);\
	}
arm: clean
	{ \
	set -e;\
	mkdir bin;\
	arm-linux-gnueabihf-g++ -I$(INCDIRS) $(INCLUDES) $(SOURCES) -o $(BINDIR)/$(BIN_NAME_ARM);\
	}
    
clean:
	rm -f -r $(BINDIR)
run:
	./bin/$(BIN_NAME)
