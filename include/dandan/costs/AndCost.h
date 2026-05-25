#ifndef DANDAN_ANDCOST_H
#define DANDAN_ANDCOST_H

#include "dandan/costs/ICost.h"
#include <memory>
#include <vector>

namespace dandan::costs
{
    // TODO: consider renaming to CostList
    /** A composite cost that requires its left and right sub-costs to be
     * satisfied.
     * @class AndCost
     *
     * @implements ICost
     */
    class AndCost : public ICost
    {
    public:
        /** Constructs an AndCost with two sub-costs.
         * @param first The first sub-cost.
         * @param second The second sub-cost.
         */
        AndCost(std::unique_ptr<ICost> first, std::unique_ptr<ICost> second)
            : m_first(std::move(first)), m_second(std::move(second))
        {
        }

        /** Gets the sub-costs.
         * @return A vector of the sub-costs.
         */
        [[nodiscard]] std::vector<ICost *> getCosts() const
        {
            return {m_first.get(), m_second.get()};
        }

        void pay(
            [[maybe_unused]] core::Game &game,
            [[maybe_unused]] abilities::AbilityContext context) const override
        {
            m_first->pay(game, context);
            m_second->pay(game, context);
        }

        [[nodiscard]] bool canPay(const core::Card &source,
                                  const core::Player &player) const override
        {
            return m_first->canPay(source, player) &&
                   m_second->canPay(source, player);
        }

    private:
        std::unique_ptr<ICost> m_first;
        std::unique_ptr<ICost> m_second;
    };
} // namespace dandan::costs
#endif // DANDAN_ANDCOST_H