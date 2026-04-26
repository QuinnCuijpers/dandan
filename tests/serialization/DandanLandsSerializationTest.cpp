#ifdef DANDAN_BUILD_SERIALIZE
#include "common.h"
#include "dandan/abilities/StaticAbility.h"
#include "dandan/costs/AndCost.h"
#include "dandan/dandan.h"
#include "dandan/mana/AndMana.h"
#include "gtest/gtest.h"
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
        dandan::abilities::StaticAbility::Replacement,
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
        dandan::abilities::StaticAbility::Replacement,
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
        dandan::abilities::StaticAbility::Replacement,
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
        dandan::abilities::StaticAbility::Replacement,
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
        dandan::abilities::StaticAbility::Replacement,
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
        dandan::abilities::StaticAbility::Replacement,
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

INSTANTIATE_TEST_SUITE_P(LandTests, DeserializeTest,
                         testing::ValuesIn(getCards()), CardParamName);

#endif