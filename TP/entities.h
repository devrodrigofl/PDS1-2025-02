#ifndef ENTITIES_H
#define ENTITIES_H

#include "cards.h"

typedef enum EnemyType {
    weak = 0,
    strong = 1,
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
    Deck discard_pile;
    int current_energy;
    int max_energy;
} Player;

typedef struct Enemy{
    Status status;
    int current_energy;
    int max_energy;
    EnemyAction actions[3];
} Enemy;

void buildPlayer(Player* player);

void setActions(Enemy* enemy);




#endif