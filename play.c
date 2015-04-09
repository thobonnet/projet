#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "grid.h"

#include <curses.h>

//définition des touches
#define TZ 122
#define T8 56
#define TQ 113
#define T4 52
#define TS 115
#define T5 53
#define TD 100
#define T6 54
#define TX 120

static void
usage(char * commande){
  fprintf(stderr,"%s enter a param : terminal or ncurses\n", commande);
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
  printf("move with zqsd or pav_num and quit with x\n");
 }

int
highest_tile(grid g){
	int t=0;
	for(int x = 0; x < GRID_SIDE; x++){
	  for(int y = 0; y < GRID_SIDE; y++){
		if(t < get_tile(g,x,y))
		  t=get_tile(g,x,y);
		}
	}
	return t;
}

bool
validDirection(int c){
  return c == TZ || c==T8 || c == KEY_UP
    || c == TQ || c==T4 || c == KEY_LEFT
    || c == TS || c==T5 || c == KEY_DOWN
    || c == TD || c==T6 || c == KEY_RIGHT;
}
  
dir
getDirection(int c){
   switch(c){
   case TZ:
   case T8:
   case KEY_UP:
     return UP;
     break;
   case TQ:
   case T4:
   case KEY_LEFT:
     return LEFT;
     break;
   case TS:
   case T5:
   case KEY_DOWN:
     return DOWN;
     break;
   case TD:
   case T6:
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

    if(c == TX) 
      playing = false;
    
    else if(can_move(g,d)){
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
  bool change=true;
  int c;
  dir d;

  afficher_grille_terminal(g);
  while(playing){
    c=getchar();

    if(validDirection(c)){
      d = getDirection(c);
      change=true;
    }
    
    if(c == TX)
      playing = false;
    
    else if(can_move(g,d) && change){
      play(g,d);
      afficher_grille_terminal(g);
      playing=!game_over(g);
    }
    change=false;
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
  srand(time(NULL));   // Initialisation de random
  switch(option){
  case 0:
    play_terminal(g);
    break;
  case 1:
    play_ncurses(g);
    break;
  }
  printf("GAME OVER\n");
  printf("Your Score is: %lu\n",grid_score(g));
  printf("The Highest Tile you got was: %d\n",(int)pow(2,highest_tile(g)));
  delete_grid(g);
  return EXIT_SUCCESS;
}
