CC= gcc
RM= rm -f
AR= ar
LN= ln -sfn
CP= cp
MKDIR = mkdir -p

LIBVER=0.6
LIBMAINVER=0
FLAGS= -Wall -O3 -fomit-frame-pointer -fpic

prefix = /usr
exec_prefix = ${prefix}
datadir = ${datarootdir}
includedir = ${prefix}/include/picsim
bindir = ${exec_prefix}/bin
libdir = ${exec_prefix}/lib


OBJS= common.o p16fxxx.o p18fxxx.o hexfile.o periferic.o periferic18.o serial.o icsp.o icsp18.o util.o 

all: all-lib picsim

picsim: libpicsim.a picsim.c 
	$(CC) $(FLAGS) picsim.c -o picsim  libpicsim.a 


%.o: %.c  
	$(CC) $< -c  $(FLAGS) 


# The static lib name, the shared lib name, and the internal ('so') name of
# the shared lib.
LIBNAME = libpicsim
LIBSHBASENAME = $(LIBNAME).so
LIBSHLIBNAME = $(LIBNAME).so.$(LIBVER)
LIBSTLIBNAME = $(LIBNAME).a
LIBSHSONAME := $(LIBNAME).so.$(LIBMAINVER)

LIBTARGETS := $(LIBSHLIBNAME) $(LIBSHSONAME) $(LIBSHBASENAME)



LIBHEADERFILES := p16fxxx_defs.h  p18fxxx_defs.h periferic18.h periferic.h picsim.h 

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

clean-lib:
	$(RM) *.ld *.ad
	$(RM) *.lo *.ao *.a
	$(RM) $(LIBTARGETS) $(LIBEXTRACLEAN)

install: all
	strip -s $(LIBNAME).so
	$(CP) -dvf $(LIBNAME)* ${libdir}
	${MKDIR} ${includedir}
	$(CP) -dvf $(LIBHEADERFILES) ${includedir}
	chmod 644 ${includedir}/*

uninstall:
	$(RM) ${libdir}/$(LIBNAME)* 
	$(RM) -r ${includedir} 


clean:  clean-lib
	rm -f picsim libpicsim.a $(OBJS)
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

