#ifndef DANDAN_ENTERSTAPPEDEFFECT_H
#define DANDAN_ENTERSTAPPEDEFFECT_H

#include "IReplacementEffect.h"
#include "dandan/events/IEvent.h"

namespace dandan::effects
{
    class EntersTappedEffect : public IReplacementEffect
    {
    public:
        std::unique_ptr<dandan::events::IEvent> replace(dandan::events::IEvent &event) override;

        void from_json(const nlohmann::json &j, IReplacementEffect &effect) override;

        void to_json(nlohmann::json &j, const IReplacementEffect &effect) override;
    };
}

#endif