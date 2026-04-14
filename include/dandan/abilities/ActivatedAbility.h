#ifndef DANDAN_ACTIVATED_ABILITY_H
#define DANDAN_ACTIVATED_ABILITY_H

#include "IAbility.h"
#include "dandan/costs/ICost.h"
#include "dandan/effects/IEffect.h"
#include <memory>

namespace dandan::abilities
{
    class ActivatedAbility final : public IAbility
    {
    public:
        ActivatedAbility(std::unique_ptr<costs::ICost> cost,
                         std::unique_ptr<effects::IEffect> effect)
            : m_cost(std::move(cost)), m_effect(std::move(effect))
        {
        }

        void resolve() const override;

        const costs::ICost *getCost() const
        {
            return m_cost.get();
        }
        const effects::IEffect *getEffect() const
        {
            return m_effect.get();
        }

    private:
        std::unique_ptr<costs::ICost> m_cost;
        std::unique_ptr<effects::IEffect> m_effect;
    };
} // namespace dandan::abilities

#endif