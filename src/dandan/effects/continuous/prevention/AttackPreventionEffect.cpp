#include "dandan/effects/continuous/prevention/AttackPreventionEffect.h"
#include "dandan/core/actions/AttackAction.h"
#include <iostream>

namespace dandan::effects
{
    bool AttackPreventionEffect::prevents(const core::IAction &action,
                                          const core::Game &game)
    {
        if ([[maybe_unused]] const auto *attack_action =
                dynamic_cast<const core::AttackAction *>(&action))
        {
            std::cout << "Checking attack prevention effect condition\n";
            if (m_condition->isSatisfied(game))
            {
                std::cout << "Condition met, preventing attack\n";
                return true;
            }
        }
        return false;
    }

} // namespace dandan::effects