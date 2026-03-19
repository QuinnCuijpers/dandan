#ifndef IABILITYDECORATOR_H
#define IABILITYDECORATOR_H

#include "IAbility.h"
#include <memory>

class IAbilityDecorator : public IAbility
{
public:
    IAbilityDecorator(std::unique_ptr<IAbility> ability) : m_ability{std::move(ability)} {};
    virtual void resolve() = 0;

    void from_json(const nlohmann::json &j, IAbility &ability) override
    {
        auto &decorator = dynamic_cast<IAbilityDecorator &>(ability);
        decorator.m_ability->from_json(j, *decorator.m_ability);
    }

    void to_json(nlohmann::json &j, const IAbility &ability) override
    {
        const auto &decorator = dynamic_cast<const IAbilityDecorator &>(ability);
        decorator.m_ability->to_json(j, *decorator.m_ability);
    }

protected:
    std::unique_ptr<IAbility> m_ability;
};

class WithDamage : public IAbilityDecorator
{
public:
    WithDamage(std::unique_ptr<IAbility> ability, int damage) : IAbilityDecorator(std::move(ability)), m_damage{damage} {}
    void resolve() override;

private:
    int m_damage;
};

#endif