#ifndef IABILITYDECORATOR_H
#define IABILITYDECORATOR_H

#include "IAbility.h"
#include <memory>

namespace dandan::abilities
{
    class IAbilityDecorator : public IAbility
    {
    public:
        IAbilityDecorator(std::unique_ptr<IAbility> ability)
            : m_ability{std::move(ability)} {};
        virtual void resolve() = 0;

    protected:
        std::unique_ptr<IAbility> m_ability;
    };
} // namespace dandan::abilities

#endif