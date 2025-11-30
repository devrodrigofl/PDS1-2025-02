#include "entities.h"

void initStatus(Status* status, int max_hp, int max_shield) {
    status->max_hp = max_hp;
    status->current_hp = max_hp;
    status->current_shield = 0;
    status->max_shild = max_shield;
}

void buildPlayer(Player* player) {
    initStatus(&player->status, 100, 100);

    player->max_energy = 3;
    player->current_energy = 3;
    
    generateDeck(&player->deck);
    ShuffleDeck(&player->deck);

    player->hand.deck_size = 0;
    player->hand.max_size = 20;

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

    initStatus(&enemy->status, hp, hp);

    enemy->action_count = numActions(enemy->type);

    int check_cost = 0;
    int check_attack = 0;

    for(int i = 0; i < enemy->action_count; i++) {

        if (i == enemy->action_count - 1 && check_attack == 0) {
            enemy->actions[i].type = attack;
        } else {
            enemy->actions[i].type = (rand() % 2 == 0) ? attack : defense;
        }

        if (enemy->actions[i].type == attack) {
            check_attack = 1;
        }
        
        int cost = actionsCost(enemy->type);

        //check if cost 1 has already occurred
        if (enemy->type == strong) {
            if (cost == 1) {
                if (check_cost == 0) {
                    check_cost = 1;
                } else {
                    while (cost == 1) {
                        cost = actionsCost(enemy->type);
                    }
                }
            }
        }

        enemy->actions[i].effect = enemyEffect(cost);  
    }
}

void buildEnemyGroup(EnemyGroup* group) {
    group->count = MAX_ENEMIES;
    group->active_count = MAX_ENEMIES;

    int strong_spawned = 0;

    for (int i = 0; i < group->count; i++) {
        //strong enemy probability
        if (!strong_spawned && (rand() % 100 < 5)) { 
            group->enemies[i].type = strong;
            buildEnemy(&group->enemies[i]);
            strong_spawned = 1;
        }
        else {
            group->enemies[i].type = weak;
            buildEnemy(&group->enemies[i]);
        }
    }
}

int combatState(EnemyGroup* group) {
    for (int i = 0; i < group->count; i++) {
        if (group->enemies[i].status.current_hp > 0) {
            return 0;
        }
    }
    return 1;
}