#ifndef DANDAN_ABILITYCONTEXT_H
#define DANDAN_ABILITYCONTEXT_H

#include "dandan/core/CardID.h"
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
         * ability
         */
        explicit AbilityContext(core::CardID source_card_id)
            : source_card_id(source_card_id)
        {
        }

        /// The CardID of the card that generated the ability.
        core::CardID source_card_id;
        // core::PlayerID controller_id;
    };
} // namespace dandan::abilities

#endif