CC= emcc
RM= rm -f
AR= emar
LN= ln -sfn
CP= cp
MKDIR = mkdir -p

LIBVER=0.6
LIBMAINVER=0
FLAGS= -Os 

prefix = /usr
exec_prefix = ${prefix}
datadir = ${datarootdir}
bindir = ${exec_prefix}/bin
libdir = ${exec_prefix}/lib


OBJS= common.o p16fxxx.o p16fxxxe.o p18fxxx.o hexfile.o periferic16.o periferic16e.o periferic18.o \
      serial.o icsp.o icsp18.o util.o \
      pics/PIC18F4520.o pics/PIC18F452.o pics/PIC18F4550.o pics/PIC18F45K50.o pics/PIC18F4620.o \
      pics/PIC16F628A.o pics/PIC16F648A.o pics/PIC16F777.o pics/PIC16F877A.o pics/PIC16F84A.o \
      pics/PIC16F1619.o pics/PIC16F18855.o pics/PIC16F1939.o pics/PIC16F1788.o pics/PIC16F1789.o

all: all-lib picsim

picsim: libpicsim_js.a picsim.c 
	$(CC) $(FLAGS) picsim.c -o picsim  libpicsim_js.a 


%.o: %.c  
	$(CC) -c $(FLAGS) $< -o $@ 


# The static lib name, the shared lib name, and the internal ('so') name of
# the shared lib.
LIBNAME = libpicsim_js
LIBSHBASENAME = $(LIBNAME).so
LIBSHLIBNAME = $(LIBNAME).so.$(LIBVER)
LIBSTLIBNAME = $(LIBNAME).a
LIBSHSONAME := $(LIBNAME).so.$(LIBMAINVER)

LIBTARGETS := $(LIBSTLIBNAME)



# How to create the shared library
$(LIBSHLIBNAME): $(OBJS)
	$(CC) -shared -Wl,-soname,$(LIBSHSONAME) -o $@  $^    

$(LIBSHSONAME): $(LIBSHLIBNAME)
	$(RM) $@
	$(LN) $(LIBSHLIBNAME) $(LIBSHSONAME)

$(LIBSHBASENAME): $(LIBSHLIBNAME)
	$(RM) $@ 
	$(LN) $(LIBSHLIBNAME) $(LIBSHBASENAME)

# And the static library
$(LIBSTLIBNAME): $(OBJS)
	$(RM) $@
	$(AR) rcvs $(LIBSTLIBNAME) $^

# Include all dependency files
#INCLUDEFILES += $(LIBCSOURCES:.c=.ld) $(LIBCSOURCES:.c=.ad)

all-lib: $(LIBTARGETS)

static :: $(LIBSTLIBNAME)

install: all
	strip -s $(LIBNAME).so
	$(CP) -dvf $(LIBNAME)* ${libdir}

uninstall:
	$(RM) ${libdir}/$(LIBNAME)* 


clean:  
	rm -f picsim libpicsim_js.a $(OBJS)
	rm -f examples/*_sdcc*/*.asm
	rm -f share/examples/*_mikroc_pro*/*.asm
	rm -f examples/*/*.adb
	rm -f examples/*/*.lst
	rm -f examples/*/*.o
	rm -f examples/*/*.cod
	rm -f examples/*/*.cof
	rm -f examples/*/*.map
	rm -f examples/*/*.err
	rm -f examples/*/*.p
	rm -f examples/*/*.pre
	rm -f examples/*/*.p1
	rm -f examples/*/funclist
	rm -f examples/*/*.obj
	rm -f examples/*/*.as
	rm -f examples/*/*.rlf
	rm -f examples/*/*.sym
	rm -f examples/*/*.sdb
	rm -f examples/*/*.hxl
	rm -f examples/*/*.ini
	rm -f examples/*/*.cp
	rm -f examples/*/*.cfg
	rm -f examples/*/*.dbg
	rm -f examples/*/*.dct
	rm -f examples/*/*.dlt
	rm -f examples/*/*.dic
	rm -f examples/*/*callertable.txt
	rm -f examples/*/*.mcl
	rm -f examples/*/*.log

