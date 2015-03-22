#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "grid.h"

bool
test_new_grid(){
	grid g = new_grid();

	return g != NULL;
}

bool
test_delete_grid(grid g){
	delete_grid(g);

	return g == NULL;
}

bool
test_copy_grid(grid src, grid dst){
	copy_grid(src, dst);
	for(int x=0;x<GRID_SIDE;x++)
    	for(int y=0;y<GRID_SIDE;y++)
    		if(get_tile(src, x, y) != get_tile(dst, x, y))
    			return false;

    return true;
}

bool
test_add_tile(){
	int n = 0;
	grid g = new_grid(); // Doit etre testé sur une grille vide
	add_tile(g);
	for(int x=0;x<GRID_SIDE;x++)
    	for(int y=0;y<GRID_SIDE;y++)
    		if(get_tile(g, x, y) != 0)
    			n+=1;

    return n == 1;
}

bool
test_can_move(grid g){
	tile t = 1;
	for(int x=1;x>GRID_SIDE;x++)
		for (int y=1;y<GRID_SIDE;y++)
			set_tile(g,x,y,t++); // Remplissage de la grille de façon a autoriser seulement 2 direction

	return can_move(g, DOWN) && can_move(g, RIGHT) 
		&& !can_move(g, UP) && !can_move(g, LEFT);
}

bool
test_game_over(grid g){
	tile t = 1;
	for(int x=0;x<GRID_SIDE;x++)
		for(int y=0;y<GRID_SIDE;y++)
			set_tile(g,x,y,t++); // Remplissage de la grille pour eviter tout mouvement possible.

	return game_over(g);
}

bool
test_play(grid g, dir d){
	return test_add_tile();
}

int
main(int argc, char **argv){

	printf("Test new_grid      : %d \n", test_new_grid());

	grid tmp = new_grid();
	printf("Test delete_grid   : %d \n", test_delete_grid(tmp));

	grid src = new_grid();
	grid dst = new_grid();
	printf("Test copy_grid     : %d \n", test_copy_grid(src, dst));


	printf("Test add_tile      : %d \n",test_add_tile());

	printf("Test can_move      : %d \n",test_can_move(dst));

	printf("Test game_over     : %d \n",test_game_over(dst));

	printf("Test play          : %d \n",test_play(dst, DOWN));

	delete_grid(dst);
	delete_grid(src);

}

