CFLAGS = -g -Wall -std=c99 `pkg-config --cflags MLV`
CPPFLAGS = -I .
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
DEPS = $(SRC:.c=.d)

all:libgrid.a play test 2048

%d: %c
	gcc -M $(CPPFLAGS) $< > $@

include $(DEPS)

libgrid.a:play.o grid.o
	ar cr $@ $^

play:
	gcc $(CFLAGS) -L . -lgrid -lm -lcurses -o $@

2048:2048.o 
	gcc $(CFLAGS) $^ -L . `pkg-config --libs MLV` -lgrid -o $@

test:test.o grid.o
	gcc $(CFLAGS) $^ -lm -o $@

%o: %c
	gcc $^ -o $@ $(LDFLAGS)

.PHONY : clean
clean:
	rm -f libgrid.a play 2048 test $(OBJ) $(DEPS) *~
