#ifndef DANDAN_PUTCARDONTOPEFFECT_H
#define DANDAN_PUTCARDONTOPEFFECT_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>

namespace dandan::effects
{
    /** @brief A one-shot effect that puts a card on top of the deck from the
     * hand.
     * @class PutCardOnTopEffect
     * @implements IOneShotEffect
     */
    class PutCardOnTopEffect : public IOneShotEffect
    {
    public:
        /** @brief Create a PutCardOnTopEffect.
         * @param amount The number of cards to put on top.
         */
        explicit PutCardOnTopEffect(int amount) : m_amount(amount)
        {
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> clone() const override;

        [[nodiscard]] std::string display() const override;

        /** @brief Get the amount of cards to put on top.
         * @return The number of cards to put on top.
         */
        [[nodiscard]] int getAmount() const
        {
            return m_amount;
        }

    private:
        int m_amount{};
    };

} // namespace dandan::effects

#endif