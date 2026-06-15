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

    effects::IOneShotEffect &EntersTappedEffect::replace(
        effects::IOneShotEffect &effect) const
    {
        std::cout << "Checking entertapped replacement effect\n";
        if (appliesTo(effect))
        {
            std::cout << "Applying etb tapped replacement effect\n";
            auto *etbEffect = dynamic_cast<effects::ETBEffect *>(&effect);
            etbEffect->setTapped(true);
            return *etbEffect;
        }

        throw std::runtime_error(
            "EntersTappedEffect can only replace ETB effects");
    }

} // namespace dandan::effects