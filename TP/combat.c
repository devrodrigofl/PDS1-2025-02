#include "combat.h"

void addShield(Status* status, int effect){
    status->current_shield += effect;
    
    if (status->current_shield > status->max_shild) {
        status->current_shield = status->max_shild;
    }
}

void takeDamage(Status* status, int effect){
    if (effect <= 0) return;

    if (status->current_shield > 0) {
        if (status->current_shield >= effect) {
            status->current_shield -= effect;
            effect = 0;
        } else {
            effect -= status->current_shield;
            status->current_shield = 0;
        }
    }

    if (effect > 0) {
        status->current_hp -= effect;
        
        if (status->current_hp < 0) {
            status->current_hp = 0;
        }
    }
}

void executeAction(CombatManager* manager, Status* user, Status* target, type_of_card type, int effect) {
    if (type == attack) {
        printf("attack: %d of damage!\n", effect);
        takeDamage(target, effect);
    } 
    else if (type == defense) {
        printf("Defense: +%d of shield!\n", effect);
        addShield(user, effect);
    }
    else if (type == especial) {
        printf("Especial: new hand!\n");
        
        discardAllCards(&manager->player->hand, &manager->player->discard_pile);
        buildHand(&manager->player->hand, &manager->player->deck, &manager->player->discard_pile, 5);
    }
}


void startCombat(CombatManager* manager, Player* player, EnemyGroup* enemies) {
    manager->player = player;
    manager->enemies = enemies;
    manager->input_mode = INPUT_SELECT_CARD;

    startPlayerTurn(manager);
}

void startPlayerTurn(CombatManager* manager) {
    manager->state = player_turn;

    //reset the energy
    manager->player->current_energy = 3;
    
    //reset thge shield
    manager->player->status.current_shield = 0;

    buildHand(&manager->player->hand, &manager->player->deck, &manager->player->discard_pile, 5);

}

void enemyTurn(CombatManager* manager) {
    printf("\n=== Turno dos Inimigos ===\n");
    
    for (int i = 0; i < manager->enemies->count; i++) {
        Enemy* current_enemy = &manager->enemies->enemy[i];
        
        if (current_enemy->status.current_hp > 0) {
            
            //reset the shield
            current_enemy->status.current_shield = 0;
            
            EnemyAction action = current_enemy->actions[current_enemy->action_count];
            executeAction(manager, &current_enemy->status, &manager->player->status, action.type, action.effect);
            
            //prepare next action
            current_enemy->action_count++;
            
            if (current_enemy->action_count >= current_enemy->num_actions) {
                current_enemy->action_count = 0;
            }
        }
    }
}

void endPlayerTurn(CombatManager* manager) {
    discardAllCards(&manager->player->hand, &manager->player->discard_pile);

    manager->state = enemy_turn;

    enemyTurn(manager);

    startPlayerTurn(manager);
}

void combatUpdate(CombatManager* manager) {
    if (manager->state == victory || manager->state == defeat) {
        return;
    }

    if (manager->player->status.current_hp <= 0) {
        manager->state = defeat;
        printf("GAME OVER\n");
        return;
    }

    if (combatState(manager->enemies)) {
        manager->state = victory;
        printf("Victory! all enemies were defeated.\n");
    }
}

int isKeyPressed(unsigned char* keys, int key_code) {
    return keys[key_code] & GAME_KEY_SEEN;
}

void moveCursor(CombatManager* manager, CursorMovementDirection direction){
    if (manager->input_mode == INPUT_SELECT_CARD) {
        int max_index = manager->player->hand.deck_size - 1;
        //between cards
        if (direction == MOVE_LEFT) {
            if (manager->selected_card_index > 0) {
                manager->selected_card_index--;
            }
        } 
        else if (direction == MOVE_RIGHT) {
            if (manager->selected_card_index < max_index) {
                manager->selected_card_index++;
            }
        }
    }
    
    else if (manager->input_mode == INPUT_SELECT_TARGET) {
        int max_index = manager->enemies->count - 1;

        //between enemies
        if (direction == MOVE_LEFT) {
            if (manager->selected_target_index > 0) {
                manager->selected_target_index--;
            }
        } 
        else if (direction == MOVE_RIGHT) {
            if (manager->selected_target_index < max_index) {
                manager->selected_target_index++;
            }
        }
    }
}

void combatHandleInput(CombatManager* manager, unsigned char* keys) {
    //check if it's the player's turn
    if (manager->state != player_turn) return;

    if (isKeyPressed(keys, ALLEGRO_KEY_LEFT)) {
        printf("antes de entrar left\n");
        moveCursor(manager, MOVE_LEFT);
        printf("depois de entrar left\n");
    }
    if (isKeyPressed(keys, ALLEGRO_KEY_RIGHT)) {
        printf("antes de entrar right\n");
        moveCursor(manager, MOVE_RIGHT);
        printf("depois de entrar direita\n");
    }

    if (isKeyPressed(keys, ALLEGRO_KEY_ENTER)) {
        
        //choosing card
        if (manager->input_mode == INPUT_SELECT_CARD) {
            
            // empty hand
            if (manager->player->hand.deck_size == 0) return;
            printf("%d\n", manager->selected_card_index);
            Card* card_selected = &manager->player->hand.cards[manager->selected_card_index];

            // check for suficient energy
            if (manager->player->current_energy >= card_selected->energy_cost) {
                
                //attack chose target
                if (card_selected->type == attack) {
                    manager->input_mode = INPUT_SELECT_TARGET;
                    manager->selected_target_index = 0;
                    printf("Selecione o alvo\n");
                } 
                //defense and especial execute action
                else {
                    // remove energy
                    manager->player->current_energy -= card_selected->energy_cost;

                    executeAction(manager, &manager->player->status, &manager->player->status, card_selected->type, card_selected->effect);

                    // throw card in discard pile
                    if (card_selected->type != especial) {
                        playedCard(&manager->player->hand, manager->selected_card_index, &manager->player->discard_pile);
                    }

                    if (manager->selected_card_index >= manager->player->hand.deck_size) {
                        manager->selected_card_index = manager->player->hand.deck_size - 1;
                        if (manager->selected_card_index < 0) manager->selected_card_index = 0;
                    }
                }
            } else printf("Sem energia suficiente! (Custo: %d)\n", card_selected->energy_cost);
        }
        
        //choosing enemy
        if (manager->input_mode == INPUT_SELECT_TARGET) {
            
            Enemy* target = &manager->enemies->enemy[manager->selected_target_index];

            if (target->status.current_hp > 0) {
                
                Card* card_selected = &manager->player->hand.cards[manager->selected_card_index];
                
                // remove energy
                manager->player->current_energy -= card_selected->energy_cost;
                
                printf("Ataque realizado! Dano: %d\n", card_selected->effect);

                executeAction(manager, &manager->player->status, &target->status, card_selected->type, card_selected->effect);
                
                // throw card in discard pile
                playedCard(&manager->player->hand, manager->selected_card_index, &manager->player->discard_pile);

                manager->input_mode = INPUT_SELECT_CARD;
                
                if (manager->selected_card_index >= manager->player->hand.deck_size) {
                    manager->selected_card_index = manager->player->hand.deck_size - 1;
                    if (manager->selected_card_index < 0) manager->selected_card_index = 0;
                }
            } else {
                printf("target invalido (ja morreu)!\n");
            }
        }
    }

    if (isKeyPressed(keys, ALLEGRO_KEY_ESCAPE)) {
        
        if (manager->input_mode == INPUT_SELECT_TARGET) {
            printf("Ataque cancelado. Voltando para a mao.\n");
            manager->input_mode = INPUT_SELECT_CARD;
        } 
        else {
            endPlayerTurn(manager);
        }
    }
}