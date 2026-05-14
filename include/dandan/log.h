#ifndef DANDAN_LOG_H
#define DANDAN_LOG_H

#ifdef DANDAN_ENABLE_LOGGING
#include <plog/Log.h>

// NOLINTNEXTLINE
#define DLOGI PLOGI
// NOLINTNEXTLINE
#define DLOGD PLOGD
// NOLINTNEXTLINE
#define DLOGW PLOGW
// NOLINTNEXTLINE
#define DLOGE PLOGE
// NOLINTNEXTLINE
#define DLOGF PLOGF

namespace dandan
{
    void initLogging();
} // namespace dandan

#else

#include <ostream>

namespace dandan::log
{
    struct NullStream
    {
        template <typename T>
        constexpr const NullStream &operator<<(const T &) const noexcept
        {
            return *this;
        }

        constexpr const NullStream &operator<<(
            std::ostream &(*)(std::ostream &)) const noexcept
        {
            return *this;
        }

        constexpr const NullStream &operator<<(
            std::ios_base &(*)(std::ios_base &)) const noexcept
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