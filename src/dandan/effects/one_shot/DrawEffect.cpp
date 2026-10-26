#include "dandan/effects/one_shot/DrawEffect.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/GameState.h"
#include "dandan/numbers/ExactNumber.h"

#include "dandan/utils/convertToWords.h"
#include <iostream>
#include <memory>
#include <utility>

namespace dandan::effects
{
    DrawEffect::DrawEffect(std::unique_ptr<numbers::INumber> amount,
                           EffectContext context)
        : IOneShotEffect(std::move(context)), m_amount(std::move(amount))
    {
    }

    std::unique_ptr<IOneShotEffect> DrawEffect::copy() const
    {
        return std::make_unique<DrawEffect>(m_amount->clone(),
                                            getEffectContext());
    }

    DrawEffectDefinition::DrawEffectDefinition(int amount)
        : m_amount(std::make_unique<numbers::ExactNumber>(amount))
    {
    }

    DrawEffectDefinition::DrawEffectDefinition(
        std::unique_ptr<numbers::INumber> amount)
        : m_amount(std::move(amount))
    {
    }

    const std::unique_ptr<numbers::INumber> &DrawEffectDefinition::getNumber()
        const
    {
        return m_amount;
    }

    std::unique_ptr<IOneShotEffect> DrawEffectDefinition::bind(
        [[maybe_unused]] core::ExecutionContext exec_ctx,
        EffectContext context) const
    {
        return std::make_unique<DrawEffect>(m_amount->clone(), context);
    }

    std::unique_ptr<IOneShotEffectDefinition> DrawEffectDefinition::clone()
        const
    {
        return std::make_unique<DrawEffectDefinition>(m_amount->clone());
    }

    std::string DrawEffectDefinition::display() const
    {
        if (const auto *fixed =
                dynamic_cast<const numbers::ExactNumber *>(m_amount.get()))
        {
            std::string res{};
            if (fixed->getValue() == 1)
            {
                res += "Draw a card";
            }
            else
            {
                res += "Draw " + utils::convertToWords(fixed->getValue()) +
                       " cards";
            }

            return res;
        }
        throw std::runtime_error("Unknown INumber type in DrawEffect display");
        // return "Draw " + m_amount->display() + " cards";
    }

    std::unique_ptr<events::IEvent> DrawEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};

        int value{m_amount->getValue(exec_ctx, getEffectContext())};

        if (value == 1)
        {
            std::cout << "Applying draw effect\n";
            auto &player{game.getPlayer(getEffectContext().player_id)};
            player.drawCard(exec_ctx);
            return nullptr;
        }
        // Break down the draw effect into multiple single card draws to
        // trigger any relevant state triggers

        std::cout << "Applying draw effect for " << value << " cards\n";
        for (int i = 0; i < value; ++i)
        {
            auto draw_definition{std::make_unique<DrawEffectDefinition>(1)};
            const auto &player{game.getPlayer(getEffectContext().player_id)};
            auto draw_effect{
                draw_definition->bind(exec_ctx, EffectContext{player.getID()}),
            };

            // breaking effect up doesnt require checking replacement effects as
            // all underlying effects are checked
            static_cast<void>(draw_effect->apply(exec_ctx));
        }

        return nullptr;
    }

} // namespace dandan::effects
