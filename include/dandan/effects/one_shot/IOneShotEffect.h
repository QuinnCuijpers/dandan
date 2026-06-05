#ifndef DANDAN_I_EFFECT_H
#define DANDAN_I_EFFECT_H

#include "dandan/events/IEvent.h"
#include <memory>
#include <stdexcept>

namespace dandan::core
{
    class Game;
}

namespace dandan::effects
{
    /**
     * @brief The base interface for One shot Effects.
     * @class IOneShotEffect
     */
    class IOneShotEffect
    {
    public:
        IOneShotEffect() = default;
        IOneShotEffect(const IOneShotEffect &) = delete;
        IOneShotEffect(IOneShotEffect &&) = delete;
        IOneShotEffect &operator=(const IOneShotEffect &) = delete;
        IOneShotEffect &operator=(IOneShotEffect &&) = delete;
        virtual ~IOneShotEffect() = default;

        /** @brief Get the display string for the effect
         * @return The display string
         */
        [[nodiscard]] virtual std::string display() const
        {
            throw std::runtime_error("Unimplemented display");
        }

        /**
         * creates a new Effect that clones the underlying effect.
         *
         * @returns A unique ptr to the cloned effect.
         */
        [[nodiscard]] virtual std::unique_ptr<IOneShotEffect> clone() const = 0;

        /**
         * apply the Effect to the game state by mutating it.
         * also updates the condition manager
         * @param game the game to apply the effect to
         * @return an event to notify that the effect happened
         */
        std::unique_ptr<events::IEvent> apply(core::Game &game) const;

        virtual std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const = 0;
    };

} // namespace dandan::effects

#endif
