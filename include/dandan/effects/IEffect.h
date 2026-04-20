#ifndef DANDAN_I_EFFECT_H
#define DANDAN_I_EFFECT_H

namespace dandan::effects
{
    // TODO: change `apply` to take in a `GameState` object and modify it
    // instead of just printing something to the console
    class IEffect
    {
    public:
        IEffect() = default;
        IEffect(const IEffect &) = delete;
        IEffect(IEffect &&) = delete;
        IEffect &operator=(const IEffect &) = delete;
        IEffect &operator=(IEffect &&) = delete;
        virtual ~IEffect() = default;
        virtual void apply() = 0;
    };

} // namespace dandan::effects

#endif