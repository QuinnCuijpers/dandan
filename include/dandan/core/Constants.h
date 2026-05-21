#ifndef DANDAN_CONSTANTS_H
#define DANDAN_CONSTANTS_H

#include <array>
#include <filesystem>
#include <string>

namespace dandan::core
{
    const static int AMOUNT_PLAYERS{2};

    const static std::array<std::string, AMOUNT_PLAYERS> DEFAULT_NAMES{
        std::array<std::string, AMOUNT_PLAYERS>{"Player 1", "Player 2"}};

    const static int CLEAR_SCREEN_LINES{10};

    const static auto DANDAN_DECKLIST =
        std::filesystem::path(DANDAN_PROJECT_SOURCE) / "data/temp_decklist.txt";
} // namespace dandan::core

#endif // DANDAN_CONSTANTS_H