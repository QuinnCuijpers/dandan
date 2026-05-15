#include "dandan/log.h"

#ifdef DANDAN_ENABLE_LOGGING
#include "plog/Initializers/RollingFileInitializer.h"
#include <plog/Log.h>

static const int MAX_FILE_SIZE{1000000}; // 1 MB
static const int MAX_FILES{3};           // Keep up to 3 log files
namespace dandan
{
    void initLogging(const std::string &path)
    {
        plog::init(plog::info, path.c_str(), MAX_FILE_SIZE, MAX_FILES);
    }
} // namespace dandan
#endif // DANDAN_ENABLE_LOGGING