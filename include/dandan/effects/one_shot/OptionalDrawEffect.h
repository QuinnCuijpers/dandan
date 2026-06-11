#ifndef DANDAN_OPTIONALDRAWEFFECT_H
#define DANDAN_OPTIONALDRAWEFFECT_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"

namespace dandan::effects
{
    class OptionalDrawEffect : public IOneShotEffect
    {
    public:
        OptionalDrawEffect(int amount, bool each_player)
            : m_amount(amount), m_each_player(each_player)
        {
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<OptionalDrawEffect>(m_amount,
                                                        m_each_player);
        }

    private:
        int m_amount;
        bool m_each_player{false};
    };

    class OptionalDrawEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] core::Game &game,
            [[maybe_unused]] EffectContext context) const override
        {
            return std::make_unique<OptionalDrawEffect>(m_amount,
                                                        m_each_player);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<OptionalDrawEffectDefinition>(
                m_amount, m_each_player);
        }

        OptionalDrawEffectDefinition(int amount, bool each_player)
            : m_amount(amount), m_each_player(each_player)
        {
        }

        [[nodiscard]] int getAmount() const
        {
            return m_amount;
        }

        [[nodiscard]] bool isEachPlayer() const
        {
            return m_each_player;
        }

    private:
        int m_amount;
        bool m_each_player{false};
    };
} // namespace dandan::effects

#endif