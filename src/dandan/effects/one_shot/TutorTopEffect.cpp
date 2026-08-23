#include "dandan/effects/one_shot/TutorTopEffect.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Game.h"
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace
{

    using namespace dandan::serialization;
    using namespace dandan::effects;
    using namespace dandan::abilities;
    using namespace dandan::core;
    using namespace dandan::numbers;

    const auto registered = []
    {
        OneShotEffectRegistry::instance()
            .registerType<TutorTopEffectDefinition>(
                "TutorTopEffect",
                []([[maybe_unused]] const IOneShotEffectDefinition *effect)
                {
                    auto json = nlohmann::json::object();
                    const auto *tutor =
                        dynamic_cast<const TutorTopEffectDefinition *>(effect);
                    json["filter_types"] = nlohmann::json::array();
                    for (auto type : tutor->getFilterTypes())
                    {
                        json["filter_types"].push_back(type);
                    }
                    return json;
                },
                [](const nlohmann::json &data,
                   [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
                   [[maybe_unused]] ExpireTime expiry)
                {
                    std::vector<Type> filter_types;
                    std::transform(data.at("filter_types").begin(),
                                   data.at("filter_types").end(),
                                   std::back_inserter(filter_types),
                                   [](const auto &type_json)
                                   { return type_json.template get<Type>(); });

                    return std::make_unique<TutorTopEffectDefinition>(
                        std::move(filter_types));
                });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> TutorTopEffect::apply_impl(
        core::Game &game) const
    {
        // get all cards matching the filter types
        auto included = [&game](const core::CardID &card_id,
                                const std::vector<core::Type> &filter_types)
        {
            return std::any_of(filter_types.begin(), filter_types.end(),
                               [&card_id, &game](const auto &type)
                               {
                                   const auto *card = game.getCardByID(card_id);
                                   return card->getData().type == type;
                               });
        };

        std::vector<core::CardID> options{};

        std::copy_if(game.library().getCards().begin(),
                     game.library().getCards().end(),
                     std::back_inserter(options), [&](const auto &card)
                     { return included(card, m_filter_types); });

        // ask player which cardid they want
        game.printCards(options);
        std::cout << "Choose a card to put on top of your library: ";
        std::string input;
        std::getline(game.istream(), input);
        int chosen_card_id = std::stoi(input);

        // remove card from lib and shuffle
        const auto *card = game.getCardByID(chosen_card_id);
        game.moveCardFromZone(game.activePlayer(), *card);
        game.library().shuffle();

        // move that card to the top of the library
        game.library().getCards().push_front(
            core::CardID::fromInt(chosen_card_id));

        return nullptr;
    }
} // namespace dandan::effects
