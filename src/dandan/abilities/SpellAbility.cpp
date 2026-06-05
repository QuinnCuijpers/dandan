#include "dandan/abilities/SpellAbility.h"

namespace dandan::abilities
{
    std::unique_ptr<effects::IOneShotEffect> SpellAbility::createEffect(
        [[maybe_unused]] core::Game &game,
        [[maybe_unused]] AbilityContext context) const
    {
        throw std::runtime_error(
            "SpellAbility does not support creating an effect yet");
    }

} // namespace dandan::abilities