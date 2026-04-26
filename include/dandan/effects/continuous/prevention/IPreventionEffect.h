#ifndef DANDAN_IPREVENTION_EFFECT_H
#define DANDAN_IPREVENTION_EFFECT_H

#include "../IContinuousEffect.h"

namespace dandan::effects
{
    class IPreventionEffect : public IContinuousEffect
    {
    public:
        IPreventionEffect() = default;

        virtual void check() = 0;
    };

} // namespace dandan::effects

#endif // DANDAN_IPREVENTION_EFFECT_H