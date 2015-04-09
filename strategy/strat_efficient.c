#include "strategy.h"
#include "stdlib.h"
#include <assert.h>
#include "grid.h"

dir
play_move(strategy strat, grid g){

}

strategy
strat_efficient(){
  strategy strat=malloc(sizeof(struct strategy_s));
  assert(strat!=NULL);
  strat->name="strat_efficient";
  strat->play_move=play_move;
  return strat;
}

void free_memless_strat (strategy strat){
  free (strat);
}
