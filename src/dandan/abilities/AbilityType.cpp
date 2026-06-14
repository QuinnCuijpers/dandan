#include "dandan/abilities/AbilityType.h"
#include "dandan/abilities/ActivatedAbility.h"
#include "dandan/abilities/BasicLandAbility.h"
#include "dandan/abilities/EventTriggeredAbility.h"
#include "dandan/abilities/IAbilityDecorator.h"
#include "dandan/abilities/ManaAbility.h"
#include "dandan/abilities/SpellAbility.h"
#include "dandan/abilities/StateTriggeredAbility.h"
#include "dandan/abilities/StaticAbility.h"
#include <stdexcept>

namespace dandan::abilities
{
    AbilityType AbilityType::from(const IAbility *ability)
    {
        if (dynamic_cast<const ActivatedAbility *>(ability) != nullptr)
        {
            return AbilityType{Activated};
        }
        if (dynamic_cast<const BasicLandAbility *>(ability) != nullptr)
        {
            return AbilityType{BasicLand};
        }

        if (dynamic_cast<const EventTriggeredAbility *>(ability) != nullptr)
        {
            return AbilityType{EventTriggered};
        }
        if (dynamic_cast<const ManaAbility *>(ability) != nullptr)
        {
            return AbilityType{Mana};
        }

        if (dynamic_cast<const SpellAbility *>(ability) != nullptr)
        {
            return AbilityType{Spell};
        }

        if (dynamic_cast<const StateTriggeredAbility *>(ability) != nullptr)
        {
            return AbilityType{StateTriggered};
        }

        if (const auto *static_ability =
                dynamic_cast<const StaticAbility *>(ability))
        {
            switch (static_ability->getType())
            {

            case StaticAbility::Type::CharacteristicDefining:
                return AbilityType{StaticCharacteristicDefining};
            case StaticAbility::Type::Prevention:
                return AbilityType{StaticPrevention};
            case StaticAbility::Type::Replacement:
                return AbilityType{StaticReplacement};
            }
        }

        if (const auto *wrapped =
                dynamic_cast<const IAbilityDecorator *>(ability))
        {
            const auto *underlying{wrapped->getInnerAbility()};
            return AbilityType::from(underlying);
        }

        throw std::runtime_error("unreachable path in AbilityType::from");
    }
} // namespace dandan::abilities