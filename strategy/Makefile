CC = gcc
CFLAGS = -g -std=c99 -Wall

all:
	gcc -c $(CFLAGS) -fPIC A4_bonnet_jajoux_fast.c
	gcc -c $(CFLAGS) -fPIC A4_bonnet_jajoux_efficient.c
	gcc -shared -o libA4_bonnet_jajoux_fast.so A4_bonnet_jajoux_fast.o
	gcc -shared -o libA4_bonnet_jajoux_efficient.so A4_bonnet_jajoux_efficient.o 


.PHONY: clean

clean:
	-rm -f *.o *.gch *.so *~
