#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "combat.h"
#include "entities.h"

typedef struct {
  //pointer to combat logic
  CombatManager* manager;

  ALLEGRO_DISPLAY* display;
  ALLEGRO_BITMAP* display_buffer;
  
  //add the background images
  ALLEGRO_BITMAP *background_1;
  ALLEGRO_BITMAP *background_2;
  ALLEGRO_BITMAP *background_3;
  ALLEGRO_BITMAP *background_4;

  ALLEGRO_BITMAP *card_attack;
  ALLEGRO_BITMAP *card_defense;
  ALLEGRO_BITMAP *card_especial;

  ALLEGRO_FONT* font;

} Renderer;

void FillRenderer(Renderer* renderer);

void Render(Renderer* renderer);

void ClearRenderer(Renderer* renderer);

#endif