#include "dandan/effects/one_shot/TimeTwisterEffect.h"
#include "dandan/core/Game.h"
#include "dandan/core/Zone.h"
#include <cassert>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> TimeTwisterEffect::apply_impl(
        core::Game &game) const
    {
        for (auto &player : game.getPlayers())
        {
            auto hand_cards{player.hand().getCards()};

            for (auto card_id : hand_cards)
            {
                auto *card{game.getCardByID(card_id)};
                assert(card->getZone() == core::Zone::HAND);
                game.moveCardFromZone(player, *card);
                game.library().addCard(*card);
            }
        }

        auto graveyard{game.graveyard().getCards()};
        for (auto card_id : graveyard)
        {
            auto *card{game.getCardByID(card_id)};
            assert(card->getZone() == core::Zone::GRAVEYARD);
            game.moveCardFromZone(game.activePlayer(), *card);
            game.library().addCard(*card);
        }

        game.library().shuffle();
        return nullptr;
    }
} // namespace dandan::effects