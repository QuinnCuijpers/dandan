#include "dandan/abilities/StaticAbility.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

namespace dandan::abilities
{

    StaticAbility::StaticAbility(
        Type type, std::unique_ptr<effects::IContinuousEffect> effect)
        : m_type(type), m_effect(std::move(effect))
    {
    }

    std::unique_ptr<effects::IOneShotEffect> StaticAbility::createEffect(
        [[maybe_unused]] core::ExecutionContext exec_ctx,
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
