#ifndef DANDAN_BOUNCELANDEFFECT_H
#define DANDAN_BOUNCELANDEFFECT_H

#include "IOneShotEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>

namespace dandan::effects
{
    /** Represents bouncing a land you control back to your hand
     * @class BounceLandEffect
     *
     * @implements IOneShotEffect
     */
    class BounceLandEffect : public IOneShotEffect
    {
    public:
        [[nodiscard]] std::unique_ptr<IOneShotEffect> clone() const override
        {
            return std::make_unique<BounceLandEffect>();
        }

        std::unique_ptr<events::IEvent> apply(core::Game &game) const override;
    };
} // namespace dandan::effects

#endif // DANDAN_BOUNCELANDEFFECT_H