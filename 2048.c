#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <MLV/MLV_all.h>
#include "grid.h"

int
pickColor(int i){
  if(i == 2)
    return MLV_rgba(238,228,218,255);
  if(i == 4)
    return MLV_rgba(237,224,200,255);
  if(i == 8)
    return MLV_rgba(242,177,121,255);
  if(i == 16)
    return MLV_rgba(245,149,99,255);
  if(i == 32)
    return MLV_rgba(246,124,95,255);
  if(i == 64)
    return MLV_rgba(246,94,59,255);
  if(i == 128)
    return MLV_rgba(237,207,114,255);
  if(i == 256)
    return MLV_rgba(237,204,97,255);
  if(i == 512)
    return MLV_rgba(237,200,80,255);
  if(i == 1024)
    return MLV_rgba(237,197,63,255);
  if(i == 2048)
    return MLV_rgba(237,194,46,255);
  return MLV_rgba(89,85,81,255);
}

void
afficherGrille(grid g){
  int cordx = 0;
  int cordy = 10;

  char buffer[10];
  for(int i = 0; i < GRID_SIDE; i++){
    for(int j = 0; j < GRID_SIDE; j++){
      
      int tile = get_tile(g,i,j)==0?0:(int)pow(2,get_tile(g,i,j));
      sprintf(buffer, "%d", tile);

      int color = pickColor(tile);

      MLV_draw_text_box(cordx, cordy, 100, 100,buffer,
        11,
        MLV_COLOR_WHITE, MLV_rgba(89,85,81,255), color,
        MLV_TEXT_LEFT,
        MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
      cordx += 100;
    }
    cordx = 0;
    cordy += 100;
    /*sprintf(buffer, "SCORE : %lu", grid_score(g));
    MLV_draw_text_box(cordx, cordy, 200, 100,buffer,
        11,
        MLV_COLOR_WHITE, MLV_rgba(89,85,81,255), MLV_COLOR_WHITE,
        MLV_TEXT_LEFT,
        MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);*/
  }
}

int 
main(int argc, char *argv[]){

  MLV_Keyboard_button touche;

  grid g = new_grid();
  add_tile(g);

  MLV_create_window( "2048", "2048", (GRID_SIDE + 1) * 100, (GRID_SIDE + 1) * 100 );

  afficherGrille(g);
  MLV_actualise_window();

  while(!game_over(g)){
    MLV_wait_keyboard(&touche, NULL, NULL);
    if(touche == MLV_KEYBOARD_UP)
      play(g, UP);

    if(touche == MLV_KEYBOARD_LEFT)
      play(g, LEFT);

    if(touche == MLV_KEYBOARD_DOWN)
      play(g, DOWN);

    if(touche == MLV_KEYBOARD_RIGHT)
      play(g, RIGHT);

    afficherGrille(g);
    MLV_actualise_window();
  }

  MLV_wait_keyboard(&touche, NULL, NULL);
  MLV_wait_seconds(2);
  MLV_free_window();

  return EXIT_SUCCESS;
}
