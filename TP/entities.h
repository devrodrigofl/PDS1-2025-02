#ifndef ENTITIES_H
#define ENTITIES_H

#include "cards.h"
#include <string.h>
#include <stdlib.h>

#define MAX_ENEMIES 2

typedef enum EnemyType {
    weak = 0,
    strong = 1,
    boss = 2,
} EnemyType;

typedef struct EnemyAction {
    type_of_card type;
    int effect;
} EnemyAction;

typedef struct Status{
    int max_hp;
    int current_hp;
    int current_shield;
    int max_shild;
} Status;

typedef struct Player{
    Status status;
    Deck deck;
    Deck hand;
    Deck discard_pile;
    int current_energy;
    int max_energy;
} Player;

typedef struct Enemy{
    Status status;
    EnemyType type;
    EnemyAction actions[3];
    int action_count;
    int num_actions;
    float x_axis;
    float y_axis;
} Enemy;

typedef struct {
    Enemy enemy[MAX_ENEMIES];
    int count;
    int active_count;
} EnemyGroup;

void initStatus(Status* status, int max_hp, int max_shield);

void buildPlayer(Player* player);

int enemyEffect(int cost);
int numActions(EnemyType type);
int actionsCost(EnemyType type);
void buildEnemy(Enemy* enemy);

void buildEnemyGroup(EnemyGroup* group, int current_round);
int combatState(EnemyGroup* group);

#endif