#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <MLV/MLV_all.h>
#include "grid.h"

#define COLOR_BACKGROUND MLV_rgba(250,248,239,255)
#define COLOR_BACKGROUND_POPUP MLV_rgba(250,248,239,170)
#define COLOR_TEXT MLV_rgba(119,110,101,255)
#define COLOR_GRID_BORDER MLV_rgba(204,192,179,255)

#define LARGEUR (GRID_SIDE)*100
#define HAUTEUR (GRID_SIDE +2)*100


/* Return the color of a tile depend on his value */
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
  if( i > 2048)
    return MLV_rgba(236, 240, 241,255);
  return COLOR_TEXT;
}

void
afficherGrille(grid g){
  int cordx = 0;
  int cordy = 10;

  // Font initialisation
  MLV_Font* font = MLV_load_font( "fonts/helveticaneue.ttf" , 30 );

  // Background
  MLV_draw_text_box(0, 0, GRID_SIDE * 100, (GRID_SIDE + 2) * 100, "",
        11, MLV_COLOR_WHITE, MLV_COLOR_BLACK, COLOR_BACKGROUND,
        MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
  
  for(int i = 0; i < GRID_SIDE; i++){
    char buffer[1000];
    for(int j = 0; j < GRID_SIDE; j++){
      
      int tile = get_tile(g,i,j)==0?0:(int)pow(2,get_tile(g,i,j));
      sprintf(buffer, "%d", tile);

      int color = pickColor(tile);

      MLV_draw_text_box_with_font(cordx, cordy, 100, 100,buffer, font,
        11, COLOR_GRID_BORDER, COLOR_TEXT, color, MLV_TEXT_LEFT,
        MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

      cordx += 100;
    }
    cordx = 0;
    cordy += 100;
    
    sprintf(buffer, "SCORE \n %lu", grid_score(g));
    MLV_draw_text_box_with_font(cordx, cordy, LARGEUR, 100,buffer, font,
        6, COLOR_BACKGROUND, COLOR_TEXT, COLOR_BACKGROUND, MLV_TEXT_CENTER,
        MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
  }

  MLV_Font* font_footer = MLV_load_font( "fonts/helveticaneue.ttf" , 20 );
  MLV_draw_text_box_with_font(0, HAUTEUR - 100, LARGEUR, 100,
   "Play with ZQSD || 8456 || Arrows keys\n Press X to QUIT.", 
    font_footer, 6,COLOR_BACKGROUND, COLOR_TEXT, COLOR_BACKGROUND, 
    MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
  MLV_free_font(font_footer);

  // Free font
  MLV_free_font(font);

}

bool
validDirection(MLV_Keyboard_button c){
  return c == MLV_KEYBOARD_z || c==MLV_KEYBOARD_8|| c == MLV_KEYBOARD_UP
    || c == MLV_KEYBOARD_q || c==MLV_KEYBOARD_4 || c == MLV_KEYBOARD_LEFT
    || c == MLV_KEYBOARD_s || c==MLV_KEYBOARD_5 || c == MLV_KEYBOARD_DOWN
    || c == MLV_KEYBOARD_d || c==MLV_KEYBOARD_6 || c == MLV_KEYBOARD_RIGHT;
}

dir
getDirection(MLV_Keyboard_button c){
   switch(c){
   case MLV_KEYBOARD_z:
   case MLV_KEYBOARD_KP8:
   case MLV_KEYBOARD_UP:
     return UP;
     break;
   case MLV_KEYBOARD_q:
   case MLV_KEYBOARD_KP4:
   case MLV_KEYBOARD_LEFT:
     return LEFT;
     break;
   case MLV_KEYBOARD_s:
   case MLV_KEYBOARD_KP5:
   case MLV_KEYBOARD_DOWN:
     return DOWN;
     break;
   case MLV_KEYBOARD_d:
   case MLV_KEYBOARD_KP6:
   case MLV_KEYBOARD_RIGHT:
     return RIGHT;
     break;  
  default:
      break;

   }
  return UP;
   
   
}

bool
quit(MLV_Keyboard_button c){
  return c == MLV_KEYBOARD_x;
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

void
showWin(grid g){
  MLV_Font* font = MLV_load_font( "fonts/helveticaneue.ttf" , 25 );
  MLV_draw_text_box_with_font(0, 0, LARGEUR, HAUTEUR,"YOU WON ! \n Press c to keep playing, x to quit.", font,
        11,COLOR_GRID_BORDER, MLV_COLOR_WHITE, COLOR_BACKGROUND_POPUP,
        MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
  MLV_free_font(font);
  MLV_actualise_window();

}

void
showGameOver(grid g){
  MLV_Font* font = MLV_load_font( "fonts/helveticaneue.ttf" , 40 );
  MLV_draw_text_box_with_font(0, 0, LARGEUR, HAUTEUR,"GAME OVER ! \n Press a key to quit.", font,
        11,COLOR_GRID_BORDER, MLV_COLOR_WHITE, COLOR_BACKGROUND_POPUP,
        MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
  MLV_free_font(font);
  MLV_actualise_window();
  MLV_wait_keyboard(NULL,NULL,NULL);

}


int 
main(int argc, char *argv[]){

  bool playing = true;
  bool keep = false;
  int d;

  grid g = new_grid();
  add_tile(g);

  MLV_create_window( "2048", "2048", LARGEUR, HAUTEUR );

  afficherGrille(g);
  MLV_actualise_window();

  do{
    MLV_Keyboard_button touche;
    MLV_wait_keyboard(&touche, NULL, NULL);

    if(validDirection(touche)){
      d=getDirection(touche);
      if(can_move(g,d)){
        play(g,d);
        afficherGrille(g);
        MLV_actualise_window();
        playing = !game_over(g);
      }
    }

    if(highest_tile(g) == 11 && keep == false){ //2048 ou continuer de jouer
      showWin(g);
      bool ok = false;
      while(!ok){
        MLV_wait_keyboard(&touche,NULL,NULL);
        if(touche == MLV_KEYBOARD_c){
          keep = true;
          ok = true;
          afficherGrille(g);
          MLV_actualise_window();
        }else if(touche == MLV_KEYBOARD_x){
          playing = false;
          ok = true;
        }
      }
    }

    if(quit(touche))
      playing = false;

  }while(playing);

  if(game_over(g))
    showGameOver(g);

  MLV_wait_seconds(1);
  MLV_free_window();
  printf("Your score is : %lu\n", grid_score(g));
  delete_grid(g);

  return EXIT_SUCCESS;
}