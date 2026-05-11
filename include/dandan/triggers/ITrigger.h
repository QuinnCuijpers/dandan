#ifndef TRIGGERS_H
#define TRIGGERS_H

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
            const events::IEvent &other) const = 0;
    };

} // namespace dandan::triggers

#endif