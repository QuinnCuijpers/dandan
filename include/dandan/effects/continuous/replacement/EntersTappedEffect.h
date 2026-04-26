#ifndef DANDAN_ENTERSTAPPEDEFFECT_H
#define DANDAN_ENTERSTAPPEDEFFECT_H

#include "IReplacementEffect.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"

namespace dandan::effects
{
    struct EntersTappedEffect final : public IReplacementEffect
    {
        [[nodiscard]] bool appliesTo(
            const effects::IOneShotEffect &effect) const override;
        effects::IOneShotEffect &replace(
            dandan::effects::IOneShotEffect &effect) override;
    };
} // namespace dandan::effects

#endif