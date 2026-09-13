#ifndef DANDAN_CASTCONTEXT_H
#define DANDAN_CASTCONTEXT_H

#include "dandan/core/CardID.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/Zone.h"
#include "dandan/core/actions/PlayCardAction.h"
#include "dandan/mana/ManaPrice.h"

namespace dandan::core
{
    struct CastContext
    {
        CardID card_id;
        Zone zone = Zone::HAND;
        CastMode mode = CastMode::Normal;
        mana::ManaPrice cost;

        bool operator==(const core::CastContext &cast_ctx) const
        {
            return card_id == cast_ctx.card_id;
        }

        static CastContext resolveCast(const CastRequest &req,
                                       ExecutionContext exec_ctx);
    };

} // namespace dandan::core

#endif // !DANDAN_CASTCONTEXT_H
