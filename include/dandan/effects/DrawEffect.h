#ifndef DANDAN_DRAWEFFECT_H
#define DANDA_DRAWEFFECT_H

#include <nlohmann/json_fwd.hpp>

#include "IEffect.h"

namespace dandan::effects
{
    class DrawEffect : public IEffect
    {
    public:
        DrawEffect() = default;
        void apply() override;

        void from_json(const nlohmann::json &j, IEffect &effect) override;
        void to_json(nlohmann::json &j, const IEffect &effect) override;

    private:
        int m_amount{1};
    };

}

#endif