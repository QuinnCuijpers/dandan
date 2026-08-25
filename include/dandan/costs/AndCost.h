#ifndef DANDAN_ANDCOST_H
#define DANDAN_ANDCOST_H

#include "dandan/costs/ICost.h"
#include <memory>
#include <vector>

namespace dandan::costs
{
    /** @brief A composite cost that requires its left and right sub-costs to be
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
        AndCost(std::unique_ptr<ICost> first, std::unique_ptr<ICost> second);

        [[nodiscard]] std::string display(
            [[maybe_unused]] bool isFinal = true) const override;

        /** Gets the sub-costs.
         * @return A vector of the sub-costs.
         */
        [[nodiscard]] std::vector<ICost *> getCosts() const;

        void pay(core::ExecutionContext exec_ctx,
                 abilities::AbilityContext context) const override;

        [[nodiscard]] bool canPay(const core::Card &source,
                                  const core::Player &player) const override;

    private:
        std::unique_ptr<ICost> m_first;
        std::unique_ptr<ICost> m_second;
    };
} // namespace dandan::costs
#endif // DANDAN_ANDCOST_H
