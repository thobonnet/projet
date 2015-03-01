#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
      printf(" %4d |", (int)pow(2,get_tile(g,x,y)));
    printf("\n");
    for(int i = 0; i < GRID_SIDE; i++)
      printf("+------");
    printf("+\n");
  }
}

int
main(int argc, char **argv){
  grid g = new_grid();
  bool playing=true;
  char c;
  dir d=0;
  while(playing){
	  printf("Enter character: ");
	  c=getchar();
	  printf("character %d\n",c);
	  if(c=='a')
		  d=UP;
	  if(c==76)
		  d=LEFT;
	  if(c==68)
		  d=DOWN;
	  if(c==82)
		  d=RIGHT;
	  else
		  playing=false;
	  play(g,d);
  }
  printf("GAME OVER\n");
  printf("Your Score is: %lu\n",grid_score(g));
  delete_grid(g);
  return EXIT_SUCCESS;
}
