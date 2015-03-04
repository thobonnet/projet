#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grid.h"

#include <curses.h>

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
  printw("SCORE:%d\n",grid_score(g));
  printw("move with keypad arrows,zqsd or pav_num and quit with x\n");
}

int
main(int argc, char **argv){
  grid g = new_grid();
  add_tile(g);
  add_tile(g);
  bool playing=true;
  int c;
  dir d;
  initscr(); // Initialisation
  cbreak();  // de
  noecho();  // nCurses
  keypad(stdscr,TRUE);
  afficher_grille_ncurses(g);
  while(playing){
	  c=getch();
	  switch(c){
	  case 122: //Z
	  case 56:  //8
	  case KEY_UP:
	    d=UP;
	    break;
	  case 113: //Q
	  case 52:  //4
	  case KEY_LEFT:
	    d=LEFT;
	    break;
	  case 115: //S
	  case 53:  //5
	  case 50:  //2
	  case KEY_DOWN:
	    d=DOWN;
	    break;
	  case 100: //D
	  case 54:  //6
	  case KEY_RIGHT:
	    d=RIGHT;
	    break;
	  case 120: //X
	    playing=false;
	    break;	    
	  }
	  if(c!=120){
	    play(g,d);
	    clear();
	    afficher_grille_ncurses(g);
	    playing=!game_over(g);
	  }
  }
  endwin();
  printf("GAME OVER\n");
  printf("Your Score is: %lu\n",grid_score(g));
  delete_grid(g);
  return EXIT_SUCCESS;
}
