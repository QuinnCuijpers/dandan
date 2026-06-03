#include "dandan/core/actions/CardDrawAction.h"
#include "dandan/effects/one_shot/DrawEffect.h"
#include "dandan/log.h"

namespace dandan::core
{
    std::unique_ptr<effects::IOneShotEffect> CardDrawAction::createEffect(
        [[maybe_unused]] core::Game &game)
    {
        DLOGI << "Executing card draw action\n";
        return std::make_unique<effects::DrawEffect>();
    }
} // namespace dandan::core