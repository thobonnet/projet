#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "grid.h"

void
afficher_grille(grid g){
  for(int i = 0; i < GRID_SIDE; i++){
    printf("+------");
  }
  printf("+\n");

  for(int x = 0; x < GRID_SIDE; x++){
    printf("|");
    for(int y = 0; y < GRID_SIDE; y++)
      printf(" %4d |", get_tile(g,x,y)==0?0:(int)pow(2,get_tile(g,x,y)));
    printf("\n");
    for(int i = 0; i < GRID_SIDE; i++)
      printf("+------");
    printf("+\n");
  }
 }

int
main(int argc, char **argv){

	grid g = new_grid();
	printf("Affichage de la grille : \n");
	afficher_grille(g);

	printf("Test add_tile       : \n");
	add_tile(g);
	afficher_grille(g);

	printf("Test can_move       : \n");
	printf("Remplissage de la grille pour autoriser des deplacements\n");
	printf("vers la gauche et vers le haut \n");
	tile t = 1;
	for(int x=1;x<GRID_SIDE;x++){
		for (int y=1;y<GRID_SIDE;y++){
			set_tile(g,x,y,t);
			t++;
		}
	}

	afficher_grille(g);

	printf("Test can_move(UP)    : %d \n", can_move(g, UP));
	printf("Test can_move(LEFT)  : %d \n", can_move(g, LEFT));
	printf("Test can_move(DOWN)  : %d \n", can_move(g, DOWN));
	printf("Test can_move(RIGHT) : %d \n", can_move(g, RIGHT));
	
	printf("Test do_move         : \n");
	afficher_grille(g);
	do_move(g, UP);
	afficher_grille(g);
	if(!can_move(g,UP)){
		printf("Test do_move(UP) : OK \n\n");
	}else{
		printf("Test do_move(UP) : NOT OK\n\n");
	}

	do_move(g, LEFT);
	afficher_grille(g);
	if(!can_move(g,LEFT)){
		printf("Test do_move(LEFT) : OK \n\n");
	}else{
		printf("Test do_move(LEFT) : NOT OK\n\n");
	}

	do_move(g, DOWN);
	afficher_grille(g);
	if(!can_move(g,DOWN)){
		printf("Test do_move(DOWN) : OK \n\n");
	}else{
		printf("Test do_move(DOWN) : NOT OK\n\n");
	}

	do_move(g, RIGHT);
	afficher_grille(g);
	if(!can_move(g,RIGHT)){
		printf("Test do_move(RIGHT) : OK \n\n");
	}else{
		printf("Test do_move(RIGHT) : NOT OK\n\n");
	}

	printf("Test copy_grid : Les deux grille doivent être identique \n");
	grid g2 = new_grid();
	copy_grid(g,g2);
	afficher_grille(g);
	afficher_grille(g2);

	bool b = true;
	for(int x=0;x<GRID_SIDE;x++)
    	for(int y=0;y<GRID_SIDE;y++)
    		if(get_tile(g, x, y) != get_tile(g2, x, y))
    			b = false;

    printf("Test copy_grid : %d \n", b);

    t = 1;
    for(int x=0;x<GRID_SIDE;x++){
		for (int y=0;y<GRID_SIDE;y++){
			set_tile(g,x,y,t);
			t++;
		}
	}
	printf("Test game_over : Aucune direction possible \n");
	afficher_grille(g);
	printf("test_game_over : %d \n", game_over(g));

	delete_grid(g);
	delete_grid(g2);
}

