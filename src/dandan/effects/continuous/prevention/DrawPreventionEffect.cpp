#include "dandan/effects/continuous/prevention/DrawPreventionEffect.h"
#include "dandan/core/actions/CardDrawAction.h"
#include "dandan/utils/log.h"
#include <optional>

namespace dandan::effects
{
    DrawPreventionEffect::DrawPreventionEffect(
        std::unique_ptr<conditions::ICondition> condition)
        : IPreventionEffect(std::move(condition))
    {
    }

    bool DrawPreventionEffect::prevents(
        const core::IAction &action, core::ExecutionContext exec_ctx,
        std::optional<effects::EffectContext> context) const
    {

        if ([[maybe_unused]] const auto *card_draw_action =
                dynamic_cast<const core::CardDrawAction *>(&action))
        {
            if (getCondition()->isSatisfied(exec_ctx, context))
            {
                DLOGI << "Draw prevention effect prevents drawing card\n";
                return true;
            }
        }
        return false;
    }

    std::unique_ptr<IPreventionEffect> DrawPreventionEffect::clone() const
    {
        return std::make_unique<DrawPreventionEffect>(cloneCondition());
    }
} // namespace dandan::effects
