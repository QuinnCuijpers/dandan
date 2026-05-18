#ifndef DANDAN_UNTAPEFFECT_H
#define DANDAN_UNTAPEFFECT_H

#include "dandan/core/Card.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/events/IEvent.h"
#include "dandan/events/UntapEvent.h"
#include <memory>

namespace dandan::effects
{
    class UntapEffect : public IOneShotEffect
    {
    public:
        explicit UntapEffect(core::Card &card) : m_card{card}
        {
        }

        std::unique_ptr<events::IEvent> apply(
            [[maybe_unused]] core::Game &game) const override
        {
            DLOGI << "Untapping " << m_card.getData().getName() << "with ID "
                  << m_card.getID().getID() << "\n";
            m_card.setTapped(false);
            return std::make_unique<events::UntapEvent>(m_card);
        }

    private:
        core::Card &m_card;
    };
} // namespace dandan::effects

#endif