#include "dandan/core/Constants.h"
#include "dandan/dandan.h"
#include "dandan/utils/log.h"

#include <iostream>

#ifdef DANDAN_SERIALIZE
#include <filesystem>
#include <nlohmann/json.hpp>
#endif

int main()
{
#ifdef DANDAN_ENABLE_LOGGING
    dandan::log::initLogging(dandan::log::DANDAN_LOG_FILE_PATH.string());
    DLOGI << "Application started";
#endif

#ifdef DANDAN_SERIALIZE
    auto game = dandan::Game{dandan::core::DANDAN_DECKLIST};
    game.run();
#endif
    std::cout << "Hello, Dandan!\n";
}
