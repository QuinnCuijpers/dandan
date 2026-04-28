#ifndef DANDAN_PREVENTION_MANAGER_H
#define DANDAN_PREVENTION_MANAGER_H

#include "dandan/core/Actions.h"
#include "dandan/effects/continuous/prevention/IPreventionEffect.h"
#include <vector>

namespace dandan::core
{
    class PreventionManager
    {
    public:
        void subscribe(const effects::IPreventionEffect *effect);
        void unsubscribe(const effects::IPreventionEffect *effect);

        // TODO: update to take an IAction instead of ActionType, to allow for
        // more complex prevention logic
        [[nodiscard]] bool isPrevented(actions::ActionType) const;

    private:
        std::vector<effects::IPreventionEffect *> m_prevention_effects;
    };
} // namespace dandan::core

#endif