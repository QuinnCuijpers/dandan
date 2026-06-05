#include "dandan/effects/one_shot/DrawEffect.h"

#include "dandan/core/Game.h"
#include "dandan/util.h"
#include <iostream>

namespace dandan::effects
{

    std::string DrawEffect::display() const
    {
        std::string res{};
        if (m_amount == 1)
        {
            res += "Draw a card";
        }
        else
        {
            res += "Draw " + utils::convertToWords(m_amount) + " cards";
        }

        return res;
    }
    std::unique_ptr<events::IEvent> DrawEffect::apply_impl(
        [[maybe_unused]] core::Game &game) const
    {
        std::cout << "Applying draw effect\n";

        if (m_amount == 1)
        {
            game.activePlayer().drawCard(game);
            return nullptr;
        }
        // Break down the draw effect into multiple single card draws to trigger
        // any relevant state triggers
        for (int i = 0; i < m_amount; ++i)
        {
            auto draw_effect{std::make_unique<DrawEffect>(1)};
            draw_effect->apply(game);
        }

        return nullptr;
    }

} // namespace dandan::effects