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
  
  //INICIALIZAÇÃO DO JOGO
    printf("=== INICIANDO O JOGO ===\n");

    Player player;
    buildPlayer(&player);
    printf("> Player criado com %d/3 Energia e %d Cartas no Deck.\n", player.current_energy, player.deck.deck_size);

    EnemyGroup enemies;
    buildEnemyGroup(&enemies);
    printf("> Grupo de Inimigos criado com %d inimigos.\n", enemies.count);

    CombatManager combat_manager;
    startCombat(&combat_manager, &player, &enemies);
    printf("> Combate Iniciado! Turno do Jogador.\n");
    printf("========================\n\n");

    int current_round = 1;
    
    printf(">>> INICIO DO ROUND %d/%d <<<\n", current_round, TOTAL_ROUNDS);


    renderer.manager = &combat_manager;

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

        combatHandleInput(&combat_manager, keyboard_keys);
        combatUpdate(&combat_manager);
        
        if (keyboard_keys[ALLEGRO_KEY_SPACE]) {
          renderer.manager->state = victory;
        }
        
        if (combat_manager.state == victory) {
          
          if (keyboard_keys[ALLEGRO_KEY_ENTER] & GAME_KEY_SEEN) {
            
            if (current_round < TOTAL_ROUNDS) {
              printf("\n=== VITORIA NO ROUND %d! ===\n", current_round);
              printf("Preparando proximo combate...\n");
                  
              current_round++;
  
              discardAllCards(&player.hand, &player.deck);
              discardAllCards(&player.discard_pile, &player.deck);
              ShuffleDeck(&player.deck);
              buildEnemyGroup(&enemies);
              startCombat(&combat_manager, &player, &enemies);
  
              printf(">>> INICIO DO ROUND %d/%d <<<\n", current_round, TOTAL_ROUNDS);
  
            } else {
              printf("\n=================================\n");
              printf("   PARABENS! VOCE COMPLETOU A TORRE!   \n");
              printf("=================================\n");
              done = 1;
            }
          }
          else if (combat_manager.state == defeat) {
            printf("\n=================================\n");
            printf("      GAME OVER - Voce Morreu      \n");
            printf("      Chegou ate o Round %d/%d     \n", current_round, TOTAL_ROUNDS);
            printf("=================================\n");
            done = 1;
          }
            
          keyboard_keys[ALLEGRO_KEY_ENTER] &= ~GAME_KEY_SEEN;
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