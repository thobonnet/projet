CC = gcc
CFLAGS = -g -std=c99 -Wall

all:
	gcc -c $(CFLAGS) grid.h -fPIC strat_fast.c
	gcc -c $(CFLAGS) grid.h -fPIC strat_efficient.c
	gcc -shared -o libstrat_fast.so strat_fast.o
	gcc -shared -o libstrat_efficient.so strat_efficient.o 


.PHONY: clean

clean:
	-rm -f *.o *.gch *.so *~
