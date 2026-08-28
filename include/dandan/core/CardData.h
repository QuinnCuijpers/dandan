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
