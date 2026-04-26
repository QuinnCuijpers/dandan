#ifdef DANDAN_BUILD_SERIALIZE
#include "common.h"

TEST_P(DeserializeTest, DeserializeCorrect)
{
    EXPECT_EQ(m_received, m_expected);
}
#endif
