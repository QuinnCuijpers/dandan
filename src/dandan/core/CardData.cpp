#include "dandan/core/CardData.h"
#include "dandan/core/CardTypes.h"
#include <cassert>
#include <memory>
#include <optional>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <utility>
#endif
namespace dandan::core
{
#ifdef DANDAN_SERIALIZE

    std::optional<CardData> getCardData(std::string_view name)
    {
        auto json_path{std::filesystem::path(DANDAN_PROJECT_SOURCE) /
                       "data/jsons" / (std::string(name) + ".json")};
        std::ifstream file{json_path};
        if (!file)
        {
            std::cerr << "Failed to open JSON file for card: " << name << '\n';
            return std::nullopt;
        }
        nlohmann::json json;
        file >> json;
        CardData card_data{json.get<core::CardData>()};
        return std::make_optional(std::move(card_data));
    }

    void from_json(const nlohmann::json &json, CardData &card)
    {
        card = std::move(*dandan::serialization::JsonFactory<
                         dandan::core::CardData>::create_product(json));
    }

    void to_json(nlohmann::json &json, const CardData &card)
    {
        json = dandan::serialization::JsonFactory<
            dandan::core::CardData>::create_json(&card);
    }
#endif

    std::ostream &operator<<(std::ostream &ostream,
                             const dandan::core::CardData &card)
    {
        ostream << "Card{name: " << card.name << ", cost: "
                << dandan::mana::ManaToSymbols(card.mana_cost->getMana())
                << ", type: " << TypeToString(card.type) << ", subtypes: ";
        for (auto type : card.subtypes)
        {
            ostream << SubTypeToString(type) << '}';
        }
        return ostream;
    }

} // namespace dandan::core
