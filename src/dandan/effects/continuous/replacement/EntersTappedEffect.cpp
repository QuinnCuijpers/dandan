#include "dandan/effects/continuous/replacement/EntersTappedEffect.h"
#include "dandan/effects/one_shot/ETBEffect.h"
#include <stdexcept>

namespace dandan::effects
{
    // TODO: simplify double dynamic_cast
    bool EntersTappedEffect::appliesTo(
        const effects::IOneShotEffect &effect) const
    {
        return dynamic_cast<const effects::ETBEffect *>(&effect) != nullptr;
    }

    IOneShotEffect &EntersTappedEffect::replace(IOneShotEffect &effect)
    {

        if (appliesTo(effect))
        {
            auto *etbEffect = dynamic_cast<effects::ETBEffect *>(&effect);
            etbEffect->setTapped(true);
            return *etbEffect;
        }

        throw std::runtime_error(
            "EntersTappedEffect can only replace ETB effects");
    }

} // namespace dandan::effects