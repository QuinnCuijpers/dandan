#include "dandan/effects/one_shot/MemoryLapseEffect.h"
#include "dandan/core/Game.h"
#include "dandan/events/IEvent.h"
#include <memory>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> MemoryLapseEffect::apply_impl(
        core::Game &game) const
    {
        if (!std::holds_alternative<core::CardID>(m_target))
        {
            throw std::runtime_error(
                "MemoryLapseEffect target is not a CardID");
        }
        auto card_id{std::get<core::CardID>(m_target)};
        auto *card{game.getCardByID(card_id)};
        auto &controller{game.getPlayer(card->getControllerID())};

        if (card->canBeCountered())
        {
            game.moveCardFromZone(controller, *card);
            game.moveCardToZone(*card, controller, m_target_zone);
        }
        return nullptr;
    }
} // namespace dandan::effects