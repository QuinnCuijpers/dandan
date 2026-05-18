#ifndef DANDAN_ETBEFFECT_H
#define DANDAN_ETBEFFECT_H

#include "dandan/core/Card.h"
#include "dandan/effects//one_shot/IOneShotEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>
namespace dandan::effects
{
    class ETBEffect : public IOneShotEffect
    {
    public:
        explicit ETBEffect(core::Card &card) : m_card{card}
        {
        }

        std::unique_ptr<events::IEvent> apply(core::Game &game) const override;

        void setTapped(bool tapped)
        {
            m_tapped = tapped;
        }

    private:
        core::Card &m_card;
        bool m_tapped{false};
    };
} // namespace dandan::effects

#endif