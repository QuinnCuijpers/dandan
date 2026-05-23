#ifndef DANDAN_SELFSACRIFICECOST_H
#define DANDAN_SELFSACRIFICECOST_H

#include "dandan/core/Game.h"
#include "dandan/costs/ICost.h"

namespace dandan::costs
{
    class SelfSacrificeCost : public ICost
    {
    public:
        [[nodiscard]] bool canPay(const core::Card &source,
                                  const core::Player &player) const override
        {
            return source.getControllerID().id() == player.getID().id();
        }

        void pay(
            [[maybe_unused]] core::Game &game,
            [[maybe_unused]] abilities::AbilityContext context) const override
        {
            [[maybe_unused]] auto &player =
                game.getPlayer(context.controller_id);
            // TODO: implement sacrifice
            //  player.sacrificeCard(context.source_card_id);
        }
    };
} // namespace dandan::costs

#endif