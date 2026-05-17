#include <gtest/gtest.h>
#ifdef DANDAN_SERIALIZE
#include "common.h"

TEST_P(DeserializeTest, DeserializeCorrect)
{
    EXPECT_EQ(m_received, m_expected);
}

#endif
