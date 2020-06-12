
FILE=Makefile


SUBDIRS= src include

.PHONY: $(SUBDIRS)  

all:$(SUBDIRS) doc

doc:
	doxygen 1>/dev/null 2>/dev/null
	gitchangelog > CHANGELOG.md
	! leasot -r markdown  src/*.{c,h} src/*/*.{c,h}  > TODO.md 

install:$(SUBDIRS) 
	
clean:$(SUBDIRS) 

uninstall:$(SUBDIRS) 

	
$(SUBDIRS):
	$(MAKE) -f $(FILE) -C $@ $(MAKECMDGOALS)
