#include "CreatureDefinitions.h"
#include "dandan/effects/continuous/prevention/AttackPreventionEffect.h"

std::vector<std::unique_ptr<dandan::IAbility>> Dandan_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(std::make_unique<dandan::StateTriggeredAbility>(
        std::make_unique<dandan::conditions::SelfControlsNoBasicCondition>(
            dandan::core::SubType::Island),
        std::make_unique<dandan::effects::SelfSacrificeEffectDefinition>()));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Type::Prevention,
        std::make_unique<dandan::effects::AttackPreventionEffect>(
            std::make_unique<
                dandan::conditions::DefenderControlsNoBasicCondition>(
                dandan::core::SubType::Island))));
    return abilities;
}
