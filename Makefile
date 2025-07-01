.DEFAULT_GOAL := all

CC ?= cc

# Source Files
SRCS = calc.c 
STLSRC = stdmath.c
STBSRC = stdbitwise.c

# Output files
OUT = calc
STLIB = stdmath.dylib
STBLIB = stdbit.dylib

PLATFORM:=osx # Flag set in command line to set the right flags for the platform

# Setting main flags
FLAGS = -I/opt/will/include -L/opt/will/lib -ldyn -Wl,-rpath,/opt/will/lib
ifeq ($(PLATFORM),linux)
    FLAGS += -ldl
endif

# Setting flags for building Dynamic Libraries
ifeq ($(PLATFORM),osx)
SOFLAGS = -dynamiclib -fPIC
else ifeq ($(PLATFORM),linux)
SOFLAGS = -shared -fPIC
endif

$(info PLATFORM = $(PLATFORM))
$(info SOFLAGS = $(SOFLAGS))
# Call all necessary building
all: $(OUT) $(STLIB) $(STBLIB)

# Make main app
$(OUT): $(SRCS)
	$(CC) -o $@ $(FLAGS) $^

# Make Standard Math Library
$(STLIB): $(STLSRC)
	$(CC) -o $@ $(SOFLAGS) $^

# Make Bitwise Math Library
$(STBLIB): $(STBSRC)
	$(CC) -o $@ $(SOFLAGS) $^

# Clean build files
clean:
	rm -f $(OUT) $(STLIB) $(STBLIB)

.PHONY: clean