#ifndef DANDAN_TEST_CREATUREDEFINITIONS_H
#define DANDAN_TEST_CREATUREDEFINITIONS_H

#include "dandan/conditions/ControlsNoIslandCondition.h"
#include "dandan/dandan.h"
#include "dandan/effects/continuous/prevention/AttackPreventionEffect.h"
#include "dandan/effects/one_shot/SelfSacrificeEffect.h"
#include <memory>
#include <vector>

inline std::vector<std::unique_ptr<dandan::IAbility>> Dandan_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(std::make_unique<dandan::StateTriggeredAbility>(
        std::make_unique<dandan::conditions::ControlsNoIslandCondition>(),
        std::make_unique<dandan::effects::SelfSacrificeEffect>()));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Type::Prevention,
        std::make_unique<dandan::effects::AttackPreventionEffect>(
            std::make_unique<
                dandan::conditions::ControlsNoIslandCondition>())));
    return abilities;
}

#endif