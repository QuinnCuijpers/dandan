#ifndef DANDAN_ENTERSTAPPEDEFFECT_H
#define DANDAN_ENTERSTAPPEDEFFECT_H

#include "IReplacementEffect.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"

namespace dandan::effects
{
    /** @brief A replacement effect that causes a permanent to enter the battlefield
     * tapped. It listens to `ETBEvent`s and replaces the event with a modified
     * version that causes the permanent to enter tapped.
     * @class EntersTappedEffect
     *
     * @implements IReplacementEffect
     */
    struct EntersTappedEffect final : public IReplacementEffect
    {
        [[nodiscard]] bool appliesTo(
            const effects::IOneShotEffect &effect) const override;
        [[nodiscard]] effects::IOneShotEffect &replace(
            dandan::effects::IOneShotEffect &effect) const override;
    };
} // namespace dandan::effects

#endif
