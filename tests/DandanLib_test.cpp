#include "dandan/dandan.h"
#include <gtest/gtest.h>
#include <memory>
#include <nlohmann/json.hpp>

// TODO: Use test suite to generate all tests

static const char *CARD_NAMES[] = {
    "Island",         "Remote Isle", "Shivan Reef", "Temple of Epiphany",
    "Halimar Depths",
};

TEST(DandanLibTest, Island)
{
    auto file{"../data/jsons/Island.json"};

    nlohmann::json j{file};

    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>()};

    abilities.push_back(
        std::make_unique<dandan::ManaAbility>(dandan::ManaAbility::COLORLESS));

    abilities.push_back(std::make_unique<dandan::WithDamage>(
        std::make_unique<dandan::ManaAbility>(dandan::ManaAbility::RED)));

    auto island_expected{
        dandan::Card("Island", 0, dandan::Card::Land, std::move(abilities))};

    auto island_recieved{j.get<dandan::Card>()};

    EXPECT_EQ(island_recieved.get_name(), island_expected.get_name());
}