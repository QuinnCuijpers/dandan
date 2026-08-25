#include "dandan/effects/one_shot/MemoryLapseEffect.h"
#include "dandan/core/Game.h"
#include "dandan/events/IEvent.h"
#include <memory>

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
            .registerType<MemoryLapseEffectDefinition>(
                "MemoryLapseEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    return json;
                },
                []([[maybe_unused]] const nlohmann::json &data,
                   const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                {
                    return std::make_unique<MemoryLapseEffectDefinition>(
                        TargetRequirement{target_specs});
                });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> MemoryLapseEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};

        if (!std::holds_alternative<core::CardID>(m_target))
        {
            throw std::runtime_error(
                "MemoryLapseEffect target is not a CardID");
        }
        auto card_id{std::get<core::CardID>(m_target)};
        auto *card{card_registry[card_id]};
        auto &controller{game.getPlayer(card->getControllerID())};

        if (card->canBeCountered())
        {
            game.moveCardFromZone(controller, *card);
            game.moveCardToZone(*card, controller, m_target_zone);
        }
        return nullptr;
    }
} // namespace dandan::effects
