#include "dandan/effects/one_shot/PeekEffect.h"
#include "dandan/core/Game.h"
#include <iostream>

namespace dandan::effects
{

    std::unique_ptr<events::IEvent> PeekEffect::apply(
        [[maybe_unused]] core::Game &game) const
    {
        std::cout << "Applying PeekEffect: peeking at the top " << m_peek_amount
                  << " cards of the library\n";
        auto cards{game.library().peek(m_peek_amount)};
        std::cout << "Peeked cards: [ ";
        for (const auto &card : cards)
        {
            auto *cardp{game.getCardByID(card)};
            std::cout << cardp->getData().getName() << ", ";
        }
        std::cout << " ]\n";
        return nullptr;
    }

} // namespace dandan::effects