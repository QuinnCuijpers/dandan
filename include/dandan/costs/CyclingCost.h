#ifndef DANDAN_CYCLING_H
#define DANDAN_CYCLING_H

#include "ICost.h"
#include "GenericManaCost.h"

namespace dandan::costs
{
    // TODO: should arguably be done as a wrapper around a GenericManaCost, but for now this is simpler to implement and test
    class CyclingCost : public ICost
    {
    public:
        CyclingCost(std::unique_ptr<ICost> mc) : m_inner_cost{std::move(mc)} {};

        void evaluate() override;

        const ICost *getInnerCost() const { return m_inner_cost.get(); }

    private:
        std::unique_ptr<ICost> m_inner_cost{};
    };
}

#endif