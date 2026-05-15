#include "dandan/effects/continuous/prevention/PlayCardPreventionEffect.h"
#include "dandan/core/actions/PlayCardAction.h"

namespace dandan::effects
{
    bool PlayCardPreventionEffect::prevents(const core::IAction &action,
                                            const core::Game &game)
    {
        if (dynamic_cast<const core::PlayCardAction *>(&action) != nullptr)
        {
            if (m_condition->isSatisfied(game))
            {
                DLOGI << "Play card prevention effect prevents playing card\n";
                return true;
            }
        }
        return false;
    }
} // namespace dandan::effects