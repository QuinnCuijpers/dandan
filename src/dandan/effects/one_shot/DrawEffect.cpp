#include "dandan/effects/one_shot/DrawEffect.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/Game.h"
#include "dandan/numbers/ExactNumber.h"

#include "dandan/serialization/JsonFactory.h"
#include "dandan/utils/convertToWords.h"
#include <iostream>
#include <memory>

namespace dandan::effects
{

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
            auto &player{game.getPlayer(getEffectContext().player_id.value())};
            player.drawCard(exec_ctx);
            return nullptr;
        }
        // Break down the draw effect into multiple single card draws to
        // trigger any relevant state triggers

        std::cout << "Applying draw effect for " << value << " cards\n";
        for (int i = 0; i < value; ++i)
        {
            auto draw_definition{std::make_unique<DrawEffectDefinition>(1)};
            const auto &player{
                game.getPlayer(getEffectContext().player_id.value())};
            auto draw_effect{
                draw_definition->bind(exec_ctx, EffectContext{player.getID()})};

            // breaking effect up doesnt require checking replacement effects as
            // all underlying effects are checked
            static_cast<void>(draw_effect->apply(exec_ctx));
        }

        return nullptr;
    }

} // namespace dandan::effects
