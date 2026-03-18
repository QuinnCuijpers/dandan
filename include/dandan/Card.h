#ifndef CARD_H
#define CARD_H

#include "IAbility.h"

#include <nlohmann/json.hpp>

#include <iostream>
#include <string>

class Card
{
public:
    enum Type
    {
        Land,
        Creature,
        Sorcery,
        Instant,
        Enchantment,
        Artifact,
        Planeswalker,
        MaxType
    };

    friend void from_json(const nlohmann::json &j, Card &c);
    friend void to_json(nlohmann::json &j, const Card &c);
    friend std::ostream &operator<<(std::ostream &os, const Card &c)
    {
        os << "Card{name: " << c.m_name << ", cost: " << c.m_cost << ", type: " << c.TypeToString(c.m_type) << '}';
        return os;
    }

private:
    std::string m_name{"unknown"};
    int m_cost{0};
    Type m_type{Type::Land};
    std::vector<IAbility *> m_abilities;

    std::string_view TypeToString(Type type) const;
};

#endif // CARD_H