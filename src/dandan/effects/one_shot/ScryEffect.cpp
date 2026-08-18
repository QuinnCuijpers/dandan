#include "dandan/effects/one_shot/ScryEffect.h"
#include "dandan/core/Game.h"

#ifdef DANDAN_SERIALIZE
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
        OneShotEffectRegistry::instance().registerType<ScryEffectDefinition>(
            "ScryEffect",
            []([[maybe_unused]] const IOneShotEffectDefinition *effect)
            {
                auto json = nlohmann::json::object();
                const auto *scry_effect =
                    dynamic_cast<const ScryEffectDefinition *>(effect);
                json["scry_amount"] = scry_effect->getScryAmount();

                return json;
            },
            [](const nlohmann::json &data,
               [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
               [[maybe_unused]] ExpireTime expiry)
            {
                return std::make_unique<ScryEffectDefinition>(
                    data.at("scry_amount").get<int>());
            });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{

    std::unique_ptr<events::IEvent> ScryEffect::apply_impl(
        [[maybe_unused]] core::Game &game) const
    {
        auto cards = game.library().draw(m_scry_amount);
        std::cout << "Scryed cards: [ ";
        for (const auto &card : cards)
        {
            auto *cardp{game.getCardByID(card)};
            std::cout << cardp->getData().name << " ,";
        }
        std::cout << " ]\n";

        while (!cards.empty())
        {
            // choose a card index if cards.size() > 1, otherwise just put the
            // card on top or bottom
            int card_index{-1};
            if (cards.size() > 1)
            {
                std::cout << "Choose a card index to scry (0 to "
                          << cards.size() - 1 << "): ";
                std::string input;
                std::getline(game.istream(), input);
                card_index = std::stoi(input);
                if (card_index < 0 ||
                    card_index >= static_cast<int>(cards.size()))
                {
                    std::cout << "Invalid card index";
                    continue;
                }
            }
            else
            {
                card_index = 0;
            }

            // ask to put on top or bottom
            std::cout << "Put card on top or bottom? (top/bottom) ";
            std::string input;
            std::getline(game.istream(), input);
            if (input == "top")
            {
                game.library().getCards().push_front(cards[card_index]);
                cards.erase(cards.begin() + card_index);
            }
            else if (input == "bottom")
            {
                game.library().getCards().push_back(cards[card_index]);
                cards.erase(cards.begin() + card_index);
            }
            else
            {
                std::cout << "Invalid input, please enter top or bottom\n";
                continue;
            }
        }
        return nullptr;
    }

} // namespace dandan::effects
