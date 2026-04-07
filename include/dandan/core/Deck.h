#ifndef DECK_H
#define DECK_H

#include <deque>
#include "dandan/core/Card.h"

namespace dandan::core
{
    class Deck
    {
    private:
        std::deque<Card> cards;
    };
} // namespace dandan::core
#endif