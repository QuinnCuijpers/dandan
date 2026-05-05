#include "dandan/effects/continuous/prevention/DrawPreventionEffect.h"
#include "dandan/core/actions/CardDrawAction.h"

namespace dandan::effects
{
    bool DrawPreventionEffect::prevents(const core::IAction &action,
                                        const core::Game &game)
    {
        if ([[maybe_unused]] const auto *card_draw_action =
                dynamic_cast<const core::CardDrawAction *>(&action))
        {
            if (m_condition->isSatisfied(game))
            {
                std::cout << "Draw prevention effect prevents drawing card\n";
                return true;
            }
        }
        return false;
    }
} // namespace dandan::effects