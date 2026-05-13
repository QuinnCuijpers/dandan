#ifndef DANDAN_NOISLANDSTRIGGER_H
#define DANDAN_NOISLANDSTRIGGER_H

#include "dandan/events/NoIslandsEvent.h"
#include "dandan/triggers/ITrigger.h"

namespace dandan::triggers
{
    class NoIslandsTrigger : public ITrigger
    {
    public:
        NoIslandsTrigger() = default;

        [[nodiscard]] bool triggersOn(
            const events::IEvent &other,
            [[maybe_unused]] abilities::AbilityContext context) const override
        {
            const auto *noIslandsEvent =
                dynamic_cast<const events::NoIslandsEvent *>(&other);
            return noIslandsEvent != nullptr;
        }
    };
} // namespace dandan::triggers

#endif