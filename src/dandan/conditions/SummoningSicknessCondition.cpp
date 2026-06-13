#include "dandan/conditions/SummoningSicknessCondition.h"
#include "dandan/core/Game.h"
#include "dandan/core/TextReplacement.h"
#include <optional>
#include <vector>

namespace dandan::conditions
{

    bool SummoningSicknessCondition::isSatisfied(
        const core::Game &game,
        [[maybe_unused]] std::optional<std::vector<core::TextReplacement>>
            text_replacements) const
    {
        const auto *card = game.getCardByID(m_card_id);
        std::cout << "Checking summoning sickness condition for card "
                  << card->getData().getName()
                  << " (CardID: " << card->getID().getID() << ")\n";
        std::cout << "Card state: tapped=" << std::boolalpha
                  << card->getTapped()
                  << ", summoning_sick=" << card->getSummoningSickness()
                  << ", is_attacking=" << card->isAttacking() << "\n";
        // TODO: consider splitting this into two conditions, one for summoning
        // sickness and one for attacking status
        return card->getSummoningSickness() || card->isAttacking();
    }

} // namespace dandan::conditions