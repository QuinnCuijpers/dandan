#include "dandan/log.h"
#include <filesystem>

#ifdef DANDAN_ENABLE_LOGGING
#include "plog/Initializers/RollingFileInitializer.h"
#include <plog/Log.h>

static const std::filesystem::path LOG_FILE_PATH =
    std::filesystem::path{DANDAN_PROJECT_SOURCE} / "logs/dandan.log";
namespace dandan
{
    void initLogging()
    {
        plog::init(plog::info, LOG_FILE_PATH.string().c_str());
    }
} // namespace dandan
#endif // DANDAN_ENABLE_LOGGING