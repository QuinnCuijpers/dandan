#include "DeserializeTest.h"
#include "SpellDefinitions.h"
#include "common.h"
#include "dandan/dandan.h"
#include "dandan/mana/AndMana.h"
#include <gtest/gtest.h>
#include <memory>

static const std::vector<const dandan::Card *> &getCards()
{
    static const std::vector<const dandan::Card *> cards = {
        new SPELL(Brainstorm, std::make_unique<dandan::mana::BlueMana>(1),
                  Instant),
        new SPELL(Accumulated_Knowledge,
                  std::make_unique<dandan::mana::AndMana>(
                      std::make_unique<dandan::mana::GenericMana>(1),
                      std::make_unique<dandan::mana::BlueMana>(1)),
                  Instant),
        new SPELL(Diminishing_Returns,
                  std::make_unique<dandan::mana::AndMana>(
                      std::make_unique<dandan::mana::GenericMana>(2),
                      std::make_unique<dandan::mana::BlueMana>(2)),
                  Sorcery),
        new SPELL(Mystical_Tutor, std::make_unique<dandan::mana::BlueMana>(1),
                  Instant),
        new SPELL(Vision_Charm, std::make_unique<dandan::mana::BlueMana>(1),
                  Instant)};
    return cards;
};

INSTANTIATE_TEST_SUITE_P(
    SpellTests, DeserializeTest, testing::ValuesIn(getCards()),
    [](const ::testing::TestParamInfo<const dandan::Card *> &info)
    { return CardParamName(info.param->getData().getName()); });
