#ifndef DANDAN_PUTCARDONTOPEFFECT_H
#define DANDAN_PUTCARDONTOPEFFECT_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
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
         * @param playerID The ID of the player who will use this effect.
         */
        PutCardOnTopEffect(int amount, core::PlayerID playerID)
            : m_amount(amount), m_playerID(playerID)
        {
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

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
        core::PlayerID m_playerID;
    };

    class PutCardOnTopEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        /** @brief Create a PutCardOnTopEffect.
         * @param amount The number of cards to put on top.
         */
        explicit PutCardOnTopEffectDefinition(int amount) : m_amount(amount)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            EffectContext context) const override
        {
            return std::make_unique<PutCardOnTopEffect>(
                m_amount, context.player().value());
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<PutCardOnTopEffectDefinition>(m_amount);
        }

        // [[nodiscard]] std::string display() const override;

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