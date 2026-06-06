#include "SpellDefinitions.h"
#include "dandan/dandan.h"
#include <gtest/gtest.h>

TEST(SpellAbilityCreateEffectTest, CreatesEffectChain)
{
    dandan::Game game;
    auto abilities{Brainstorm_Abilities()};
    auto *spell_ability{abilities[0].get()};
    auto effect{spell_ability->createEffect(
        game, dandan::abilities::AbilityContext{
                  dandan::core::CardID::fromInt(1),
                  dandan::core::PlayerID::getInvalidID()})};
    auto next_effect{effect->getNext()};

    std::cout << "Root effect: " << effect->display() << '\n';
    std::cout << "Next effect: " << next_effect.value()->display() << '\n';

    EXPECT_TRUE(effect != nullptr);
    EXPECT_TRUE(next_effect != std::nullopt);
    EXPECT_TRUE(next_effect.value() != nullptr);
    EXPECT_TRUE(next_effect.value()->getNext() == std::nullopt);
}