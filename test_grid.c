#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grid.h"

#include <curses.h>



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

void
afficher_grille_ncurses(grid g){
  for(int i = 0; i < GRID_SIDE; i++){
    printw("+------");
  }
  printw("+\n");

  for(int x = 0; x < GRID_SIDE; x++){
    printw("|");
    for(int y = 0; y < GRID_SIDE; y++)
      printw(" %4d |", get_tile(g,x,y)==0?0:(int)pow(2,get_tile(g,x,y)));
    printw("\n");
    for(int i = 0; i < GRID_SIDE; i++)
      printw("+------");
    printw("+\n");
  }
}

int
main(int argc, char **argv){
  grid g = new_grid();
  add_tile(g);
  bool playing=true;
  int c;
  dir d;
  initscr(); // Initialisation
  cbreak();  // de
  noecho();  // nCurses
  afficher_grille_ncurses(g);
  while(playing){
	  printw("Enter direction: ");
	  c=getch();
	  printw("character %d\n",c);
	  switch(c){
	  case 122:
	    d=UP;
	    break;
	  case 113:
	    d=LEFT;
	    break;
	  case 115:
	    d=DOWN;
	    break;
	  case 100:
	    d=RIGHT;
	    break;
	  default:
	    playing=false;
	  }
	  play(g,d);
	  clear();
	  afficher_grille_ncurses(g);
	  playing=!game_over(g);
  }
  printf("GAME OVER\n");
  printf("Your Score is: %lu\n",grid_score(g));
  delete_grid(g);
  
  endwin();
  
  return EXIT_SUCCESS;
}
