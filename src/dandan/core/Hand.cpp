#include "dandan/core/Hand.h"
#include "dandan/core/Game.h"

namespace dandan::core
{
    void Hand::discardCard(Card &card, Game &game)
    {
        std::cout << "Discarding card " << card.getData().getName() << '\n';
        // TODO: move to graveyard instead of just removing from hand
        // awaiting implementation of graveyard
        // and gamewise src -> dest moving of cards
        game.graveyard().addCard(card);
        removeCard(card);
    }
} // namespace dandan::core