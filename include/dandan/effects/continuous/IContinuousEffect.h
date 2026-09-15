#ifndef DANDAN_CONTINOUS_EFFECT_H
#define DANDAN_CONTINOUS_EFFECT_H

#include <memory>

namespace dandan::effects
{
    /** @brief A marker class for continuous effects.
     * This is used to distinguish between one-shot effects and continuous
     * effects.
     * @class IContinuousEffect
     */
    class IContinuousEffect
    {
    public:
        IContinuousEffect() = default;
        IContinuousEffect(const IContinuousEffect &) = delete;
        IContinuousEffect(IContinuousEffect &&) = delete;
        IContinuousEffect &operator=(const IContinuousEffect &) = delete;
        IContinuousEffect &operator=(IContinuousEffect &&) = delete;
        virtual ~IContinuousEffect() = default;

        /** Create a copy of the continuous effect.
         * @return The copy of the continuous effect
         */
        [[nodiscard]] virtual std::unique_ptr<IContinuousEffect>
        cloneContinuous() const = 0;
    };

} // namespace dandan::effects

#endif
