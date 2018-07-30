
MKDIR = mkdir -p
CP= cp

prefix = /usr
includedir = ${prefix}/include/picsim/

LIBHEADERFILES := p16fxxx_defs.h  p16fxxxe_defs.h p16fxxxe2_defs.h p18fxxx_defs.h periferic18.h periferic16.h periferic16e.h periferic16e2.h picsim.h 

install: 
	${MKDIR} ${includedir}
	$(CP) -dvf $(LIBHEADERFILES) ${includedir}
	chmod 644 ${includedir}/*

uninstall:
	$(RM) -r ${includedir} 

clean:

all:

