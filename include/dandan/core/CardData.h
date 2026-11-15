#ifndef DANDAN_CARD_DATA_H
#define DANDAN_CARD_DATA_H

#include "dandan/abilities/IAbility.h"
#include "dandan/core/CardTypes.h"
#include "dandan/core/ColorWord.h"
#include "dandan/core/Stats.h"
#include "dandan/mana/ManaPrice.h"
#include <iostream>
#include <optional>
#include <string>

#ifdef DANDAN_SERIALIZE
#include <nlohmann/json_fwd.hpp>
#include <string_view>
#endif

namespace dandan::core
{

    /** @brief A class to hold the static data for a card.
     * @struct CardData
     */
    struct CardData
    {
        /// The printed name of the card.
        std::string name{"unknown"};
        /// The mana cost required to cast the card.
        mana::ManaPrice mana_cost;
        /// The card's primary type.
        Type type{Type::Land};
        /// The card's subtypes.
        std::vector<SubType> subtypes;
        /// The card's supertype.
        SuperType supertype{SuperType::None};
        /// The abilities printed on the card.
        std::vector<std::unique_ptr<abilities::IAbility>> abilities;
        /// The printed power and toughness, if the card has them.
        std::optional<Stats> stats;
        /// The color of the card.
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
