#ifndef DANDAN_I_EFFECT_H
#define DANDAN_I_EFFECT_H

#include <nlohmann/json_fwd.hpp>

namespace dandan::effects
{

    class IEffect
    {
    public:
        virtual ~IEffect() = default;
        virtual void apply() = 0;
    };

}

#endif