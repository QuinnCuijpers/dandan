#ifndef DANDAN_TAPCOST_H
#define DANDAN_TAPCOST_H

#include "dandan/core/Game.h"
#include "dandan/core/Zone.h"
#include "dandan/costs/ICost.h"

namespace dandan::costs
{

    /**
     * @brief A cost that requires the player to tap the source card.
     * @class TapCost
     *
     * @implements ICost
     */
    class TapCost : public ICost
    {
    public:
        TapCost() = default;

        [[nodiscard]] bool canPay(
            const core::Card &source,
            [[maybe_unused]] const core::Player &player) const override
        {
            return !source.getTapped() &&
                   source.getZone() == core::Zone::BATTLEFIELD;
        }

        void pay(
            [[maybe_unused]] core::Game &game,
            [[maybe_unused]] abilities::AbilityContext context) const override
        {
            auto *card = game.getCardByID(context.source_card_id);
            card->setTapped(true);
        }
    };
} // namespace dandan::costs

#endif
