#include "dandan/effects/one_shot/TimeTwisterEffect.h"
#include "dandan/core/Game.h"
#include "dandan/core/Zone.h"
#include <cassert>
#include <vector>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> TimeTwisterEffect::apply_impl(
        core::Game &game) const
    {
        for (auto &player : game.getPlayers())
        {
            auto hand_card_ids{std::vector<core::CardID>{}};
            for (const auto &card_id : player.hand().getCards())
            {
                hand_card_ids.emplace_back(card_id);
            }

            for (auto card_id : hand_card_ids)
            {
                auto *card{game.getCardByID(card_id)};
                std::cout << "Moving card " << card->getData().getName()
                          << " with ID " << card_id.getID()
                          << " and zone: " << card->getZone()
                          << " from hand to library\n";
                assert(card->getZone() == core::Zone::HAND);
                game.moveCardFromZone(player, *card);
                game.library().addCard(*card);
            }
        }

        auto graveyard_ids{std::vector<core::CardID>{}};
        for (const auto &card_id : game.graveyard().getCards())
        {
            graveyard_ids.emplace_back(card_id);
        }

        for (auto card_id : graveyard_ids)
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