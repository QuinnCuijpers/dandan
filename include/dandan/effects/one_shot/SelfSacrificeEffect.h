#ifndef DANDAN_SELFSACRIFICEEFFECT_H
#define DANDAN_SELFSACRIFICEEFFECT_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>

namespace dandan::effects
{
    class SelfSacrificeEffect : public IOneShotEffect
    {
    public:
        void apply() override
        {
            std::cout << "Resolving SelfSacrificeEffect: Sacrificing the "
                         "source card.\n";
        }
    };
} // namespace dandan::effects

#endif