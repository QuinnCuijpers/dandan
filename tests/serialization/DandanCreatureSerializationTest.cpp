
#ifdef DANDAN_BUILD_SERIALIZE
#include "common.h"
#include "dandan/abilities/StaticAbility.h"
#include "dandan/conditions/ControlsIslandCondition.h"
#include "dandan/dandan.h"
#include "dandan/effects/continuous/prevention/AttackPreventionEffect.h"
#include "dandan/effects/one_shot/SelfSacrificeEffect.h"
#include "dandan/events/NoIslandsEvent.h"
#include "gtest/gtest.h"
#include <memory>
#include <string>
#include <vector>

#define CREATURE(name, subtype)                                                \
    dandan::Card                                                               \
    {                                                                          \
        formatCardName(#name), std::make_unique<dandan::mana::BlueMana>(2),    \
            dandan::Card::Creature, subtype, name##_Abilities(),               \
            dandan::Stats{4, 1}                                                \
    }

static std::vector<std::unique_ptr<dandan::IAbility>> Dandan_Abilities()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(std::make_unique<dandan::TriggeredAbility>(
        std::make_unique<dandan::events::NoIslandsEvent>(),
        std::make_unique<dandan::effects::SelfSacrificeEffect>()));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Prevention,
        std::make_unique<dandan::effects::AttackPreventionEffect>(
            std::make_unique<dandan::conditions::ControlsIslandCondition>())));
    return abilities;
}

static const std::vector<const dandan::Card *> &getCards()
{
    static const std::vector<const dandan::Card *> cards = {
        new CREATURE(Dandan, dandan::core::Card::Fish)};
    return cards;
};

INSTANTIATE_TEST_SUITE_P(CreatureTests, DeserializeTest,
                         testing::ValuesIn(getCards()), CardParamName);

#endif