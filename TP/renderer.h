#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

typedef struct {
  ALLEGRO_DISPLAY* display;
  ALLEGRO_BITMAP* display_buffer;
  
  //add the background images
  ALLEGRO_BITMAP *background_1;
  ALLEGRO_BITMAP *background_2;
  ALLEGRO_BITMAP *background_3;
  ALLEGRO_BITMAP *background_4;

  ALLEGRO_FONT* font;

} Renderer;

void FillRenderer(Renderer* renderer);

void Render(Renderer* renderer);

void ClearRenderer(Renderer* renderer);

#endif