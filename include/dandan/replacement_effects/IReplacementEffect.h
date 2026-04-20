#ifndef IREPLACEMENTEFFECT_H
#define IREPLACEMENTEFFECT_H

#include "dandan/effects/IEffect.h"

namespace dandan::replacement_effects
{
    class IReplacementEffect
    {
    public:
        IReplacementEffect() = default;
        IReplacementEffect(const IReplacementEffect &) = default;
        IReplacementEffect(IReplacementEffect &&) = delete;
        IReplacementEffect &operator=(const IReplacementEffect &) = default;
        IReplacementEffect &operator=(IReplacementEffect &&) = delete;
        virtual effects::IEffect &replace(effects::IEffect &effect) = 0;
        virtual ~IReplacementEffect() = default;
    };

} // namespace dandan::replacement_effects
#endif