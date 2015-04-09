#include "strategy.h"
#include "stdlib.h"
#include <assert.h>
#include "grid.h"

dir
play_move(strategy strat, grid g){
  if(can_move(g,UP))
     return UP;
  if(can_move(g,RIGHT))
     return RIGHT;
  if(can_move(g,DOWN))
     return DOWN;
  return LEFT;
}

strategy
strat_fast(){
  strategy strat=malloc(sizeof(struct strategy_s));
  assert(strat!=NULL);
  strat->name="strat_fast";
  strat->play_move=play_move;
  return strat;
}

void free_memless_strat (strategy strat){
  free (strat);
}
