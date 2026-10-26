#include "dandan/effects/one_shot/TimeTwisterEffect.h"
#include "dandan/core/Game.h"
#include "dandan/core/Zone.h"
#include <algorithm>
#include <cassert>
#include <memory>
#include <utility>
#include <vector>

namespace dandan::effects
{
    TimeTwisterEffect::TimeTwisterEffect(EffectContext context)
        : IOneShotEffect(std::move(context))
    {
    }

    std::unique_ptr<IOneShotEffect> TimeTwisterEffect::copy() const
    {
        return std::make_unique<TimeTwisterEffect>(getEffectContext());
    }

    std::unique_ptr<IOneShotEffectDefinition> TimeTwisterEffectDefinition::
        clone() const
    {
        return std::make_unique<TimeTwisterEffectDefinition>();
    }

    std::unique_ptr<IOneShotEffect> TimeTwisterEffectDefinition::bind(
        [[maybe_unused]] const core::ExecutionContext exec_ctx,
        [[maybe_unused]] EffectContext context) const
    {
        return std::make_unique<TimeTwisterEffect>(context);
    }

    std::unique_ptr<events::IEvent> TimeTwisterEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};

        for (auto &player : game.getPlayers())
        {
            auto hand_card_ids{std::vector<core::CardID>{}};
            std::copy(player.hand().getCards().begin(),
                      player.hand().getCards().end(),
                      std::back_inserter(hand_card_ids));

            for (auto card_id : hand_card_ids)
            {
                auto *card{card_registry.get(card_id)};
                std::cout << "Moving card " << card->getData().name
                          << " with ID " << card_id.getID()
                          << " and zone: " << card->getZone()
                          << " from hand to library\n";
                assert(card->getZone() == core::Zone::HAND);
                game.moveCardFromZone(player, *card);
                game.library().addCardBottom(*card);
            }
        }

        auto graveyard_ids{std::vector<core::CardID>{}};
        std::copy(game.graveyard().getCards().begin(),
                  game.graveyard().getCards().end(),
                  std::back_inserter(graveyard_ids));

        for (auto card_id : graveyard_ids)
        {
            auto *card{card_registry.get(card_id)};
            assert(card->getZone() == core::Zone::GRAVEYARD);
            game.moveCardFromZone(game.activePlayer(), *card);
            game.library().addCardBottom(*card);
        }

        game.library().shuffle();
        return nullptr;
    }
} // namespace dandan::effects
