#ifndef DANDAN_SELFSACRIFICECOST_H
#define DANDAN_SELFSACRIFICECOST_H

#include "dandan/core/Game.h"
#include "dandan/costs/ICost.h"

namespace dandan::costs
{
    /** @brief A cost that requires the player to sacrifice one of their own
     * cards.
     * @class SelfSacrificeCost
     * @implements ICost
     */
    class SelfSacrificeCost : public ICost
    {
    public:
        SelfSacrificeCost() = default;

        [[nodiscard]] std::string display(
            [[maybe_unused]] bool isFinal = true) const override;

        [[nodiscard]] bool canPay(const core::Card &source,
                                  const core::Player &player) const override;

        void pay(core::Game &game,
                 abilities::AbilityContext context) const override;
    };
} // namespace dandan::costs

#endif
