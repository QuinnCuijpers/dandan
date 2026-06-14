#include "dandan/effects/continuous/prevention/PlayCardPreventionEffect.h"
#include "dandan/core/TextReplacement.h"
#include "dandan/core/actions/PlayCardAction.h"
#include "dandan/log.h"
#include <vector>

namespace dandan::effects
{
    bool PlayCardPreventionEffect::prevents(
        const core::IAction &action, const core::Game &game,
        std::optional<std::vector<core::TextReplacement>> text_replacements)
        const
    {
        if (const auto *play_card_action =
                dynamic_cast<const core::PlayCardAction *>(&action))
        {
            const auto *card{game.getCardByID(play_card_action->getCardID())};
            if (getCondition()->isSatisfied(game, text_replacements) &&
                card->getData().getType() == core::CardData::Type::Land)
            {
                DLOGI << "Play card prevention effect prevents playing card\n";
                return true;
            }
        }
        return false;
    }
} // namespace dandan::effects