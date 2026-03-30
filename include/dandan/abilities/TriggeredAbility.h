#ifndef TRIGGEREDABILITY_H
#define TRIGGEREDABILITY_H

#include "IAbility.h"
#include "dandan/effects/ITriggeredEffect.h"
#include "dandan/events/IEvent.h"

namespace dandan::abilities
{

    class TriggeredAbility : public IAbility
    {
    public:
        TriggeredAbility(std::unique_ptr<dandan::events::IEvent> on, std::unique_ptr<dandan::effects::ITriggeredEffect> effect)
            : m_on(std::move(on)), m_effect(std::move(effect)) {}

        void resolve() override;

        void from_json(const nlohmann::json &j, IAbility &ability) override;

        void to_json(nlohmann::json &j, const IAbility &ability) override;

    private:
        std::unique_ptr<dandan::events::IEvent> m_on;
        std::unique_ptr<dandan::effects::ITriggeredEffect> m_effect;
    };
}

#endif