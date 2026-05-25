#ifndef DANDAN_PREVENTION_MANAGER_H
#define DANDAN_PREVENTION_MANAGER_H

#include "dandan/core/actions/IAction.h"
#include "dandan/effects/continuous/prevention/IPreventionEffect.h"
#include <memory>
#include <vector>

namespace dandan::core
{
    /** The class that manages prevention effects.
     * @class PreventionManager
     */
    class PreventionManager
    {
    public:
        /** Subscribe a prevention effect.
         * @param effect The prevention effect to subscribe.
         */
        void subscribe(std::unique_ptr<effects::IPreventionEffect> effect);

        /** Unsubscribe the prevention effect.
         * @param effect The prevention effect to unsubscribe.
         */
        void unsubscribe(const effects::IPreventionEffect *effect);

        /** Check if an action is prevented.
         * @param action The action to check.
         * @param game The game instance.
         * @return True if the action is prevented by a prevention effect, false
         * otherwise.
         */
        [[nodiscard]] bool isPrevented(const IAction &action,
                                       const Game &game) const;

    private:
        std::vector<std::unique_ptr<effects::IPreventionEffect>>
            m_prevention_effects;
    };
} // namespace dandan::core

#endif