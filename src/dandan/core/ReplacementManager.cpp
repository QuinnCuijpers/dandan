#include "dandan/core/ReplacementManager.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <algorithm>
#include <memory>

namespace dandan::core
{
    void ReplacementManager::subscribe(
        const effects::IReplacementEffect *effect)
    {
        m_replacement_effects.emplace_back(effect);
    }

    void ReplacementManager::unsubscribe(
        const effects::IReplacementEffect *effect)
    {
        m_replacement_effects.erase(std::remove(m_replacement_effects.begin(),
                                                m_replacement_effects.end(),
                                                effect),
                                    m_replacement_effects.end());
    }

    std::unique_ptr<effects::IOneShotEffect> ReplacementManager::
        applyReplacementEffects(effects::IOneShotEffect &effect,
                                [[maybe_unused]] Game &game) const
    {
        effects::IOneShotEffect *current_effect{&effect};
        for (const auto *replacement_effect : m_replacement_effects)
        {
            if (replacement_effect->appliesTo(*current_effect))
            {
                current_effect = &replacement_effect->replace(*current_effect);
            }
        }
        // TODO: clone doesnt clone the next chain, so we need to make sure to
        // clone the entire chain
        return current_effect->clone();
    }
} // namespace dandan::core