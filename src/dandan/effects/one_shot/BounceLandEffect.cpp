#include "dandan/effects/one_shot/BounceLandEffect.h"
#include "dandan/core/Game.h"
#include <iostream>
#include <string>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
#endif

#ifdef DANDAN_SERIALIZE
namespace
{

    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::core;

    const auto registered = []
    {
        OneShotEffectRegistry::instance()
            .registerType<BounceLandEffectDefinition>(
                "BounceLandEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    const auto json = nlohmann::json::object();
                    return json;
                },
                []([[maybe_unused]] const nlohmann::json &data,
                   [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                { return std::make_unique<BounceLandEffectDefinition>(); });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> BounceLandEffect::apply_impl(
        [[maybe_unused]] core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};

        std::cout << "Applying BounceLandEffect\n";
        std::cout << "what land index to bounce? ";
        std::string input;
        std::getline(game.istream(), input);
        int land_index{std::stoi(input)};
        std::cout << "Bouncing land at index " << land_index << "\n";
        auto land{game.activePlayer().battlefield().getLand(land_index)};
        auto *card{card_registry[land.getID()]};
        game.eventManager().unsubscribe(*card);
        game.activePlayer().hand().addCard(*card);
        return nullptr;
    }
} // namespace dandan::effects
