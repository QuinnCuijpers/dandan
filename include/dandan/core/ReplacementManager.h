

#include "dandan/effects/continuous/replacement/IReplacementEffect.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <vector>

namespace dandan::core
{
    // TODO: consider implementing this as a map of cardID's like the event
    // manager

    /** The class that manages replacement effects.
     * @class ReplacementManager
     */
    class ReplacementManager
    {
    public:
        /** Subscribes to replacement effects.
         * @param effect The replacement effect to subscribe to.
         */
        void subscribe(const effects::IReplacementEffect *effect);

        /** Unsubscribes from replacement effects.
         * @param effect The replacement effect to unsubscribe from.
         */
        void unsubscribe(const effects::IReplacementEffect *effect);

        /** Applies all active replacement effects to the given effect.
         * @param effect The effect to apply replacement effects to.
         * @param game The game instance.
         * @return The modified effect.
         */
        const effects::IOneShotEffect &applyReplacementEffects(
            effects::IOneShotEffect &effect, Game &game) const;

    private:
        std::vector<const effects::IReplacementEffect *> m_replacement_effects;
    };
} // namespace dandan::core
