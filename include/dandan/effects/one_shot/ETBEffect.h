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

        [[nodiscard]] std::unique_ptr<IOneShotEffect> clone() const override
        {
            auto cloned_effect = std::make_unique<ETBEffect>(m_card);
            cloned_effect->setTapped(m_tapped);
            return cloned_effect;
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