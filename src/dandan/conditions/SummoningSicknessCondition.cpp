#include "dandan/conditions/SummoningSicknessCondition.h"
#include "dandan/core/Game.h"
#include <optional>

namespace dandan::conditions
{

    SummoningSicknessCondition::SummoningSicknessCondition(core::CardID card_id)
        : m_card_id(card_id)
    {
    }

    bool SummoningSicknessCondition::isSatisfied(
        const core::Game &game,
        [[maybe_unused]] std::optional<effects::EffectContext> context) const
    {
        const auto *card = game.getCardByID(m_card_id);
        std::cout << "Checking summoning sickness condition for card "
                  << card->getData().name
                  << " (CardID: " << card->getID().getID() << ")\n";
        std::cout << "Card state: tapped=" << std::boolalpha
                  << card->getTapped()
                  << ", summoning_sick=" << card->getSummoningSickness()
                  << ", is_attacking=" << card->isAttacking() << "\n";
        // TODO: consider splitting this into two conditions, one for summoning
        // sickness and one for attacking status
        return card->getSummoningSickness() || card->isAttacking();
    }

    [[nodiscard]] std::unique_ptr<ICondition> SummoningSicknessCondition::
        clone() const
    {
        return std::make_unique<SummoningSicknessCondition>(m_card_id);
    }

} // namespace dandan::conditions
