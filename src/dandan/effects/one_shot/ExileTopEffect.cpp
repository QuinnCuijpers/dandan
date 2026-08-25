#include "dandan/effects/one_shot/ExileTopEffect.h"
#include "dandan/core/Game.h"

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
            .registerType<ExileTopEffectDefinition>(
                "ExileTopEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    const auto *exile =
                        dynamic_cast<const ExileTopEffectDefinition *>(effect);
                    json["amount"] = exile->getAmount();
                    return json;
                },
                [](const nlohmann::json &data,
                   [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                {
                    return std::make_unique<ExileTopEffectDefinition>(
                        data.at("amount").get<int>());
                });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> ExileTopEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};

        for (int i = 0; i < m_amount; ++i)
        {
            if (game.library().getCards().empty())
            {
                break;
            }
            auto card_id{game.library().getCards().front()};
            auto *card{card_registry[card_id]};
            game.moveCardFromZone(game.activePlayer(), *card);
            game.exile().addCard(*card);
        }
        return nullptr;
    }
} // namespace dandan::effects
