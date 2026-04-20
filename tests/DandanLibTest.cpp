#include "dandan/mana/AndMana.h"
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
        formatCardName(#name), 0, dandan::Card::Land, name##_Abilities()       \
    }

static std::string formatCardName(std::string_view name)
{
    std::string result{};
    for (char c : name)
    {
        if (c == '_')
        {
            result += ' ';
        }
        else
        {
            result += c;
        }
    }
    return result;
}

static std::vector<std::unique_ptr<dandan::IAbility>> Island_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};
    abilities.push_back(std::make_unique<dandan::ManaAbility>(
        dandan::mana::ManaList{std::make_unique<dandan::mana::BlueMana>()}));
    return abilities;
}

static std::vector<std::unique_ptr<dandan::IAbility>> Remote_Isle_Abilities()
{

    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.push_back(std::make_unique<dandan::ManaAbility>(
        dandan::mana::ManaList{std::make_unique<dandan::mana::BlueMana>()}));

    abilities.push_back(std::make_unique<dandan::StaticAbility>(
        std::make_unique<dandan::ETBEffect>(),
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.push_back(std::make_unique<dandan::ActivatedAbility>(
        std::make_unique<dandan::CyclingCost>(
            std::make_unique<dandan::ManaCost>(
                std::make_unique<dandan::mana::GenericMana>(2))),
        std::make_unique<dandan::DrawEffect>()));

    return abilities;
}

static std::vector<std::unique_ptr<dandan::IAbility>> Lonely_Sandbar_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(std::make_unique<dandan::ManaAbility>(
        dandan::mana::ManaList{std::make_unique<dandan::mana::BlueMana>()}));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        std::make_unique<dandan::ETBEffect>(),
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(std::make_unique<dandan::ActivatedAbility>(
        std::make_unique<dandan::CyclingCost>(
            std::make_unique<dandan::ManaCost>(
                std::make_unique<dandan::mana::BlueMana>())),
        std::make_unique<dandan::DrawEffect>()));

    return abilities;
}

static std::vector<std::unique_ptr<dandan::IAbility>> Halimar_Depths_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(std::make_unique<dandan::ManaAbility>(
        dandan::mana::ManaList{std::make_unique<dandan::mana::BlueMana>()}));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        std::make_unique<dandan::ETBEffect>(),
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(std::make_unique<dandan::TriggeredAbility>(
        std::make_unique<dandan::ETBEvent>(),
        std::make_unique<dandan::PeekEffect>()));

    return abilities;
}

static std::vector<std::unique_ptr<dandan::IAbility>> Shivan_Reef_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(
        std::make_unique<dandan::ManaAbility>(dandan::mana::ManaList{
            std::make_unique<dandan::mana::ColorlessMana>()}));

    auto mana_list{std::vector<std::unique_ptr<dandan::mana::Mana>>{}};
    mana_list.emplace_back(std::make_unique<dandan::mana::BlueMana>());
    mana_list.emplace_back(std::make_unique<dandan::mana::RedMana>());

    abilities.emplace_back(std::make_unique<dandan::WithDamage>(
        std::make_unique<dandan::ManaAbility>(
            dandan::ManaList{std::move(mana_list)})));
    return abilities;
}

static std::vector<std::unique_ptr<dandan::IAbility>>
Temple_of_Epiphany_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    auto mana_list{std::vector<std::unique_ptr<dandan::mana::Mana>>{}};
    mana_list.emplace_back(std::make_unique<dandan::mana::BlueMana>());
    mana_list.emplace_back(std::make_unique<dandan::mana::RedMana>());

    abilities.emplace_back(std::make_unique<dandan::ManaAbility>(
        dandan::ManaList{std::move(mana_list)}));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        std::make_unique<dandan::ETBEffect>(),
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(std::make_unique<dandan::TriggeredAbility>(
        std::make_unique<dandan::ETBEvent>(),
        std::make_unique<dandan::ScryEffect>()));

    return abilities;
}

static std::vector<std::unique_ptr<dandan::IAbility>>
Izzet_Boilerworks_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(std::make_unique<dandan::ManaAbility>(
        dandan::ManaList{std::make_unique<dandan::mana::AndMana>(
            std::make_unique<dandan::mana::BlueMana>(),
            std::make_unique<dandan::mana::RedMana>())}));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        std::make_unique<dandan::ETBEffect>(),
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(std::make_unique<dandan::TriggeredAbility>(
        std::make_unique<dandan::ETBEvent>(),
        std::make_unique<dandan::BounceLandEffect>()));

    return abilities;
}

static std::vector<std::unique_ptr<dandan::IAbility>>
Svyelunite_Temple_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>()};

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        std::make_unique<dandan::ETBEffect>(),
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(std::make_unique<dandan::ManaAbility>(
        dandan::ManaList{std::make_unique<dandan::BlueMana>()}));

    return abilities;
}

static const std::vector<const dandan::Card *> &getCards()
{
    static const std::vector<const dandan::Card *> cards = {
        new LAND(Island),
        new LAND(Remote_Isle),
        new LAND(Lonely_Sandbar),
        new LAND(Halimar_Depths),
        new LAND(Shivan_Reef),
        new LAND(Temple_of_Epiphany),
        new LAND(Izzet_Boilerworks),
        new LAND(Svyelunite_Temple)};
    return cards;
};

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