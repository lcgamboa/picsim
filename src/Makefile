include Makefile.Common

CC= gcc
RM= rm -f
AR= ar
LN= ln -sfn
CP= cp
MKDIR = mkdir -p

FLAGS= -Wall -O3 -fpic -fsigned-char -Winline 

prefix = /usr
exec_prefix = ${prefix}
datadir = ${datarootdir}
bindir = ${exec_prefix}/bin
libdir = ${exec_prefix}/lib


all: all-lib picsim

picsim: libpicsim.a picsim.c 
	$(CC) $(FLAGS) picsim.c -o picsim  libpicsim.a 

%.o: %.c  
	$(CC) -c $(FLAGS) $< -o $@ 



# The static lib name, the shared lib name, and the internal ('so') name of
# the shared lib.
LIBNAME = libpicsim
LIBSHBASENAME = $(LIBNAME).so
LIBSHLIBNAME = $(LIBNAME).so.$(LIBVER)
LIBSTLIBNAME = $(LIBNAME).a
LIBSHSONAME := $(LIBNAME).so.$(LIBMAINVER)

LIBTARGETS := $(LIBSHLIBNAME) $(LIBSHSONAME) $(LIBSHBASENAME)



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
	$(RM) *.lo *.ao 
	$(RM) $(LIBTARGETS) $(LIBEXTRACLEAN)

install: all
	strip -s $(LIBNAME).so
	$(CP) -dvf $(LIBNAME)* ${libdir}

uninstall:
	$(RM) ${libdir}/$(LIBNAME)* 


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
	rm -f pics/*.o
	rm -f *.o

