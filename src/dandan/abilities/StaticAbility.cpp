#include "dandan/abilities/StaticAbility.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

namespace dandan::abilities
{

    std::unique_ptr<effects::IOneShotEffect> StaticAbility::createEffect(
        [[maybe_unused]] core::Game &game,
        [[maybe_unused]] AbilityContext context) const
    {
        std::cout << "Resolving StaticAbility\n";
        return nullptr;
    }
    [[nodiscard]] StaticAbility::Type StaticAbility::getType() const
    {
        return m_type;
    }

    [[nodiscard]] const effects::IContinuousEffect *StaticAbility::getEffect()
        const
    {
        return m_effect.get();
    }
} // namespace dandan::abilities
