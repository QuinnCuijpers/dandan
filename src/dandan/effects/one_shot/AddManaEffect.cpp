#include "dandan/effects/one_shot/AddManaEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> AddManaEffect::apply_impl(
        core::Game &game) const
    {

        auto &player{
            game.getPlayer(game.priorityManager().getPlayerWithPriority())};
        player.manaPool().add(m_mana);
        return nullptr;
    }
} // namespace dandan::effects
