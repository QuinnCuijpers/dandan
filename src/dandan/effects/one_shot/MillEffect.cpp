#include "dandan/effects/one_shot/MillEffect.h"
#include "dandan/utils/convertToWords.h"

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> MillEffect::apply_impl(
        core::Game &game) const
    {
        game.library().mill(game, m_amount);
        return nullptr;
    }

    std::string MillEffectDefinition::display() const
    {
        return "Target player mills " + utils::convertToWords(m_amount) +
               " card" + (m_amount > 1 ? "s" : "");
    }
} // namespace dandan::effects