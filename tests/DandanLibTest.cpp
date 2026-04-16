#ifdef DANDAN_BUILD_SERIALIZE
#include "dandan/dandan.h"
#include "nlohmann/json.hpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#define LAND(name)                                                             \
    dandan::Card                                                               \
    {                                                                          \
        formatCardName(#name), 0, dandan::Card::Land, name##Abilities()        \
    }

static std::string formatCardName(std::string_view name)
{
    {
        std::string result;
        for (char c : name)
        {
            if (std::isupper(c) && !result.empty())
                result += ' ';
            result += c;
        }
        return result;
    }
}

static std::vector<std::unique_ptr<dandan::IAbility>> IslandAbilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};
    abilities.push_back(
        std::make_unique<dandan::ManaAbility>(dandan::ManaAbility::BLUE));
    return abilities;
}

static std::vector<std::unique_ptr<dandan::IAbility>> RemoteIsleAbilities()
{

    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.push_back(
        std::make_unique<dandan::ManaAbility>(dandan::ManaAbility::BLUE));

    abilities.push_back(std::make_unique<dandan::StaticAbility>(
        std::make_unique<dandan::ETBEffect>(),
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.push_back(std::make_unique<dandan::ActivatedAbility>(
        std::make_unique<dandan::CyclingCost>(
            std::make_unique<dandan::GenericManaCost>(2)),
        std::make_unique<dandan::DrawEffect>()));

    return abilities;
}

static std::vector<std::unique_ptr<dandan::IAbility>> LonelySandbarAbilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(
        std::make_unique<dandan::ManaAbility>(dandan::ManaAbility::BLUE));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        std::make_unique<dandan::ETBEffect>(),
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(std::make_unique<dandan::ActivatedAbility>(
        std::make_unique<dandan::CyclingCost>(
            std::make_unique<dandan::ColoredManaCost>(
                dandan::ColoredManaCost::BLUE)),
        std::make_unique<dandan::DrawEffect>()));

    return abilities;
}

static std::vector<std::unique_ptr<dandan::IAbility>> HalimarDepthsAbilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(
        std::make_unique<dandan::ManaAbility>(dandan::ManaAbility::BLUE));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        std::make_unique<dandan::ETBEffect>(),
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(std::make_unique<dandan::TriggeredAbility>(
        std::make_unique<dandan::ETBEvent>(),
        std::make_unique<dandan::PeekEffect>()));

    return abilities;
}

static const std::vector<const dandan::Card *> &getCards()
{
    static const std::vector<const dandan::Card *> cards = {
        new LAND(Island), new LAND(RemoteIsle), new LAND(LonelySandbar),
        new LAND(HalimarDepths)};
    return cards;
}

class JsonTest : public testing::TestWithParam<const dandan::Card *>
{

protected:
    nlohmann::json m_expected;
    nlohmann::json m_received;
    void SetUp() override
    {
        auto params{GetParam()};
        auto card = params;
        std::string_view name{card->getName()};

        auto json_file_path{std::filesystem::path{DANDAN_PROJECT_SOURCE} /
                            "data/jsons" / name};
        json_file_path += ".json";

        std::ifstream file{json_file_path};
        nlohmann::json j{};
        file >> j;

        m_expected = j;
        m_received = nlohmann::json(*card);
    }
};

TEST_P(JsonTest, DeserializeCorrect)
{
    EXPECT_EQ(m_received, m_expected);
};

std::string CardParamName(
    const testing::TestParamInfo<const dandan::Card *> &info)
{
    const std::string raw_name{info.param->getName()};
    std::string name;
    std::copy_if(raw_name.begin(), raw_name.end(), std::back_inserter(name),
                 [](char c) { return std::isalnum(c); });
    if (name.empty())
        name = "unnamed";
    return name;
}

INSTANTIATE_TEST_SUITE_P(DeserializationTests, JsonTest,
                         testing::ValuesIn(getCards()), CardParamName);

#endif