#ifndef DANDAN_BOUNCELANDEFFECT_H
#define DANDAN_BOUNCELANDEFFECT_H

#include "IEffect.h"

namespace dandan::effects
{
    class BounceLandEffect : public IEffect
    {
    public:
        void apply() override;
    };
} // namespace dandan::effects

#endif // DANDAN_BOUNCELANDEFFECT_H