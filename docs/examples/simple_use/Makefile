
CC= gcc

FLAGS= -Wall -ggdb

all: picsim_simple.c
	$(CC) $(FLAGS) picsim_simple.c -o picsim_simple -lpicsim

clean:
	rm -rf picsim_simple

run:
	picsim_simple P16F628A ../../examples/shift.hex



