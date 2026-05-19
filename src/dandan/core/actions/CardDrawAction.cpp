#include "dandan/core/actions/CardDrawAction.h"
#include "dandan/log.h"

namespace dandan::core
{
    std::unique_ptr<effects::IOneShotEffect> CardDrawAction::createEffect()
    {
        DLOGI << "Executing card draw action\n";
        m_game.activePlayer().drawCard(m_game.deck());
        return std::make_unique<effects::DrawEffect>();
    }
} // namespace dandan::core