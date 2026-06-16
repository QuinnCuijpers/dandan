#include "dandan/dandan.h"
#include "dandan/log.h"

#include <iostream>

#ifdef DANDAN_SERIALIZE
#include <filesystem>
#include <nlohmann/json.hpp>
#endif

int main()
{
#ifdef DANDAN_ENABLE_LOGGING
    dandan::initLogging(dandan::DANDAN_LOG_FILE_PATH.string());
    DLOGI << "Application started";
#endif

#ifdef DANDAN_SERIALIZE
    // check_card_serialize();
    auto game = dandan::Game{};
    game.run();
#endif
    std::cout << "Hello, Dandan!\n";
}