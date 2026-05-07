#include "dandan/effects/one_shot/DrawEffect.h"

#include <iostream>

namespace dandan::effects
{

    std::unique_ptr<events::IEvent> DrawEffect::apply(
        [[maybe_unused]] core::Game &game)
    {
        std::cout << "Applying draw effect\n";
        return nullptr;
    }

} // namespace dandan::effects