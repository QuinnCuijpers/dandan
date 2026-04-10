#include "dandan/dandan.h"
#include "nlohmann/json.hpp"
#include "gtest/gtest.h"
#include <cctype>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
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

    abilities.push_back(std::make_unique<dandan::ReplacementAbility>(
        std::make_unique<dandan::EntersBattlefieldEvent>(),
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

    abilities.emplace_back(std::make_unique<dandan::ReplacementAbility>(
        std::make_unique<dandan::EntersBattlefieldEvent>(),
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

    abilities.emplace_back(std::make_unique<dandan::ReplacementAbility>(
        std::make_unique<dandan::EntersBattlefieldEvent>(),
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(std::make_unique<dandan::TriggeredAbility>(
        std::make_unique<dandan::EntersBattlefieldEvent>(),
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
    dandan::Card m_recieved{};
    const dandan::Card *m_expected{};

    void SetUp() override
    {
        auto params{GetParam()};
        m_expected = params;
        std::string_view name{m_expected->get_name()};

        auto json_file_path{std::filesystem::path{DANDAN_SOURCE_DIR} /
                            "data/jsons" / name};
        json_file_path += ".json";

        std::ifstream file{json_file_path};
        nlohmann::json j{};
        file >> j;
        m_recieved = j.get<dandan::Card>();
    }
};

TEST_P(JsonTest, DeserializeCorrect)
{
    std::cout << m_recieved.get_name() << '\n';
    EXPECT_EQ(m_recieved.get_name(), m_expected->get_name());
};

std::string CardParamName(
    const testing::TestParamInfo<const dandan::Card *> &info)
{
    const std::string raw_name{info.param->get_name()};
    std::string name;
    for (char c : raw_name)
    {
        if (std::isalnum(static_cast<unsigned char>(c)))
            name.push_back(c);
    }
    if (name.empty())
        name = "unnamed";
    return name;
}

INSTANTIATE_TEST_SUITE_P(DeserializationTests, JsonTest,
                         testing::ValuesIn(getCards()), CardParamName);
