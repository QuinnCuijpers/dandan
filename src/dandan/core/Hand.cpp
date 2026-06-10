#include "dandan/core/Hand.h"
#include "dandan/core/Game.h"

namespace dandan::core
{
    void Hand::discardCard(CardID card_id, Game &game)
    {
        auto *card = game.getCardByID(card_id);
        std::cout << "Discarding card " << card->getData().getName() << '\n';
        removeCard(*card);
        game.graveyard().addCard(*card);
    }
} // namespace dandan::core