
FILE=Makefile


SUBDIRS= src include

.PHONY: $(SUBDIRS)  

all:$(SUBDIRS) 

doc:
	doxygen
	gitchangelog > CHANGELOG.md
	! leasot -r markdown  src/*.{c,h} src/*/*.{c,h}  > TODO.md 

install:$(SUBDIRS) 
	
clean:$(SUBDIRS) 

uninstall:$(SUBDIRS) 

	
$(SUBDIRS):
	$(MAKE) -f $(FILE) -C $@ $(MAKECMDGOALS)
