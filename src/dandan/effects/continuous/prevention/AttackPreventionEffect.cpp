#include "dandan/effects/continuous/prevention/AttackPreventionEffect.h"
#include "dandan/core/actions/AttackAction.h"
#include <iostream>

namespace dandan::effects
{
    bool AttackPreventionEffect::prevents(
        const core::IAction &action, const core::Game &game,
        std::optional<std::vector<core::TextReplacement>> text_replacements)
        const
    {
        if ([[maybe_unused]] const auto *attack_action =
                dynamic_cast<const core::AttackAction *>(&action))
        {

            std::cout << "Checking attack prevention effect condition\n";
            if (getCondition()->isSatisfied(game, text_replacements))
            {
                // TODO: give conditions display
                //  std::cout << "Attack prevention with condition "
                //            << typeid(*getCondition()).name()
                //            << " prevents attack action\n";
                return true;
            }
        }
        return false;
    }
} // namespace dandan::effects