#ifndef DANDAN_H
#define DANDAN_H
#include "dandan/core/Card.h"
#include "dandan/abilities/WithDamage.h"
#include "dandan/abilities/ManaAbility.h"
#include "dandan/abilities/ReplacementAbility.h"
#include "dandan/abilities/TriggeredAbility.h"
#include "dandan/abilities/IAbility.h"
#include "dandan/events/EntersBattleFieldEvent.h"
#include "dandan/effects/EntersTappedEffect.h"

namespace dandan
{
    using abilities::IAbility;
    using abilities::ManaAbility;
    using abilities::ReplacementAbility;

    using core::Card;

    using effects::EntersTappedEffect;
    using effects::IReplacementEffect;

    using events::EntersBattlefieldEvent;
    using events::IEvent;
}

#endif