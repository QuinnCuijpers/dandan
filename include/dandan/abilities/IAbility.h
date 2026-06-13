#ifndef IABILITY_H
#define IABILITY_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/core/ColorWord.h"
#include "dandan/core/SubType.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>
#include <stdexcept>

namespace dandan::core
{
    class Game;
} // namespace dandan::core

namespace dandan::events
{
    class IEvent;
}

namespace dandan::abilities
{
    /** @brief The interface for all abilities.
     *
     *It defines the definition of an
     * ability, all cards instead hold BoundAbilities that are attached to a
     * specific card and player, but the definition of the ability is shared
     * between all instances of that ability.
     *
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

        /** @brief Get the display string for the ability
         * @return The display string
         */
        [[nodiscard]] virtual std::string display() const
        {
            throw std::runtime_error("Unimplemented display for " +
                                     std::string(typeid(*this).name()));
        }

        /** @brief Get the display string for a specific option of the ability
         * @param index The index of the option
         * @return The display string for the option
         */
        [[nodiscard]] virtual std::string displayOption(
            [[maybe_unused]] size_t index) const
        {
            throw std::runtime_error(
                "Unimplemented display option for ability " +
                std::string(typeid(*this).name()));
        }

        /** Create the effect for the ability
         * @param game The game object to mutate when the ability is resolving
         * @param context The context for the ability's execution
         * @return The effect created by the ability
         */
        virtual std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game, AbilityContext context) const = 0;

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

        /** @brief Get the number of options for the ability
         * @return The number of options
         */
        [[nodiscard]] virtual size_t optionsAmount() const
        {
            throw std::runtime_error(
                "Unimplemented options count for ability " +
                std::string(typeid(*this).name()));
        }

        // // NOLINTBEGIN(bugprone-easily-swappable-parameters)
        // virtual void replaceColorWord(
        //     [[maybe_unused]] core::ColorWord from,
        //     [[maybe_unused]] core::ColorWord new_color)
        // {
        // }

        // virtual void replaceBasicWord([[maybe_unused]] core::SubType from,
        //                               [[maybe_unused]] core::SubType
        //                               new_basic)
        // {
        // }
        // // NOLINTEND(bugprone-easily-swappable-parameters)
    };
}; // namespace dandan::abilities

#endif
