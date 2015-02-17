#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "grid.h"

struct grid_s{
  int score;
  tile** cells;
};

grid new_grid (){
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
    

/*void delete_grid (grid g);
void copy_grid (grid src, grid dst);
unsigned long int grid_score (grid g);
tile get_tile (grid g, int x, int y);
void set_tile (grid g, int x, int y, tile t);
bool can_move (grid g, dir d);
bool game_over (grid g);
void do_move (grid g, dir d);void add_tile (grid g);
void play (grid g, dir d);*/
