#ifndef TRIGGEREDABILITY_H
#define TRIGGEREDABILITY_H

#include "IAbility.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/triggers/ITrigger.h"
#include <memory>

namespace dandan::abilities
{

    class TriggeredAbility final : public IAbility
    {
    public:
        TriggeredAbility(
            std::unique_ptr<dandan::triggers::ITrigger> trigger,
            std::unique_ptr<dandan::effects::IOneShotEffect> effect)
            : m_trigger(std::move(trigger)), m_effect(std::move(effect))
        {
        }

        [[nodiscard]] bool appliesToEvent(
            const events::IEvent &event) const override
        {
            return m_trigger->triggersOn(event);
        }

        [[nodiscard]] const dandan::triggers::ITrigger *getTrigger() const
        {
            return m_trigger.get();
        }
        [[nodiscard]] const dandan::effects::IOneShotEffect *getEffect() const
        {
            return m_effect.get();
        }

        void resolve(core::Game &game) const override;

    private:
        std::unique_ptr<dandan::triggers::ITrigger> m_trigger;
        std::unique_ptr<dandan::effects::IOneShotEffect> m_effect;
    };
} // namespace dandan::abilities

#endif