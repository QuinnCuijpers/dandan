#include "dandan/effects/continuous/prevention/DrawPreventionEffect.h"
#include "dandan/core/actions/CardDrawAction.h"
#include "dandan/log.h"
#include <optional>

namespace dandan::effects
{
    bool DrawPreventionEffect::prevents(
        const core::IAction &action, const core::Game &game,
        std::optional<effects::EffectContext> context) const
    {
        if ([[maybe_unused]] const auto *card_draw_action =
                dynamic_cast<const core::CardDrawAction *>(&action))
        {
            if (getCondition()->isSatisfied(game, context))
            {
                DLOGI << "Draw prevention effect prevents drawing card\n";
                return true;
            }
        }
        return false;
    }
} // namespace dandan::effects