#ifndef DANDAN_REPLACEMENTMANAGER_H
#define DANDAN_REPLACEMENTMANAGER_H

#include "dandan/abilities/BoundAbility.h"
#include "dandan/core/Card.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <vector>

namespace dandan::core
{

    /** @brief The class that manages replacement effects.
     * @class ReplacementManager
     */
    class ReplacementManager
    {
    public:
        /** Subscribes to replacement effects.
         * @param ability The bound ability providing the replacement effect.
         */
        void subscribe(abilities::BoundAbility &ability);

        /** Unsubscribes from replacement effects.
         * @param card The card whose replacement effects to unsubscribe.
         */
        void unsubscribe(Card &card);

        void unsubscribe(const abilities::BoundAbility &ability);

        [[nodiscard]] std::size_t size() const;

        /** Applies all active replacement effects to the given effect.
         * @param effect The effect to apply replacement effects to.
         * @param exec_ctx The execution context.
         * @return The modified effect.
         */
        std::unique_ptr<effects::IOneShotEffect> applyReplacementEffects(
            effects::IOneShotEffect &effect, ExecutionContext exec_ctx) const;

    private:
        std::vector<abilities::BoundAbility *> m_replacement_effects;
    };
} // namespace dandan::core

#endif
