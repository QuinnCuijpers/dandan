#ifndef CARD_H
#define CARD_H

#include "dandan/abilities/IAbility.h"
#include "dandan/mana/Mana.h"

#include <cstdint>
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
        enum Type : std::uint8_t
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

        Card(std::string_view name, std::unique_ptr<mana::Mana> cost, Type type,
             std::vector<std::unique_ptr<abilities::IAbility>> abilities = {})
            : m_name{name}, m_mana_cost{std::move(cost)}, m_type{type},
              m_abilities{std::move(abilities)}
        {
        }

        [[nodiscard]] std::string_view getName() const
        {
            return m_name;
        }
        [[nodiscard]] const mana::Mana *getCost() const
        {
            return m_mana_cost.get();
        }
        [[nodiscard]] Type getType() const
        {
            return m_type;
        }
        [[nodiscard]] const std::vector<std::unique_ptr<abilities::IAbility>> &
        getAbilities() const
        {
            return m_abilities;
        }

        void play() const
        {
            std::cout << "Playing card: " << m_name << '\n';
            for (const auto &ability : m_abilities)
            {
                ability->resolve();
            }
        }

        friend std::ostream &operator<<(std::ostream &ostream, const Card &card)
        {
            ostream << "Card{name: " << card.m_name << ", cost: "
                    << dandan::mana::ManaToSymbols(card.m_mana_cost->getMana())
                    << ", type: " << Card::TypeToString(card.m_type) << '}';
            return ostream;
        }

        static std::string_view TypeToString(Type type);

#ifdef DANDAN_BUILD_SERIALIZE
        friend void from_json(const nlohmann::json &json, Card &card);
        friend void to_json(nlohmann::json &json, const Card &card);
#endif

    private:
        std::string m_name{"unknown"};
        std::unique_ptr<mana::Mana> m_mana_cost;
        Type m_type{Type::Land};
        std::vector<std::unique_ptr<abilities::IAbility>> m_abilities;
    };
} // namespace dandan::core

#endif