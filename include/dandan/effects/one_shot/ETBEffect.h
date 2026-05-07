#ifndef DANDAN_ETBEFFECT_H
#define DANDAN_ETBEFFECT_H

#include "dandan/effects//one_shot/IOneShotEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>
namespace dandan::effects
{
    struct ETBEffect final : public IOneShotEffect
    {
        std::unique_ptr<events::IEvent> apply(core::Game &game) override;

        void setTapped(bool tapped)
        {
            m_tapped = tapped;
        }

        bool m_tapped{false};
    };
} // namespace dandan::effects

#endif