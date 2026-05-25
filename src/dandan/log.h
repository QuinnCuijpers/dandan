#ifndef DANDAN_LOG_H
#define DANDAN_LOG_H

#ifdef DANDAN_ENABLE_LOGGING
#include <filesystem>
#include <plog/Log.h>

#define DLOGI PLOGI
#define DLOGD PLOGD
#define DLOGW PLOGW
#define DLOGE PLOGE
#define DLOGF PLOGF

namespace dandan
{

    const std::filesystem::path DANDAN_LOG_FILE_PATH =
        std::filesystem::path{DANDAN_PROJECT_SOURCE} / "logs/dandan.log";
    void initLogging(const std::string &path);
} // namespace dandan

#else

namespace dandan::log
{
    /** A stream that discards all output.
     * @class NullStream
     */
    struct NullStream
    {
        template <typename T>
        /** A function that discards all output.
         * @return A reference to the null stream.
         */
        constexpr const NullStream &operator<<(
            const T & /*unused*/) const noexcept
        {
            return *this;
        }
    };

    inline constexpr NullStream nullLogStream{};
} // namespace dandan::log

#define DLOGI (::dandan::log::nullLogStream)
#define DLOGD (::dandan::log::nullLogStream)
#define DLOGW (::dandan::log::nullLogStream)
#define DLOGE (::dandan::log::nullLogStream)
#define DLOGF (::dandan::log::nullLogStream)

#endif // DANDAN_ENABLE_LOGGING

#endif // DANDAN_LOG_H