#ifndef DANDAN_ABILITYTYPE_H
#define DANDAN_ABILITYTYPE_H

#include "dandan/abilities/IAbility.h"
#include <cstdint>

namespace dandan::abilities
{
    class AbilityType
    {
    public:
        enum Type : uint8_t
        {
            Activated,
            BasicLand,
            EventTriggered,
            Mana,
            Spell,
            StateTriggered,
            StaticReplacement,
            StaticPrevention,
            StaticCharacteristicDefining,
            AbilityDecorator
        };

        explicit AbilityType(Type type) : m_type(type)
        {
        }

        [[nodiscard]] Type getType() const
        {
            return m_type;
        }

        static AbilityType from(const IAbility *ability);

    private:
        Type m_type;
    };
} // namespace dandan::abilities

#endif