#ifndef TRIGGEREDABILITY_H
#define TRIGGEREDABILITY_H

#include "IAbility.h"
#include "dandan/effects/IEffect.h"
#include "dandan/events/IEvent.h"

namespace dandan::abilities
{

    class TriggeredAbility final : public IAbility
    {
    public:
        TriggeredAbility(std::unique_ptr<dandan::events::IEvent> on,
                         std::unique_ptr<dandan::effects::IEffect> effect)
            : m_on(std::move(on)), m_effect(std::move(effect))
        {
        }

        const dandan::events::IEvent *getOnEvent() const
        {
            return m_on.get();
        }
        const dandan::effects::IEffect *getEffect() const
        {
            return m_effect.get();
        }

        void resolve() override;

    private:
        std::unique_ptr<dandan::events::IEvent> m_on;
        std::unique_ptr<dandan::effects::IEffect> m_effect;
    };
} // namespace dandan::abilities

#endif