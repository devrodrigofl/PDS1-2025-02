#include "cards.h"

Card generateCard (type_of_card type, int energy_cost) {
    //set new card
    Card newCard;
    newCard.type = type;
    newCard.status = notUsed;
    newCard.energy_cost = energy_cost;
    
    //set and adjust the effect and action according to the energy cost and type
    switch (type) {

    case especial:
        newCard.energy_cost = 0;
        newCard.effect = 0;
        sprintf(newCard.action, "Discard");
        break;

    case attack:
        if (newCard.energy_cost == 0) newCard.effect = (rand() % 5) + 1;
        else if (newCard.energy_cost == 1) newCard.effect = (rand() % 6) + 5;
        else if (newCard.energy_cost == 2) newCard.effect = (rand() % 6) + 10;
        else if (newCard.energy_cost == 3) newCard.effect = (rand() % 16) + 15;
        sprintf(newCard.action, "%d of damage", newCard.effect);
        break;

    case defense:
        if (newCard.energy_cost == 0) newCard.effect = (rand() % 5) + 1;
        else if (newCard.energy_cost == 1) newCard.effect = (rand() % 6) + 5;
        else if (newCard.energy_cost == 2) newCard.effect = (rand() % 6) + 10;
        else if (newCard.energy_cost == 3) newCard.effect = (rand() % 16) + 15;
        sprintf(newCard.action, "%d of shield", newCard.effect);
        break;

    default:
        break;
    }

    return newCard;
}

void generateDeck (Deck* deck) {
    deck->deck_size = 20;
    deck->max_size = 20;

    int i = 0;

    //preset 6 attack cards
    deck->cards[i++] = generateCard(attack, 0);
    deck->cards[i++] = generateCard(attack, 1);
    deck->cards[i++] = generateCard(attack, 1);
    deck->cards[i++] = generateCard(attack, 1);
    deck->cards[i++] = generateCard(attack, 2);
    deck->cards[i++] = generateCard(attack, 3);

    //randomly generates the last 4 attack cards
    for(int j = 0; j < 4; j++) {
        deck->cards[i++] = generateCard(attack, (rand() % 4));
    }

    //preset 6 defense cards
    deck->cards[i++] = generateCard(defense, 0);
    deck->cards[i++] = generateCard(defense, 1);
    deck->cards[i++] = generateCard(defense, 1);
    deck->cards[i++] = generateCard(defense, 1);
    deck->cards[i++] = generateCard(defense, 2);
    deck->cards[i++] = generateCard(defense, 3);
    
    //randomly generates the last 2 defense cards
    for(int j = 0; j < 2; j++) {
        deck->cards[i++] = generateCard(defense, (rand() % 3));
    }

    //preset 2 especial cards
    deck->cards[i++] = generateCard(especial, 0);
    deck->cards[i++] = generateCard(especial, 0);

}

void ShuffleDeck(Deck* deck) {
  if (deck->deck_size > 1) {
    int i;
    for (i = 0; i < deck->deck_size - 1; i++) {
      int j = i + rand() / (RAND_MAX / (deck->deck_size - i) + 1);
      if (j == i) {
        continue;
      }
      Card int_j = deck->cards[j];

      deck->cards[j] = deck->cards[i];

      deck->cards[i] = int_j;
    }
  }
}

void printDeck (Deck deck) {

    for (int i = 0; i < deck.deck_size; i++) {
        char *type;

        if (deck.cards[i].type == attack) type = "Attack";
        else if (deck.cards[i].type == defense) type = "Defense";
        else if (deck.cards[i].type == especial) type = "Especial";

        printf("\n[%d]\n\tType: %s \n\tCost: %d \n\tEffect: %d \n", i, type, deck.cards[i].energy_cost, deck.cards[i].effect);
    }
}

void moveCard(Deck* source, Deck* destination) {
    if (source->deck_size <= 0) return;
    if (destination->deck_size >= 20) return;

    //copy the top card of source
    Card top = source->cards[source->deck_size - 1];
    source->deck_size--;

    //paste on the top spot of destination
    destination->cards[destination->deck_size] = top;
    destination->deck_size++;
}

void discardAllCards(Deck* source, Deck* destination) {
    while (source->deck_size > 0) {
        moveCard(source, destination);
    }
}

void buildHand(Deck* hand, Deck* deck, Deck* discard_pile, int numCards) {
    //if the buy pile is empty
    if (deck->deck_size == 0) {
        //and the discard pile have cards
        if(discard_pile->deck_size > 0) {
            //move everything to the buy pile and shuffle
            discardAllCards(discard_pile, deck);
            ShuffleDeck(deck);
        }
    }
    
    for (int i = 0; i < numCards; i++) {
        moveCard(deck, hand);
    }
}

void playedCard(Deck* hand, int cardIndex, Deck* discard_pile) {

    if (cardIndex < 0 || cardIndex >= hand->deck_size) return;
    if (discard_pile->deck_size >= 20) return;


    Card played_card = hand->cards[cardIndex];

    played_card.status = used; 
    
    discard_pile->cards[discard_pile->deck_size] = played_card;
    discard_pile->deck_size++;

    for (int i = cardIndex; i < hand->deck_size - 1; i++) {
        hand->cards[i] = hand->cards[i + 1];
    }

    hand->deck_size--;
}