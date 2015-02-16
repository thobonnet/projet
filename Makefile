CFLAGS = -g -Wall -std=c99
CPPFLAGS = -I .
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
DEPS = $(SRC:.c=.d)

all:libgrid.a

%d: %c
	gcc -M $(CPPFLAGS) $< > $@ include $(DEPS)

libgrid.a:$(OBJ)
	ar cr $@ $(OBJ)

.PHONY : clean
clean:
	rm -f libgrid.a grid.o
