#include "dandan/abilities/SpellAbility.h"
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
            return nullptr;
        }

        auto root_effect{effects()[0]->clone()};

        effects::IOneShotEffect *current_effect = root_effect.get();

        for (size_t i{1}; i < effects().size(); ++i)
        {
            std::cout << "Adding chain effect with index: " << i << "\n";
            auto next_effect = effects()[i]->clone();
            auto *next_effect_raw = next_effect.get();
            current_effect->setNext(std::move(next_effect));
            current_effect = next_effect_raw;
        }

        return root_effect;
    }

} // namespace dandan::abilities