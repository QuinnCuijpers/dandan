#include "dandan/conditions/FlyingCondition.h"
#include "dandan/abilities/BoundAbility.h"
#include "dandan/core/Keyword.h"

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace
{
    using namespace dandan::conditions;
    using namespace dandan::serialization;

    const auto registered = []
    {
        ConditionRegistry::instance().registerType<FlyingCondition>(
            "FlyingCondition",
            []([[maybe_unused]] const ICondition *condition)
            {
                auto json = nlohmann::json::object();
                return json;
            },
            []([[maybe_unused]] const nlohmann::json &json)
            { return std::make_unique<FlyingCondition>(); });
        return true;
    }();
} // namespace
#endif

namespace dandan::conditions
{
    bool FlyingCondition::isSatisfied(
        const core::ExecutionContext exec_ctx,
        std::optional<effects::EffectContext> context) const
    {

        const auto &card_registry{exec_ctx.cards.get()};

        const auto *card{card_registry[context->card_id.value()]};
        const auto &current_abilities{card->getCurrentAbilities()};
        return std::any_of(
            current_abilities.begin(), current_abilities.end(),
            [](const abilities::BoundAbility &ability)
            { return core::isFlyingAbility(ability.definition()); });
    }

    [[nodiscard]] std::unique_ptr<ICondition> FlyingCondition::clone() const
    {
        return std::make_unique<FlyingCondition>();
    }
} // namespace dandan::conditions
