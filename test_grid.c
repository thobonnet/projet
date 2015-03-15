#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "grid.h"

#include <curses.h>

static void
usage(char * commande){
  fprintf(stderr,"%s enter a param : terminal, ncurses or a test \n", commande);
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
  return c == 122 || c==56 || c == KEY_UP
    || c == 113 || c==52 || c == KEY_LEFT
    || c == 115 || c==53 || c == KEY_DOWN
    || c == 100 || c==54 || c == KEY_RIGHT;
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
  int c;
  dir d;

  afficher_grille_terminal(g);
  while(playing){
    c=getchar();

    if(validDirection(c))
      d = getDirection(c);
    
    if(c == 120) // X 
      playing = false;
    
    else if(can_move(g,d)){
      play(g,d);
      clear();
      afficher_grille_terminal(g);
      playing=!game_over(g);
    }
  }
    
}

void
auto1(grid g){
	dir d;
	while(!game_over(g)){
		d=RIGHT;
		if(!can_move(g,d)){
		  d=DOWN;
		  if(!can_move(g,d)){
		    d=LEFT;
		    if(!can_move(g,d))
		      d=UP;
		  }
		}
		play(g,d);
	}
}

void
auto2(grid g){
	dir d=UP;
	while(!game_over(g)){
		switch(d){
		case UP:
			d=RIGHT;
			break;
		case RIGHT:
			d=DOWN;
			break;
		case DOWN:
			d=LEFT;
			break;
		case LEFT:
			d=UP;
			break;
		}
		if(can_move(g,d)){
		  play(g,d);
		}
	}
}

void
testx100(int i){
	int* t=malloc(sizeof(int)*20);
	assert(t!=NULL);
	for(int x = 1; x < 20; x++)
		t[x]=0;
	int n=100;
	while(n > 0){
		grid h=new_grid();
		add_tile(h);
		add_tile(h);
		if(i==1)
			auto1(h);
		if(i==2)
			auto2(h);
		t[highest_tile(h)]+=1;
		delete_grid(h);
		n-=1;
	}
	printf("End of Tests \n");
	for(int x = 1; x < 20; x++)
		if(t[x]!=0)
			printf("Number of %d: %d \n", (int)pow(2,x), t[x]);
	free(t);
}

int 
traitementOption(char* option){
	if(strcmp(option, "terminal") == 0)
		return 0;
	if(strcmp(option, "ncurses") == 0)
		return 1;
	if(strcmp(option, "auto1") == 0)
		return 2;
	if(strcmp(option, "auto2") == 0)
		return 3;
	if(strcmp(option, "auto1x100") == 0)
		return 4;
	if(strcmp(option, "auto2x100") == 0)
		return 5;
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
  case 2:
  	auto1(g);
  	break;
  case 3:
  	auto2(g);
  	break;
  case 4:
  	testx100(1);
  	break;
  case 5:
	testx100(2);
	break;
  }
  if(option<4){
    printf("GAME OVER\n");
    printf("Your Score is: %lu\n",grid_score(g));
    printf("The Highest Tile you got was: %d\n",(int)pow(2,highest_tile(g)));
  }
  delete_grid(g);
  return EXIT_SUCCESS;
}
