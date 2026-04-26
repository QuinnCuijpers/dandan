#ifndef DANDAN_ETBEFFECT_H
#define DANDAN_ETBEFFECT_H

#include "dandan/effects//one_shot/IOneShotEffect.h"
namespace dandan::effects
{
    struct ETBEffect final : public IOneShotEffect
    {
        void apply() override;

        void setTapped(bool tapped)
        {
            m_tapped = tapped;
        }

        bool m_tapped{false};
    };
} // namespace dandan::effects

#endif