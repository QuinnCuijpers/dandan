#include "dandan/effects/continuous/prevention/PlayCardPreventionEffect.h"
#include "dandan/core/actions/PlayCardAction.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/utils/log.h"

namespace dandan::effects
{
    bool PlayCardPreventionEffect::prevents(
        const core::IAction &action, const core::ExecutionContext exec_ctx,
        std::optional<effects::EffectContext> context) const
    {
        const auto &card_registry{exec_ctx.cards.get()};

        if (const auto *play_card_action =
                dynamic_cast<const core::PlayCardAction *>(&action))
        {
            const auto *card{card_registry[play_card_action->getCardID()]};
            if (getCondition()->isSatisfied(exec_ctx, context) &&
                card->getData().type == core::Type::Land)
            {
                DLOGI << "Play card prevention effect prevents playing card\n";
                return true;
            }
        }
        return false;
    }
} // namespace dandan::effects
