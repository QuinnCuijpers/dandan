#include "dandan/effects/one_shot/OptionalDrawEffect.h"
#include "dandan/core/GameState.h"
#include "dandan/effects/one_shot/DrawEffect.h"
#include <string>

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
            .registerType<OptionalDrawEffectDefinition>(
                "OptionalDrawEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    const auto *optionalDrawEffect =
                        dynamic_cast<const OptionalDrawEffectDefinition *>(
                            effect);
                    json["amount"] = optionalDrawEffect->getAmount();
                    json["each_player"] = optionalDrawEffect->isEachPlayer();

                    return json;
                },
                [](const nlohmann::json &data,
                   [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                {
                    return std::make_unique<OptionalDrawEffectDefinition>(
                        data.at("amount").get<int>(),
                        data.at("each_player").get<bool>());
                });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> OptionalDrawEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &istream{exec_ctx.input_manager.get().stream()};

        if (m_each_player)
        {
            auto starting_player_id{game.activePlayer().getID()};
            auto current_player_id{starting_player_id};

            while (true)
            {
                auto &player{game.getPlayer(current_player_id)};
                std::cout << player.getName()
                          << ", how many cards do you want to draw (0-"
                          << m_amount << ")?\n";

                std::string input;
                std::getline(istream, input);
                int draw_amount{std::stoi(input)};

                auto def{dandan::effects::DrawEffectDefinition(draw_amount)};
                auto context{EffectContext{player.getID()}};
                auto effect{def.bind(exec_ctx, context)};
                static_cast<void>(effect->apply(exec_ctx));

                current_player_id = game.getNextPlayerID(current_player_id);
                if (current_player_id == starting_player_id)
                {
                    break;
                }
            }
        }
        else
        {
            game.activePlayer().drawCard(exec_ctx);
        }
        return nullptr;
    }
} // namespace dandan::effects
