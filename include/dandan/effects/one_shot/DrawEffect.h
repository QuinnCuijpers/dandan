#ifndef DANDAN_DRAWEFFECT_H
#define DANDAN_DRAWEFFECT_H

#include "IOneShotEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>

namespace dandan::effects
{
    /** @brief Represents drawing cards as an effect.
     * @struct DrawEffect
     *
     *@implements IOneShotEffect
     */
    struct DrawEffect final : public IOneShotEffect
    {
    public:
        /// the amount of cards to draw with this effect
        int m_amount{1};

        [[nodiscard]] std::string display() const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> clone() const override
        {
            return std::make_unique<DrawEffect>(m_amount);
        }

        DrawEffect() = default;
        /** Constructor
         * @param amount the amount of cards this effect would draw
         */
        explicit DrawEffect(int amount) : m_amount(amount)
        {
        }

        std::unique_ptr<events::IEvent> apply(core::Game &game) const override;
    };

} // namespace dandan::effects

#endif
