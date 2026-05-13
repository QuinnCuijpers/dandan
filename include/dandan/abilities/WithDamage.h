#ifndef WITHDAMAGE_H
#define WITHDAMAGE_H

#include "IAbilityDecorator.h"

namespace dandan::abilities
{

    class WithDamage final : public IAbilityDecorator
    {
    public:
        explicit WithDamage(std::unique_ptr<IAbility> ability)
            : IAbilityDecorator(std::move(ability)) {};
        WithDamage(std::unique_ptr<IAbility> ability, int damage)
            : IAbilityDecorator(std::move(ability)), m_damage{damage}
        {
        }

        [[nodiscard]] int getDamage() const
        {
            return m_damage;
        }

        [[nodiscard]] bool appliesTo(
            const events::IEvent &event,
            abilities::AbilityContext context) const override
        {
            return m_ability->appliesTo(event, context);
        }

        void resolve(core::Game &game, AbilityContext context) const override;

    private:
        int m_damage{1};
    };
} // namespace dandan::abilities

#endif