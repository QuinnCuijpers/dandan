#ifndef IABILITYDECORATOR_H
#define IABILITYDECORATOR_H

#include "IAbility.h"
#include <memory>

class IAbilityDecorator : public IAbility
{
public:
    IAbilityDecorator(std::unique_ptr<IAbility> ability) : m_ability{std::move(ability)} {};
    virtual void resolve() = 0;

    virtual void from_json(const nlohmann::json &j, IAbility &ability) = 0;

    virtual void to_json(nlohmann::json &j, const IAbility &ability) = 0;

protected:
    std::unique_ptr<IAbility>
        m_ability;
};

#endif