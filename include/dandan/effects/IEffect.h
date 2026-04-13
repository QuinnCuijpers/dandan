#ifndef DANDAN_I_EFFECT_H
#define DANDAN_I_EFFECT_H

#include <nlohmann/json_fwd.hpp>

namespace dandan::effects
{
    // TODO: change `apply` to take in a `GameState` object and modify it
    // instead of just printing something to the console
    class IEffect
    {
    public:
        virtual ~IEffect() = default;
        virtual void apply() = 0;
    };

} // namespace dandan::effects

#endif