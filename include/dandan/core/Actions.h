#ifndef DANDAN_ACTIONS_H
#define DANDAN_ACTIONS_H

#include <cstdint>
namespace dandan::actions
{
    enum class ActionType : uint8_t
    {
        PlayLand,
        DrawCard,
        CastSpell,
        ActivateAbility,
        Attack,
        Block,
        PassPriority,
        // Add more action types as needed
    };
} // namespace dandan::actions

#endif // DANDAN_ACTIONS_H