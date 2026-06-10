#include "dandan/core/Battlefield.h"
#include "dandan/core/Game.h"

namespace dandan::core
{
    void Battlefield::sacrificeCard(Card &card, core::Game &game)
    {
        removeCard(card);
        game.graveyard().addCard(card);
    }
} // namespace dandan::core