#include "dandan/effects/one_shot/BounceEffect.h"
#include <stdexcept>
#include <variant>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> BounceEffect::apply_impl(
        core::Game &game) const
    {
        if (!std::holds_alternative<core::CardID>(m_target))
        {
            throw std::runtime_error("Bounce Effect target is not a CardID");
        }
        auto card_id{std::get<core::CardID>(m_target)};
        auto *card{game.getCardByID(card_id)};
        auto &controller{game.getPlayer(card->getControllerID())};

        game.moveCardFromZone(controller, *card);
        controller.hand().addCard(*card);
        return nullptr;
    }

} // namespace dandan::effects