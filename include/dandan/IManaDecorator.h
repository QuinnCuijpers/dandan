#ifndef MANADECORATOR_H
#define MANADECORATOR_H

#include "ManaAbility.h"
#include <memory>

class IManaDecorator : public ManaAbility
{
public:
    IManaDecorator(std::unique_ptr<ManaAbility> ability) : m_ability{std::move(ability)} {};
    virtual void resolve() = 0;

protected:
    std::unique_ptr<ManaAbility> m_ability;
};

class WithDamage : public IManaDecorator
{
public:
    WithDamage(std::unique_ptr<ManaAbility> ability, int damage) : IManaDecorator(std::move(ability)), m_damage{damage} {}
    void resolve() override;

private:
    int m_damage;
};

#endif