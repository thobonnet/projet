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

  printf("Test can_move(UP)    : %s \n", can_move(g, UP)?"OK":"KO");
  printf("Test can_move(LEFT)  : %s \n", can_move(g, LEFT)?"OK":"KO");
  printf("Test !can_move(DOWN)  : %s \n", !can_move(g, DOWN)?"OK":"KO");
  printf("Test !can_move(RIGHT) : %s \n", !can_move(g, RIGHT)?"OK":"KO");
	
  printf("Test do_move         : \n");
  afficher_grille(g);
  do_move(g, UP);
  printf("Test do_move(UP)     : \n");
  afficher_grille(g);
  if(!can_move(g,UP)){
    printf("OK \n\n");
  }else{
    printf("KO \n\n");
  }

  printf("Test do_move(LEFT)   : \n");
  do_move(g, LEFT);
  afficher_grille(g);
  if(!can_move(g,LEFT)){
    printf("OK \n\n");
  }else{
    printf("KO \n\n");
  }

  printf("Test do_move(DOWN)   : \n");
  do_move(g, DOWN);
  afficher_grille(g);
  if(!can_move(g,DOWN)){
    printf("OK \n\n");
  }else{
    printf("KO \n\n");
  }

  printf("Test do_move(RIGHT)  : \n");
  do_move(g, RIGHT);
  afficher_grille(g);
  if(!can_move(g,RIGHT)){
    printf("OK \n\n");
  }else{
    printf("KO \n\n");
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

  printf("Test copy_grid : %s \n", b?"OK":"KO");

  t = 1;
  for(int x=0;x<GRID_SIDE;x++){
    for (int y=0;y<GRID_SIDE;y++){
      set_tile(g,x,y,t);
      t++;
    }
  }
  printf("Test game_over : Aucune direction possible \n");
  afficher_grille(g);
  printf("Test_game_over : %s \n", game_over(g)?"OK":"KO");

  delete_grid(g);
  delete_grid(g2);
}

