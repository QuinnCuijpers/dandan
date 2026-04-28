#ifndef CARD_H
#define CARD_H

#include "dandan/abilities/IAbility.h"
#include "dandan/mana/Mana.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#ifdef DANDAN_BUILD_SERIALIZE
#include <nlohmann/json.hpp>
#endif

namespace dandan::core
{

    struct Stats
    {
        int power{0};
        int toughness{1};
    };

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

        enum SubType : std::uint8_t
        {
            None,
            Forest,
            Island,
            Mountain,
            Plains,
            Swamp,
            Fish,
            MaxSubType
        };

        Card() = default;

#ifdef DANDAN_BUILD_SERIALIZE
        explicit Card(std::string_view name);
#endif

        Card(std::string_view name, std::unique_ptr<mana::Mana> cost, Type type,
             SubType subtype,
             std::vector<std::unique_ptr<abilities::IAbility>> abilities = {},
             std::optional<Stats> stats = std::nullopt)
            : m_name{name}, m_mana_cost{std::move(cost)}, m_type{type},
              m_subtype{subtype}, m_abilities{std::move(abilities)},
              m_stats{stats}
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
        [[nodiscard]] SubType getSubType() const
        {
            return m_subtype;
        }
        [[nodiscard]] const std::optional<Stats> &getStats() const
        {
            return m_stats;
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
                    << ", type: " << Card::TypeToString(card.m_type)
                    << ", subtype: " << Card::SubTypeToString(card.m_subtype)
                    << '}';
            return ostream;
        }

        static std::string_view TypeToString(Type type);
        static std::string_view SubTypeToString(SubType subtype);

#ifdef DANDAN_BUILD_SERIALIZE
        friend void from_json(const nlohmann::json &json, Card &card);
        friend void to_json(nlohmann::json &json, const Card &card);
#endif

    private:
        std::string m_name{"unknown"};
        std::unique_ptr<mana::Mana> m_mana_cost;
        Type m_type{Type::Land};
        SubType m_subtype{SubType::None};
        std::vector<std::unique_ptr<abilities::IAbility>> m_abilities;
        std::optional<Stats> m_stats;
    };
} // namespace dandan::core

#endif