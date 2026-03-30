#ifndef DANDAN_I_EFFECT_H
#define DANDAN_I_EFFECT_H

namespace dandan::effects
{

    class IEffect
    {
    public:
        virtual ~IEffect() = default;
        virtual void apply() = 0;

        virtual void from_json(const nlohmann::json &j, IEffect &effect) = 0;
        virtual void to_json(nlohmann::json &j, const IEffect &effect) = 0;
    };

}

#endif