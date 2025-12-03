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
  
  //load the strong_enemy_idle
  for (int i = 0; i < 16; i++) {
    char filename[50];

      if(i < 9) {
        sprintf(filename, "assets/strong_enemy_idle/Idle_Body_270_000%d.png", i + 1); 
      }
      else sprintf(filename, "assets/strong_enemy_idle/Idle_Body_270_00%d.png", i + 1);
        
      renderer->strong_enemy_idle[i] = al_load_bitmap(filename);
      must_init(renderer->strong_enemy_idle[i], filename);
  }

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

void RenderCreature(Renderer* renderer, int begin_x, int mid_y, int width) {
  al_draw_filled_circle(begin_x + width / 2.0, mid_y, width, al_map_rgb(255, 255, 255));
  float x_end = begin_x + width;

  float health_bar_y = mid_y + width + 20;
  //RenderHealthBar(renderer, 220, 200 + 60, renderer->font);

  float xscale = 1, yscale = 1;

  for(int i = 0; i < renderer->manager->enemies->enemy->num_actions; i++) {
    char text[50] = "";
    xscale = 1.5, yscale = 1.5;

    if (renderer->manager->enemies->enemy[i].actions[i].type == attack) {
      sprintf(text, "Attack: %d of damage!", renderer->manager->enemies->enemy[i].actions[i].effect);
      ALLEGRO_COLOR color = al_map_rgb(255, 100, 100);
      DrawScaledText(renderer->font, color, ENEMY_ACTION_X / xscale, ENEMY_ACTION_Y / yscale, xscale, yscale, ALLEGRO_ALIGN_CENTER, text);
    }

    if (renderer->manager->enemies->enemy[i].actions[i].type == defense) {
      sprintf(text, "Defense: +%d of shield!\n", renderer->manager->enemies->enemy[i].actions[i].effect);
      ALLEGRO_COLOR color = al_map_rgb(100, 100, 255);
      DrawScaledText(renderer->font, color, ENEMY_ACTION_X / xscale, ENEMY_ACTION_Y / yscale, xscale, yscale, ALLEGRO_ALIGN_LEFT, text);
    }
  }
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

void RenderEnemy(Renderer* renderer, int x_left, int y_top, EnemyType type) {
  ALLEGRO_BITMAP* enemy_bitmap = al_create_bitmap(ENEMY_WIDTH, ENEMY_HEIGHT);
  al_set_target_bitmap(enemy_bitmap);

  int frame = (int)(al_get_time() * 16) % 16;

  if (type == strong) {
    for(int i = 0; i < 16; i++) {
      al_draw_scaled_bitmap(renderer->strong_enemy_idle[frame], 0, 0, al_get_bitmap_width(renderer->strong_enemy_idle[frame]), 
        al_get_bitmap_height(renderer->strong_enemy_idle[frame]), 0, 0, ENEMY_WIDTH, ENEMY_HEIGHT, 0);
    }
  }

  if (type == weak) {
    for(int i = 0; i < 16; i++) {
      al_draw_scaled_bitmap(renderer->strong_enemy_idle[frame], 0, 0, al_get_bitmap_width(renderer->strong_enemy_idle[frame]), 
        al_get_bitmap_height(renderer->strong_enemy_idle[frame]), 0, 0, ENEMY_WIDTH, ENEMY_HEIGHT, 0);
    }
  }

  al_set_target_bitmap(renderer->display_buffer);
  al_draw_scaled_bitmap(enemy_bitmap, 0, 0, ENEMY_WIDTH, ENEMY_HEIGHT, x_left, y_top, ENEMY_WIDTH, ENEMY_HEIGHT, 0);
  al_destroy_bitmap(enemy_bitmap);
}

void RenderEnemies(Renderer* renderer) {
  int space = 0;
  for(int i = 0; i < renderer->manager->enemies->count; i ++) {

    if(renderer->manager->enemies->enemy[i].status.current_hp > 0) {

      if(renderer->manager->input_mode == INPUT_SELECT_TARGET && renderer->manager->selected_target_index == i){
        RenderEnemy(renderer, ENEMY_BEGIN_X - 100, ENEMY_BEGIN_Y + space, renderer->manager->enemies->enemy[i].type);
        RenderHealthBar(renderer, renderer->manager->enemies->enemy[i].status, health_bar, ENEMY_BEGIN_X, ENEMY_BEGIN_Y + ENEMY_HEALTH_BAR + space, renderer->font);
        RenderHealthBar(renderer, renderer->manager->enemies->enemy[i].status, shield_bar, ENEMY_BEGIN_X, ENEMY_BEGIN_Y + ENEMY_HEALTH_BAR + space + 25, renderer->font);
      }
      else {
        RenderEnemy(renderer, ENEMY_BEGIN_X, ENEMY_BEGIN_Y + space, renderer->manager->enemies->enemy[i].type);
        RenderHealthBar(renderer, renderer->manager->enemies->enemy[i].status, health_bar, ENEMY_BEGIN_X, ENEMY_BEGIN_Y + ENEMY_HEALTH_BAR + space, renderer->font);
        RenderHealthBar(renderer, renderer->manager->enemies->enemy[i].status, shield_bar, ENEMY_BEGIN_X, ENEMY_BEGIN_Y + ENEMY_HEALTH_BAR + space + 25, renderer->font);
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

void Render(Renderer* renderer) {
  al_set_target_bitmap(renderer->display_buffer);
  RenderBackground(renderer);
  RenderCreature(renderer, PLAYER_BEGIN_X, PLAYER_BEGIN_Y + PLAYER_RADIUS, PLAYER_RADIUS);
  RenderEnergy(renderer);
  RenderEnemies(renderer);
  RenderBackground2(renderer);
  RenderDeck(renderer);
  RenderPlayerHand(renderer);
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
  
  //clear the strong_enemy_idle
  for (int i = 0; i < 16; i++) {
        char filename[50];

        if(i < 9) {
          sprintf(filename, "assets/strong_enemy_idle/Idle_Body_270_000%d.png", i + 1); 
        }
        else sprintf(filename, "assets/strong_enemy_idle/Idle_Body_270_00%d.png", i + 1);

        al_destroy_bitmap(renderer->strong_enemy_idle[i]);
    }
}