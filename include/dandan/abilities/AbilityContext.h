#ifndef DANDAN_ABILITYCONTEXT_H
#define DANDAN_ABILITYCONTEXT_H

#include "dandan/core/CardID.h"
// #include "dandan/core/PlayerID.h"

namespace dandan::abilities
{
    struct AbilityContext
    {
        explicit AbilityContext(core::CardID source_card_id)
            : source_card_id(source_card_id)
        {
        }

        core::CardID source_card_id;
        // core::PlayerID controller_id;
    };
} // namespace dandan::abilities

#endif