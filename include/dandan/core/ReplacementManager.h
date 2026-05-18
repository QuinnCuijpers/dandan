

#include "dandan/effects/continuous/replacement/IReplacementEffect.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <vector>

namespace dandan::core
{
    // TODO: consider implementing this as a map of cardID's like the event
    // manager
    class ReplacementManager
    {
    public:
        void subscribe(const effects::IReplacementEffect *effect);
        void unsubscribe(const effects::IReplacementEffect *effect);

        const effects::IOneShotEffect &applyReplacementEffects(
            effects::IOneShotEffect &effect, Game &game) const;

    private:
        std::vector<const effects::IReplacementEffect *> m_replacement_effects;
    };
} // namespace dandan::core
