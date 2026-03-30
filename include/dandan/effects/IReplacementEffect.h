#ifndef IREPLACEMENTEFFECT_H
#define IREPLACEMENTEFFECT_H

#include "dandan/events/IEvent.h"
#include <memory>
#include <nlohmann/json_fwd.hpp>

namespace dandan::effects
{
    // TODO: implement a singular base effect interface/ abstract class
    class IReplacementEffect
    {
    public:
        virtual std::unique_ptr<events::IEvent> replace(events::IEvent &event) = 0;
        virtual ~IReplacementEffect() = default;

        virtual void from_json(const nlohmann::json &j, IReplacementEffect &effect) = 0;
        virtual void to_json(nlohmann::json &j, const IReplacementEffect &effect) = 0;
    };

}
#endif