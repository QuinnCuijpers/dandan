#ifndef WITHDAMAGE_H
#define WITHDAMAGE_H

#include "IAbilityDecorator.h"

class WithDamage : public IAbilityDecorator
{
public:
    WithDamage(std::unique_ptr<IAbility> ability, int damage) : IAbilityDecorator(std::move(ability)), m_damage{damage} {}
    void resolve() override;

    void to_json(nlohmann::json &j, const IAbility &ability) override;

    void from_json(const nlohmann::json &j, IAbility &ability) override;

private:
    int m_damage;
};

#endif