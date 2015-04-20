#include "strategy.h"
#include "stdlib.h"
#include <assert.h>
#include "grid.h"

void
free_strategy (strategy strat){
  free (strat->mem);
  free (strat->name);
  free (strat);
}

void free_memless_strat (strategy strat){
  free (strat);
}

int
play_move2(grid g,int depth){
  grid h=new_grid();
  int score = 0;
  int score2 = 0;
  if(depth > 0){
    if(can_move(g,RIGHT)){
      copy_grid(g,h);
      play(h,RIGHT);
      score=play_move2(h,depth-1);
    }
    if(can_move(g,UP)){
      copy_grid(g,h);
      play(h,UP);
      score2=play_move2(h,depth-1);
      if(score<score2)
	score=score2;
    }
    if(can_move(g,LEFT)){
      copy_grid(g,h);
      play(h,LEFT);
      score2=play_move2(h,depth-1);
      if(score<score2)
	score=score2;
    }
    if(can_move(g,DOWN)){
      copy_grid(g,h);
      play(h,DOWN);
      score2=play_move2(h,depth-1);
      if(score<score2)
	score=score2;
	  }
  }
  else{
    if(can_move(g,RIGHT)){
      copy_grid(g,h);
      play(h,RIGHT);
      score=grid_score(h);
    }
    if(can_move(g,UP)){
      copy_grid(g,h);
      play(h,UP);
      if(score<grid_score(h))
	score=grid_score(h);
    }
    if(can_move(g,LEFT)){
      copy_grid(g,h);
      play(h,LEFT);
      if(score<grid_score(h))
	score=grid_score(h);
    }
    if(can_move(g,DOWN)){
      copy_grid(g,h);
      play(h,DOWN);
      if(score<grid_score(h))
	score=grid_score(h);
    }
  }
  return score;
}

dir
play_move(strategy strat, grid g){
  grid h=new_grid();
  int depth = 3;
  int score = 0;
  int score2 = 0;
  dir d;
  if(can_move(g,RIGHT)){
    copy_grid(g,h);
    play(h,RIGHT);
    score=play_move2(h,depth);
    d=RIGHT;
  }
  if(can_move(g,UP)){
    copy_grid(g,h);
    play(h,UP);
    score2=play_move2(h,depth);
    if(score<score2){
      score=score2;
      d=UP;
    }
  }
  if(can_move(g,LEFT)){
    copy_grid(g,h);
    play(h,LEFT);
    score2=play_move2(h,depth);
    if(score<score2){
      score=score2;
      d=LEFT;
    }
  }
  if(can_move(g,DOWN)){
    copy_grid(g,h);
    play(h,DOWN);
    score2=play_move2(h,depth);
    if(score<score2){
      score=score2;
      d=DOWN;
    }
  }
  if(!can_move(g,d)){
    if(can_move(g,RIGHT))
      return RIGHT;
    if(can_move(g,UP))
      return UP;
    if(can_move(g,LEFT))
      return LEFT;
    return DOWN;
  }
  return d;
}

strategy
A4_bonnet_jajoux_fast(){
  strategy strat=malloc(sizeof(struct strategy_s));
  assert(strat!=NULL);
  strat->name="A4_bonnet_jajoux_fast";
  strat->play_move=play_move;
  strat->free_strategy=free_memless_strat;
  return strat;
}
