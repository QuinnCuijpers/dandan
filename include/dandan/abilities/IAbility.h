#ifndef IABILITY_H
#define IABILITY_H

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

        virtual void resolve(core::Game &game) const = 0;

        [[nodiscard]] virtual bool appliesToEvent(
            [[maybe_unused]] const events::IEvent &event) const
        {
            return false;
        }
    };
}; // namespace dandan::abilities

#endif