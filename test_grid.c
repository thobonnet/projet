#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

void
afficher_grille(grid g){
  for(int x = 0; x < GRID_SIDE; x++){
    for(int y = 0; y < GRID_SIDE; y++){
      printf("%d ", g->cells[x][y]);
    }
    printf("\n");
  }
}

int
main(int argc, char **argv){
  grid g = new_grid();
  afficher_grille(g);
	return EXIT_SUCCESS;
}
