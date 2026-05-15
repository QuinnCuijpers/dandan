#include "dandan/core/CardData.h"
#include <gtest/gtest.h>

TEST(DeserializeTest, NonExistantFile)
{
    const auto *card_name = "NonExistantCard";
    std::ostringstream buffer;
    auto *old = std::cerr.rdbuf(buffer.rdbuf());
    dandan::core::CardData card_data(card_name);

    std::string output = buffer.str();
    std::cerr.rdbuf(old);
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output, "Failed to open JSON file for card: " +
                          std::string(card_name) + "\n");
}