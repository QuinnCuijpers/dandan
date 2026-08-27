#include "dandan/core/actions/CardDrawAction.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/DrawEffect.h"
#include "dandan/numbers/ExactNumber.h"
#include "dandan/utils/log.h"

namespace dandan::core
{
    CardDrawAction::CardDrawAction(PlayerID player) : m_player{player}
    {
    }

    [[nodiscard]] ActionActor CardDrawAction::getActor() const
    {
        return m_player;
    }

    std::unique_ptr<effects::IOneShotEffect> CardDrawAction::createEffect(
        [[maybe_unused]] core::ExecutionContext exec_ctx)
    {
        DLOGI << "Executing card draw action\n";
        auto context{effects::EffectContext{m_player}};

        return std::make_unique<effects::DrawEffect>(
            std::make_unique<numbers::ExactNumber>(1), context);
    }
} // namespace dandan::core
