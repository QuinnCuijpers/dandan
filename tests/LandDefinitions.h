#ifndef DANDAN_TEST_LANDDEFINITIONS_H
#define DANDAN_TEST_LANDDEFINITIONS_H

#include "dandan/costs/AndCost.h"
#include "dandan/dandan.h"
#include "dandan/mana/AndMana.h"
#include <memory>
#include <vector>

inline std::vector<std::unique_ptr<dandan::IAbility>> Island_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};
    abilities.push_back(std::make_unique<dandan::ManaAbility>(
        dandan::mana::ManaList{std::make_unique<dandan::mana::BlueMana>()}));
    return abilities;
}

inline std::vector<std::unique_ptr<dandan::IAbility>> Remote_Isle_Abilities()
{

    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.push_back(std::make_unique<dandan::ManaAbility>(
        dandan::mana::ManaList{std::make_unique<dandan::mana::BlueMana>()}));

    abilities.push_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Type::Replacement,
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.push_back(std::make_unique<dandan::ActivatedAbility>(
        std::make_unique<dandan::CyclingCost>(
            std::make_unique<dandan::ManaCost>(
                std::make_unique<dandan::mana::GenericMana>(2))),
        std::make_unique<dandan::DrawEffectDefinition>()));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::IAbility>> Lonely_Sandbar_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(std::make_unique<dandan::ManaAbility>(
        dandan::mana::ManaList{std::make_unique<dandan::mana::BlueMana>()}));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Type::Replacement,
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(std::make_unique<dandan::ActivatedAbility>(
        std::make_unique<dandan::CyclingCost>(
            std::make_unique<dandan::ManaCost>(
                std::make_unique<dandan::mana::BlueMana>())),
        std::make_unique<dandan::DrawEffectDefinition>()));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::IAbility>> Halimar_Depths_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(std::make_unique<dandan::ManaAbility>(
        dandan::mana::ManaList{std::make_unique<dandan::mana::BlueMana>()}));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Type::Replacement,
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(std::make_unique<dandan::EventTriggeredAbility>(
        std::make_unique<dandan::SelfETBTrigger>(),
        std::make_unique<dandan::effects::PeekEffectDefinition>()));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::IAbility>> Shivan_Reef_Abilities()
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

inline std::vector<std::unique_ptr<dandan::IAbility>>
Temple_of_Epiphany_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    auto mana_list{std::vector<std::unique_ptr<dandan::mana::Mana>>{}};
    mana_list.emplace_back(std::make_unique<dandan::mana::BlueMana>());
    mana_list.emplace_back(std::make_unique<dandan::mana::RedMana>());

    abilities.emplace_back(std::make_unique<dandan::ManaAbility>(
        dandan::ManaList{std::move(mana_list)}));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Type::Replacement,
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(std::make_unique<dandan::EventTriggeredAbility>(
        std::make_unique<dandan::SelfETBTrigger>(),
        std::make_unique<dandan::effects::ScryEffectDefinition>()));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::IAbility>>
Izzet_Boilerworks_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(std::make_unique<dandan::ManaAbility>(
        dandan::ManaList{std::make_unique<dandan::mana::AndMana>(
            std::make_unique<dandan::mana::BlueMana>(),
            std::make_unique<dandan::mana::RedMana>())}));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Type::Replacement,
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(std::make_unique<dandan::EventTriggeredAbility>(
        std::make_unique<dandan::SelfETBTrigger>(),
        std::make_unique<dandan::effects::BounceLandEffectDefinition>()));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::IAbility>>
Svyelunite_Temple_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>()};

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Type::Replacement,
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

#endif