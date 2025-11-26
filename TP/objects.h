#ifndef OBJECTS_H
#define OBJECTS_H

#include "cards.h"

typedef struct {
    int max_hp;
    int current_hp;
    int current_shield;
    int max_shild;
} Status;

typedef struct {
    Status status;
    int max_cards;
    int current_energy;
    int max_energy;
    Deck deck;
    Deck discard_pile;
} Player;

#endif