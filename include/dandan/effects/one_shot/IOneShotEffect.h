#ifndef DANDAN_I_EFFECT_H
#define DANDAN_I_EFFECT_H

#include "dandan/core/ExecutionContext.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/events/IEvent.h"
#include <memory>
#include <stdexcept>
#include <utility>

namespace dandan::core
{
    class Game;
}

namespace dandan::effects
{
    /**
     * @brief The base abstract class for One shot Effects.
     * @class IOneShotEffect
     */
    class IOneShotEffect
    {
    public:
        IOneShotEffect(EffectContext effect_context)
            : m_effect_context(std::move(effect_context))
        {
        }

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
        [[nodiscard]] virtual std::unique_ptr<IOneShotEffect> copy() const = 0;

        /**
         * apply the Effect to the game state by mutating it.
         * also updates the condition manager
         * @param exec_ctx the context to apply the effect to
         * @return an event to notify that the effect happened
         */
        [[nodiscard]] std::unique_ptr<events::IEvent> apply(
            core::ExecutionContext exec_ctx) const;

        /** @brief Apply the effect specific implementation.
         * @param game The game instance.
         * @return The event to notify that the effect happened.
         */
        [[nodiscard]] virtual std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const = 0;

        [[nodiscard]] virtual EffectContext getEffectContext() const
        {
            return m_effect_context;
        }

    private:
        EffectContext m_effect_context;
    };

} // namespace dandan::effects

#endif
