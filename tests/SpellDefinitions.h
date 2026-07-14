#ifndef DANDAN_SPELL_DEFINITIONS_H
#define DANDAN_SPELL_DEFINITIONS_H

#include "dandan/abilities/IAbility.h"
#include "dandan/abilities/KeyWords.h"
#include "dandan/conditions/ICondition.h"
#include "dandan/conditions/MatchesReadLinksCondition.h"
#include "dandan/core/CardCharacteristics.h"
#include "dandan/core/CardData.h"
#include "dandan/core/ColorWord.h"
#include "dandan/core/Expire.h"
#include "dandan/core/SubType.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/dandan.h"
#include "dandan/effects/one_shot/BounceEffect.h"
#include "dandan/effects/one_shot/ChangeCharasticsEffect.h"
#include "dandan/effects/one_shot/ChangeLandTypeEffect.h"
#include "dandan/effects/one_shot/ChooseCardNameAndMillEffect.h"
#include "dandan/effects/one_shot/DrawEffect.h"
#include "dandan/effects/one_shot/ExileTopEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "dandan/effects/one_shot/MemoryLapseEffect.h"
#include "dandan/effects/one_shot/MillEffect.h"
#include "dandan/effects/one_shot/MindBendEffect.h"
#include "dandan/effects/one_shot/ModalEffect.h"
#include "dandan/effects/one_shot/OptionalDrawEffect.h"
#include "dandan/effects/one_shot/PutCardOnTopEffect.h"
#include "dandan/effects/one_shot/ShowAndTellEffect.h"
#include "dandan/effects/one_shot/SpinToTopEffect.h"
#include "dandan/effects/one_shot/TimeTwisterEffect.h"
#include "dandan/effects/one_shot/TutorTopEffect.h"
#include "dandan/numbers/ConditionalNumber.h"
#include "dandan/numbers/GraveyardCount.h"
#include <memory>
#include <utility>
#include <vector>

inline std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Brainstorm_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    auto ability_effects{std::vector<
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition>>{}};
    ability_effects.emplace_back(
        std::make_unique<dandan::effects::DrawEffectDefinition>(3));
    ability_effects.emplace_back(
        std::make_unique<dandan::effects::PutCardOnTopEffectDefinition>(2));

    abilities.emplace_back(
        std::make_unique<dandan::SpellAbility>(std::move(ability_effects)));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Accumulated_Knowledge_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    auto ability_effects{std::vector<
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition>>{}};

    ability_effects.emplace_back(
        std::make_unique<dandan::effects::DrawEffectDefinition>(1));
    ability_effects.emplace_back(
        std::make_unique<dandan::effects::DrawEffectDefinition>(
            std::make_unique<dandan::numbers::GraveyardCount>(
                std::string("Accumulated Knowledge"))));

    abilities.emplace_back(
        std::make_unique<dandan::SpellAbility>(std::move(ability_effects)));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Diminishing_Returns_Abilities()
{
    static const int EXILE_AMOUNT = 10;
    static const int DRAW_AMOUNT = 7;

    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    auto ability_effects{std::vector<
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition>>{}};

    ability_effects.emplace_back(
        std::make_unique<dandan::effects::TimeTwisterEffectDefinition>());
    ability_effects.emplace_back(
        std::make_unique<dandan::effects::ExileTopEffectDefinition>(
            EXILE_AMOUNT));
    ability_effects.emplace_back(
        std::make_unique<dandan::effects::OptionalDrawEffectDefinition>(
            DRAW_AMOUNT, true));

    abilities.emplace_back(
        std::make_unique<dandan::SpellAbility>(std::move(ability_effects)));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Mystical_Tutor_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    auto ability_effects{std::vector<
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition>>{}};
    ability_effects.emplace_back(
        std::make_unique<dandan::effects::TutorTopEffectDefinition>(
            std::vector<dandan::CardData::Type>{
                dandan::CardData::Type::Instant,
                dandan::CardData::Type::Sorcery}));

    abilities.emplace_back(
        std::make_unique<dandan::SpellAbility>(std::move(ability_effects)));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Vision_Charm_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::abilities::IAbility>>{}};

    auto target_requirement{dandan::core::TargetRequirement{
        std::vector<std::vector<dandan::core::TargetType>>{
            {dandan::core::TargetType::Player}}}};

    auto options{std::vector<
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition>>{}};
    options.emplace_back(
        std::make_unique<dandan::effects::MillEffectDefinition>(
            4, target_requirement));
    options.emplace_back(
        std::make_unique<dandan::effects::ChangeLandTypeEffectDefinition>());

    auto modal_effect{std::make_unique<dandan::effects::ModalEffectDefinition>(
        std::move(options))};

    auto spell_effects{std::vector<
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition>>{}};
    spell_effects.emplace_back(std::move(modal_effect));

    abilities.emplace_back(
        std::make_unique<dandan::SpellAbility>(std::move(spell_effects)));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Crystal_Spray_Abilities()
{
    auto target_req{dandan::core::TargetRequirement{
        std::vector<std::vector<dandan::core::TargetType>>{
            {dandan::core::TargetType::Spell,
             dandan::core::TargetType::Permanent}}}};

    auto abilities{std::vector<std::unique_ptr<dandan::abilities::IAbility>>{}};

    auto ability_effects{std::vector<
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition>>{}};

    auto mind_bend_effect{
        std::make_unique<dandan::effects::MindBendEffectDefinition>(
            target_req)};
    mind_bend_effect->addExpireTime(dandan::core::ExpireTime::EnfOfTurn);

    ability_effects.emplace_back(std::move(mind_bend_effect));

    ability_effects.emplace_back(
        std::make_unique<dandan::effects::DrawEffectDefinition>(1));

    abilities.emplace_back(
        std::make_unique<dandan::SpellAbility>(std::move(ability_effects)));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Mind_Bend_Abilities()
{
    auto target_req{dandan::core::TargetRequirement{
        std::vector<std::vector<dandan::core::TargetType>>{
            {dandan::core::TargetType::Permanent}}}};

    auto abilities{std::vector<std::unique_ptr<dandan::abilities::IAbility>>{}};

    auto ability_effects{std::vector<
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition>>{}};

    ability_effects.emplace_back(
        std::make_unique<dandan::effects::MindBendEffectDefinition>(
            target_req));

    abilities.emplace_back(
        std::make_unique<dandan::SpellAbility>(std::move(ability_effects)));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Unsubstantiate_Abilities()
{

    auto target_req{dandan::core::TargetRequirement{
        std::vector<std::vector<dandan::core::TargetType>>{
            {dandan::core::TargetType::Spell,
             dandan::core::TargetType::Creature}}}};

    auto abilities{std::vector<std::unique_ptr<dandan::abilities::IAbility>>{}};

    auto ability_effects{std::vector<
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition>>{}};

    ability_effects.emplace_back(
        std::make_unique<dandan::effects::BounceEffectDefinition>(target_req));

    abilities.emplace_back(
        std::make_unique<dandan::SpellAbility>(std::move(ability_effects)));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Memory_Lapse_Abilities()
{

    auto target_req{dandan::core::TargetRequirement{
        std::vector<std::vector<dandan::core::TargetType>>{
            {dandan::core::TargetType::Spell}}}};

    auto abilities{std::vector<std::unique_ptr<dandan::abilities::IAbility>>{}};

    auto ability_effects{std::vector<
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition>>{}};

    ability_effects.emplace_back(
        std::make_unique<dandan::effects::MemoryLapseEffectDefinition>(
            target_req));

    abilities.emplace_back(
        std::make_unique<dandan::SpellAbility>(std::move(ability_effects)));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Predict_Abilities()
{

    auto target_req{dandan::core::TargetRequirement{
        std::vector<std::vector<dandan::core::TargetType>>{
            {dandan::core::TargetType::Player}}}};

    auto abilities{std::vector<std::unique_ptr<dandan::abilities::IAbility>>{}};

    auto ability_effects{std::vector<
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition>>{}};

    auto first_effect{std::make_unique<
        dandan::effects::ChooseCardNameAndMillEffectDefinition>(1, target_req)};

    first_effect->addWriteLink("chosenCardName");
    first_effect->addWriteLink("milledCardName");

    ability_effects.emplace_back(std::move(first_effect));

    std::unique_ptr<dandan::conditions::ICondition> condition{
        std::make_unique<dandan::conditions::MatchesReadLinksCondition>(
            "chosenCardName", "milledCardName")};

    auto conditional_number{
        std::make_unique<dandan::numbers::ConditionalNumber>(
            2, 1, std::move(condition))};

    auto second_effect{std::make_unique<dandan::effects::DrawEffectDefinition>(
        std::move(conditional_number))};

    second_effect->addReadLink("chosenCardName");
    second_effect->addReadLink("milledCardName");

    ability_effects.emplace_back(std::move(second_effect));

    abilities.emplace_back(
        std::make_unique<dandan::SpellAbility>(std::move(ability_effects)));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Dance_of_the_Skywise_Abilities()
{

    auto types{std::vector<dandan::core::TargetType>{
        dandan::core::TargetType::Creature}};

    auto *flying{dandan::abilities::FLYING_ABILITY.get()};

    auto added_abilities{std::vector<const dandan::abilities::IAbility *>{}};

    added_abilities.push_back(flying);

    auto changes{dandan::core::CardCharacteristics{
        dandan::core::ColorWord::Blue,
        {dandan::core::SubType::Dragon, dandan::core::SubType::Illusion},
        dandan::core::Stats{4, 4},
        true,
        std::move(added_abilities)}};

    dandan::core::TargetSpec target_spec{types, dandan::core::Controller::You};

    auto target_req{dandan::core::TargetRequirement{{target_spec}}};

    auto abilities{std::vector<std::unique_ptr<dandan::abilities::IAbility>>{}};

    auto ability_effects{std::vector<
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition>>{}};

    auto change_effect{std::make_unique<
        dandan::effects::ChangeCharacteristicsEffectDefinition>(target_req,
                                                                changes)};
    change_effect->addExpireTime(dandan::core::ExpireTime::EnfOfTurn);

    ability_effects.push_back(std::move(change_effect));

    abilities.emplace_back(
        std::make_unique<dandan::SpellAbility>(std::move(ability_effects)));

    return abilities;
}

inline std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Metamorphose_Abilities()
{
    auto controller{dandan::core::Controller::Opponent};
    auto types{std::vector<dandan::core::TargetType>{
        dandan::core::TargetType::Permanent}};

    dandan::core::TargetSpec target_specs{types, controller};

    auto target_specs_1{std::vector<dandan::core::TargetSpec>{target_specs}};

    dandan::core::TargetRequirement target_req{target_specs_1};

    auto abilities{std::vector<std::unique_ptr<dandan::abilities::IAbility>>{}};

    auto ability_effects{std::vector<
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition>>{}};

    auto spin_effect{
        std::make_unique<dandan::effects::SpinToTopEffectDefinition>(
            target_req)};
    spin_effect->addWriteLink("targetOwner");

    ability_effects.push_back(std::move(spin_effect));

    auto types_2{std::vector<dandan::core::TargetType>{
        dandan::core::TargetType::Player}};
    dandan::core::TargetSpec target_spec_2{types_2, "targetOwner", controller};

    dandan::core::TargetRequirement targets_2{
        std::vector<dandan::core::TargetSpec>{target_spec_2}};

    auto show_and_tell_effect{
        std::make_unique<dandan::effects::ShowAndTellEffectDefinition>(
            targets_2)};

    show_and_tell_effect->addReadLink("targetOwner");

    ability_effects.push_back(std::move(show_and_tell_effect));

    abilities.emplace_back(
        std::make_unique<dandan::SpellAbility>(std::move(ability_effects)));

    return abilities;
}
#endif