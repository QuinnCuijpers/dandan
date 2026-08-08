#include "dandan/numbers/GraveyardCount.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <string>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonRegisterMacros.h"
#include <nlohmann/json.hpp>
namespace
{
    using namespace dandan::numbers;
    using namespace dandan::serialization;

    DANDAN_JSONREGISTER_NUMBER(
        GraveyardCount, "GraveyardCount",
        [](const INumber *number)
        {
            auto json = nlohmann::json::object();
            const auto *graveyard_count{
                dynamic_cast<const GraveyardCount *>(number)};
            json["card_name"] = graveyard_count->getName();
            return json;
        },
        [](const nlohmann::json &json)
        {
            std::string name = json.at("card_name").get<std::string>();
            return std::make_unique<GraveyardCount>(name);
        },
        JsonRepresentation::TAGGED);
} // namespace
#endif

namespace dandan::numbers
{
    GraveyardCount::GraveyardCount(std::string name) : m_name(std::move(name))
    {
    }

    [[nodiscard]] const std::string &GraveyardCount::getName() const
    {
        return m_name;
    }

    [[nodiscard]] int GraveyardCount::getValue(
        core::Game &game, [[maybe_unused]] effects::EffectContext context) const
    {
        auto count{std::count_if(game.graveyard().getCards().begin(),
                                 game.graveyard().getCards().end(),
                                 [this, &game](const auto &card_id)
                                 {
                                     auto card{game.getCardByID(card_id)};
                                     return card->getData().name == m_name;
                                 })};
        return static_cast<int>(count);
    }

    [[nodiscard]] std::unique_ptr<INumber> GraveyardCount::clone() const
    {
        return std::make_unique<GraveyardCount>(m_name);
    }

} // namespace dandan::numbers
