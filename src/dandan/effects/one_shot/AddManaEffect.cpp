#include "dandan/effects/one_shot/AddManaEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> AddManaEffect::apply(core::Game &game) const
    {
        for (const auto &[type, amount] : m_mana)
        {
            game.activePlayer().manaPool().addMana(type, amount);
        }
        return nullptr;
    }
} // namespace dandan::effects