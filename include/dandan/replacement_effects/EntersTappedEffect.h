#ifndef DANDAN_ENTERSTAPPEDEFFECT_H
#define DANDAN_ENTERSTAPPEDEFFECT_H

#include "IReplacementEffect.h"
#include "dandan/effects/IEffect.h"

namespace dandan::replacement_effects
{
    struct EntersTappedEffect final : public IReplacementEffect
    {
        effects::IEffect &replace(dandan::effects::IEffect &effect) override;
    };
} // namespace dandan::replacement_effects

#endif