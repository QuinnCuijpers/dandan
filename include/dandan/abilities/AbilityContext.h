#ifndef DANDAN_ABILITYCONTEXT_H
#define DANDAN_ABILITYCONTEXT_H

#include "dandan/core/CardID.h"
#include "dandan/core/PlayerID.h"
#include "dandan/core/TextReplacement.h"
#include <optional>
#include <vector>
// #include "dandan/core/PlayerID.h"

namespace dandan::abilities
{
    /** @brief Context for an ability's execution
     * @struct AbilityContext
     */
    struct AbilityContext
    {

        /// The CardID of the card that generated the ability.
        core::CardID source_card_id;
        /// The PlayerID of the player who controls the source of the ability.
        /// generally this is also the player who controls the ability
        core::PlayerID controller_id;
        /// for modal abilities this represents the index of the chosen mode
        std::optional<size_t> chosen_mode_index = std::nullopt;
        /// Optional text replacements
        std::optional<std::vector<core::TextReplacement>> text_replacements =
            std::nullopt;
    };
} // namespace dandan::abilities

#endif
