#ifndef IABILITY_H
#define IABILITY_H

#include "dandan/abilities/AbilityContext.h"

namespace dandan::core
{
    class Game;
}

namespace dandan::events
{
    class IEvent;
}

namespace dandan::abilities
{
    class IAbility
    {
    public:
        IAbility() = default;
        IAbility(const IAbility &) = delete;
        IAbility(IAbility &&) = delete;
        IAbility &operator=(const IAbility &) = delete;
        IAbility &operator=(IAbility &&) = delete;
        virtual ~IAbility() = default;

        virtual void resolve(core::Game &game,
                             AbilityContext context) const = 0;

        [[nodiscard]] virtual bool appliesTo(
            [[maybe_unused]] const events::IEvent &event,
            [[maybe_unused]] abilities::AbilityContext context) const
        {
            return false;
        }
    };
}; // namespace dandan::abilities

#endif