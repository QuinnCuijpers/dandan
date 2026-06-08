#ifndef DANDAN_SPELL_DEFINITIONS_H
#define DANDAN_SPELL_DEFINITIONS_H

#include "dandan/abilities/IAbility.h"
#include "dandan/dandan.h"
#include "dandan/effects/one_shot/PutCardOnTopEffect.h"
#include "dandan/numbers/GraveyardCount.h"
#include <memory>
#include <vector>

inline std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Brainstorm_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    auto ability_effects{
        std::vector<std::unique_ptr<dandan::effects::IOneShotEffect>>{}};
    ability_effects.emplace_back(
        std::make_unique<dandan::effects::DrawEffect>(3));
    ability_effects.emplace_back(
        std::make_unique<dandan::effects::PutCardOnTopEffect>(2));

    abilities.emplace_back(
        std::make_unique<dandan::SpellAbility>(std::move(ability_effects)));

    return abilities;
}

std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Accumulated_Knowledge_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    auto ability_effects{
        std::vector<std::unique_ptr<dandan::effects::IOneShotEffect>>{}};

    ability_effects.emplace_back(
        std::make_unique<dandan::effects::DrawEffect>(1));
    ability_effects.emplace_back(std::make_unique<dandan::effects::DrawEffect>(
        std::make_unique<dandan::numbers::GraveyardCount>(
            std::string("Accumulated Knowledge"))));

    abilities.emplace_back(
        std::make_unique<dandan::SpellAbility>(std::move(ability_effects)));

    return abilities;
}

#endif