#include "dandan/costs/ManaCost.h"
#include <iostream>

namespace dandan::costs
{
    void ManaCost::evaluate()
    {
        // This is a placeholder implementation. In a real implementation, this
        // would check if the player has enough mana to pay the cost and then
        // deduct that mana from the player's mana pool.
        // For now, we'll just print out the mana cost for demonstration.
        auto mana = m_mana->getMana();
        for (const auto &[mana_type, amount] : mana)
        {
            std::string_view type_str{};
            switch (mana_type)
            {
            case mana::ManaType::COLORLESS:
                type_str = "Colorless";
                break;
            case mana::ManaType::WHITE:
                type_str = "White";
                break;
            case mana::ManaType::BLUE:
                type_str = "Blue";
                break;
            case mana::ManaType::BLACK:
                type_str = "Black";
                break;
            case mana::ManaType::RED:
                type_str = "Red";
                break;
            case mana::ManaType::GREEN:
                type_str = "Green";
                break;
            case mana::ManaType::GENERIC:
                type_str = "Generic";
                break;
            default:
                type_str = "Unknown";
                break;
            }
            std::cout << amount << " " << type_str << " mana\n";
        }
    }
} // namespace dandan::costs