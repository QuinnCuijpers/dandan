#ifndef DANDAN_I_TRIGGERED_EFFECT_H
#define DANDAN_I_TRIGGERED_EFFECT_H

#include <nlohmann/json_fwd.hpp>

namespace dandan::effects
{
    class ITriggeredEffect
    {
    public:
        virtual void apply() = 0;
        virtual ~ITriggeredEffect() = default;
        virtual void from_json(const nlohmann::json &j, ITriggeredEffect &effect) = 0;
        virtual void to_json(nlohmann::json &j, const ITriggeredEffect &effect) = 0;
    };
}

#endif