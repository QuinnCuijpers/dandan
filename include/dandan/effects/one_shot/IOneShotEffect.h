#ifndef DANDAN_I_EFFECT_H
#define DANDAN_I_EFFECT_H

#include "dandan/events/IEvent.h"
#include <memory>
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

        /**
         * creates a new Effect that clones the underlying effect.
         *
         * @returns A unique ptr to the cloned effect.
         */
        [[nodiscard]] virtual std::unique_ptr<IOneShotEffect> clone() const = 0;

        /**
         * apply the Effect to the game state by mutating it.
         * @param game the game to apply the effect to
         * @return an event to notify that the effect happened
         */
        virtual std::unique_ptr<events::IEvent> apply(
            core::Game &game) const = 0;
    };

} // namespace dandan::effects

#endif
