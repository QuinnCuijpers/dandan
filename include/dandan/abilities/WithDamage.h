#ifndef WITHDAMAGE_H
#define WITHDAMAGE_H

#include "IAbilityDecorator.h"

namespace dandan::abilities
{

    class WithDamage : public IAbilityDecorator
    {
    public:
        WithDamage(std::unique_ptr<IAbility> ability)
            : IAbilityDecorator(std::move(ability)) {};
        WithDamage(std::unique_ptr<IAbility> ability, int damage)
            : IAbilityDecorator(std::move(ability)), m_damage{damage}
        {
        }

        int getDamage() const
        {
            return m_damage;
        }

        const IAbility *getInnerAbility() const
        {
            return m_ability.get();
        }

        void resolve() override;

    private:
        int m_damage{1};
    };
} // namespace dandan::abilities

#endif