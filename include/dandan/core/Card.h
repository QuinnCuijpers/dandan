#ifndef CARD_H
#define CARD_H

#include "dandan/abilities/IAbility.h"

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#ifdef DANDAN_BUILD_SERIALIZE
#include <nlohmann/json_fwd.hpp>
#endif

namespace dandan::core
{

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

#ifdef DANDAN_BUILD_SERIALIZE
        explicit Card(std::string_view name);
#endif

        Card(std::string_view name, int cost, Type type,
             std::vector<std::unique_ptr<abilities::IAbility>> abilities = {})
            : m_name{name}, m_cost{cost}, m_type{type},
              m_abilities{std::move(abilities)}
        {
        }

        std::string_view getName() const
        {
            return m_name;
        }
        int getCost() const
        {
            return m_cost;
        }
        Type getType() const
        {
            return m_type;
        }
        const std::vector<std::unique_ptr<abilities::IAbility>> &getAbilities()
            const
        {
            return m_abilities;
        }

        friend std::ostream &operator<<(std::ostream &os, const Card &c)
        {
            os << "Card{name: " << c.m_name << ", cost: " << c.m_cost
               << ", type: " << c.TypeToString(c.m_type) << '}';
            return os;
        }

        static std::string_view TypeToString(Type type);

#ifdef DANDAN_BUILD_SERIALIZE
        friend void from_json(const nlohmann::json &j, Card &c);
        friend void to_json(nlohmann::json &j, const Card &c);
#endif

    private:
        std::string m_name{"unknown"};
        int m_cost{0};
        Type m_type{Type::Land};
        std::vector<std::unique_ptr<abilities::IAbility>> m_abilities;
    };
} // namespace dandan::core

#endif