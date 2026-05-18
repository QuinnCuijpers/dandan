#ifndef DANDAN_SELFSACRIFICEEFFECT_H
#define DANDAN_SELFSACRIFICEEFFECT_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>

namespace dandan::effects
{
    class SelfSacrificeEffect : public IOneShotEffect
    {
    public:
        std::unique_ptr<events::IEvent> apply(
            [[maybe_unused]] core::Game &game) const override
        {
            std::cout << "Resolving SelfSacrificeEffect: Sacrificing the "
                         "source card.\n";
            return nullptr;
        }
    };
} // namespace dandan::effects

#endif