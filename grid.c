#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
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

static bool
can(grid g,int x1,int y1,int x2,int y2){
  if(get_tile(g,x1,y1)!=0){
    if(get_tile(g,x2,y2)!=0){
      if(get_tile(g,x1,y1)==get_tile(g,x2,y2))
	return true;}
    return true;}
  return false;
}

bool
can_move (grid g, dir d){
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=1;y<GRID_SIDE;y++){
      switch(d){
      case UP:
	if(can(g,GRID_SIDE-y,x,GRID_SIDE-y-1,x))
	  return true;
	break;
      case LEFT:
	if(can(g,x,GRID_SIDE-y,x,GRID_SIDE-y-1))
	  return true;
	break;
      case DOWN:
	if(can(g,y-1,x,y,x))
	  return true;
	break;
      case RIGHT:
	if(can(g,x,y-1,x,y))
	  return true;
	break;
      }}}
  return false;
}

bool
game_over (grid g){
  return !can_move(g,UP) && !can_move(g,LEFT) && !can_move(g,DOWN) && !can_move(g,RIGHT);
}

/*static void
push(grid g,int x1,int y1,int x2,int y2){
  
}*/

void
do_move (grid g, dir d){
  if(can_move(g,d)){
    switch(d){
    case UP:
      for(int y=0;y<GRID_SIDE;y++){
	int i=0;
	for(int x=0;x<GRID_SIDE;x++){
	  if(get_tile(g,x,y)!=0 && x!=i){
	    set_tile(g,i,y,get_tile(g,x,y));
	    set_tile(g,x,y,0);
	    i+=1;
	  }
	}
	for(int x=1;x<GRID_SIDE;x++){
	  if(get_tile(g,x,y)!=0 && get_tile(g,x,y)==get_tile(g,x-1,y)){
	    set_tile(g,x-1,y,get_tile(g,x,y)+1);
	    g->score+=pow(2,get_tile(g,x-1,y));
	    set_tile(g,x,y,0);
	  }
	}
	i=0;
	for(int x=0;x<GRID_SIDE;x++){
	  if(get_tile(g,x,y)!=0 && x!=i){
	    set_tile(g,i,y,get_tile(g,x,y));
	    set_tile(g,x,y,0);
	    i+=1;
	  }
	}
      }
      break;
    case LEFT:
      for(int x=0;x<GRID_SIDE;x++){
	int i=GRID_SIDE;
	for(int y=GRID_SIDE;y>=0;y--){
	  if(get_tile(g,x,y)!=0 && y!=i){
	    set_tile(g,x,i,get_tile(g,x,y));
	    set_tile(g,x,y,0);
	    i-=1;
	  }
	}
	for(int y=GRID_SIDE-1;y>=0;y--){
	  if(get_tile(g,x,y)!=0 && get_tile(g,x,y)==get_tile(g,x,y+1)){
	    set_tile(g,x,y+1,get_tile(g,x,y)+1);
	    g->score+=pow(2,get_tile(g,x,y+1));
	    set_tile(g,x,y,0);
	  }
	}
	i=GRID_SIDE;
	for(int y=GRID_SIDE;y>=0;y--){
	  if(get_tile(g,x,y)!=0 && y!=i){
	    set_tile(g,x,i,get_tile(g,x,y));
	    set_tile(g,x,y,0);
	    i-=1;
	  }
	}
      }
      break;
    case DOWN:
      for(int y=0;y<GRID_SIDE;y++){
	int i=GRID_SIDE;
	for(int x=GRID_SIDE;x>=0;x--){
	  if(get_tile(g,x,y)!=0 && x!=i){
	    set_tile(g,i,y,get_tile(g,x,y));
	    set_tile(g,x,y,0);
	    i-=1;
	  }
	}
	for(int x=GRID_SIDE-1;x>=0;x--){
	  if(get_tile(g,x,y)!=0 && get_tile(g,x,y)==get_tile(g,x+1,y)){
	    set_tile(g,x+1,y,get_tile(g,x,y)+1);
	    g->score+=pow(2,get_tile(g,x+1,y));
	    set_tile(g,x,y,0);
	  }
	}
	i=GRID_SIDE;
	for(int x=0;x<GRID_SIDE;x++){
	  if(get_tile(g,x,y)!=0 && x!=i){
	    set_tile(g,i,y,get_tile(g,x,y));
	    set_tile(g,x,y,0);
	    i-=1;
	  }
	}
      }
      break;
    case RIGHT:
      for(int x=0;x<GRID_SIDE;x++){
	int i=0;
	for(int y=0;y<GRID_SIDE;y++){
	  if(get_tile(g,x,y)!=0 && y!=i){
	    set_tile(g,x,i,get_tile(g,x,y));
	    set_tile(g,x,y,0);
	    i+=1;
	  }
	}
	for(int y=1;y<GRID_SIDE;y++){
	  if(get_tile(g,x,y)!=0 && get_tile(g,x,y)==get_tile(g,x,y-1)){
	    set_tile(g,x,y-1,get_tile(g,x,y)+1);
	    g->score+=pow(2,get_tile(g,x,y-1));
	    set_tile(g,x,y,0);
	  }
	}
	i=0;
	for(int y=0;y<GRID_SIDE;y++){
	  if(get_tile(g,x,y)!=0 && y!=i){
	    set_tile(g,x,i,get_tile(g,x,y));
	    set_tile(g,x,y,0);
	    i+=1;
	  }
	}
      }
      break;
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
  int c=rand()%(n+1);
  int v=rand()%100;
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
