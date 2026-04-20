#include "dandan/replacement_effects/EntersTappedEffect.h"
#include "dandan/effects/ETBEffect.h"
#include "dandan/effects/IEffect.h"
#include <stdexcept>

namespace dandan::replacement_effects
{

    effects::IEffect &EntersTappedEffect::replace(effects::IEffect &effect)
    {

        if (auto *etbEffect = dynamic_cast<effects::ETBEffect *>(&effect))
        {
            etbEffect->setTapped(true);
            return *etbEffect;
        }

        throw std::runtime_error(
            "EntersTappedEffect can only replace ETB effects");
    }

} // namespace dandan::replacement_effects