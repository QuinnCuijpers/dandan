#ifndef IREPLACEMENTEFFECT_H
#define IREPLACEMENTEFFECT_H

#include "../IContinuousEffect.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"

namespace dandan::effects
{
    /** The interface class for replacement effects.
     * @class IReplacementEffect
     * @implements IContinuousEffect
     */
    class IReplacementEffect : public IContinuousEffect
    {
    public:
        /** Determines if this replacement effect applies to the given one-shot
         * effect.
         * @param effect The one-shot effect to check.
         * @return True if the replacement effect applies, false otherwise.
         */
        [[nodiscard]] virtual bool appliesTo(
            const effects::IOneShotEffect &effect) const = 0;

        /** Replaces the given one-shot effect with a modified version.
         * @param effect The one-shot effect to replace.
         * @return A reference to the replaced effect.
         */
        [[nodiscard]] virtual effects::IOneShotEffect &replace(
            effects::IOneShotEffect &effect) const = 0;
    };

} // namespace dandan::effects
#endif // IREPLACEMENTEFFECT_H