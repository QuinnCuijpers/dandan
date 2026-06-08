#include "dandan/effects/one_shot/DrawEffect.h"

#include "dandan/core/Game.h"
#include "dandan/util.h"
#include <iostream>

namespace dandan::effects
{

    std::string DrawEffect::display() const
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
            game.activePlayer().drawCard(game);
            return nullptr;
        }
        // Break down the draw effect into multiple single card draws to
        // trigger any relevant state triggers

        std::cout << "Applying draw effect for " << value << " cards\n";
        for (int i = 0; i < value; ++i)
        {
            auto draw_effect{std::make_unique<DrawEffect>(1)};
            draw_effect->apply(game);
        }

        return nullptr;
    }

} // namespace dandan::effects