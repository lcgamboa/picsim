CC= gcc

#FLAGS= -ggdb -Wall
FLAGS= -Wall -O3 -fomit-frame-pointer

OBJS= common.o p16fxxx.o p18fxxx.o hexfile.o periferic.o periferic18.o serial.o icsp.o icsp18.o util.o 

all: picsim

picsim: lib picsim.c 
	$(CC) $(FLAGS) picsim.c -o picsim  libpicsim.a 
	$(CC) $(FLAGS) picsim_.c -o picsim_  libpicsim.a 
	$(CC) $(FLAGS) picsim18.c -o picsim18  libpicsim.a 


%.o: %.c  
	$(CC) $< -c  $(FLAGS) 

lib:    $(OBJS)
	ar rcs libpicsim.a  $(OBJS)


clean:
	rm -f picsim picsim_ picsim18 libpicsim.a $(OBJS)
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

