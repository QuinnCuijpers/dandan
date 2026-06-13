#ifndef DANDAN_SPELL_DEFINITIONS_H
#define DANDAN_SPELL_DEFINITIONS_H

#include "dandan/abilities/IAbility.h"
#include "dandan/dandan.h"
#include "dandan/effects/one_shot/ChangeLandTypeEffect.h"
#include "dandan/effects/one_shot/ExileTopEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "dandan/effects/one_shot/MillEffect.h"
#include "dandan/effects/one_shot/MindBendEffect.h"
#include "dandan/effects/one_shot/ModalEffect.h"
#include "dandan/effects/one_shot/OptionalDrawEffect.h"
#include "dandan/effects/one_shot/PutCardOnTopEffect.h"
#include "dandan/effects/one_shot/TimeTwisterEffect.h"
#include "dandan/effects/one_shot/TutorTopEffect.h"
#include "dandan/numbers/GraveyardCount.h"
#include <memory>
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
        std::make_unique<dandan::effects::TimeTwisterEffect>());
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

    ability_effects.emplace_back(
        std::make_unique<dandan::effects::MindBendEffectDefinition>(
            target_req));

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

#endif