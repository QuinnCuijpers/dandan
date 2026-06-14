#ifndef DANDAN_SUMMONING_SICKNESS_CONDITION_H
#define DANDAN_SUMMONING_SICKNESS_CONDITION_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/conditions/ICondition.h"
#include "dandan/core/Card.h"
#include "dandan/core/TextReplacement.h"
#include <optional>
#include <vector>

namespace dandan::conditions
{
    /**
     * A condition that checks whether a card has summoning sickness.
     * @class SummoningSicknessCondition
     *
     * @implements ICondition
     */
    class SummoningSicknessCondition : public ICondition
    {
    public:
        /** Constructor
         * @param card_id The ID of the card to check for summoning sickness
         */
        explicit SummoningSicknessCondition(core::CardID card_id)
            : m_card_id(card_id)
        {
        }
        [[nodiscard]] bool isSatisfied(
            const core::Game &game,
            std::optional<abilities::AbilityContext> context =
                std::nullopt) const override;

        [[nodiscard]] std::unique_ptr<ICondition> clone() const override
        {
            return std::make_unique<SummoningSicknessCondition>(m_card_id);
        }

    private:
        core::CardID m_card_id;
    };
} // namespace dandan::conditions

#endif