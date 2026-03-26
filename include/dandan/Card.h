#ifndef CARD_H
#define CARD_H

#include "IAbility.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <memory>

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

    Card() = default;
    Card(std::string_view name, int cost, Type type, std::vector<std::unique_ptr<IAbility>> abilities = {})
        : m_name{name}, m_cost{cost}, m_type{type}, m_abilities{std::move(abilities)} {}

    std::string_view get_name() const { return m_name; }
    int get_cost() const { return m_cost; }
    Type get_type() const { return m_type; }
    const std::vector<std::unique_ptr<IAbility>> &get_abilities() const { return m_abilities; }

    friend void from_json(const nlohmann::json &j, Card &c);
    friend void to_json(nlohmann::json &j, const Card &c);

    friend std::ostream &operator<<(std::ostream &os, const Card &c)
    {
        os << "Card{name: " << c.m_name << ", cost: " << c.m_cost << ", type: " << c.TypeToString(c.m_type) << '}';
        return os;
    }

    std::string_view TypeToString(Type type) const;

private:
    std::string m_name{"unknown"};
    int m_cost{0};
    Type m_type{Type::Land};
    std::vector<std::unique_ptr<IAbility>> m_abilities;
};

#endif // CARD_H