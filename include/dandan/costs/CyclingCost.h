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

        void evaluate() override;

        [[nodiscard]] const ICost *getInnerCost() const
        {
            return m_inner_cost.get();
        }

    private:
        std::unique_ptr<ICost> m_inner_cost;
    };
} // namespace dandan::costs

#endif