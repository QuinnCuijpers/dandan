#include "dandan/abilities/keywords/FlyingAbility.h"

namespace dandan::abilities
{
    std::unique_ptr<effects::IOneShotEffect> FlyingAbility::createEffect(
        [[maybe_unused]] core::ExecutionContext exec_ctx,
        [[maybe_unused]] AbilityContext context) const
    {
        return nullptr;
    }

    std::unique_ptr<IAbility> FlyingAbility::clone() const
    {
        return std::make_unique<FlyingAbility>();
    }

    Keyword FlyingAbility::keyword() const
    {
        return Keyword::Flying;
    }
} // namespace dandan::abilities
