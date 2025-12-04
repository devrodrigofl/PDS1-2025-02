#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "constants.h"
#include "renderer.h"
#include "utils.h"
#include "entities.h"
#include "cards.h"
#include "combat.h"

int main() {
  must_init(al_init(), "allegro");
  must_init(al_init_image_addon(), "allegro");
  must_init(al_init_primitives_addon(), "primitives");
  must_init(al_install_keyboard(), "keyboard");
  
  srand(time(0));

  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
  must_init(timer, "timer");

  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  must_init(queue, "queue");

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_timer_event_source(timer));
  
  unsigned char keyboard_keys[ALLEGRO_KEY_MAX];
  ClearKeyboardKeys(keyboard_keys);
  ALLEGRO_EVENT event;

  Renderer renderer;
  FillRenderer(&renderer);
  al_register_event_source(queue, al_get_display_event_source(renderer.display));
  
  printf("=== Starting game ===\n");
  int current_round = 0;

  Player player;
  buildPlayer(&player);
  printf("> player created with %d/3 of energy on %d cards on the deck.\n", player.current_energy, player.deck.deck_size);

  EnemyGroup enemies;
  buildEnemyGroup(&enemies, current_round);
  printf("> Enemy group created with %d enemies.\n", enemies.count);

  CombatManager combat_manager;
  startCombat(&combat_manager, &player, &enemies);
  printf("> Combat started! Player turn.\n");
  printf("========================\n\n");

    int menu_option = 0; // 0 = Começar, 1 = Sair
    int menu_cooldown = 0;
    combat_manager.current_round = current_round;
    combat_manager.state = menu;

    printf(">>> begining of the round %d/%d <<<\n", combat_manager.current_round, TOTAL_ROUNDS);

    renderer.manager = &combat_manager;
    int victory_timer = 0;

  al_start_timer(timer);  
  while (1) {
    al_wait_for_event(queue, &event);
    int done = 0, print_combat = 0, redraw = 0;

    switch (event.type) {
      case ALLEGRO_EVENT_TIMER:
        redraw = 1;
        if (keyboard_keys[ALLEGRO_KEY_Q]) {
          done = 1;
          break;
        }

        if (combat_manager.state == menu) {
                    
          if (menu_cooldown > 0) menu_cooldown--;

          if (menu_cooldown == 0) {
            if (keyboard_keys[ALLEGRO_KEY_UP]) {
              menu_option--;
              if (menu_option < 0) menu_option = 1;
              menu_cooldown = 10;
            }
            if (keyboard_keys[ALLEGRO_KEY_DOWN]) {
              menu_option++;
              if (menu_option > 1) menu_option = 0;
              menu_cooldown = 10;
            }
            combat_manager.selected_menu_index = menu_option;
          }

          if (keyboard_keys[ALLEGRO_KEY_ENTER] & GAME_KEY_SEEN) {
          if (menu_option == 0) {
                    current_round = 1;
                    combat_manager.current_round = 1;
                    //buildPlayer(&player);
                    //buildEnemyGroup(&enemies, current_round);
                    //startCombat(&combat_manager, &player, &enemies); 

                    combat_manager.state = player_turn;
                    combatHandleInput(&combat_manager, keyboard_keys);
                    combatUpdate(&combat_manager);
          } else done = 1;
                keyboard_keys[ALLEGRO_KEY_ENTER] &= ~GAME_KEY_SEEN;
            }
        }
        else {

          combatHandleInput(&combat_manager, keyboard_keys);
          combatUpdate(&combat_manager);
          
          if (keyboard_keys[ALLEGRO_KEY_SPACE]) {
            renderer.manager->state = victory;
          }
          
          if (combat_manager.state == victory) {
  
            victory_timer++;
            
            if (victory_timer > 30) {
  
              if (keyboard_keys[ALLEGRO_KEY_ENTER] & GAME_KEY_SEEN) {
                
                if (combat_manager.current_round < TOTAL_ROUNDS) {
                  printf("\n=== Win on round %d! ===\n", combat_manager.current_round);
                  
                  current_round++;
                  combat_manager.current_round++;
      
                  discardAllCards(&player.hand, &player.deck);
                  discardAllCards(&player.discard_pile, &player.deck);
                  ShuffleDeck(&player.deck);
                  buildEnemyGroup(&enemies, combat_manager.current_round);
                  startCombat(&combat_manager, &player, &enemies);
  
                  victory_timer = 0;
      
                  printf(">>> begining of round %d/%d <<<\n", combat_manager.current_round, TOTAL_ROUNDS);
      
                } else {
                  printf("\n=================================\n");
                  printf("              You win!            \n");
                  printf("=================================\n");
                  //done = 1;
                }
              }
              else if (combat_manager.state == defeat) {
                printf("\n=================================\n");
                printf("      GAME OVER - You died      \n");
                printf("      You maked to round %d/%d     \n", combat_manager.current_round, TOTAL_ROUNDS);
                printf("=================================\n");
                done = 1;
              }
            }
            keyboard_keys[ALLEGRO_KEY_ENTER] &= ~GAME_KEY_SEEN;
    
          } else victory_timer = 0;
        }

        for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
          keyboard_keys[i] &= ~GAME_KEY_SEEN;
        }
        break;

      case ALLEGRO_EVENT_KEY_DOWN:
        keyboard_keys[event.keyboard.keycode] = GAME_KEY_SEEN | GAME_KEY_DOWN;
        break;
      case ALLEGRO_EVENT_KEY_UP:
        keyboard_keys[event.keyboard.keycode] &= ~GAME_KEY_DOWN;
        break;
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        done = true;
        break;
    }
    if (done) {
      break;
    }

    if (redraw) {
      Render(&renderer);
      redraw = 0;
    }
  }
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
  ClearRenderer(&renderer);
  return 0;
}