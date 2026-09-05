#include "DeserializeTest.h"
#include "common/SpellDefinitions.h"
#include "common/common.h"
#include "dandan/dandan.h"
#include <algorithm>
#include <array>
#include <gtest/gtest.h>
#include <iterator>
#include <memory>
#include <vector>

static const std::array<std::string, 12> card_names{
    "Brainstorm",     "Accumulated_Knowledge", "Diminishing_Returns",
    "Mystical_Tutor", "Vision_Charm",          "Crystal_Spray",
    "Mind_Bend",      "Unsubstantiate",        "Memory_Lapse",
    "Predict",        "Dance_of_the_Skywise",  "Metamorphose"};

static std::vector<dandan::Card> getCards()
{
    auto cards = std::vector<dandan::Card>{};

    static auto card_data = []
    {
        std::vector<std::unique_ptr<dandan::CardData>> card_data;

        card_data.push_back(create_spell_data(
            "Brainstorm",
            dandan::mana::ManaPrice{
                dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}},
            dandan::core::Type::Instant, Brainstorm_Abilities()));

        card_data.push_back(create_spell_data(
            "Accumulated Knowledge",
            dandan::mana::ManaPrice{
                dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}, 1},
            dandan::core::Type::Instant, Accumulated_Knowledge_Abilities()));

        card_data.push_back(create_spell_data(
            "Diminishing Returns",
            dandan::mana::ManaPrice{
                dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 2}}, 2},
            dandan::core::Type::Sorcery, Diminishing_Returns_Abilities()));

        card_data.push_back(create_spell_data(
            "Mystical Tutor",
            dandan::mana::ManaPrice{
                dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}},
            dandan::core::Type::Instant, Mystical_Tutor_Abilities()));

        card_data.push_back(create_spell_data(
            "Vision Charm",
            dandan::mana::ManaPrice{
                dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}},
            dandan::core::Type::Instant, Vision_Charm_Abilities()));

        card_data.push_back(create_spell_data(
            "Crystal Spray",
            dandan::mana::ManaPrice{
                dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}, 2},
            dandan::core::Type::Instant, Crystal_Spray_Abilities()));

        card_data.push_back(create_spell_data(
            "Mind Bend",
            dandan::mana::ManaPrice{
                dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}},
            dandan::core::Type::Instant, Mind_Bend_Abilities()));

        card_data.push_back(create_spell_data(
            "Unsubstantiate",
            dandan::mana::ManaPrice{
                dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}, 1},
            dandan::core::Type::Instant, Unsubstantiate_Abilities()));

        card_data.push_back(create_spell_data(
            "Memory Lapse",
            dandan::mana::ManaPrice{
                dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}, 1},
            dandan::core::Type::Instant, Memory_Lapse_Abilities()));

        card_data.push_back(create_spell_data(
            "Predict",
            dandan::mana::ManaPrice{
                dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}},
            dandan::core::Type::Instant, Predict_Abilities()));

        card_data.push_back(create_spell_data(
            "Dance of the Skywise",
            dandan::mana::ManaPrice{
                dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}, 1},
            dandan::core::Type::Instant, Dance_of_the_Skywise_Abilities()));

        card_data.push_back(create_spell_data(
            "Metamorphose",
            dandan::mana::ManaPrice{
                dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}, 1},
            dandan::core::Type::Instant, Metamorphose_Abilities()));

        return card_data;
    }();

    std::transform(card_data.begin(), card_data.end(),
                   std::back_inserter(cards), [](const auto &data)
                   { return dandan::core::Card{data.get()}; });

    return cards;
}

INSTANTIATE_TEST_SUITE_P(SpellTests, DeserializeTest,
                         testing::ValuesIn(getCards()),
                         [](const ::testing::TestParamInfo<dandan::Card> &info)
                         { return CardParamName(info.param.getData().name); });
