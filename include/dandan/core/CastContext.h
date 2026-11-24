#ifndef DANDAN_CASTCONTEXT_H
#define DANDAN_CASTCONTEXT_H

#include "dandan/core/CardID.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/Zone.h"
#include "dandan/core/actions/PlayCardAction.h"
#include "dandan/mana/ManaPrice.h"

namespace dandan::core
{
    /** @brief The resolved information needed to cast a card.
     * @struct CastContext
     */
    struct CastContext
    {
        /// The ID of the card being cast.
        CardID card_id;
        /// The zone the card is cast from.
        Zone zone = Zone::HAND;
        /// The mode used to cast the card.
        CastMode mode = CastMode::Normal;
        /// The mana cost that must be paid.
        mana::ManaPrice cost;

        /** Compares two cast contexts for equality.
         * @param cast_ctx The context to compare with.
         * @return True if all fields are equal, false otherwise.
         */
        bool operator==(const core::CastContext &cast_ctx) const;

        /** Resolves a cast request into a concrete cast context.
         * @param req The cast request to resolve.
         * @param exec_ctx The execution context.
         * @return The resolved cast context.
         */
        static CastContext resolveCast(const CastRequest &req,
                                       ExecutionContext exec_ctx);
    };

} // namespace dandan::core

#endif // !DANDAN_CASTCONTEXT_H
