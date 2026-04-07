#include "dandan/abilities/TriggeredAbility.h"
#include <nlohmann/json.hpp>

namespace dandan::abilities
{

    void TriggeredAbility::resolve()
    {
        // In a real implementation, you would check the game state to see if
        // the event specified in m_on has occurred. If it has, you would then
        // apply the effect specified in m_effect. This is a placeholder
        // implementation. You would need to implement the logic to check for
        // the event and apply the effect based on your game's architecture.
    }

} // namespace dandan::abilities