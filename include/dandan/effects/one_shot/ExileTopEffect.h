#ifndef DANDAN_EXILETOPEFFECT_H
#define DANDAN_EXILETOPEFFECT_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"

namespace dandan::effects
{
    class ExileTopEffect : public IOneShotEffect
    {
    public:
        ExileTopEffect(int amount, core::PlayerID player)
            : m_amount(amount), m_player(player)
        {
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<ExileTopEffect>(m_amount, m_player);
        }

    private:
        int m_amount;
        core::PlayerID m_player;
    };

    class ExileTopEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            EffectContext context) const override
        {
            return std::make_unique<ExileTopEffect>(m_amount,
                                                    context.player().value());
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<ExileTopEffectDefinition>(m_amount);
        }

        ExileTopEffectDefinition(int amount) : m_amount(amount)
        {
        }

        [[nodiscard]] int getAmount() const
        {
            return m_amount;
        }

    private:
        int m_amount;
    };
} // namespace dandan::effects

#endif