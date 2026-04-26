#ifndef DANDAN_BOUNCELANDEFFECT_H
#define DANDAN_BOUNCELANDEFFECT_H

#include "IOneShotEffect.h"

namespace dandan::effects
{
    class BounceLandEffect : public IOneShotEffect
    {
    public:
        void apply() override;
    };
} // namespace dandan::effects

#endif // DANDAN_BOUNCELANDEFFECT_H