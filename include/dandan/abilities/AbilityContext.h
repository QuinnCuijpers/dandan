#ifndef DANDAN_ABILITYCONTEXT_H
#define DANDAN_ABILITYCONTEXT_H

#include "dandan/core/CardID.h"
#include "dandan/core/PlayerID.h"
#include <optional>
// #include "dandan/core/PlayerID.h"

namespace dandan::abilities
{
    /** @brief Context for an ability's execution
     * @struct AbilityContext
     */
    struct AbilityContext
    {
        /** Constructor
         * @param source_card_id The CardID of the card that generated the
         * @param controller_id The PlayerID of the player who controls the
         * ability
         * @param chosen_mode_index The index of the chosen mode for modal
         * ability
         */
        AbilityContext(core::CardID source_card_id,
                       core::PlayerID controller_id,
                       std::optional<size_t> chosen_mode_index = std::nullopt)
            : source_card_id(source_card_id), controller_id(controller_id),
              chosen_mode_index(chosen_mode_index)
        {
        }

        /// The CardID of the card that generated the ability.
        core::CardID source_card_id;
        /// The PlayerID of the player who controls the source of the ability.
        /// generally this is also the player who controls the ability
        core::PlayerID controller_id;
        /// for modal abilities this represents the index of the chosen mode
        std::optional<size_t> chosen_mode_index;
    };
} // namespace dandan::abilities

#endif
