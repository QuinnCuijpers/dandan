#ifndef DANDAN_H
#define DANDAN_H
#include "dandan/core/Card.h"
#include "dandan/abilities/WithDamage.h"
#include "dandan/abilities/ManaAbility.h"
#include "dandan/abilities/ReplacementAbility.h"
#include "dandan/abilities/TriggeredAbility.h"
#include "dandan/abilities/IAbility.h"

namespace dandan
{
    using abilities::EntersBattlefieldEvent;
    using abilities::EntersTappedEffect;
    using abilities::IAbility;
    using abilities::IEvent;
    using abilities::IReplacementEffect;
    using abilities::ManaAbility;
    using abilities::ReplacementAbility;
    using core::Card;
}

#endif