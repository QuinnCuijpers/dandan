#ifndef DANDAN_CARD_DATA_H
#define DANDAN_CARD_DATA_H

#include "dandan/abilities/IAbility.h"
#include "dandan/mana/Mana.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#ifdef DANDAN_SERIALIZE
#include <nlohmann/json.hpp>
#endif

namespace dandan::core
{

    struct Stats
    {
        int power{0};
        int toughness{1};
    };

    class CardData
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
        };

        CardData() = default;

#ifdef DANDAN_SERIALIZE
        explicit CardData(std::string_view name);
#endif

        CardData(
            std::string_view name, std::unique_ptr<mana::Mana> cost, Type type,
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

        friend std::ostream &operator<<(std::ostream &ostream,
                                        const CardData &card)
        {
            ostream << "Card{name: " << card.m_name << ", cost: "
                    << dandan::mana::ManaToSymbols(card.m_mana_cost->getMana())
                    << ", type: " << CardData::TypeToString(card.m_type)
                    << ", subtype: "
                    << CardData::SubTypeToString(card.m_subtype) << '}';
            return ostream;
        }

        static std::string_view TypeToString(Type type);
        static std::string_view SubTypeToString(SubType subtype);

#ifdef DANDAN_SERIALIZE
        friend void from_json(const nlohmann::json &json, CardData &card);
        friend void to_json(nlohmann::json &json, const CardData &card);
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