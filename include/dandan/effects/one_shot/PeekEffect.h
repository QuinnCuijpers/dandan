#ifndef DANDAN_PEEK_EFFECT_H
#define DANDAN_PEEK_EFFECT_H

#include "IOneShotEffect.h"
// TODO: change into reordering top effect
namespace dandan::effects
{

    /** @brief Represents the effect of looking at the top few cards of the
     * library
     * @struct PeekEffect
     *
     * @implements @IOneShotEffect
     */
    struct PeekEffect final : public IOneShotEffect
    {
        /// The amount of cards that would be peeked.
        int m_peek_amount{3};

        [[nodiscard]] std::unique_ptr<IOneShotEffect> clone() const override
        {
            return std::make_unique<PeekEffect>(m_peek_amount);
        }

        PeekEffect() = default;

        /** Constructor
         *@param peek_amount the amount of cards to peek.
         */
        explicit PeekEffect(int peek_amount) : m_peek_amount(peek_amount)
        {
        }
        // TODO: should ask for rearranging similar to scry
        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;
    };
} // namespace dandan::effects

#endif
