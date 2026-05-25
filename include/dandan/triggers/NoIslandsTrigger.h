#ifndef DANDAN_NOISLANDSTRIGGER_H
#define DANDAN_NOISLANDSTRIGGER_H

#include "ITrigger.h"
#include "dandan/events/NoIslandsEvent.h"

namespace dandan::triggers
{
    /** A trigger that activates when no islands are present.
     * @class NoIslandsTrigger
     */
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