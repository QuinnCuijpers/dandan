#include "dandan/costs/ColoredManaCost.h"
#include <iostream>

namespace dandan::costs
{

    void ColoredManaCost::evaluate()
    {
        // Placeholder implementation
        std::cout << "Evaluating ColoredManaCost of color: " << m_color << '\n';
    }

    ColoredManaCost::ManaColor ColoredManaCost::ManaColorFromString(
        const std::string &colorStr)
    {
        if (colorStr == "WHITE")
        {
            return WHITE;
        }
        else if (colorStr == "BLUE")
        {
            return BLUE;
        }
        else if (colorStr == "BLACK")
        {
            return BLACK;
        }
        else if (colorStr == "RED")
        {
            return RED;
        }
        else if (colorStr == "GREEN")
        {
            return GREEN;
        }
        else
        {
            throw std::runtime_error("Invalid mana color string: " + colorStr);
        }
    }

    std::string ColoredManaCost::ManaColorToString(ManaColor color)
    {
        switch (color)
        {
        case WHITE:
            return "WHITE";
        case BLUE:
            return "BLUE";
        case BLACK:
            return "BLACK";
        case RED:
            return "RED";
        case GREEN:
            return "GREEN";
        default:
            throw std::runtime_error("Invalid mana color enum value");
        }
    }

} // namespace dandan::costs