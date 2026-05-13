#ifndef TRIGGERS_H
#define TRIGGERS_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/events/IEvent.h"

namespace dandan::triggers
{
    class ITrigger
    {
    public:
        ITrigger() = default;
        ITrigger(const ITrigger &) = delete;
        ITrigger(ITrigger &&) = delete;
        ITrigger &operator=(const ITrigger &) = delete;
        ITrigger &operator=(ITrigger &&) = delete;
        virtual ~ITrigger() = default;
        [[nodiscard]] virtual bool triggersOn(
            const events::IEvent &other,
            abilities::AbilityContext context) const = 0;
    };

} // namespace dandan::triggers

#endif