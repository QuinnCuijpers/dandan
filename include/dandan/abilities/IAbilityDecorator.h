#ifndef IABILITYDECORATOR_H
#define IABILITYDECORATOR_H

#include "IAbility.h"
#include <memory>

namespace dandan::abilities
{
    /** An interface for ability decorators to use the decorator pattern with
     * abilities
     * @class IAbilityDecorator
     *
     * @implements IAbility
     */
    struct IAbilityDecorator : public IAbility
    {
    public:
        /// The ability being decorated
        std::unique_ptr<IAbility> m_ability;

        /** Constructor
         * @param ability The ability to decorate
         */
        explicit IAbilityDecorator(std::unique_ptr<IAbility> ability)
            : m_ability{std::move(ability)} {};

        /**
         * Get the inner ability being decorated
         * @return The inner ability being decorated
         */
        [[nodiscard]] const IAbility *getInnerAbility() const
        {
            return m_ability.get();
        }

        [[nodiscard]] bool canActivate(core::Game &game,
                                       AbilityContext context) const override
        {
            return m_ability->canActivate(game, context);
        }
    };
} // namespace dandan::abilities

#endif