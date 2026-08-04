#ifndef DANDAN_TAPCOST_H
#define DANDAN_TAPCOST_H

#include "dandan/core/Game.h"
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

        [[nodiscard]] std::string display(bool isFinal = true) const override;

        [[nodiscard]] bool canPay(const core::Card &source,
                                  const core::Player &player) const override;

        void pay(core::Game &game,
                 abilities::AbilityContext context) const override;
    };
} // namespace dandan::costs

#endif
