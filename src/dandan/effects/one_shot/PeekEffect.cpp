#include "dandan/effects/one_shot/PeekEffect.h"
#include "dandan/core/Game.h"
#include <iostream>

namespace dandan::effects
{

    void PeekEffect::apply([[maybe_unused]] core::Game &game)
    {
        std::cout << "Applying PeekEffect: peeking at the top " << m_peek_amount
                  << " cards of the library\n";
    }

} // namespace dandan::effects