#ifndef DANDAN_DRAWEFFECT_H
#define DANDA_DRAWEFFECT_H

#include <nlohmann/json_fwd.hpp>

#include "IEffect.h"

namespace dandan::effects
{
    struct DrawEffect : public IEffect
    {
    public:
        int m_amount{1};

        DrawEffect() = default;
        explicit DrawEffect(int amount) : m_amount(amount) {}

        void apply() override;
    };

}

#endif