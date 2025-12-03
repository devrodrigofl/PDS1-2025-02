#ifndef COMBAT_H
#define COMBAT_H

#include "entities.h"
#include "constants.h"
#include <stdio.h>
#include <allegro5/allegro.h>

typedef enum InputState {
    INPUT_SELECT_CARD,
    INPUT_SELECT_TARGET,
} InputState;

typedef enum CombatState{
    player_turn,
    enemy_turn,
    victory,
    defeat,
} CombatState;

typedef struct {
    Player* player;
    EnemyGroup* enemies;
    CombatState state;
    InputState input_mode;  
    int selected_card_index;
    int selected_target_index;
    int current_round;
} CombatManager;

void addShield(Status* status, int effect);
void takeDamage(Status* Status, int effect);
void executeAction(CombatManager* manager, Status* user, Status* target, type_of_card type, int effect);
void startCombat(CombatManager* manager, Player* player, EnemyGroup* enemies);
void startPlayerTurn(CombatManager* manager);
void endPlayerTurn(CombatManager* manager);

void enemyTurn(CombatManager* manager);

void combatUpdate(CombatManager* manager);

void moveCursor(CombatManager* manager, CursorMovementDirection direction);
void combatHandleInput(CombatManager* manager, unsigned char* keys);
int isKeyPressed(unsigned char* keys, int key_code);

#endif