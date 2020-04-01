
MKDIR = mkdir -p
CP= cp

prefix = /usr
includedir = ${prefix}/include/picsim/

LIBHEADERFILES := p16fxxx_defs.h  p16fxxxe_defs.h  p18fxxx_defs.h periferic18.h periferic16.h periferic16e.h picsim.h 

all:

install: 
	${MKDIR} ${includedir}
	$(CP) -dvf $(LIBHEADERFILES) ${includedir}
	chmod 644 ${includedir}/*

uninstall:
	$(RM) -r ${includedir} 

clean:



