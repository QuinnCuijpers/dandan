#include "dandan/costs/AndCost.h"
#ifdef DANDAN_BUILD_SERIALIZE
#include "dandan/dandan.h"
#include "dandan/mana/AndMana.h"
#include "nlohmann/json.hpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#define LAND(name, subtype)                                                    \
    dandan::Card                                                               \
    {                                                                          \
        formatCardName(#name), std::make_unique<dandan::mana::GenericMana>(0), \
            dandan::Card::Land, subtype, name##_Abilities()                    \
    }

static std::string formatCardName(std::string_view name)
{
    std::string result{};
    for (char char_ : name)
    {
        if (char_ == '_')
        {
            result += ' ';
        }
        else
        {
            result += char_;
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

    abilities.emplace_back(std::make_unique<dandan::ManaAbility>(
        std::make_unique<dandan::costs::AndCost>(
            std::make_unique<dandan::costs::TapCost>(),
            std::make_unique<dandan::costs::SelfSacrificeCost>()),
        dandan::ManaList{std::make_unique<dandan::BlueMana>(2)}));

    return abilities;
}

static const std::vector<const dandan::Card *> &getCards()
{
    static const std::vector<const dandan::Card *> cards = {
        new LAND(Island, dandan::Card::SubType::Island),
        new LAND(Remote_Isle, dandan::Card::SubType::None),
        new LAND(Lonely_Sandbar, dandan::Card::SubType::None),
        new LAND(Halimar_Depths, dandan::Card::SubType::None),
        new LAND(Shivan_Reef, dandan::Card::SubType::None),
        new LAND(Temple_of_Epiphany, dandan::Card::SubType::None),
        new LAND(Izzet_Boilerworks, dandan::Card::SubType::None),
        new LAND(Svyelunite_Temple, dandan::Card::SubType::None)};
    return cards;
};

class JsonTest : public testing::TestWithParam<const dandan::Card *>
{

public:
    nlohmann::json m_expected;
    nlohmann::json m_received;

protected:
    void SetUp() override
    {
        const auto *params{GetParam()};
        const auto *card = params;
        std::string_view name{card->getName()};

        auto json_file_path{std::filesystem::path{DANDAN_PROJECT_SOURCE} /
                            "data/jsons" / name};
        json_file_path += ".json";

        std::ifstream file{json_file_path};
        nlohmann::json json{};
        file >> json;

        m_expected = json;
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
                 [](char char_) { return std::isalnum(char_); });
    if (name.empty())
    {
        name = "unnamed";
    }
    return name;
}

INSTANTIATE_TEST_SUITE_P(DeserializationTests, JsonTest,
                         testing::ValuesIn(getCards()), CardParamName);

#endif