#include "entities.h"

void init_status(Status* status, int max_hp, int max_shield) {
    status->max_hp = max_hp;
    status->current_hp = max_hp;
    status->current_shield = 0;
    status->max_shild = max_shield;
}

void buildPlayer(Player* player) {
    init_status(&player->status, 100, 100);

    player->max_energy = 3;
    player->current_energy = 3;
    
    generateDeck(&player->deck);
    ShuffleDeck(&player->deck);

    player->discard_pile.deck_size = 0;
    player->discard_pile.max_size = 20;
}

int enemyEffect(int cost) {
    switch (cost) {
        case 0: return 1 + (rand() % 5);
        case 1: return 5 + (rand() % 6);
        case 2: return 10 + (rand() % 6);
        case 3: return 15 + (rand() % 16);
        default: return 0;
    }
}

int numActions(EnemyType type) {
    switch (type) {
        case weak: return 1 + (rand() % 2);
        case strong: return 2 + (rand() % 2);
        default: return 0;
    }
}

int actionsCost(EnemyType type) {
    switch (type) {
        case weak: return rand() % 2;
        case strong: return 1 + (rand() % 3);
        default: return 0;
    }
}

void buildEnemy(Enemy* enemy) {
    int hp;
    if(enemy->type) hp = 40 + (rand() % 61);
    else hp = 10 + (rand() % 21);

    init_status(&enemy->status, hp, hp);

    enemy->action_count = numActions(enemy->type);

    int check = 0;

    for(int i = 0; i < enemy->action_count; i++) {
        enemy->actions[i].type = (rand() % 2 == 0) ? attack : defense;

        int cost = actionsCost(enemy->type);

        //check if cost 1 has already occurred
        if (cost == 1 && check == 0) check = 1;
        else if(cost == 1 && check == 1) {
            while(cost == 1) {
                cost = actionsCost(enemy->type);
            }
        }

        enemy->actions[i].effect = enemyEffect(cost);  
    }
}