#ifndef DANDAN_TESTS_SERIALIZATION_COMMON_H
#define DANDAN_TESTS_SERIALIZATION_COMMON_H

#ifdef DANDAN_SERIALIZE

#include "dandan/core/Card.h"
#include "gtest/gtest.h"
#include <nlohmann/json.hpp>

class DeserializeTest : public testing::TestWithParam<dandan::core::Card>
{

public:
    nlohmann::json m_expected;
    nlohmann::json m_received;

protected:
    void SetUp() override;
};

#endif

#endif
