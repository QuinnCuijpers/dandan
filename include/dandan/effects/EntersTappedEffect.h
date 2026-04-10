#ifndef DANDAN_ENTERSTAPPEDEFFECT_H
#define DANDAN_ENTERSTAPPEDEFFECT_H

#include "IReplacementEffect.h"
#include "dandan/events/IEvent.h"

namespace dandan::effects
{
    struct EntersTappedEffect final : public IReplacementEffect
    {
        std::unique_ptr<dandan::events::IEvent> replace(
            dandan::events::IEvent &event) override;
    };
} // namespace dandan::effects

#endif