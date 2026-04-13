#ifndef IREPLACEMENTEFFECT_H
#define IREPLACEMENTEFFECT_H

#include "dandan/effects/IEffect.h"
#include <nlohmann/json_fwd.hpp>

namespace dandan::replacement_effects
{
    class IReplacementEffect
    {
    public:
        virtual effects::IEffect &replace(effects::IEffect &effect) = 0;
        virtual ~IReplacementEffect() = default;
    };

} // namespace dandan::replacement_effects
#endif