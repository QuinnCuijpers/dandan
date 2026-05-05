#include "dandan/core/PreventionManager.h"
#include "dandan/core/Game.h"
#include <algorithm>
#include <memory>

namespace dandan::core
{
    void PreventionManager::subscribe(
        std::unique_ptr<effects::IPreventionEffect> effect)
    {
        m_prevention_effects.push_back(std::move(effect));
    }

    void PreventionManager::unsubscribe(
        const effects::IPreventionEffect *effect)
    {
        m_prevention_effects.erase(
            std::remove_if(
                m_prevention_effects.begin(), m_prevention_effects.end(),
                [effect](const std::unique_ptr<effects::IPreventionEffect>
                             &candidate) { return candidate.get() == effect; }),
            m_prevention_effects.end());
    }

    bool PreventionManager::isPrevented(const IAction &action,
                                        const Game &game) const
    {
        return std::any_of(
            m_prevention_effects.begin(), m_prevention_effects.end(),
            [&action, &game](
                const std::unique_ptr<effects::IPreventionEffect> &candidate)
            { return candidate->prevents(action, game); });
    }
} // namespace dandan::core