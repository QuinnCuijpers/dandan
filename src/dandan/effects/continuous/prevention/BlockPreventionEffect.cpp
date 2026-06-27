#include "dandan/effects/continuous/prevention/BlockPreventionEffect.h"
#include "dandan/core/actions/BlockAction.h"
#include "dandan/effects/EffectContext.h"
#include <iostream>

namespace dandan::effects
{
    bool BlockPreventionEffect::prevents(
        const core::IAction &action, const core::Game &game,
        [[maybe_unused]] std::optional<effects::EffectContext> context) const
    {
        if ([[maybe_unused]] const auto *block_action =
                dynamic_cast<const core::BlockAction *>(&action))
        {
            auto blocker{block_action->getBlocker()};

            // check condition for blocker
            EffectContext context{blocker};

            std::cout << "Checking block prevention effect condition\n";
            if (getCondition()->isSatisfied(game, context))
            {
                return true;
            }
        }
        return false;
    }
} // namespace dandan::effects