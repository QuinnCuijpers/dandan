#ifndef TRIGGEREDABILITY_H
#define TRIGGEREDABILITY_H

#include "IAbility.h"
#include "dandan/events/IEvent.h"
#include "dandan/effects/IEffect.h"

namespace dandan::abilities
{

    class TriggeredAbility : public IAbility
    {
    public:
        TriggeredAbility(std::unique_ptr<dandan::events::IEvent> on, std::unique_ptr<dandan::effects::IEffect> effect)
            : m_on(std::move(on)), m_effect(std::move(effect)) {}

        void resolve() override;

    private:
        std::unique_ptr<dandan::events::IEvent> m_on;
        std::unique_ptr<dandan::effects::IEffect> m_effect;
    };
}

#endif