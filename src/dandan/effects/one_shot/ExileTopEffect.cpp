#include "dandan/effects/one_shot/ExileTopEffect.h"
#include "dandan/core/Game.h"

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> ExileTopEffect::apply_impl(
        core::Game &game) const
    {
        for (int i = 0; i < m_amount; ++i)
        {
            if (game.library().getCards().empty())
            {
                break;
            }
            auto card_id{game.library().getCards().front()};
            auto *card{game.getCardByID(card_id)};
            game.moveCardFromZone(game.activePlayer(), *card);
            game.exile().addCard(*card);
        }
        return nullptr;
    }
} // namespace dandan::effects