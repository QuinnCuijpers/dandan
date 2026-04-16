#ifndef IABILITY_H
#define IABILITY_H

#include "dandan/events/IEvent.h"

namespace dandan::abilities
{
    class IAbility
    {
    public:
        virtual ~IAbility() = default;
        virtual void resolve() const = 0;

        virtual bool appliesToEvent(
            [[maybe_unused]] const events::IEvent &event) const
        {
            return false;
        }
    };
}; // namespace dandan::abilities

#endif