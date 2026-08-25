#include <gtest/gtest.h>

#ifdef DANDAN_SERIALIZE
#include "dandan/abilities/IAbility.h"
#include "dandan/core/CardData.h"

TEST(CardDataTest, NonExistantFile)
{
    const auto *card_name = "NonExistantCard";
    std::ostringstream buffer;
    auto *old = std::cerr.rdbuf(buffer.rdbuf());
    auto card_data(dandan::core::getCardData(card_name));

    EXPECT_FALSE(card_data.has_value());

    std::string output = buffer.str();
    std::cerr.rdbuf(old);
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output, "Failed to open JSON file for card: " +
                          std::string(card_name) + "\n");
}
#endif
