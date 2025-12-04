#include "renderer.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "utils.h"

void DrawScaledText(ALLEGRO_FONT* font, ALLEGRO_COLOR color, float x, float y, float xscale, float yscale, int alignment, const char* text) {
  ALLEGRO_TRANSFORM transform;
  al_identity_transform(&transform);  // Start with an identity transform
  al_scale_transform(&transform, xscale, yscale);  // Apply scaling (e.g., sx=2.0, sy=2.0 for double size)
  al_use_transform(&transform);  // Use the transform for subsequent drawing

  al_draw_multiline_text(font, color, x, y, 150, 10, alignment, text);
  // al_draw_text(font, color, x, y, alignment, text);
  al_identity_transform(&transform);
  al_use_transform(&transform);  // Use the transform for subsequent drawing
}

void DrawCenteredScaledText(ALLEGRO_FONT* font, ALLEGRO_COLOR color, float x, float y, float xscale, float yscale, char* text) {
  DrawScaledText(font, color, x, y, xscale, yscale, ALLEGRO_ALIGN_CENTRE, text);
}

void DrawVerticalGradient(float x, float y, float w, float h, ALLEGRO_COLOR top_color, ALLEGRO_COLOR bottom_color) {
    ALLEGRO_VERTEX v[4];

    // upper left
    v[0].x = x;     
    v[0].y = y;     
    v[0].z = 0; 
    v[0].color = top_color;

    // upper right
    v[1].x = x + w; 
    v[1].y = y;     
    v[1].z = 0; 
    v[1].color = top_color;

    // bottom right
    v[2].x = x + w; 
    v[2].y = y + h; 
    v[2].z = 0; 
    v[2].color = bottom_color;

    // bottom left
    v[3].x = x;     
    v[3].y = y + h; 
    v[3].z = 0; 
    v[3].color = bottom_color;

    al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
}

void FillRenderer(Renderer* renderer) {
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
  al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

  renderer->display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
  must_init(renderer->display, "display");

  renderer->display_buffer =
      al_create_bitmap(DISPLAY_BUFFER_WIDTH, DISPLAY_BUFFER_HEIGHT);
  must_init(renderer->display_buffer, "display buffer");

  //load the background images
  renderer->background_1 = 
      al_load_bitmap("assets/back 1.png");
  must_init(renderer->background_1, "back1");

  renderer->background_2 = 
      al_load_bitmap("assets/back 2.png");
  must_init(renderer->background_2, "back2");

  renderer->background_3 = 
      al_load_bitmap("assets/back 3.png");    
  must_init(renderer->background_3, "back3");

  renderer->background_4 = 
      al_load_bitmap("assets/back 4.png");    
  must_init(renderer->background_4, "back4");

  //load the card images
  renderer->card_attack = 
      al_load_bitmap("assets/card_attack.png");
  must_init(renderer->card_attack, "card_attack");

  renderer->card_defense = 
      al_load_bitmap("assets/card_defense.png");
  must_init(renderer->card_defense, "card_defense");

  renderer->card_especial = 
      al_load_bitmap("assets/card_especial.png");
  must_init(renderer->card_especial, "card_especial");
  
  //load the player_idle
  for (int i = 0; i < 12; i++) {
    char filename[50];

      sprintf(filename, "assets/player_idle/player_idle_%d.png", i + 1); 
        
      renderer->player_idle[i] = al_load_bitmap(filename);
      must_init(renderer->player_idle[i], filename);
  }

  //load the strong_enemy_idle
  for (int i = 0; i < 16; i++) {
    char filename[50];

      if(i < 9) {
        sprintf(filename, "assets/weak_enemy_idle/Idle_Body_270_000%d.png", i + 1); 
      }
      else sprintf(filename, "assets/weak_enemy_idle/Idle_Body_270_00%d.png", i + 1);
        
      renderer->weak_enemy_idle[i] = al_load_bitmap(filename);
      must_init(renderer->weak_enemy_idle[i], filename);
  }

  //load the weak_enemy
  renderer->strong_enemy = 
      al_load_bitmap("assets/strong_enemy.png");
  must_init(renderer->strong_enemy, "strong_enemy");

  //load the boss_enemy
  renderer->boss_enemy = 
      al_load_bitmap("assets/boss_enemy.png");
  must_init(renderer->boss_enemy, "boss_enemy");

  //load the health bar and shield bar
  renderer->health_bar = 
      al_load_bitmap("assets/health_bar.png");
  must_init(renderer->health_bar, "health_bar");

  renderer->shield_bar = 
      al_load_bitmap("assets/shield_bar.png");
  must_init(renderer->shield_bar, "shield_bar");

  //load the energy
  renderer->energy_indicator = 
      al_load_bitmap("assets/energy.png");
  must_init(renderer->energy_indicator, "energy");

  //load the deck and discard piles
  renderer->discard_pile = 
      al_load_bitmap("assets/discard_pile.png");
  must_init(renderer->discard_pile, "energy");

  renderer->deck_pile = 
      al_load_bitmap("assets/deck_pile.png");
  must_init(renderer->deck_pile, "energy");

  renderer->font = al_create_builtin_font();
  must_init(renderer->font, "font");
}

void RenderBackground(Renderer* renderer) {
  al_clear_to_color(al_map_rgb(0, 0, 0));

  // Background 1
  if (renderer->background_1) {
      al_draw_scaled_bitmap(renderer->background_1, 0, 0, al_get_bitmap_width(renderer->background_1), 
        al_get_bitmap_height(renderer->background_1), 0, 0, DISPLAY_BUFFER_WIDTH, DISPLAY_BUFFER_HEIGHT, 0);
  }
  // Background 2
  if (renderer->background_2) {
      al_draw_scaled_bitmap(renderer->background_2, 0, 0, al_get_bitmap_width(renderer->background_2), 
        al_get_bitmap_height(renderer->background_2), 0, 0, DISPLAY_BUFFER_WIDTH, DISPLAY_BUFFER_HEIGHT, 0);
  }

  // Background 3
  if (renderer->background_3) {
      al_draw_scaled_bitmap(renderer->background_3, 0, 0, al_get_bitmap_width(renderer->background_3), 
        al_get_bitmap_height(renderer->background_3), 0, 0, DISPLAY_BUFFER_WIDTH, DISPLAY_BUFFER_HEIGHT, 0);
  }

  // Background 4
  if (renderer->background_4) {
      al_draw_scaled_bitmap(renderer->background_4, 0, 0, al_get_bitmap_width(renderer->background_4), 
        al_get_bitmap_height(renderer->background_4), 0, 0, DISPLAY_BUFFER_WIDTH, DISPLAY_BUFFER_HEIGHT, 0);
  }
}

void RenderBackground2(Renderer* renderer) {
  // Background 4
  if (renderer->background_4) {
      al_draw_scaled_bitmap(renderer->background_4, 0, 0, al_get_bitmap_width(renderer->background_4), 
        al_get_bitmap_height(renderer->background_4), 0, 0, DISPLAY_BUFFER_WIDTH, DISPLAY_BUFFER_HEIGHT, 0);
  }
}

void RenderDeck(Renderer* renderer) {
  al_draw_scaled_bitmap(renderer->deck_pile, 0, 0, al_get_bitmap_width(renderer->deck_pile), 
    al_get_bitmap_height(renderer->deck_pile), DRAW_DECK_X, DRAW_DECK_Y, DECK_WIDTH, DECK_HEIGHT, 0);

  al_draw_scaled_bitmap(renderer->discard_pile, 0, 0, al_get_bitmap_width(renderer->discard_pile), 
    al_get_bitmap_height(renderer->discard_pile), 1150 - DRAW_DECK_X, DRAW_DECK_Y, DECK_WIDTH, DECK_HEIGHT, 0);
    
  char text[50] = "";
  int xscale = 2, yscale = 2;

  sprintf(text, "%d", renderer->manager->player->deck.deck_size); // renderer->manager->player->deck.max_size
  DrawScaledText(renderer->font, al_map_rgb(255, 255, 255), (DECK_WIDTH / 2) - 28, 226 + (DECK_HEIGHT / 2), xscale, yscale, ALLEGRO_ALIGN_LEFT, text);

  sprintf(text, "%d", renderer->manager->player->discard_pile.deck_size); // add this if i want to show the max renderer->manager->player->discard_pile.max_size
  DrawScaledText(renderer->font, al_map_rgb(255, 255, 255), (DECK_WIDTH / 2) + 498, 226 + (DECK_HEIGHT / 2), xscale, yscale, ALLEGRO_ALIGN_LEFT, text);
}

void RenderHealthBar(Renderer* renderer, Status status, Asset asset, int x_left, int y_top, ALLEGRO_FONT* font) {

  if(asset == health_bar) {
    al_draw_scaled_bitmap(renderer->health_bar, 0, 0, al_get_bitmap_width(renderer->health_bar), 
      al_get_bitmap_height(renderer->health_bar), x_left, y_top, HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT, 0);
  
    float percent = 0;
    if (status.max_hp > 0) {
      percent = (float)status.current_hp / (float)status.max_hp;
    }
    if (percent < 0) percent = 0;
    if (percent > 1) percent = 1;
  
    float bar_start_x = x_left + 59;
    float bar_start_y = y_top + 27;
    float max_width = 148.0;
    float bar_height = 32;
    float bar_end_x = bar_start_x + (max_width * percent);
  
    al_draw_filled_rounded_rectangle(bar_start_x, bar_start_y, bar_end_x, y_top + bar_height, 0, 0, al_map_rgb(200, 0, 0));
      
    char text[50];
    sprintf(text, "%d / %d", status.current_hp, status.max_hp); 
      
    float text_x = x_left + (HEALTH_BAR_WIDTH / 2.0);
    float text_y = y_top + (HEALTH_BAR_HEIGHT / 2.0) - 5;
  
    DrawScaledText(font, al_map_rgb(255, 255, 255), text_x, text_y, 1.0, 1.0, ALLEGRO_ALIGN_CENTRE, text);   
  }

  if(asset == shield_bar) {
    al_draw_scaled_bitmap(renderer->shield_bar, 0, 0, al_get_bitmap_width(renderer->shield_bar), 
      al_get_bitmap_height(renderer->shield_bar), x_left, y_top, HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT, 0);
  
    float percent = 0;
    if (status.max_hp > 0) {
      percent = (float)status.current_shield / (float)status.max_shild;
    }
    if (percent < 0) percent = 0;
    if (percent > 1) percent = 1;
  
    float bar_start_x = x_left + 59;
    float bar_start_y = y_top + 27;
    float max_width = 148.0;
    float bar_height = 32;
    float bar_end_x = bar_start_x + (max_width * percent);
  
    al_draw_filled_rounded_rectangle(bar_start_x, bar_start_y, bar_end_x, y_top + bar_height, 0, 0, al_map_rgb(0, 0, 200));
      
    char text[50];
    sprintf(text, "%d / %d", status.current_shield, status.max_shild); 
      
    float text_x = x_left + (HEALTH_BAR_WIDTH / 2.0);
    float text_y = y_top + (HEALTH_BAR_HEIGHT / 2.0) - 5;
  
    DrawScaledText(font, al_map_rgb(255, 255, 255), text_x, text_y, 1.0, 1.0, ALLEGRO_ALIGN_CENTRE, text);  
  }

}

void RenderCreature(Renderer* renderer, int x_left, int y_top) {
  ALLEGRO_BITMAP* player_bitmap = al_create_bitmap(PLAYER_WIDTH, PLAYER_HEIGHT);
  al_set_target_bitmap(player_bitmap);

  int frame = (int)(al_get_time() * 4) % 12;

  al_draw_scaled_bitmap(renderer->player_idle[frame], 0, 0, al_get_bitmap_width(renderer->player_idle[frame]), 
    al_get_bitmap_height(renderer->player_idle[frame]), 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT, 0);

  al_set_target_bitmap(renderer->display_buffer);
  al_draw_scaled_bitmap(player_bitmap, 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT, x_left, y_top, PLAYER_WIDTH, PLAYER_HEIGHT, 0);

  RenderHealthBar(renderer, renderer->manager->player->status, health_bar, x_left - 50, y_top + PLAYER_HEIGHT - 24, renderer->font);
  RenderHealthBar(renderer, renderer->manager->player->status, shield_bar, x_left - 50, y_top + PLAYER_HEIGHT + 1, renderer->font);

  al_destroy_bitmap(player_bitmap);
}

void RenderCard(const Renderer* renderer, int x_left, int y_top, type_of_card type, int effect, int energy_cost) {
  ALLEGRO_BITMAP* card_bitmap = al_create_bitmap(CARD_WIDTH, CARD_HEIGHT);
  al_set_target_bitmap(card_bitmap);
  
  float xscale = 1, yscale = 1;
  ALLEGRO_COLOR color = al_map_rgb(0, 0, 0);

  char text[100] = "";
  xscale = 1.05, yscale = 1.3;

  if (renderer->card_attack && type == attack) {
      al_draw_scaled_bitmap(renderer->card_attack, 0, 0, al_get_bitmap_width(renderer->card_attack), 
        al_get_bitmap_height(renderer->card_attack), 0, 0, CARD_WIDTH, CARD_HEIGHT, 0);

      sprintf(text, "Attack:\n\n\nEffect:\n%d of damage!\n\nCost:\n%d of energy!", effect, energy_cost);
      DrawScaledText(renderer->font, color, (CARD_WIDTH * 0.14) / xscale, (CARD_HEIGHT * 0.07) / yscale, xscale, yscale, ALLEGRO_ALIGN_LEFT, text);
  }

  if (renderer->card_defense && type == defense) {
      al_draw_scaled_bitmap(renderer->card_defense, 0, 0, al_get_bitmap_width(renderer->card_defense), 
        al_get_bitmap_height(renderer->card_defense), 0, 0, CARD_WIDTH, CARD_HEIGHT, 0);

      sprintf(text, "Defense:\n\n\nEffect:\n%d of shield!\n\nCost:\n%d of energy!", effect, energy_cost);
      DrawScaledText(renderer->font, color, (CARD_WIDTH * 0.14) / xscale, (CARD_HEIGHT * 0.07) / yscale, xscale, yscale, ALLEGRO_ALIGN_LEFT, text);
  }

  if (renderer->card_especial && type == especial) {
      al_draw_scaled_bitmap(renderer->card_especial, 0, 0, al_get_bitmap_width(renderer->card_especial), 
        al_get_bitmap_height(renderer->card_especial), 0, 0, CARD_WIDTH, CARD_HEIGHT, 0);

      sprintf(text, "Especial:\n\n\nEffect:\nnew hand!");
      DrawScaledText(renderer->font, color, (CARD_WIDTH * 0.14) / xscale, (CARD_HEIGHT * 0.07) / yscale, xscale, yscale, ALLEGRO_ALIGN_LEFT, text);
  }

  al_set_target_bitmap(renderer->display_buffer);
  al_draw_scaled_bitmap(card_bitmap, 0, 0, CARD_WIDTH, CARD_HEIGHT, x_left, y_top, CARD_WIDTH, CARD_HEIGHT, 0);
  al_destroy_bitmap(card_bitmap);
}

void RenderPlayerHand(Renderer* renderer) {
  int space = 0;
  for(int i = 0; i < renderer->manager->player->hand.deck_size; i++) {
    if (renderer->manager->selected_card_index == i)  {
      RenderCard(renderer, HAND_BEGIN_X + space, HAND_BEGIN_Y - 120, renderer->manager->player->hand.cards[i].type, 
      renderer->manager->player->hand.cards[i].effect, renderer->manager->player->hand.cards[i].energy_cost);
    }
    else {
    RenderCard(renderer, HAND_BEGIN_X + space, HAND_BEGIN_Y, renderer->manager->player->hand.cards[i].type, 
      renderer->manager->player->hand.cards[i].effect, renderer->manager->player->hand.cards[i].energy_cost);
    }
    space += 108;
  }
}

void RenderEnemyAction(Renderer* renderer, int i, int x_left, int y_top) {

  float xscale = 1.3, yscale = 1.3;
  char text[100] = "";
  ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);

    if (renderer->manager->enemies->enemy[0].actions[renderer->manager->enemies->enemy->action_count].type == attack) {
        sprintf(text, "Attack: %d", renderer->manager->enemies->enemy[i].actions[renderer->manager->enemies->enemy->action_count].effect);
        color = al_map_rgb(200, 0, 0);
    } 
    else if (renderer->manager->enemies->enemy[0].actions[renderer->manager->enemies->enemy->action_count].type == defense) {
        sprintf(text, "Defense: %d", renderer->manager->enemies->enemy[i].actions[renderer->manager->enemies->enemy->action_count].effect);
        color = al_map_rgb(0, 0, 200);
    }
    if (text[0] != '\0') {
        DrawScaledText(renderer->font, color, x_left, y_top, xscale, yscale, ALLEGRO_ALIGN_CENTER, text);
    }

}

void RenderEnemy(Renderer* renderer, int x_left, int y_top, EnemyType type) {
  ALLEGRO_BITMAP* enemy_bitmap = al_create_bitmap(ENEMY_WIDTH, ENEMY_HEIGHT);
  al_set_target_bitmap(enemy_bitmap);

  int frame = (int)(al_get_time() * 16) % 16;

  if (type == strong) {
    al_draw_scaled_bitmap(renderer->strong_enemy, 0, 0, al_get_bitmap_width(renderer->strong_enemy), 
      al_get_bitmap_height(renderer->strong_enemy), 0, 0, ENEMY_WIDTH, ENEMY_HEIGHT, 0);
  }

  if (type == weak) {
    al_draw_scaled_bitmap(renderer->weak_enemy_idle[frame], 0, 0, al_get_bitmap_width(renderer->weak_enemy_idle[frame]), 
      al_get_bitmap_height(renderer->weak_enemy_idle[frame]), 0, 0, ENEMY_WIDTH, ENEMY_HEIGHT, 0);
  }

  if (type == boss) {
    al_draw_scaled_bitmap(renderer->boss_enemy, 0, 0, al_get_bitmap_width(renderer->boss_enemy), 
      al_get_bitmap_height(renderer->boss_enemy), 0, 0, ENEMY_WIDTH, ENEMY_HEIGHT, 0);
    }

  al_set_target_bitmap(renderer->display_buffer);
  al_draw_scaled_bitmap(enemy_bitmap, 0, 0, ENEMY_WIDTH, ENEMY_HEIGHT, x_left, y_top, ENEMY_WIDTH, ENEMY_HEIGHT, 0);
  al_destroy_bitmap(enemy_bitmap);
}

void RenderEnemies(Renderer* renderer) {
  int space = 0;

  if(renderer->manager->current_round == 11) {
    if(renderer->manager->input_mode == INPUT_SELECT_TARGET && renderer->manager->selected_target_index == 0){
      RenderEnemy(renderer, ENEMY_BEGIN_X - 150, ENEMY_BEGIN_Y + 100, boss);
      RenderHealthBar(renderer, renderer->manager->enemies->enemy[0].status, health_bar, ENEMY_BEGIN_X - 150, ENEMY_BEGIN_Y + ENEMY_HEALTH_BAR + 100, renderer->font);
      RenderHealthBar(renderer, renderer->manager->enemies->enemy[0].status, shield_bar, ENEMY_BEGIN_X - 150, ENEMY_BEGIN_Y + ENEMY_HEALTH_BAR + 100 + 25, renderer->font);
      RenderEnemyAction(renderer, 0, ENEMY_BEGIN_X + 20 - 130, ENEMY_BEGIN_Y + 100 + 25);
    }
    else {
      RenderEnemy(renderer, ENEMY_BEGIN_X - 50, ENEMY_BEGIN_Y + 100, boss);
      RenderHealthBar(renderer, renderer->manager->enemies->enemy[0].status, health_bar, ENEMY_BEGIN_X - 50, ENEMY_BEGIN_Y + ENEMY_HEALTH_BAR + 100, renderer->font);
      RenderHealthBar(renderer, renderer->manager->enemies->enemy[0].status, shield_bar, ENEMY_BEGIN_X - 50, ENEMY_BEGIN_Y + ENEMY_HEALTH_BAR + 100 + 25, renderer->font);
      RenderEnemyAction(renderer, 0, ENEMY_BEGIN_X + 20 - 50, ENEMY_BEGIN_Y + 100 + 25);
    }
  
    return;
  }

  for(int i = 0; i < renderer->manager->enemies->count; i ++) {

    if(renderer->manager->enemies->enemy[i].status.current_hp > 0) {

      if(renderer->manager->input_mode == INPUT_SELECT_TARGET && renderer->manager->selected_target_index == i){
        RenderEnemy(renderer, ENEMY_BEGIN_X - 100, ENEMY_BEGIN_Y + space, renderer->manager->enemies->enemy[i].type);
        RenderHealthBar(renderer, renderer->manager->enemies->enemy[i].status, health_bar, ENEMY_BEGIN_X - 100, ENEMY_BEGIN_Y + ENEMY_HEALTH_BAR + space, renderer->font);
        RenderHealthBar(renderer, renderer->manager->enemies->enemy[i].status, shield_bar, ENEMY_BEGIN_X - 100, ENEMY_BEGIN_Y + ENEMY_HEALTH_BAR + space + 25, renderer->font);
        RenderEnemyAction(renderer, i, ENEMY_BEGIN_X + 20, ENEMY_BEGIN_Y + space + 25);
      }
      else {
        RenderEnemy(renderer, ENEMY_BEGIN_X, ENEMY_BEGIN_Y + space, renderer->manager->enemies->enemy[i].type);
        RenderHealthBar(renderer, renderer->manager->enemies->enemy[i].status, health_bar, ENEMY_BEGIN_X, ENEMY_BEGIN_Y + ENEMY_HEALTH_BAR + space, renderer->font);
        RenderHealthBar(renderer, renderer->manager->enemies->enemy[i].status, shield_bar, ENEMY_BEGIN_X, ENEMY_BEGIN_Y + ENEMY_HEALTH_BAR + space + 25, renderer->font);
        RenderEnemyAction(renderer, i, ENEMY_BEGIN_X + 40, ENEMY_BEGIN_Y + space + 25);
      }
    }

    space += 220;
  }
}

void RenderEnergy(Renderer* renderer) {

  al_draw_scaled_bitmap(renderer->energy_indicator, 0, 0, al_get_bitmap_width(renderer->energy_indicator), 
    al_get_bitmap_height(renderer->energy_indicator), 148, 410, ENERGY_WIDTH, ENERGY_HEIGHT, 0);

  char text[50] = "";
  int xscale = 2, yscale = 2;

  sprintf(text, "%d/%d", renderer->manager->player->current_energy, renderer->manager->player->max_energy);
  DrawScaledText(renderer->font, al_map_rgb(0, 0, 0), 10 + (ENERGY_WIDTH / 2), 150 + (ENERGY_HEIGHT / 2), xscale, yscale, ALLEGRO_ALIGN_LEFT, text);

}

void RenderVictoryScreen(Renderer* renderer) {

  al_draw_filled_rectangle(0, 0, DISPLAY_BUFFER_WIDTH, DISPLAY_BUFFER_HEIGHT, al_map_rgba(0, 0, 0, 220));

  float center_x = DISPLAY_BUFFER_WIDTH / 2.0;
  float center_y = DISPLAY_BUFFER_HEIGHT / 2.0;
  float big_scale = 6.0;
  float small_scale = 1.8;
    
  DrawCenteredScaledText(renderer->font, al_map_rgb(100, 255, 100), center_x / big_scale, (center_y - 80) / big_scale, big_scale, big_scale, "WIN!");

  if(renderer->manager->current_round >= TOTAL_ROUNDS) {
    DrawCenteredScaledText(renderer->font, al_map_rgb(255, 255, 255), center_x / small_scale, (center_y + 120) / small_scale, small_scale, small_scale, "Press Q to quit");
  }
  else {
    DrawCenteredScaledText(renderer->font, al_map_rgb(255, 255, 255), center_x / small_scale, (center_y + 120) / small_scale, small_scale, small_scale, "Press Enter to continue");
  }
  
}


void RenderDefeatScreen(Renderer* renderer) {
  al_draw_filled_rectangle(0, 0, DISPLAY_BUFFER_WIDTH, DISPLAY_BUFFER_HEIGHT, al_map_rgba(0, 0, 0, 200));

  float center_x = DISPLAY_BUFFER_WIDTH / 2.0; 
  float center_y = DISPLAY_BUFFER_HEIGHT / 2.0;
  float big_scale = 6.0;
  float small_scale = 1.5;

  DrawCenteredScaledText(renderer->font, al_map_rgb(255, 0, 0), center_x / big_scale, (center_y - 50) / big_scale, big_scale, big_scale, "GAME OVER");
  DrawCenteredScaledText(renderer->font, al_map_rgb(200, 200, 200), center_x / small_scale, (center_y + 100) / small_scale, small_scale, small_scale, "Press Q tom quit");
}

void RenderFloorHeader(Renderer* renderer) {
    float bar_height = 40;
    //al_draw_filled_rectangle(0, 0, DISPLAY_BUFFER_WIDTH, bar_height, al_map_rgba(0, 0, 0, 0));

    ALLEGRO_COLOR top_color = al_map_rgb(215, 185, 140);
    ALLEGRO_COLOR bottom_color = al_map_rgba(0, 0, 0, 0);
    ALLEGRO_COLOR black_color = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR gold_color = al_map_rgb(255, 215, 0);

    DrawVerticalGradient(0, 0, DISPLAY_BUFFER_WIDTH, bar_height, top_color, bottom_color);
    char text[50];
    sprintf(text, "FLOOR %d / %d", renderer->manager->current_round, TOTAL_ROUNDS);

    float center_x = DISPLAY_BUFFER_WIDTH / 2.0;
    
    DrawScaledText(renderer->font, black_color, center_x / 2.0, 10 / 2.0, 2.0, 2.0, ALLEGRO_ALIGN_CENTRE, text);
}

void RenderMenu(Renderer* renderer) {

    if (renderer->background_1) {
      al_draw_tinted_scaled_bitmap(renderer->background_1, al_map_rgba_f(0.3, 0.3, 0.3, 1), 0, 0, al_get_bitmap_width(renderer->background_1), 
        al_get_bitmap_height(renderer->background_1), 0, 0, DISPLAY_BUFFER_WIDTH, DISPLAY_BUFFER_HEIGHT, 0);
    }

    float center_x = DISPLAY_BUFFER_WIDTH / 2.0;
    float center_y = DISPLAY_BUFFER_HEIGHT / 2.0;

    DrawCenteredScaledText(renderer->font, al_map_rgb(200, 50, 50), center_x / 4.0, (center_y - 150) / 4.0, 4.0, 4.0, "SLAY THE SPIRE\nPDS 2025/02\nRODRIGO LANZA");

    ALLEGRO_COLOR color_start = (renderer->manager->selected_menu_index == 0) ? al_map_rgb(255, 215, 0) : al_map_rgb(150, 150, 150);
    ALLEGRO_COLOR color_quit  = (renderer->manager->selected_menu_index == 1) ? al_map_rgb(255, 215, 0) : al_map_rgb(150, 150, 150);
    
    // Escalas: A opção selecionada fica um pouco maior
    float scale_start = (renderer->manager->selected_menu_index == 0) ? 2.5 : 2.0;
    float scale_quit  = (renderer->manager->selected_menu_index == 1) ? 2.5 : 2.0;

    DrawCenteredScaledText(renderer->font, color_start, center_x / scale_start, (center_y + 50) / scale_start, scale_start, scale_start, "START");
    DrawCenteredScaledText(renderer->font, color_quit, center_x / scale_quit, (center_y + 120) / scale_quit, scale_quit, scale_quit, "Quit");           

    al_set_target_backbuffer(renderer->display);
    al_draw_scaled_bitmap(renderer->display_buffer, 0, 0, DISPLAY_BUFFER_WIDTH, DISPLAY_BUFFER_HEIGHT, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);
    al_flip_display();
}

void Render(Renderer* renderer) {
  al_set_target_bitmap(renderer->display_buffer);

  if (renderer->manager->state == menu) {
    RenderMenu(renderer); 
  }
  else {
    RenderBackground(renderer);
    RenderCreature(renderer, PLAYER_BEGIN_X, PLAYER_BEGIN_Y);
    RenderEnergy(renderer);
    RenderEnemies(renderer);
    //RenderBackground2(renderer);
    RenderDeck(renderer);
    RenderPlayerHand(renderer);
    RenderFloorHeader(renderer);
  
    if (renderer->manager) {
      if (renderer->manager->state == victory) {
        RenderVictoryScreen(renderer);
      }
      else if (renderer->manager->state == defeat) {
        RenderDefeatScreen(renderer);
      }
    }
  }

  al_set_target_backbuffer(renderer->display);

  al_draw_scaled_bitmap(renderer->display_buffer, 0, 0, DISPLAY_BUFFER_WIDTH, DISPLAY_BUFFER_HEIGHT, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);

  al_flip_display();
}

void ClearRenderer(Renderer* renderer) {
  al_destroy_display(renderer->display);
  al_destroy_bitmap(renderer->display_buffer);
  al_destroy_font(renderer->font);

  //clear added backgrounds
  al_destroy_bitmap(renderer->background_1);
  al_destroy_bitmap(renderer->background_2);
  al_destroy_bitmap(renderer->background_3);
  al_destroy_bitmap(renderer->background_4);

  //clear the card images
  al_destroy_bitmap(renderer->card_attack);
  al_destroy_bitmap(renderer->card_defense);
  al_destroy_bitmap(renderer->card_especial);
}