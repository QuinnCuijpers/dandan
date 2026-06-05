#include "dandan/core/PriorityManager.h"
#include "dandan/core/Game.h"

namespace dandan::core
{
    void PriorityManager::passPriority(const core::Game &game)
    {
        m_current_player_with_priority =
            game.getNextPlayerID(m_current_player_with_priority);
    }

    void PriorityManager::setPriorityToActivePlayer(core::Game &game)
    {
        SBAManager::checkSBAs(game);
        m_current_player_with_priority = game.activePlayer().getID();
        // TODO: move to correct place
        if (!game.stack().isEmpty())
        {
            game.stack().resolveNext(game);
            setPriorityToActivePlayer(game);
        }
    }
} // namespace dandan::core