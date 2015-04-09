CFLAGS = -g -Wall -std=c99
CPPFLAGS = -I .
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
DEPS = $(SRC:.c=.d)

all:libgrid.a play test

%d: %c
	gcc -M $(CPPFLAGS) $< > $@

include $(DEPS)

libgrid.a:play.o grid.o
	ar cr $@ $^

play:
	gcc -L . -lgrid -lm -lcurses -o $@

test:verif_test.o grid.o
	gcc $^ -lm -o $@

%o: %c
	gcc $^ -o $@ $(LDFLAGS)

.PHONY : clean
clean:
	rm -f libgrid.a play test $(OBJ) $(DEPS) *~
