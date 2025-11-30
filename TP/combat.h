#ifndef COMBAT_H
#define COMBAT_H

#include "entities.h"

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
} CombatManager;

void addShield(Status* status, int effect);
void takeDamage(Status* Status, int effect);

void startCombat(CombatManager* manager, Player* player, EnemyGroup* enemies);
void startPlayerTurn(CombatManager* manager);
void endPlayerTurn(CombatManager* manager);

void enemyTurn(CombatManager* manager);


void combatUpdate(CombatManager* manager);

#endif