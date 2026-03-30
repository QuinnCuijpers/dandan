#ifndef REPLACEMENTABILITY_H
#define REPLACEMENTABILITY_H

#include "IAbility.h"
#include "dandan/events/IEvent.h"
#include "dandan/effects/IReplacementEffect.h"
#include <functional>
#include <memory>

namespace dandan::abilities
{

    class ReplacementAbility : public IAbility
    {
    public:
        ReplacementAbility() = default;
        ReplacementAbility(std::unique_ptr<dandan::events::IEvent> event, std::unique_ptr<dandan::effects::IReplacementEffect> replace_effect)
            : m_event(std::move(event)), m_replace_effect(std::move(replace_effect)) {}

        void resolve() override;

        void from_json(const nlohmann::json &j, IAbility &ability) override;

        void to_json(nlohmann::json &j, const IAbility &ability) override;

    private:
        std::unique_ptr<dandan::events::IEvent> m_event;
        std::unique_ptr<dandan::effects::IReplacementEffect> m_replace_effect;
    };
}

#endif