#include "dandan/abilities/StaticAbility.h"
#include "gtest/gtest.h"
#include <array>
#ifdef DANDAN_SERIALIZE
#include "common.h"
#include "dandan/dandan.h"
#include <nlohmann/json.hpp>
#include <string>

static constexpr std::array<const char *, 8> activable_cards = {
    "Island",      "Halimar Depths", "Izzet Boilerworks", "Lonely Sandbar",
    "Remote Isle", "Shivan Reef",    "Svyelunite Temple", "Temple of Epiphany"};

struct AbilityDisplayCase
{
    const char *card_name;
    const char *expected_display;
};

class AbilityDisplayTest : public ::testing::TestWithParam<AbilityDisplayCase>
{
};

TEST_P(AbilityDisplayTest, DisplaysExpectedActivatableAbilities)
{
    const auto &test_case = GetParam();
    auto card{dandan::Card{test_case.card_name}};

    std::string actual{};
    for (const auto &ability : card.getData().getAbilities())
    {
        // triggered and static abilities cant be activated, so we ignore them
        // for this test
        if (dynamic_cast<const dandan::abilities::StaticAbility *>(
                ability.get()) != nullptr)
        {
            continue;
        }
        if (dynamic_cast<const dandan::abilities::TriggeredAbility *>(
                ability.get()) != nullptr)
        {
            continue;
        }
        for (size_t i{0}; i < ability->optionsAmount(); ++i)
        {
            actual += ability->displayOption(i) + '\n';
        }
    }
    EXPECT_EQ(actual, test_case.expected_display);
}

INSTANTIATE_TEST_SUITE_P(
    ActivatableCards, AbilityDisplayTest,
    ::testing::Values(
        AbilityDisplayCase{"Island", "[T]: Add U\n"},
        AbilityDisplayCase{"Halimar Depths", "[T]: Add U\n"},
        AbilityDisplayCase{"Izzet Boilerworks", "[T]: Add UR\n"},
        AbilityDisplayCase{"Lonely Sandbar",
                           "[T]: Add U\nU, Discard this card: Draw a card\n"},
        AbilityDisplayCase{"Remote Isle",
                           "[T]: Add U\n(2), Discard this card: Draw a card\n"},
        AbilityDisplayCase{
            "Shivan Reef",
            "[T]: Add C\n[T]: Add U. This Card deals 1 damage to you\n"
            "[T]: Add R. This Card deals 1 damage to you\n"},
        AbilityDisplayCase{"Svyelunite Temple",
                           "[T]: Add U\n[T], Sacrifice this Card: Add UU\n"},
        AbilityDisplayCase{"Temple of Epiphany", "[T]: Add U\n[T]: Add R\n"}),
    [](const ::testing::TestParamInfo<AbilityDisplayCase> &info)
    { return CardParamName(info.param.card_name); });

TEST(AbilityDisplayCardsTest, ActivatableListAndCasesStayAligned)
{
    static constexpr std::array<AbilityDisplayCase, activable_cards.size()>
        cases = {
            AbilityDisplayCase{"Island", "[T]: Add U\n"},
            AbilityDisplayCase{"Halimar Depths", "[T]: Add U\n"},
            AbilityDisplayCase{"Izzet Boilerworks", "[T]: Add UR\n"},
            AbilityDisplayCase{
                "Lonely Sandbar",
                "[T]: Add U\nU, Discard this card: Draw a card\n"},
            AbilityDisplayCase{
                "Remote Isle",
                "[T]: Add U\n(2), Discard this card: Draw a card\n"},
            AbilityDisplayCase{
                "Shivan Reef",
                "[T]: Add C\n[T]: Add U. This Card deals 1 damage to you\n"
                "[T]: Add R. This Card deals 1 damage to you\n"},
            AbilityDisplayCase{
                "Svyelunite Temple",
                "[T]: Add U\n[T], Sacrifice this Card: Add UU\n"},
            AbilityDisplayCase{"Temple of Epiphany",
                               "[T]: Add U\n[T]: Add R\n"},
        };

    for (size_t i{}; i < activable_cards.size(); ++i)
    {
        EXPECT_STREQ(activable_cards.at(i), cases.at(i).card_name);
    }
}

#endif