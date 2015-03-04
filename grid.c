#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "grid.h"

struct grid_s{
  unsigned long int score;
  tile** cells;
};

grid
new_grid (){
  grid g=malloc(sizeof(struct grid_s));
  assert(g!=NULL);
  g->score=0;
  g->cells=malloc(GRID_SIDE*sizeof(tile*));
  assert(g->cells!=NULL);
  for(int x=0;x<GRID_SIDE;x++){
    g->cells[x]=malloc(GRID_SIDE*sizeof(tile));
    assert(g->cells[x]!=NULL);
    for(int y=0;y<GRID_SIDE;y++)
      g->cells[x][y]=0;
  }
  return g;
}
    
void
delete_grid (grid g){
  for(int x=0;x<GRID_SIDE;x++)
    free(g->cells[x]);
  free(g->cells);
  free(g);
}

void
copy_grid (grid src, grid dst){
  dst->score=src->score;
  for(int x=0;x<GRID_SIDE;x++)
    for(int y=0;y<GRID_SIDE;y++)
      dst->cells[x][y]=src->cells[x][y];
}

unsigned long int
grid_score (grid g){
  return g->score;
}

tile
get_tile (grid g, int x, int y){
  assert((x>=0 && x<GRID_SIDE) && (y>=0 && y<GRID_SIDE));
  return g->cells[x][y];
}

void
set_tile (grid g, int x, int y, tile t){
  g->cells[x][y]=t;
}

bool
can_move (grid g, dir d){
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=1;y<GRID_SIDE;y++){
      switch(d){
      case UP:
	if(get_tile(g,y,x)!=0 && (get_tile(g,y-1,x)==0 || get_tile(g,y,x)==get_tile(g,y-1,x)))
	  return true;
	break;
      case LEFT:
	if(get_tile(g,x,y)!=0 && (get_tile(g,x,y-1)==0 || get_tile(g,x,y)==get_tile(g,x,y-1)))
	  return true;
	break;
      case DOWN:
	if(get_tile(g,y-1,x)!=0 && (get_tile(g,y,x)==0 || get_tile(g,y,x)==get_tile(g,y-1,x)))
	  return true;
	break;
      case RIGHT:
	if(get_tile(g,x,y-1)!=0 && (get_tile(g,x,y)==0 || get_tile(g,x,y)==get_tile(g,x,y-1)))
	  return true;
	break;
      }}}
  return false;
}

bool
game_over (grid g){
  return !can_move(g,UP) && !can_move(g,LEFT) && !can_move(g,DOWN) && !can_move(g,RIGHT);
}

//fait bouger la tuile en (x1,y1) a la position (x2,y2).
static void
move_tile(grid g,int x1,int y1,int x2,int y2){
  set_tile(g,x2,y2,get_tile(g,x1,y1));
  set_tile(g,x1,y1,0);
}

//fusionne la tuile en (x1,y1) a la tuile en (x2,y2) la nouvelle tuile est a la place de cette derniere, on ajoute egalement la valeur de la nouvelle tuile au score.
static void
tile_fusion(grid g,int x1,int y1,int x2,int y2){
  set_tile(g,x2,y2,get_tile(g,x1,y1)+1);
  g->score+=pow(2,get_tile(g,x1,y1));
  set_tile(g,x1,y1,0);
}

void
do_move (grid g, dir d){
  if(can_move(g,d)){
    int i;	//pointeur sur une cellule vide ou n'ayant pas encore effectue de fusion et sans cellule vide qui la precede.
    for(int x=0;x<GRID_SIDE;x++){
      i=0;
      for(int y=1;y<GRID_SIDE;y++){
	switch(d){
	case UP:
	  if(get_tile(g,y,x)!=0){                  //si la cellule indiquee par le pointeur est vide on lui donne la tuile de cette cellule.
	    if(get_tile(g,i,x)==0)	             //on verifie que la cellule regardee est pleine sinon on passe a la suivante.
	      move_tile(g,y,x,i,x);
	    else{
	      if(get_tile(g,y,x)==get_tile(g,i,x)) //si la cellule indiquee par le pointeur peu fusionner avec cette cellule on le fait.
		tile_fusion(g,y,x,i,x);
	      else			             //sinon on l'accole a la cellule pointee.
		if(y!=i+1)
		  move_tile(g,y,x,i+1,x);}
	    i+=1;		                     //on pointe maintenant la cellule deplacee dans les deux derniers cas.
	  }
	  break;
	case LEFT:
	  if(get_tile(g,x,y)!=0){
	    if(get_tile(g,x,i)==0)
	      move_tile(g,x,y,x,i);
	    else{
	      if(get_tile(g,x,y)==get_tile(g,x,i))
		tile_fusion(g,x,y,x,i);
	      else
		if(y!=i+1)
		  move_tile(g,x,y,x,i+1);}
	    i+=1;
	  }
	  break;
	case DOWN:
	  if(get_tile(g,GRID-SIDE-1-y,x)!=0){
	    if(get_tile(g,GRID_SIDE-1-i,x)==0)
	      move_tile(g,GRID_SIDE-1-y,x,GRID_SIDE-1-i,x);
	    else{
	      if(get_tile(g,GRID_SIDE-1-y,x)==get_tile(g,GRID_SIDE-1-i,x))
		tile_fusion(g,GRID_SIDE-1-y,x,GRID_SIDE-1-i,x);
	      else
		if(y!=i-1)
		  move_tile(g,GRID_SIDE-1-y,x,GRID_SIDE-2-i,x);}
	    i+=1;
	  }
	  break;
	case RIGHT:
	  if(get_tile(g,x,GRID_SIDE-1-y)!=0){
	    if(get_tile(g,x,GRID_SIDE-1-i)==0)
	      move_tile(g,x,GRID_SIDE-1-y,x,GRID_SIDE-1-i);
	    else{
	      if(get_tile(g,x,GRID_SIDE-1-y)==get_tile(g,x,GRID_SIDE-1-i))
		tile_fusion(g,x,GRID_SIDE-1-y,x,GRID_SIDE-1-i);
	      else
		if(y!i-1)
		  move_tile(g,x,GRID_SIDE-1-y,x,GRID_SIDE-2-i);}
	    i+=1;
	  }
	  break;
	}
      }
    }
  }
}

void
add_tile (grid g){
  int** t=malloc(sizeof(int*)*GRID_SIDE*GRID_SIDE);
  assert(t!=NULL);
  int n=0;
  for(int y=0;y<GRID_SIDE;y++){
    for(int x=0;x<GRID_SIDE;x++){
      if(get_tile(g,x,y)==0){
	t[n]=malloc(sizeof(int)*2);
	assert(t[n]!=NULL);
	t[n][0]=x;
	t[n][1]=y;
	n+=1;
      }
    }
  }
  srand(time(NULL)+n);
  int c=rand()%(n+1);
  int v=rand()%100;
  printf("c:%d ,v:%d \n",c,v);
  set_tile(g,t[c][0],t[c][1],v>90?2:1);
  for(int i=0;i<n;i++)
    free(t[i]);
  free(t);
}

void
play (grid g, dir d){
  if(can_move(g,d)){
    do_move(g,d);
    add_tile(g);
  }
}
