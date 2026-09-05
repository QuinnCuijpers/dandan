#ifndef DANDAN_KEYWORD_H
#define DANDAN_KEYWORD_H

#include "dandan/abilities/IAbility.h"
#include <cassert>
#include <cstdint>

namespace dandan::abilities
{
    const extern std::unique_ptr<IAbility> FLYING_ABILITY;

} // namespace dandan::abilities
//
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

    bool isFlyingAbility(const dandan::abilities::IAbility &ability);

} // namespace dandan::core

#endif
