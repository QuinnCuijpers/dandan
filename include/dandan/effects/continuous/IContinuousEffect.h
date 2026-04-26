#ifndef DANDAN_CONTINOUS_EFFECT_H
#define DANDAN_CONTINOUS_EFFECT_H

namespace dandan::effects
{
    // Marker class for continous effects. This is used to distinguish between
    // one-shot effects and continous effects
    class IContinuousEffect
    {
    public:
        IContinuousEffect() = default;
        IContinuousEffect(const IContinuousEffect &) = delete;
        IContinuousEffect(IContinuousEffect &&) = delete;
        IContinuousEffect &operator=(const IContinuousEffect &) = delete;
        IContinuousEffect &operator=(IContinuousEffect &&) = delete;
        virtual ~IContinuousEffect() = default;
    };

} // namespace dandan::effects

#endif