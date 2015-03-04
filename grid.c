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
	if(get_tile(g,y,x)!=0 && (get_tile(g,y-1,x)==0 || get_tile(g,y,x)==get_tile(g,y-1,x))) //on vérifie si une tuile peu bouger ou fusionner dans la cellule précédente sinon on passe à une autre tuile.
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
  if(x1!=x2 || y1!=y2){
    set_tile(g,x2,y2,get_tile(g,x1,y1));
    set_tile(g,x1,y1,0);
  }
}

//fusionne la tuile en (x1,y1) a la tuile en (x2,y2) la nouvelle tuile est a la place de cette derniere, on ajoute egalement la valeur de la nouvelle tuile au score.
static void
tile_fusion(grid g,int x1,int y1,int x2,int y2){
  set_tile(g,x2,y2,get_tile(g,x1,y1)+1);
  g->score+=pow(2,get_tile(g,x2,y2));
  set_tile(g,x1,y1,0);
}

static int
move(grid g,int x,int y,int i,int j,dir d){
  int a=0;
  if(get_tile(g,x,y)!=0){                    //si la cellule indiquee par le pointeur est vide on lui donne la tuile de cette cellule.
    if(get_tile(g,i,j)==0)	             //on verifie que la cellule regardee est pleine sinon on passe a la suivante.
      move_tile(g,x,y,i,j);
    else{
      if(get_tile(g,x,y)==get_tile(g,i,j))   //si la cellule indiquee par le pointeur peu fusionner avec cette cellule on le fait.
	tile_fusion(g,x,y,i,j);
      else			             //sinon on l'accole a la cellule pointee.
	switch(d){
	case UP:
	  move_tile(g,x,y,i+1,j);
	  break;
	case LEFT:
	  move_tile(g,x,y,i,j+1);
	  break;
	case DOWN:
	  move_tile(g,x,y,i-1,j);
	  break;
	case RIGHT:
	  move_tile(g,x,y,i,j-1);
	  break;}
      a=1;}		                     //on pointe maintenant la cellule deplacee dans les deux derniers cas.
  }
  return a;
}

void
do_move (grid g, dir d){
  if(can_move(g,d)){
    int i;	//pointeur sur une cellule vide ou n'ayant pas encore effectue de fusion et sans cellule vide qui la precede.
    for(int x=0;x<GRID_SIDE;x++){ //parcours de la grille.
      i=0;
      for(int y=1;y<GRID_SIDE;y++){
	switch(d){
	case UP:
	  i+=move(g,y,x,i,x,d);
	  break;
	case LEFT:
	  i+=move(g,x,y,x,i,d);
	  break;
	case DOWN:
	  i+=move(g,GRID_SIDE-1-y,x,GRID_SIDE-1-i,x,d);
	  break;
	case RIGHT:
	  i+=move(g,x,GRID_SIDE-1-y,x,GRID_SIDE-1-i,d);
	  break;
	}
      }
    }
  }
}

void
add_tile (grid g){
  int** t=malloc(sizeof(int*)*GRID_SIDE*GRID_SIDE);//initialisation d'un tableau pointant les cellules vides.
  assert(t!=NULL);
  int n=0; //nombre de cellules vide de la grille.
  for(int y=0;y<GRID_SIDE;y++){
    for(int x=0;x<GRID_SIDE;x++){
      if(get_tile(g,x,y)==0){ //si une cellule est vide on l'ajoute au tableau.
	t[n]=malloc(sizeof(int)*2);
	assert(t[n]!=NULL);
	t[n][0]=x;
	t[n][1]=y;
	n+=1;
      }
    }
  }
  srand(time(NULL)+n);
  int c=rand()%(n);//on selectionne au hasard une cellule vide
  int v=rand()%1000;//on utilise cette valeur pour ajouter une tuile de valeur 4 une fois sur 10.
  set_tile(g,t[c][0],t[c][1],v>900?2:1);
  for(int i=0;i<n;i++)//on libere le tableau de cellules vide
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
