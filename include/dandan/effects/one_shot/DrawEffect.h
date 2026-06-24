#ifndef DANDAN_DRAWEFFECT_H
#define DANDAN_DRAWEFFECT_H

#include <utility>

#include "dandan/core/Game.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "dandan/numbers/ExactNumber.h"
#include "dandan/numbers/INumber.h"

namespace dandan::effects
{
    class DrawEffect : public IOneShotEffect
    {
    public:
        DrawEffect(std::unique_ptr<numbers::INumber> amount,
                   EffectContext context)
            : IOneShotEffect(std::move(context)), m_amount(std::move(amount))
        {
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<DrawEffect>(m_amount->clone(),
                                                getEffectContext());
        }

    private:
        std::unique_ptr<numbers::INumber> m_amount;
    };

    class DrawEffectDefinition final : public IOneShotEffectDefinition
    {
    public:
        DrawEffectDefinition() = default;
        /** Constructor
         * @param amount the amount of cards this effect would draw
         */
        explicit DrawEffectDefinition(int amount)
            : m_amount(std::make_unique<numbers::ExactNumber>(amount))
        {
        }

        explicit DrawEffectDefinition(std::unique_ptr<numbers::INumber> amount)
            : m_amount(std::move(amount))
        {
        }

        [[nodiscard]] const std::unique_ptr<numbers::INumber> &getNumber() const
        {
            return m_amount;
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::Game &game,
            EffectContext context) const override
        {
            return std::make_unique<DrawEffect>(m_amount->clone(), context);
        }

        [[nodiscard]] std::string display() const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<DrawEffectDefinition>(m_amount->clone());
        }

    private:
        std::unique_ptr<numbers::INumber> m_amount{
            std::make_unique<numbers::ExactNumber>(1)};
    };

} // namespace dandan::effects

#endif