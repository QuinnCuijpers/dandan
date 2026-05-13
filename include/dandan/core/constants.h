#ifndef DANDAN_CONSTANTS_H
#define DANDAN_CONSTANTS_H

#include <array>
#include <string>

namespace dandan::core
{
    const static int AMOUNT_PLAYERS{2};

    const static std::array<std::string, AMOUNT_PLAYERS> DEFAULT_NAMES{
        std::array<std::string, AMOUNT_PLAYERS>{"Player 1", "Player 2"}};

    const static int CLEAR_SCREEN_LINES{10};
} // namespace dandan::core

#endif // DANDAN_CONSTANTS_H