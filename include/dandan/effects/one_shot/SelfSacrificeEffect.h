#ifndef DANDAN_SELFSACRIFICEEFFECT_H
#define DANDAN_SELFSACRIFICEEFFECT_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>

namespace dandan::effects
{
    class SelfSacrificeEffect : public IOneShotEffect
    {
    public:
        [[nodiscard]] std::unique_ptr<IOneShotEffect> clone() const override
        {
            return std::make_unique<SelfSacrificeEffect>();
        }

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