#ifndef DANDAN_ACTIVATED_ABILITY_H
#define DANDAN_ACTIVATED_ABILITY_H

#include "IAbility.h"
#include "dandan/costs/ICost.h"
#include "dandan/effects/ITriggeredEffect.h"
#include "dandan/effects/IEffect.h"
#include <memory>

namespace dandan::abilities
{
    class ActivatedAbility : public IAbility
    {
    public:
        ActivatedAbility(std::unique_ptr<costs::ICost> cost, std::unique_ptr<effects::IEffect> effect)
            : m_cost(std::move(cost)), m_effect(std::move(effect)) {}

        void resolve() override;

        void from_json(const nlohmann::json &j, IAbility &ability) override;

        void to_json(nlohmann::json &j, const IAbility &ability) override;

    private:
        std::unique_ptr<costs::ICost> m_cost;
        std::unique_ptr<effects::IEffect> m_effect;
    };
}

#endif