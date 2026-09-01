#include "dandan/abilities/StaticAbility.h"
#include "dandan/conditions/FlyingCondition.h"
#include "dandan/effects/continuous/prevention/BlockPreventionEffect.h"

namespace dandan::abilities
{
    const std::unique_ptr<IAbility> FLYING_ABILITY{
        std::make_unique<dandan::abilities::StaticAbility>(
            dandan::abilities::StaticAbility::Type::Prevention,
            std::make_unique<dandan::effects::BlockPreventionEffect>(
                std::make_unique<dandan::conditions::FlyingCondition>()))};
}

namespace dandan::core
{
    bool isFlyingAbility(const dandan::abilities::IAbility &ability)
    {
        const auto *static_ability =
            dynamic_cast<const dandan::abilities::StaticAbility *>(&ability);
        if ((static_ability == nullptr) ||
            static_ability->getType() !=
                dandan::abilities::StaticAbility::Type::Prevention)
        {
            return false;
        }
        const auto *effect =
            dynamic_cast<const dandan::effects::BlockPreventionEffect *>(
                static_ability->getEffect());
        if (effect == nullptr)
        {
            return false;
        }
        return dynamic_cast<const dandan::conditions::FlyingCondition *>(
                   effect->getCondition()) != nullptr;
    }
} // namespace dandan::core
