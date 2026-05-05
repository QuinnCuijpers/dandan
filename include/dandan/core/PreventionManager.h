#ifndef DANDAN_PREVENTION_MANAGER_H
#define DANDAN_PREVENTION_MANAGER_H

#include "dandan/core/actions/IAction.h"
#include "dandan/effects/continuous/prevention/IPreventionEffect.h"
#include <memory>
#include <vector>

namespace dandan::core
{
    class PreventionManager
    {
    public:
        void subscribe(std::unique_ptr<effects::IPreventionEffect> effect);
        void unsubscribe(const effects::IPreventionEffect *effect);

        [[nodiscard]] bool isPrevented(const IAction &action,
                                       const Game &game) const;

    private:
        std::vector<std::unique_ptr<effects::IPreventionEffect>>
            m_prevention_effects;
    };
} // namespace dandan::core

#endif