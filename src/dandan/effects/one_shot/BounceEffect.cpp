#include "dandan/effects/one_shot/BounceEffect.h"
#include "dandan/core/Expire.h"
#include "dandan/core/Game.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "nlohmann/json_fwd.hpp"
#include <stdexcept>
#include <variant>
#include <vector>

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
        OneShotEffectRegistry::instance().registerType<BounceEffectDefinition>(
            "BounceEffect",
            []([[maybe_unused]] const IOneShotEffectDefinition *effect)
            {
                const auto json = nlohmann::json::object();
                return json;
            },
            []([[maybe_unused]] const nlohmann::json &data,
               const std::vector<TargetSpec> &target_specs,
               [[maybe_unused]] ExpireTime expiry)
            {
                return std::make_unique<BounceEffectDefinition>(
                    TargetRequirement{target_specs});
            });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> BounceEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};

        if (!std::holds_alternative<core::CardID>(m_target))
        {
            throw std::runtime_error("Bounce Effect target is not a CardID");
        }
        auto card_id{std::get<core::CardID>(m_target)};
        auto *card{card_registry[card_id]};
        auto &controller{game.getPlayer(card->getControllerID())};

        game.moveCardFromZone(controller, *card);
        controller.hand().addCard(*card);
        return nullptr;
    }

} // namespace dandan::effects
