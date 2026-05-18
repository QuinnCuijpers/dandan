#ifndef DANDAN_BOUNCELANDEFFECT_H
#define DANDAN_BOUNCELANDEFFECT_H

#include "IOneShotEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>

namespace dandan::effects
{
    class BounceLandEffect : public IOneShotEffect
    {
    public:
        std::unique_ptr<events::IEvent> apply(core::Game &game) const override;
    };
} // namespace dandan::effects

#endif // DANDAN_BOUNCELANDEFFECT_H