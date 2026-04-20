#ifndef IABILITYDECORATOR_H
#define IABILITYDECORATOR_H

#include "IAbility.h"
#include <memory>

namespace dandan::abilities
{
    struct IAbilityDecorator : public IAbility
    {
    public:
        std::unique_ptr<IAbility> m_ability;

        explicit IAbilityDecorator(std::unique_ptr<IAbility> ability)
            : m_ability{std::move(ability)} {};

        [[nodiscard]] const IAbility *getInnerAbility() const
        {
            return m_ability.get();
        }
    };
} // namespace dandan::abilities

#endif