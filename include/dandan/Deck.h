#ifndef DECK_H
#define DECK_H

#include <deque>
#include "Card.h"

class Deck
{
private:
    std::deque<Card> cards;
};
#endif