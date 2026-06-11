#include "dandan/abilities/SpellAbility.h"
#include "dandan/effects/EffectContext.h"
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
        // TODO: fine grain this, currently we assume any effect targets the
        // player that created it

        auto bound_effects{
            std::vector<std::unique_ptr<effects::IOneShotEffect>>{}};
        for (const auto &effect_def : effects())
        {
            effects::EffectContext effect_context{context.source_card_id,
                                                  context.controller_id};
            auto effect{effect_def->bind(game, effect_context)};
            bound_effects.push_back(std::move(effect));
        }
        return std::make_unique<effects::EffectList>(std::move(bound_effects));
    }

} // namespace dandan::abilities