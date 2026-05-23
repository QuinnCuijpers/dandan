#ifndef DANDAN_CYCLING_H
#define DANDAN_CYCLING_H

#include "ICost.h"
#include <memory>

namespace dandan::costs
{
    class CyclingCost final : public ICost
    {
    public:
        explicit CyclingCost(std::unique_ptr<ICost> inner_cost)
            : m_inner_cost{std::move(inner_cost)} {};

        [[nodiscard]] const ICost *getInnerCost() const
        {
            return m_inner_cost.get();
        }

        [[nodiscard]] bool canPay(const core::Card &source,
                                  const core::Player &player) const override
        {
            if (source.getZone() != core::Zone::HAND)
            {
                return false;
            }
            return m_inner_cost->canPay(source, player);
        }

        void pay(
            [[maybe_unused]] core::Game &game,
            [[maybe_unused]] abilities::AbilityContext context) const override
        {
            m_inner_cost->pay(game, context);
        }

    private:
        std::unique_ptr<ICost> m_inner_cost;
    };
} // namespace dandan::costs

#endif