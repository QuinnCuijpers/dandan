#include "dandan/core/Hand.h"
#include "dandan/core/Game.h"

namespace dandan::core
{
    void Hand::discardCard(Card &card, Game &game)
    {
        std::cout << "Discarding card " << card.getData().getName() << '\n';
        game.graveyard().addCard(card);
        removeCard(card);
    }
} // namespace dandan::core