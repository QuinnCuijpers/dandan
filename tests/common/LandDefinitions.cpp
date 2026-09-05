#include "LandDefinitions.h"
#include "dandan/abilities/BasicLandAbility.h"

std::vector<std::unique_ptr<dandan::IAbility>> Island_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};
    return abilities;
}

std::vector<std::unique_ptr<dandan::IAbility>> Island_TESTS_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.push_back(
        std::make_unique<dandan::abilities::BasicLandAbility>());

    return abilities;
}

std::vector<std::unique_ptr<dandan::IAbility>> Remote_Isle_Abilities()
{

    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.push_back(
        std::make_unique<dandan::ManaAbility>(dandan::mana::ManaList{
            dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}}));

    abilities.push_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Type::Replacement,
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.push_back(std::make_unique<dandan::ActivatedAbility>(
        std::make_unique<dandan::CyclingCost>(
            std::make_unique<dandan::ManaCost>(
                dandan::mana::ManaPrice{dandan::mana::ManaBag{}, 2})),
        std::make_unique<dandan::effects::DrawEffectDefinition>()));

    return abilities;
}

std::vector<std::unique_ptr<dandan::IAbility>> Lonely_Sandbar_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(
        std::make_unique<dandan::ManaAbility>(dandan::mana::ManaList{
            dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}}));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Type::Replacement,
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(std::make_unique<dandan::ActivatedAbility>(
        std::make_unique<dandan::CyclingCost>(
            std::make_unique<dandan::ManaCost>(dandan::mana::ManaPrice{
                dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}})),
        std::make_unique<dandan::effects::DrawEffectDefinition>()));

    return abilities;
}

std::vector<std::unique_ptr<dandan::IAbility>> Halimar_Depths_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(
        std::make_unique<dandan::ManaAbility>(dandan::mana::ManaList{
            dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}}));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Type::Replacement,
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(std::make_unique<dandan::EventTriggeredAbility>(
        std::make_unique<dandan::SelfETBTrigger>(),
        std::make_unique<dandan::effects::PeekEffectDefinition>()));

    return abilities;
}

std::vector<std::unique_ptr<dandan::IAbility>> Shivan_Reef_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(
        std::make_unique<dandan::ManaAbility>(dandan::mana::ManaList{
            dandan::mana::ManaBag{{dandan::mana::ManaType::COLORLESS, 1}}}));

    auto mana_list{std::vector<dandan::mana::ManaBag>{}};
    mana_list.emplace_back(
        dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}});
    mana_list.emplace_back(
        dandan::mana::ManaBag{{dandan::mana::ManaType::RED, 1}});

    abilities.emplace_back(std::make_unique<dandan::WithDamage>(
        std::make_unique<dandan::ManaAbility>(
            dandan::ManaList{std::move(mana_list)})));
    return abilities;
}

std::vector<std::unique_ptr<dandan::IAbility>> Temple_of_Epiphany_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    auto mana_list{std::vector<dandan::mana::ManaBag>{}};
    mana_list.emplace_back(
        dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}});
    mana_list.emplace_back(
        dandan::mana::ManaBag{{dandan::mana::ManaType::RED, 1}});

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

std::vector<std::unique_ptr<dandan::IAbility>> Izzet_Boilerworks_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(
        std::make_unique<dandan::ManaAbility>(dandan::mana::ManaList{
            dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1},
                                  {dandan::mana::ManaType::RED, 1}},
        }));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Type::Replacement,
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(std::make_unique<dandan::EventTriggeredAbility>(
        std::make_unique<dandan::SelfETBTrigger>(),
        std::make_unique<dandan::effects::BounceLandEffectDefinition>()));

    return abilities;
}

std::vector<std::unique_ptr<dandan::IAbility>> Svyelunite_Temple_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>()};

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Type::Replacement,
        std::make_unique<dandan::EntersTappedEffect>()));

    abilities.emplace_back(
        std::make_unique<dandan::ManaAbility>(dandan::ManaList{
            dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}}));

    abilities.emplace_back(std::make_unique<dandan::ManaAbility>(
        std::make_unique<dandan::costs::AndCost>(
            std::make_unique<dandan::costs::TapCost>(),
            std::make_unique<dandan::costs::SelfSacrificeCost>()),
        dandan::ManaList{
            dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 2}}}));

    return abilities;
}
