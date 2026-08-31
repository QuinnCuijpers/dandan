#include "dandan/conditions/FlyingCondition.h"
#include "dandan/abilities/BoundAbility.h"
#include "dandan/core/Keyword.h"

namespace dandan::conditions
{
    bool FlyingCondition::isSatisfied(
        const core::ExecutionContext exec_ctx,
        std::optional<effects::EffectContext> context) const
    {

        auto &card_registry{exec_ctx.cards.get()};

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
