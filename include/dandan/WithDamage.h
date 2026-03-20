#ifndef WITHDAMAGE_H
#define WITHDAMAGE_H

#include "IAbilityDecorator.h"

class WithDamage : public IAbilityDecorator
{
public:
    WithDamage(std::unique_ptr<IAbility> ability, int damage) : IAbilityDecorator(std::move(ability)), m_damage{damage} {}
    void resolve() override;

    void to_json(nlohmann::json &j, const IAbility &ability) override;

    void from_json(const nlohmann::json &j, IAbility &ability) override {
        // auto &decorator{dynamic_cast<WithDamage &>(ability)};
        // decorator.m_damage = j.at("WithDamage").at("damage").get<int>();
        // decorator.m_ability = std::make_unique<ManaAbility>();
        // decorator.m_ability->from_json(j.at("WithDamage").at("ability"), *decorator.m_ability);
    };

private:
    int m_damage;
};

#endif