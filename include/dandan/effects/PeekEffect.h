#ifndef DANDAN_PEEK_EFFECT_H
#define DANDAN_PEEK_EFFECT_H

#include "ITriggeredEffect.h"

namespace dandan::effects
{

    class PeekEffect : public ITriggeredEffect
    {
    public:
        PeekEffect(int peek_amount) : m_peek_amount(peek_amount) {}
        void apply() override;
        void from_json(const nlohmann::json &j, ITriggeredEffect &effect) override;
        void to_json(nlohmann::json &j, const ITriggeredEffect &effect) override;

    private:
        int m_peek_amount{3};
    };
}

#endif