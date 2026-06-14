#include "dandan/effects/continuous/prevention/DrawPreventionEffect.h"
#include "dandan/core/TextReplacement.h"
#include "dandan/core/actions/CardDrawAction.h"
#include "dandan/log.h"
#include <optional>
#include <vector>

namespace dandan::effects
{
    bool DrawPreventionEffect::prevents(
        const core::IAction &action, const core::Game &game,
        std::optional<std::vector<core::TextReplacement>> text_replacements)
        const
    {
        if ([[maybe_unused]] const auto *card_draw_action =
                dynamic_cast<const core::CardDrawAction *>(&action))
        {
            if (getCondition()->isSatisfied(game, text_replacements))
            {
                DLOGI << "Draw prevention effect prevents drawing card\n";
                return true;
            }
        }
        return false;
    }
} // namespace dandan::effects