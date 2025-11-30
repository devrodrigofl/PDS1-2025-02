#ifndef CARDS_H
#define CARDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum type_of_card{
    attack = 0,
    defense = 1,
    especial = 2,
} type_of_card;

typedef enum status_of_card{
    notUsed = 0,
    used = 1,
} status_of_card;

typedef struct Card{
    type_of_card type;
    status_of_card status;
    int energy_cost;
    int effect;
    char action[50];
} Card;

typedef struct Deck{
    Card cards[20];
    int deck_size;
    int max_size;
} Deck;

Card generateCard (type_of_card type, int energy_cost);

void generateDeck (Deck* deck);

void ShuffleDeck(Deck* deck);

void printDeck (Deck deck);

void moveCard(Deck* source, Deck* destination);

void discardAllCards(Deck* source, Deck* destination);

void drawCards(Deck* hand, Deck* deck, Deck* discard_pile, int numCards);

void playedCard(Deck* hand, int cardIndex, Deck* discard_pile);

#endif