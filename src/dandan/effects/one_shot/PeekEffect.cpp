#include "dandan/effects/one_shot/PeekEffect.h"
#include "dandan/core/Game.h"
#include <iostream>

namespace dandan::effects
{

    std::unique_ptr<events::IEvent> PeekEffect::apply(
        [[maybe_unused]] core::Game &game)
    {
        std::cout << "Applying PeekEffect: peeking at the top " << m_peek_amount
                  << " cards of the library\n";
        game.deck().peek(3);
        return nullptr;
    }

} // namespace dandan::effects