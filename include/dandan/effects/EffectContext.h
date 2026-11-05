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
            core::CardID card_id = core::CardID::getInvalidID(),
            core::PlayerID player = core::PlayerID::getInvalidID());

        explicit EffectContext(core::PlayerID player_id);

        explicit EffectContext(const abilities::AbilityContext &context);

        core::CardID card_id;
        core::PlayerID player_id;
        std::optional<size_t> chosen_mode_index;
        std::optional<std::vector<core::TextReplacement>> text_replacements;
        core::ExpireTime expires{core::ExpireTime::None};
    };
} // namespace dandan::effects

#endif
