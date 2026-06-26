#ifndef DANDAN_EFFECTCONTEXT_H
#define DANDAN_EFFECTCONTEXT_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Expire.h"
#include "dandan/core/PlayerID.h"
#include <optional>

namespace dandan::effects
{
    struct EffectContext
    {
        explicit EffectContext(
            std::optional<core::CardID> card_id = std::nullopt,
            std::optional<core::PlayerID> player = std::nullopt)
            : card_id(card_id), player_id(player)
        {
        }

        explicit EffectContext(core::CardID card_id)
            : EffectContext(card_id, std::nullopt)
        {
        }

        explicit EffectContext(core::PlayerID player_id)
            : EffectContext(std::nullopt, player_id)
        {
        }

        explicit EffectContext(core::CardID card_id, core::PlayerID player_id)
            : card_id(card_id), player_id(player_id)
        {
        }

        explicit EffectContext(abilities::AbilityContext context)
            : card_id(context.source_card_id), player_id(context.controller_id),
              chosen_mode_index(context.chosen_mode_index),
              text_replacements(context.text_replacements)
        {
        }

        std::optional<core::CardID> card_id;
        std::optional<core::PlayerID> player_id;
        std::optional<size_t> chosen_mode_index;
        std::optional<std::vector<core::TextReplacement>> text_replacements;
        core::ExpireTime expires{core::ExpireTime::None};
    };
} // namespace dandan::effects

#endif