#ifndef DANDAN_KEYWORD_H
#define DANDAN_KEYWORD_H

#include "dandan/abilities/IAbility.h"
#include "dandan/abilities/KeyWords.h"
#include <cstdint>
namespace dandan::core
{
    enum class Keyword : uint8_t
    {
        Flying,
    };

    inline abilities::IAbility *getKeywordAbility(Keyword keyword)
    {
        switch (keyword)
        {
        case Keyword::Flying:
            return abilities::FLYING_ABILITY.get();
        }
        assert(false && "unreachable code in getKeywordAbility");
    }

    inline bool isFlyingAbility(const dandan::abilities::IAbility &ability)
    {
        const auto *static_ability =
            dynamic_cast<const dandan::abilities::StaticAbility *>(&ability);
        if ((static_ability == nullptr) ||
            static_ability->getType() !=
                dandan::abilities::StaticAbility::Type::Prevention)
        {
            return false;
        }
        const auto *effect =
            dynamic_cast<const dandan::effects::BlockPreventionEffect *>(
                static_ability->getEffect());
        if (effect == nullptr)
        {
            return false;
        }
        return dynamic_cast<const dandan::conditions::FlyingCondition *>(
                   effect->getCondition()) != nullptr;
    }
} // namespace dandan::core

#endif