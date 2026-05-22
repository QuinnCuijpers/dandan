#ifndef DANDAN_ABILITYCONTEXT_H
#define DANDAN_ABILITYCONTEXT_H

#include "dandan/core/CardID.h"
#include <optional>
// #include "dandan/core/PlayerID.h"

namespace dandan::abilities
{
    /** Context for an ability's execution
     * @struct AbilityContext
     */
    struct AbilityContext
    {
        /** Constructor
         * @param source_card_id The CardID of the card that generated the
         * @param chosen_mode_index The index of the chosen mode for modal
         * ability
         */
        explicit AbilityContext(
            core::CardID source_card_id,
            std::optional<size_t> chosen_mode_index = std::nullopt)
            : source_card_id(source_card_id),
              chosen_mode_index(chosen_mode_index)
        {
        }

        /// The CardID of the card that generated the ability.
        core::CardID source_card_id;
        // core::PlayerID controller_id;
        std::optional<size_t> chosen_mode_index; // for modal abilities
    };
} // namespace dandan::abilities

#endif