#ifndef DANDAN_WITHADDITIONALCOST_H
#define DANDAN_WITHADDITIONALCOST_H

#include "dandan/abilities/IAbility.h"
#include "dandan/abilities/IAbilityDecorator.h"
#include "dandan/costs/ICost.h"
#include <memory>
namespace dandan::abilities
{
    class WithAdditionalCost : public IAbilityDecorator
    {
    public:
        WithAdditionalCost(std::unique_ptr<IAbility> ability,
                           std::unique_ptr<costs::ICost> cost)
            : IAbilityDecorator(std::move(ability)), m_cost(std::move(cost))
        {
        }

        const costs::ICost *getAdditionalCost() const
        {
            return m_cost.get();
        }

        void resolve() const override;

    private:
        std::unique_ptr<costs::ICost> m_cost;
    };
} // namespace dandan::abilities

#endif // DANDAN_WITHADDITIONALCOST_H