#include "dandan/effects/one_shot/TimeTwisterEffect.h"
#include "dandan/core/Game.h"
#include "dandan/core/Zone.h"
#include <algorithm>
#include <cassert>
#include <vector>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace
{

    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::abilities;
    using namespace dandan::core;
    using namespace dandan::numbers;

    const auto registered = []
    {
        OneShotEffectRegistry::instance()
            .registerType<TimeTwisterEffectDefinition>(
                "TimeTwisterEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    return json;
                },
                []([[maybe_unused]] const nlohmann::json &data,
                   [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                { return std::make_unique<TimeTwisterEffectDefinition>(); });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> TimeTwisterEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};

        for (auto &player : game.getPlayers())
        {
            auto hand_card_ids{std::vector<core::CardID>{}};
            std::copy(player.hand().getCards().begin(),
                      player.hand().getCards().end(),
                      std::back_inserter(hand_card_ids));

            for (auto card_id : hand_card_ids)
            {
                auto *card{card_registry[card_id]};
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
            auto *card{card_registry[card_id]};
            assert(card->getZone() == core::Zone::GRAVEYARD);
            game.moveCardFromZone(game.activePlayer(), *card);
            game.library().addCardBottom(*card);
        }

        game.library().shuffle();
        return nullptr;
    }
} // namespace dandan::effects
