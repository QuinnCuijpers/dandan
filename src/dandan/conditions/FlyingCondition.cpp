#include "dandan/conditions/FlyingCondition.h"
#include "dandan/abilities/BoundAbility.h"
#include "dandan/abilities/keywords/Keyword.h"

namespace dandan::conditions
{
    bool FlyingCondition::isSatisfied(
        const core::ExecutionContext exec_ctx,
        std::optional<effects::EffectContext> context) const
    {

        if (!context.has_value())
        {
            return false;
        }

        const auto &card_registry{exec_ctx.cards.get()};

        const auto *card{card_registry.get(context->card_id)};
        return card->hasKeyword(abilities::Keyword::Flying);
    }

    [[nodiscard]] std::unique_ptr<ICondition> FlyingCondition::clone() const
    {
        return std::make_unique<FlyingCondition>();
    }
} // namespace dandan::conditions
