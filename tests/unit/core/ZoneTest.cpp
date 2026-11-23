
#include "dandan/core/Zone.h"
#include <gtest/gtest.h>
#include <tuple>

using ZoneCase = std::tuple<dandan::core::Zone, std::string>;

class ZoneToStringTest : public testing::TestWithParam<ZoneCase>
{
};

TEST_P(ZoneToStringTest, ReturnsExpectedString)
{
    const auto &[zone, expected] = GetParam();
    EXPECT_EQ(dandan::core::zoneToString(zone), expected);
}

INSTANTIATE_TEST_SUITE_P(
    AllZones, ZoneToStringTest,
    testing::Values(ZoneCase{dandan::core::Zone::LIBRARY, "Library"},
                    ZoneCase{dandan::core::Zone::HAND, "Hand"},
                    ZoneCase{dandan::core::Zone::BATTLEFIELD, "Battlefield"},
                    ZoneCase{dandan::core::Zone::GRAVEYARD, "Graveyard"},
                    ZoneCase{dandan::core::Zone::EXILE, "Exile"},
                    ZoneCase{dandan::core::Zone::STACK, "Stack"}));

TEST(ZoneTest, UnknownZoneReturnsDefault)
{
    const auto unknown_zone{static_cast<dandan::core::Zone>(255)};
    EXPECT_EQ(dandan::core::zoneToString(unknown_zone), "Unknown Zone");
}
