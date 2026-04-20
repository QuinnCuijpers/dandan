#include "dandan/costs/SelfSacrificeCost.h"
#include <iostream>

namespace dandan::costs
{
    void SelfSacrificeCost::evaluate()
    {
        std::cout << "Evaluating self-sacrifice cost...\n";
        // In a real implementation, this would interact with the game state to
        // sacrifice the card.
        std::cout << "Card sacrificed as part of the cost.\n";
    }
} // namespace dandan::costs