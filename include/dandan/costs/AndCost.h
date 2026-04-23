#ifndef DANDAN_ANDCOST_H
#define DANDAN_ANDCOST_H

#include "dandan/costs/ICost.h"
#include <memory>
#include <vector>

namespace dandan::costs
{
    // TODO: consider renaming to CostList
    class AndCost : public ICost
    {
    public:
        AndCost(std::unique_ptr<ICost> first, std::unique_ptr<ICost> second)
            : m_first(std::move(first)), m_second(std::move(second))
        {
        }

        [[nodiscard]] std::vector<ICost *> getCosts() const
        {
            return {m_first.get(), m_second.get()};
        }

        void evaluate() override
        {
            m_first->evaluate();
            m_second->evaluate();
        }

    private:
        std::unique_ptr<ICost> m_first;
        std::unique_ptr<ICost> m_second;
    };
} // namespace dandan::costs
#endif // DANDAN_ANDCOST_H