#ifndef DANDAN_DRAWEFFECT_H
#define DANDAN_DRAWEFFECT_H

#include "IOneShotEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>

namespace dandan::effects
{
    struct DrawEffect final : public IOneShotEffect
    {
    public:
        int m_amount{1};

        DrawEffect() = default;
        explicit DrawEffect(int amount) : m_amount(amount)
        {
        }

        std::unique_ptr<events::IEvent> apply(core::Game &game) const override;
    };

} // namespace dandan::effects

#endif