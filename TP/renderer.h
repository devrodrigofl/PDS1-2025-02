#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "combat.h"
#include "entities.h"

typedef enum Asset{
  health_bar,
  shield_bar,
} Asset;

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
  ALLEGRO_BITMAP *card_hybrid;

  ALLEGRO_BITMAP *strong_enemy;
  ALLEGRO_BITMAP *weak_enemy_idle[16];
  ALLEGRO_BITMAP *boss_enemy;
  ALLEGRO_BITMAP *player_idle[12];

  ALLEGRO_BITMAP *health_bar;
  ALLEGRO_BITMAP *shield_bar;
  ALLEGRO_BITMAP *energy_indicator;

  ALLEGRO_BITMAP *discard_pile;
  ALLEGRO_BITMAP *deck_pile;
  
  ALLEGRO_FONT* font;

  int menu_selection;

} Renderer;

void FillRenderer(Renderer* renderer);

void Render(Renderer* renderer);

void ClearRenderer(Renderer* renderer);

#endif