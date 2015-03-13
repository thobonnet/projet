#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "grid.h"

#include <curses.h>

static void
usage(char * commande){
  fprintf(stderr,"%s enter a param : terminal or ncurses \n", commande);
  exit(EXIT_FAILURE);
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
  printw("SCORE:%d\n",grid_score(g));
  printw("move with keypad arrows,zqsd or pav_num and quit with x\n");
}

void
afficher_grille_terminal(grid g){
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
  printf("SCORE:%lu\n",grid_score(g));
  printf("move with zqsd and quit with x\n");
 }

bool
validDirection(int c){
  return c == 122 || c == KEY_UP
    || c == 113 || c == KEY_LEFT
    || c == 115 || c == KEY_DOWN
    || c == 100 || c == KEY_RIGHT;
}

dir
getDirection(int c){
   switch(c){
   case 122: // Z
   case 56:  // 8
   case KEY_UP:
     return UP;
     break;
   case 113: // Q
   case 52:  // 4
   case KEY_LEFT:
     return LEFT;
     break;
   case 115: // S
   case 53:  // 5
   case KEY_DOWN:
     return DOWN;
     break;
   case 100: // D
   case 54:  // 6
   case KEY_RIGHT:
     return RIGHT;
     break;	    
   }
   return UP;
   
}

void
play_ncurses(grid g){
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

    if(validDirection(c))
      d = getDirection(c);

    if(c == 120) // X 
      playing = false;
    
    if(c!=120){
      play(g,d);
      clear();
      afficher_grille_ncurses(g);
      playing=!game_over(g);
    }
  }
  endwin();
}

void
play_terminal(grid g){
  bool playing=true;
  int c;
  dir d;

  afficher_grille_terminal(g);
  while(playing){
    c=getchar();

    if(validDirection(c))
      d = getDirection(c);
    
    if(c == 120) // X 
      playing = false;
    
    if(c!=120){
      play(g,d);
      clear();
      afficher_grille_terminal(g);
      playing=!game_over(g);
    }
  }
    
}

int 
traitementOption(char* option){
	if(strcmp(option, "terminal") == 0)
		return 0;
	if(strcmp(option, "ncurses") == 0)
		return 1;
	return -1;

}

int
main(int argc, char **argv){
	if ((argc != 2) || (traitementOption(argv[1]) == -1))
		usage(argv[0]);

  int option = traitementOption(argv[1]);

 	grid g = new_grid(); // Initialisation de
 	add_tile(g);         // de la
 	add_tile(g);         // grille de depart

  if(option == 1)
    play_ncurses(g);
  if(option == 0)
  	play_terminal(g);

  printf("GAME OVER\n");
  printf("Your Score is: %lu\n",grid_score(g));
  delete_grid(g);
  return EXIT_SUCCESS;
}
