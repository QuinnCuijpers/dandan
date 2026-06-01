#ifndef IABILITY_H
#define IABILITY_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>
#include <stdexcept>

namespace dandan::core
{
    class Game;
}

namespace dandan::events
{
    class IEvent;
}

namespace dandan::abilities
{
    /** @brief The interface for all abilities
     * @class IAbility
     */
    class IAbility
    {
    public:
        IAbility() = default;
        IAbility(const IAbility &) = delete;
        IAbility(IAbility &&) = delete;
        IAbility &operator=(const IAbility &) = delete;
        IAbility &operator=(IAbility &&) = delete;
        virtual ~IAbility() = default;

        [[nodiscard]] virtual std::string display() const
        {
            throw std::runtime_error("Unimplemented display");
        }

        [[nodiscard]] virtual std::string displayOption(
            [[maybe_unused]] size_t index) const
        {
            throw std::runtime_error(
                "Unimplemented display option for ability");
        }

        /** Create the effect for the ability
         * @param game The game object to mutate when the ability is resolving
         * @param context The context for the ability's execution
         * @return The effect created by the ability
         */
        virtual std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game, AbilityContext context) const = 0;

        /** Determine if the ability applies to a given event
         * @param event The event to check
         * @param context The context for the ability's execution
         * @return True if the ability applies to the event, false otherwise.
         * The default implementation returns false.
         */
        [[nodiscard]] virtual bool appliesTo(
            [[maybe_unused]] const events::IEvent &event,
            [[maybe_unused]] abilities::AbilityContext context) const
        {
            return false;
        }

        /** Determine if the ability can be activated
         * @param game The game object to check for activation conditions
         * @param context The context for the ability's execution
         * @return True if the ability can be activated, false otherwise.
         * The default implementation returns false.
         */
        [[nodiscard]] virtual bool canActivate(
            [[maybe_unused]] core::Game &game,
            [[maybe_unused]] AbilityContext context) const
        {
            return false;
        }

        [[nodiscard]] virtual size_t optionsAmount() const
        {
            throw std::runtime_error("Unimplemented options count for ability");
        }
    };
}; // namespace dandan::abilities

#endif
