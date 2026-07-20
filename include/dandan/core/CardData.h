#ifndef DANDAN_CARD_DATA_H
#define DANDAN_CARD_DATA_H

#include "dandan/abilities/IAbility.h"
#include "dandan/core/ColorWord.h"
#include "dandan/core/SubType.h"
#include "dandan/mana/Mana.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

#ifdef DANDAN_SERIALIZE
#include <nlohmann/json.hpp>
#endif

namespace dandan::core
{

    /** @brief A struct to hold the stats (power and toughness) of a creature
     * card.
     * @struct Stats
     */
    struct Stats
    {
        /// The power of the creature. Defaults to 0.
        int power{0};
        /// The toughness of the creature, defaults to 1 as creatures with 0
        /// toughness are immediately put into the graveyard.
        int toughness{1};
    };

    /** @brief A class to hold the static data for a card.
     * @class CardData
     */
    class CardData
    {
    public:
        /** The type of the card. For now every card has exactly one type.
         * @enum Type
         */
        enum class Type : std::uint8_t
        {
            /// A land card
            Land,
            /// A creature card
            Creature,
            /// A sorcery card
            Sorcery,
            /// An instant card
            Instant,
            /// An enchantment card
            Enchantment,
            /// An artifact card
            Artifact,
            /// A planeswalker card
            Planeswalker,
        };

        // TODO: expand supertypes
        enum class SuperType : std::uint8_t
        {
            None,
            Basic,
        };

        CardData() = default;

#ifdef DANDAN_SERIALIZE
        explicit CardData(std::string_view name);
#endif

        /** Constructor for creating a custom CardData instance.
         * @param name The name of the card.
         * @param cost The mana cost of the card.
         * @param type The type of the card.
         * @param subtypes The subtypes of the card.
         * @param abilities The abilities of the card.
         * @param stats The optional stats of the card, should be set when the
         * card is a creature.
         */
        CardData(
            std::string_view name, std::unique_ptr<mana::Mana> cost, Type type,
            std::vector<SubType> subtypes = {SubType::None},
            SuperType supertype = SuperType::None,
            std::vector<std::unique_ptr<abilities::IAbility>> abilities = {},
            std::optional<Stats> stats = std::nullopt,
            ColorWord color = ColorWord::Colorless);

        /** Constructor for creating a custom CardData instance.
         * @param name The name of the card.
         * @param cost The mana cost of the card.
         * @param type The type of the card.
         * @param subtype The subtype of the card.
         * @param abilities The abilities of the card.
         * @param stats The optional stats of the card, should be set when the
         * card is a creature.
         */
        CardData(
            std::string_view name, std::unique_ptr<mana::Mana> cost, Type type,
            SubType subtype = SubType::None,
            SuperType supertype = SuperType::None,
            std::vector<std::unique_ptr<abilities::IAbility>> abilities = {},
            std::optional<Stats> stats = std::nullopt,
            ColorWord color = ColorWord::Colorless);

        /** Gets the name of the card.
         * @return The name of the card.
         */
        [[nodiscard]] const std::string &getName() const
        {
            return m_name;
        }
        /** Gets the mana cost of the card.
         * @return The mana cost of the card.
         */
        [[nodiscard]] const mana::Mana *getCost() const
        {
            return m_mana_cost.get();
        }
        /** Gets the type of the card.
         * @return The type of the card.
         */
        [[nodiscard]] Type getType() const
        {
            return m_type;
        }
        /** Gets the subtype of the card.
         * @return The subtype of the card.
         */
        [[nodiscard]] const std::vector<SubType> &getSubTypes() const
        {
            return m_subtypes;
        }

        [[nodiscard]] SuperType getSuperType() const
        {
            return m_supertype;
        }

        /** Gets the stats of the card.
         * @return The stats of the card, if any.
         */
        [[nodiscard]] const std::optional<Stats> &getStats() const
        {
            return m_stats;
        }

        /** Gets the abilities of the card.
         * @return A const reference to the abilities of the card.
         */
        [[nodiscard]] const std::vector<std::unique_ptr<abilities::IAbility>> &
        getAbilities() const
        {
            return m_abilities;
        }

        [[nodiscard]] ColorWord getColor() const
        {
            return m_color;
        }

        /** Outputs the card data to an output stream.
         * @param ostream The output stream.
         * @param card The card data to output.
         * @return The output stream.
         */
        friend std::ostream &operator<<(std::ostream &ostream,
                                        const CardData &card)
        {
            ostream << "Card{name: " << card.m_name << ", cost: "
                    << dandan::mana::ManaToSymbols(card.m_mana_cost->getMana())
                    << ", type: " << CardData::TypeToString(card.m_type)
                    << ", subtypes: ";
            for (auto type : card.m_subtypes)
            {
                ostream << CardData::SubTypeToString(type) << '}';
            }
            return ostream;
        }

        /** Converts a card type to a string.
         * @param type The card type.
         * @return The string representation of the card type.
         */
        static std::string_view TypeToString(Type type);

        /** Converts a card subtype to a string.
         * @param subtype The card subtype.
         * @return The string representation of the card subtype.
         */
        static std::string_view SubTypeToString(SubType subtype);

#ifdef DANDAN_SERIALIZE
        friend void from_json(const nlohmann::json &json, CardData &card);
        friend void to_json(nlohmann::json &json, const CardData &card);
#endif

        friend class CardDataFactory;

    private:
        std::string m_name{"unknown"};
        std::unique_ptr<mana::Mana> m_mana_cost;
        ColorWord m_color{ColorWord::Colorless};
        Type m_type{Type::Land};
        std::vector<SubType> m_subtypes;
        SuperType m_supertype{SuperType::None};
        std::vector<std::unique_ptr<abilities::IAbility>> m_abilities;
        std::optional<Stats> m_stats;

        void addAbility(std::unique_ptr<abilities::IAbility> ability);
    };
} // namespace dandan::core

#endif
