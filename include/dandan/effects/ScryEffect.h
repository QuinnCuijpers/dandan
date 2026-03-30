#ifndef DANDAN_SCRY_EFFECT_H
#define DANDAN_SCRY_EFFECT_H

#include "ITriggeredEffect.h"

namespace dandan::effects
{

    class ScryEffect : public ITriggeredEffect
    {
    public:
        void apply() override;
        void from_json(const nlohmann::json &j, ITriggeredEffect &effect) override;
        void to_json(nlohmann::json &j, const ITriggeredEffect &effect) override;

    private:
        int m_scry_amount{1};
    };
}

#endif