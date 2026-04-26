#ifndef IREPLACEMENTEFFECT_H
#define IREPLACEMENTEFFECT_H

#include "../IContinuousEffect.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"

namespace dandan::effects
{
    class IReplacementEffect : public IContinuousEffect
    {
    public:
        [[nodiscard]] virtual bool appliesTo(
            const effects::IOneShotEffect &effect) const = 0;
        virtual effects::IOneShotEffect &replace(
            effects::IOneShotEffect &effect) = 0;
    };

} // namespace dandan::effects
#endif // IREPLACEMENTEFFECT_H