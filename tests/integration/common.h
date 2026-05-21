#ifndef DANDAN_INTEGRATION_TESTS_COMMON_H
#define DANDAN_INTEGRATION_TESTS_COMMON_H

#include "dandan/core/CardData.h"
#include "dandan/dandan.h"

inline dandan::core::Library createTestDeck(
    int amount_cards, dandan::core::CardData *cardData = nullptr)
{
    if (cardData == nullptr)
    {
        auto abilities{
            std::vector<std::unique_ptr<dandan::abilities::IAbility>>()};

        static dandan::core::CardData default_card_data{
            "Test Card", std::make_unique<dandan::mana::GenericMana>(0),
            dandan::core::CardData::Type::Land,
            dandan::core::CardData::SubType::Island, std::move(abilities)};

        cardData = &default_card_data;
    }

    auto cards = std::vector<dandan::Card>{};
    auto card_data = std::vector<dandan::core::CardData *>{};
    card_data.reserve(amount_cards);
    for (int i{}; i < amount_cards; ++i)
    {
        card_data.push_back(cardData);
        cards.emplace_back(card_data.back());
    };
    return dandan::core::Library{cards};
}

#endif