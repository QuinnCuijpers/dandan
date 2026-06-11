#ifndef DANDAN_PEEK_EFFECT_H
#define DANDAN_PEEK_EFFECT_H

#include "IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
namespace dandan::effects
{

    /** @brief Represents the effect of looking at the top few cards of the
     * library
     * @class PeekEffect
     *
     * @implements @IOneShotEffect
     */
    class PeekEffect final : public IOneShotEffect
    {
    public:
        /** Constructor
         *@param peek_amount the amount of cards to peek.
         */
        explicit PeekEffect(int peek_amount, core::PlayerID player_id)
            : m_peek_amount(peek_amount), m_player_id(player_id)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<PeekEffect>(m_peek_amount, m_player_id);
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

    private:
        int m_peek_amount{3};
        core::PlayerID m_player_id;
    };

    class PeekEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        PeekEffectDefinition() = default;
        explicit PeekEffectDefinition(int peek_amount)
            : m_peek_amount(peek_amount)
        {
        }
        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] core::Game &game,
            EffectContext context) const override
        {
            return std::make_unique<PeekEffect>(m_peek_amount,
                                                context.player().value());
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<PeekEffectDefinition>(m_peek_amount);
        }

        [[nodiscard]] int getPeekAmount() const
        {
            return m_peek_amount;
        }

    private:
        int m_peek_amount{3};
    };
} // namespace dandan::effects

#endif
