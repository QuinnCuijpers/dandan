#ifndef DANDAN_KEYWORDS_H
#define DANDAN_KEYWORDS_H

#include "dandan/abilities/IAbility.h"
#include "dandan/abilities/StaticAbility.h"
#include "dandan/conditions/FlyingCondition.h"
#include "dandan/effects/continuous/prevention/BlockPreventionEffect.h"
#include <memory>
namespace dandan::abilities
{
    const std::unique_ptr<IAbility> FLYING_ABILITY{
        std::make_unique<dandan::abilities::StaticAbility>(
            dandan::abilities::StaticAbility::Type::Prevention,
            std::make_unique<dandan::effects::BlockPreventionEffect>(
                std::make_unique<dandan::conditions::FlyingCondition>()))};
} // namespace dandan::abilities

#endif