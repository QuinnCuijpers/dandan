#ifndef WITHDAMAGE_H
#define WITHDAMAGE_H

#include "IAbilityDecorator.h"

namespace dandan::abilities
{
    /** @brief An ability decorator that adds self damage to an ability
     * @class WithDamage
     *
     * @implements IAbilityDecorator
     */
    class WithDamage final : public IAbilityDecorator
    {
    public:
        /** Constructor
         * the self damage amount is set to 1 by default
         * @param ability The ability to decorate
         */
        explicit WithDamage(std::unique_ptr<IAbility> ability)
            : IAbilityDecorator(std::move(ability)) {};
        /** Constructor
         * @param ability The ability to decorate
         * @param damage The amount of damage to add
         */
        WithDamage(std::unique_ptr<IAbility> ability, int damage)
            : IAbilityDecorator(std::move(ability)), m_damage{damage}
        {
        }

        [[nodiscard]] std::string display() const override;
        [[nodiscard]] std::string displayOption(size_t index) const override;

        /** Get the damage amount
         * @return The damage amount
         */
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

        [[nodiscard]] size_t optionsAmount() const override
        {
            return m_ability->optionsAmount();
        }

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game, AbilityContext context) const override;

    private:
        int m_damage{1};
    };
} // namespace dandan::abilities

#endif
