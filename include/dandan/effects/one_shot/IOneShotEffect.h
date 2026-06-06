#ifndef DANDAN_I_EFFECT_H
#define DANDAN_I_EFFECT_H

#include "dandan/events/IEvent.h"
#include <memory>
#include <optional>
#include <stdexcept>

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

        /**
         * Get the next effect in the chain.
         * @return An optional unique pointer to the next effect.
         */
        [[nodiscard]] std::optional<std::unique_ptr<IOneShotEffect>> getNext()
            const
        {
            if (m_next.has_value())
            {
                return std::make_optional(
                    std::unique_ptr<IOneShotEffect>(m_next.value()->clone()));
            }
            return std::nullopt;
        }

        void setNext(std::optional<std::unique_ptr<IOneShotEffect>> next)
        {
            m_next = std::move(next);
        }

    private:
        std::optional<std::unique_ptr<IOneShotEffect>> m_next;
    };

} // namespace dandan::effects

#endif
