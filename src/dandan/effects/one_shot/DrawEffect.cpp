#include "dandan/effects/one_shot/DrawEffect.h"
#include "dandan/numbers/ExactNumber.h"

#include "dandan/core/Game.h"
#include "dandan/util.h"
#include <iostream>

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
        [[maybe_unused]] core::Game &game) const
    {
        int value{m_amount->getValue(game)};

        if (value == 1)
        {
            std::cout << "Applying draw effect\n";
            auto &player{game.getPlayer(m_context.player().value())};
            player.drawCard(game);
            return nullptr;
        }
        // Break down the draw effect into multiple single card draws to
        // trigger any relevant state triggers

        std::cout << "Applying draw effect for " << value << " cards\n";
        for (int i = 0; i < value; ++i)
        {
            auto draw_definition{std::make_unique<DrawEffectDefinition>(1)};
            auto &player{game.getPlayer(m_context.player().value())};
            auto draw_effect{
                draw_definition->bind(EffectContext{player.getID()})};

            // breaking effect up doesnt require checking replacement effects as
            // all underlying effects are checked
            draw_effect->apply(game);
        }

        return nullptr;
    }

} // namespace dandan::effects