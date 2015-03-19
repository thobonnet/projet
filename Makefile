CFLAGS = -g -Wall -std=c99
CPPFLAGS = -I .
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
DEPS = $(SRC:.c=.d)

all:libgrid.a test_grid

%d: %c
	gcc -M $(CPPFLAGS) $< > $@

include $(DEPS)

libgrid.a:$(OBJ)
	ar cr $@ $(OBJ)

test_grid:$(OBJ)
	gcc -L . $^ -lgrid -lm -lcurses -o $@

.PHONY : clean
clean:
	rm -f libgrid.a test_grid $(OBJ) $(DEPS) *~
