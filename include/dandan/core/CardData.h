#ifndef DANDAN_CARD_DATA_H
#define DANDAN_CARD_DATA_H

#include "dandan/core/CardTypes.h"
#include "dandan/core/ColorWord.h"
#include "dandan/mana/ManaPrice.h"

#include <iostream>
#include <memory>
#include <optional>
#include <string>

#ifdef DANDAN_SERIALIZE
#include <nlohmann/json_fwd.hpp>
#include <string_view>
#endif

namespace dandan::abilities
{
    class IAbility;
}

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
    struct CardData
    {
        std::string name{"unknown"};
        mana::ManaPrice mana_cost;
        Type type{Type::Land};
        std::vector<SubType> subtypes;
        SuperType supertype{SuperType::None};
        std::vector<std::unique_ptr<abilities::IAbility>> abilities;
        std::optional<Stats> stats;
        ColorWord color{ColorWord::Colorless};
    };

    /** Outputs the card data to an output stream.
     * @param ostream The output stream.
     * @param card The card data to output.
     * @return The output stream.
     */
    std::ostream &operator<<(std::ostream &ostream,
                             const dandan::core::CardData &card);

#ifdef DANDAN_SERIALIZE
    std::optional<CardData> getCardData(std::string_view name);
    void from_json(const nlohmann::json &json, CardData &card);
    void to_json(nlohmann::json &json, const CardData &card);
#endif

} // namespace dandan::core

#endif
