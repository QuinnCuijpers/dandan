#include "dandan/effects/EffectContext.h"

namespace dandan::effects
{
    EffectContext::EffectContext(core::CardID card_id, core::PlayerID player)
        : card_id(card_id), player_id(player)
    {
    }

    EffectContext::EffectContext(core::PlayerID player_id)
        : EffectContext(core::CardID::getInvalidID(), player_id)
    {
    }

    EffectContext::EffectContext(const abilities::AbilityContext &context)
        : card_id(context.source_card_id), player_id(context.controller_id),
          chosen_mode_index(context.chosen_mode_index),
          text_replacements(context.text_replacements)
    {
    }
} // namespace dandan::effects
