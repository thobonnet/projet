#include <stdio.h>
#include <stdlib.h>
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
      printf(" %4d |", get_tile(g,x,y));
    printf("\n");
    for(int i = 0; i < GRID_SIDE; i++)
      printf("+------");
    printf("+\n");
  }
}

int
main(int argc, char **argv){
  grid g = new_grid();
  afficher_grille(g);
  return EXIT_SUCCESS;
}
