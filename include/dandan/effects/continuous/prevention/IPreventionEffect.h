#ifndef DANDAN_IPREVENTION_EFFECT_H
#define DANDAN_IPREVENTION_EFFECT_H

#include "../IContinuousEffect.h"
#include "dandan/core/actions/IAction.h"

namespace dandan::core
{
    class Game;
}

namespace dandan::effects
{
    class IPreventionEffect : public IContinuousEffect
    {
    public:
        IPreventionEffect() = default;

        virtual bool prevents(const core::IAction &action,
                              const core::Game &game) = 0;
    };

} // namespace dandan::effects

#endif // DANDAN_IPREVENTION_EFFECT_H