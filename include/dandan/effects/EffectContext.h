#ifndef DANDAN_EFFECTCONTEXT_H
#define DANDAN_EFFECTCONTEXT_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Expire.h"
#include "dandan/core/PlayerID.h"
#include <optional>

namespace dandan::effects
{
    /** @brief Contextual data associated with an effect.
     * @struct EffectContext
     */
    struct EffectContext
    {
        /** @brief Construct a context from a source card and/or player.
         * @param card_id The ID of the source card.
         * @param player The ID of the controlling player.
         */
        explicit EffectContext(
            core::CardID card_id = core::CardID::getInvalidID(),
            core::PlayerID player = core::PlayerID::getInvalidID());

        /** @brief Construct a context for a player.
         * @param player_id The ID of the controlling player.
         */
        explicit EffectContext(core::PlayerID player_id);

        /** @brief Construct a context from an ability context.
         * @param context The ability context to copy effect data from.
         */
        explicit EffectContext(const abilities::AbilityContext &context);

        /// The ID of the source card.
        core::CardID card_id;
        /// The ID of the controlling player.
        core::PlayerID player_id;
        /// The index of the chosen mode, if the effect is modal.
        std::optional<size_t> chosen_mode_index;
        /// Text replacements to apply when displaying the effect, if any.
        std::optional<std::vector<core::TextReplacement>> text_replacements;
        /// The time at which the effect expires.
        core::ExpireTime expires{core::ExpireTime::None};
    };
} // namespace dandan::effects

#endif
