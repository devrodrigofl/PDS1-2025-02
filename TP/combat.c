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

void startCombat(CombatManager* manager, Player* player, EnemyGroup* enemies) {
    manager->player = player;
    manager->enemies = enemies;

    startPlayerTurn(manager);
}

void startPlayerTurn(CombatManager* manager) {
    manager->state = player_turn;

    //reset the energy
    manager->player->current_energy = 3;
    
    //reset thge shield
    manager->player->status.current_shield = 0;

    buildhand(&manager->player->hand, &manager->player->deck, &manager->player->discard_pile, 5);

}

void enemyTurn(CombatManager* manager) {
    printf("\n=== Turno dos Inimigos ===\n");
    
    for (int i = 0; i < manager->enemies->count; i++) {
        Enemy* current_enemy = &manager->enemies->enemy[i];
        
        if (current_enemy->status.current_hp > 0) {
            
            //reset the shield
            current_enemy->status.current_shield = 0;
            
            EnemyAction action = current_enemy->actions[current_enemy->action_count];
            
            if (action.type == attack) {
                //adicioar nome aos inimigos forte e fraco depois
                printf("Enemy attack causing %d of damage!\n", action.effect);
                
                takeDamage(&manager->player->status, action.effect);
                
                // (Aqui seria o lugar para iniciar a animação ANIM_GOING)
                // e->status.anim_state = ANIM_GOING;
            } 
            else if (action.type == defense) {
                printf("enemy defends, gaining %d shield points!\n", action.effect);
                addShield(&current_enemy->status, action.effect);
            }
            
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

    combat_start_player_turn(manager);
}

void combatUpdate(CombatManager* manager) {

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