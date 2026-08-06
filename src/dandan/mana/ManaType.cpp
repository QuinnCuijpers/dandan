#include "dandan/mana/ManaType.h"
#include <stdexcept>

namespace dandan::mana
{

    ManaType ManaTypeFromString(std::string_view str)
    {
        // TODO: allow any casing
        if (str == "Colorless")
        {
            return ManaType::COLORLESS;
        }
        if (str == "White")
        {
            return ManaType::WHITE;
        }
        if (str == "Blue")
        {
            return ManaType::BLUE;
        }
        if (str == "Black")
        {
            return ManaType::BLACK;
        }
        if (str == "Red")
        {
            return ManaType::RED;
        }
        if (str == "Green")
        {
            return ManaType::GREEN;
        }
        if (str == "Generic")
        {
            return ManaType::GENERIC;
        }
        throw std::invalid_argument(std::string("Invalid mana type string: ") +
                                    std::string(str));
    }

} // namespace dandan::mana
