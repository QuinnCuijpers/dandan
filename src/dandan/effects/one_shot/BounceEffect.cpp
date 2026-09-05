#include "dandan/effects/one_shot/BounceEffect.h"
#include "dandan/core/GameState.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <stdexcept>
#include <variant>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> BounceEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};

        if (!std::holds_alternative<core::CardID>(m_target))
        {
            throw std::runtime_error("Bounce Effect target is not a CardID");
        }
        auto card_id{std::get<core::CardID>(m_target)};
        auto *card{card_registry[card_id]};
        auto &controller{game.getPlayer(card->getControllerID())};

        game.moveCardFromZone(controller, *card);
        controller.hand().addCard(*card);
        return nullptr;
    }

} // namespace dandan::effects
