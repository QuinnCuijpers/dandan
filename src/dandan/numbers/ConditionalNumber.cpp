#include "dandan/numbers/ConditionalNumber.h"
#include "dandan/effects/EffectContext.h"

namespace dandan::numbers
{
    int ConditionalNumber::getValue(core::Game &game,
                                    effects::EffectContext context) const
    {
        if (m_condition->isSatisfied(game, context))
        {
            return m_if_number->getValue(game, context);
        }

        return m_else_number->getValue(game, context);
    }
} // namespace dandan::numbers