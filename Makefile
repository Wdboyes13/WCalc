SRCS = calc.c 
STLSRC = stdmath.c
STBSRC = stdbitwise.c
CC ?= wclang

OUT = calc
STLIB = stdmath.dylib
STBLIB = stdbit.dylib

PLATFORM?=osx

FLAGS = -I/opt/will/include -L/opt/will/lib -ldyn -Wl,-rpath,/opt/will/lib
ifeq ($(PLATFORM),linux)
    FLAGS += -ldl
endif

ifeq ($(PLATFORM),osx)
SOFLAGS = -dynamiclib -fPIC
else ifeq ($(PLATFORM),linux)
SOFLAGS = -shared -fPIC
endif

all: $(OUT) $(STLIB) $(STBLIB)

$(OUT): $(SRCS)
	$(CC) -o $@ $(FLAGS) $^

$(STLIB): $(STLSRC)
	$(CC) -o $@ $(SOFLAGS) $^

$(STBLIB): $(STBSRC)
	$(CC) -o $@ $(SOFLAGS) $^

clean:
	rm -f $(OUT) $(STLIB) $(STBLIB)