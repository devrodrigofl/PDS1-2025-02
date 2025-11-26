#ifndef CARDS_H
#define CARDS_H

typedef enum {
    attack_card = 0,
    defense_card = 1,
    especial_card = 2,
} type_of_card;

typedef struct {
    type_of_card type;
    int energy_cost;
    int effect;
    int is_used;
} Card;

typedef struct {
    Card cards[20];
    int deck_size;
    int max_size;
} Deck;



#endif