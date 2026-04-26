#ifndef DANDAN_H
#define DANDAN_H

#include "dandan/abilities/ActivatedAbility.h"
#include "dandan/abilities/IAbility.h"
#include "dandan/abilities/ManaAbility.h"
#include "dandan/abilities/StaticAbility.h"
#include "dandan/abilities/TriggeredAbility.h"
#include "dandan/abilities/WithDamage.h"
#include "dandan/core/Card.h"
#include "dandan/core/Game.h"
#include "dandan/costs/CyclingCost.h"
#include "dandan/costs/ICost.h"
#include "dandan/costs/ManaCost.h"
#include "dandan/costs/SelfSacrificeCost.h"
#include "dandan/effects/continuous/replacement/EntersTappedEffect.h"
#include "dandan/effects/continuous/replacement/IReplacementEffect.h"
#include "dandan/effects/one_shot/BounceLandEffect.h"
#include "dandan/effects/one_shot/DrawEffect.h"
#include "dandan/effects/one_shot/ETBEffect.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/PeekEffect.h"
#include "dandan/effects/one_shot/ScryEffect.h"
#include "dandan/events/ETBEvent.h"
#include "dandan/mana/BlackMana.h"
#include "dandan/mana/BlueMana.h"
#include "dandan/mana/ColorlessMana.h"
#include "dandan/mana/GenericMana.h"
#include "dandan/mana/GreenMana.h"
#include "dandan/mana/ManaList.h"
#include "dandan/mana/RedMana.h"

namespace dandan
{
    using abilities::ActivatedAbility;
    using abilities::IAbility;
    using abilities::ManaAbility;
    using abilities::StaticAbility;
    using abilities::TriggeredAbility;
    using abilities::WithDamage;

    using core::Card;
    using core::Game;

    using effects::BounceLandEffect;
    using effects::DrawEffect;
    using effects::ETBEffect;
    using effects::IOneShotEffect;
    using effects::PeekEffect;
    using effects::ScryEffect;

    using effects::EntersTappedEffect;
    using effects::IReplacementEffect;

    using events::ETBEvent;
    using events::IEvent;

    using costs::CyclingCost;
    using costs::ICost;
    using costs::ManaCost;
    using costs::SelfSacrificeCost;
    using costs::TapCost;

    using mana::BlackMana;
    using mana::BlueMana;
    using mana::ColorlessMana;
    using mana::GenericMana;
    using mana::GreenMana;
    using mana::ManaList;
    using mana::RedMana;

} // namespace dandan

#endif