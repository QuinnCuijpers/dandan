#include "dandan/core/engine/ReplacementManager.h"
#include "dandan/abilities/AbilityType.h"
#include "dandan/abilities/BoundAbility.h"
#include "dandan/effects/continuous/replacement/IReplacementEffect.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <algorithm>
#include <memory>
#include <unordered_set>

namespace dandan::core
{
    void ReplacementManager::subscribe(abilities::BoundAbility &ability)
    {
        m_replacement_effects.emplace_back(&ability);
    }

    void ReplacementManager::unsubscribe(Card &card)
    {
        // Phase 1: collect pointers to remove
        std::unordered_set<const abilities::BoundAbility *> to_remove{};

        for (const auto &ability : card.getCurrentAbilities())
        {
            if (ability.type() == abilities::AbilityType::StaticReplacement)
            {
                to_remove.insert(&ability);
            }
        }

        // Phase 2: erase from target container
        m_replacement_effects.erase(
            std::remove_if(m_replacement_effects.begin(),
                           m_replacement_effects.end(), [&](const auto *effect)
                           { return to_remove.count(effect) > 0; }),
            m_replacement_effects.end());
    }

    std::unique_ptr<effects::IOneShotEffect> ReplacementManager::
        applyReplacementEffects(effects::IOneShotEffect &effect,
                                [[maybe_unused]] Game &game) const
    {
        effects::IOneShotEffect *current_effect{&effect};
        for (const auto *ability : m_replacement_effects)
        {
            if (const auto *replacement_effect =
                    dynamic_cast<const effects::IReplacementEffect *>(
                        &ability->definition()))
            {
                if (replacement_effect->appliesTo(*current_effect))
                {
                    current_effect =
                        &replacement_effect->replace(*current_effect);
                }
            }
        }
        return current_effect->copy();
    }
} // namespace dandan::core