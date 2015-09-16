CC = g++
#FLAGS = -D_VERSION_=\"0.5.0\" -ggdb -Wall -D_SHARE_=\"`pwd`/share/\"   -fomit-frame-pointer `lxrad-config --cxxflags`
FLAGS = -D_VERSION_=\"0.5.0\" -O2 -Wall -D_SHARE_=\"`pwd`/share/\"   -fomit-frame-pointer `lxrad-config --cxxflags`

OBJS = ppicsimlab.o picsimlab1.o picsimlab2.o picsimlab3.o board_1.o board_2.o board_3.o board_4.o id.o lcd.o mi2c.o rtc.o rtc2.o ../libpicsim.a prog_psp.o


all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -opicsimlab `lxrad-config --libs`

%.o: %.cc
	$(CC) -c $(FLAGS) $< 

run: all
	./picsimlab

install:

clean:
	rm -f picsimlab *.o core
