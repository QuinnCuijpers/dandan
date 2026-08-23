#include "dandan/effects/one_shot/PeekEffect.h"
#include "dandan/core/Game.h"
#include <iostream>
#include <string>

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
        OneShotEffectRegistry::instance().registerType<PeekEffectDefinition>(
            "PeekEffect",
            []([[maybe_unused]] const IOneShotEffectDefinition *effect)
            {
                auto json = nlohmann::json::object();
                const auto *peek_effect =
                    dynamic_cast<const PeekEffectDefinition *>(effect);
                json["peek_amount"] = peek_effect->getPeekAmount();

                return json;
            },
            [](const nlohmann::json &data,
               [[maybe_unused]] const std::vector<TargetSpec> &target_specs,
               [[maybe_unused]] ExpireTime expiry)
            {
                return std::make_unique<PeekEffectDefinition>(
                    data.at("peek_amount").get<int>());
            });
        return true;
    }();
} // namespace
#endif

namespace dandan::effects
{

    void printPeekedCards(const std::vector<core::CardID> &cards,
                          const core::Game &game)
    {
        std::cout << "Peeked cards: [ ";
        for (size_t i{}; i < cards.size(); ++i)
        {
            const auto *cardp{game.getCardByID(cards[i])};
            std::cout << i << ": " << cardp->getData().name << ", ";
        }
        std::cout << " ]\n";
    }

    std::unique_ptr<events::IEvent> PeekEffect::apply_impl(
        [[maybe_unused]] core::Game &game) const
    {
        std::cout << "Applying PeekEffect: peeking at the top " << m_peek_amount
                  << " cards of the library\n";
        // moves cards out of deck
        auto cards{game.library().draw(m_peek_amount)};
        printPeekedCards(cards, game);

        std::cout << "Which card to put back on top next?\n";
        std::cout << " The last card chosen will be on top\n";

        for (int i{}; i < m_peek_amount; ++i)
        {
            printPeekedCards(cards, game);
            std::cout << "Choose card (0 - " << cards.size() - 1 << "): ";
            std::string choice{};
            std::getline(game.istream(), choice);
            int choice_int{std::stoi(choice)};
            if (choice_int < 0 || choice_int >= static_cast<int>(cards.size()))
            {
                std::cout << "Invalid choice. Please try again.\n";
                --i; // Retry the same iteration
            }
            else
            {
                auto chosen_card{cards[choice_int]};
                game.library().getCards().push_front(chosen_card);
                cards.erase(cards.begin() + choice_int);
            }
        }
        return nullptr;
    }

} // namespace dandan::effects
