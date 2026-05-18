#include "dandan/mana/BlueMana.h"
#include "dandan/triggers/NoIslandsTrigger.h"
#ifdef DANDAN_SERIALIZE
#include "common.h"
#include "dandan/abilities/StaticAbility.h"
#include "dandan/conditions/ControlsIslandCondition.h"
#include "dandan/dandan.h"
#include "dandan/effects/continuous/prevention/AttackPreventionEffect.h"
#include "dandan/effects/one_shot/SelfSacrificeEffect.h"
#include "gtest/gtest.h"
#include <memory>
#include <string>
#include <vector>

#define CREATURE(name)                                                         \
    dandan::core::Card                                                         \
    {                                                                          \
        new dandan::CardData                                                   \
        {                                                                      \
            formatCardName(#name),                                             \
                std::make_unique<dandan::mana::BlueMana>(2),                   \
                dandan::core::CardData::Type::Creature,                        \
                dandan::core::CardData::SubType::Fish, name##_Abilities(),     \
                dandan::core::Stats{4, 1}                                      \
        }                                                                      \
    }

static std::vector<std::unique_ptr<dandan::IAbility>> Dandan_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(std::make_unique<dandan::TriggeredAbility>(
        std::make_unique<dandan::triggers::NoIslandsTrigger>(),
        std::make_unique<dandan::effects::SelfSacrificeEffect>()));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Type::Prevention,
        std::make_unique<dandan::effects::AttackPreventionEffect>(
            std::make_unique<dandan::conditions::ControlsIslandCondition>())));
    return abilities;
}

static const std::vector<const dandan::Card *> &getCards()
{
    static const std::vector<const dandan::Card *> cards = {
        new CREATURE(Dandan)};
    return cards;
};

INSTANTIATE_TEST_SUITE_P(CreatureTests, DeserializeTest,
                         testing::ValuesIn(getCards()), CardParamName);

#endif