#include "dandan/abilities/SpellAbility.h"
#include "dandan/effects/one_shot/EffectList.h"
#include <iostream>

namespace dandan::abilities
{
    std::unique_ptr<effects::IOneShotEffect> SpellAbility::createEffect(
        [[maybe_unused]] core::Game &game,
        [[maybe_unused]] AbilityContext context) const
    {
        std::cout << "Creating spell effect with size: " << effects().size()
                  << "\n";
        if (effects().empty())
        {
            // TODO: consider returning a no-op effect instead of nullptr to
            // avoid null checks
            std::cout << "WARNING: No effects to create for spell ability\n";
            return nullptr;
        }
        return std::make_unique<effects::EffectList>(effects());
    }

} // namespace dandan::abilities