#ifndef DANDAN_CYCLING_H
#define DANDAN_CYCLING_H

#include "ICost.h"
#include "GenericManaCost.h"

namespace dandan::costs
{
    class CyclingCost : public ICost
    {
    public:
        CyclingCost() = default;
        CyclingCost(GenericManaCost mc) : m_generic_mana_cost{mc} {}
        void evaluate() override;

        void from_json(const nlohmann::json &j, ICost &cost) override;
        void to_json(nlohmann::json &j, const ICost &cost) override;

        GenericManaCost getGenericAmount() const { return m_generic_mana_cost; }

    private:
        GenericManaCost m_generic_mana_cost{2};
    };
}

#endif