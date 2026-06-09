#include "dandan/core/actions/CardDrawAction.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/DrawEffect.h"
#include "dandan/log.h"
#include "dandan/numbers/ExactNumber.h"

namespace dandan::core
{
    std::unique_ptr<effects::IOneShotEffect> CardDrawAction::createEffect(
        [[maybe_unused]] core::Game &game)
    {
        DLOGI << "Executing card draw action\n";
        auto context{effects::EffectContext{m_player}};

        return std::make_unique<effects::DrawEffect>(
            std::make_unique<numbers::ExactNumber>(1), context);
    }
} // namespace dandan::core