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

  //load the health bar
  renderer->health_bar = 
      al_load_bitmap("assets/health_bar.png");
  must_init(renderer->health_bar, "health_bar");

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

void RenderDeck(Renderer* renderer, int x_left, int y_top) {
  ALLEGRO_BITMAP* prev_bmp_target = al_get_target_bitmap();

  ALLEGRO_BITMAP* deck_bitmap = al_create_bitmap(DECK_WIDTH, DECK_HEIGHT);
  al_set_target_bitmap(deck_bitmap);

  al_draw_filled_rounded_rectangle(0, 0, DECK_WIDTH, DECK_HEIGHT, 10, 0, al_map_rgb(255, 255, 255));
  al_set_target_bitmap(prev_bmp_target);

  al_draw_scaled_bitmap(deck_bitmap, 0, 0, DECK_WIDTH, DECK_HEIGHT, x_left, y_top, DECK_WIDTH, DECK_HEIGHT, 0);
  al_destroy_bitmap(deck_bitmap);
}

void RenderHealthBar(Renderer* renderer, Status status, int x_left, int y_top, ALLEGRO_FONT* font) {

  al_draw_scaled_bitmap(renderer->health_bar, 0, 0, al_get_bitmap_width(renderer->health_bar), 
    al_get_bitmap_height(renderer->health_bar), x_left, y_top, HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT, 0);

  float percent = (float)status.current_hp / (float)status.max_hp;
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

void RenderCard(const Renderer* renderer, int x_left, int y_top, type_of_card type, int effect) {
  ALLEGRO_BITMAP* card_bitmap = al_create_bitmap(CARD_WIDTH, CARD_HEIGHT);
  al_set_target_bitmap(card_bitmap);
  
  float xscale = 1, yscale = 1;
  ALLEGRO_COLOR color = al_map_rgb(0, 0, 0);

  char text[50] = "";
  xscale = 1.05, yscale = 1.3;

  if (renderer->card_attack && type == attack) {
      al_draw_scaled_bitmap(renderer->card_attack, 0, 0, al_get_bitmap_width(renderer->card_attack), 
        al_get_bitmap_height(renderer->card_attack), 0, 0, CARD_WIDTH, CARD_HEIGHT, 0);

      sprintf(text, "Attack:\n\n\n\n\n%d of damage!\n", effect);
      DrawScaledText(renderer->font, color, (CARD_WIDTH * 0.14) / xscale, (CARD_HEIGHT * 0.07) / yscale, xscale, yscale, ALLEGRO_ALIGN_LEFT, text);
  }

  if (renderer->card_defense && type == defense) {
      al_draw_scaled_bitmap(renderer->card_defense, 0, 0, al_get_bitmap_width(renderer->card_defense), 
        al_get_bitmap_height(renderer->card_defense), 0, 0, CARD_WIDTH, CARD_HEIGHT, 0);

      sprintf(text, "Defense:\n\n\n\n\n+%d of shield!\n", effect);
      DrawScaledText(renderer->font, color, (CARD_WIDTH * 0.14) / xscale, (CARD_HEIGHT * 0.07) / yscale, xscale, yscale, ALLEGRO_ALIGN_LEFT, text);
  }

  if (renderer->card_especial && type == especial) {
      al_draw_scaled_bitmap(renderer->card_especial, 0, 0, al_get_bitmap_width(renderer->card_especial), 
        al_get_bitmap_height(renderer->card_especial), 0, 0, CARD_WIDTH, CARD_HEIGHT, 0);

      sprintf(text, "Especial:\n\n\n\n\nnew hand!\n");
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
      RenderCard(renderer, HAND_BEGIN_X + space, HAND_BEGIN_Y - 100, renderer->manager->player->hand.cards[i].type, 
      renderer->manager->player->hand.cards[i].effect);
    }
    else {
    RenderCard(renderer, HAND_BEGIN_X + space, HAND_BEGIN_Y, renderer->manager->player->hand.cards[i].type, 
      renderer->manager->player->hand.cards[i].effect);
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
        RenderHealthBar(renderer, renderer->manager->enemies->enemy[i].status, ENEMY_BEGIN_X - 100, ENEMY_BEGIN_Y + ENEMY_HEALTH_BAR + space, renderer->font);
      }
      else {
        RenderEnemy(renderer, ENEMY_BEGIN_X, ENEMY_BEGIN_Y + space, renderer->manager->enemies->enemy[i].type);
        RenderHealthBar(renderer, renderer->manager->enemies->enemy[i].status, ENEMY_BEGIN_X, ENEMY_BEGIN_Y + ENEMY_HEALTH_BAR + space, renderer->font);
      }
    }

    space += 180;
  }
}

void RenderEnergy(Renderer* renderer) {}

void Render(Renderer* renderer) {
  al_set_target_bitmap(renderer->display_buffer);
  RenderBackground(renderer);
  RenderDeck(renderer, DRAW_DECK_X, DRAW_DECK_Y);
  RenderCreature(renderer, PLAYER_BEGIN_X, PLAYER_BEGIN_Y + PLAYER_RADIUS, PLAYER_RADIUS);
  RenderEnergy(renderer);
  RenderEnemies(renderer);
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