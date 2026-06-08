#ifndef DANDAN_DRAWEFFECT_H
#define DANDAN_DRAWEFFECT_H

#include "IOneShotEffect.h"
#include "dandan/events/IEvent.h"
#include "dandan/numbers/ExactNumber.h"
#include "dandan/numbers/INumber.h"
#include <memory>

namespace dandan::effects
{
    /** @brief Represents drawing cards as an effect.
     * @class DrawEffect
     *
     *@implements IOneShotEffect
     */
    class DrawEffect final : public IOneShotEffect
    {
    public:
        DrawEffect() = default;
        /** Constructor
         * @param amount the amount of cards this effect would draw
         */
        explicit DrawEffect(int amount)
            : m_amount(std::make_unique<numbers::ExactNumber>(amount))
        {
        }

        explicit DrawEffect(std::unique_ptr<numbers::INumber> amount)
            : m_amount(std::move(amount))
        {
        }

        [[nodiscard]] const std::unique_ptr<numbers::INumber> &getNumber() const
        {
            return m_amount;
        }

        [[nodiscard]] std::string display() const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> clone() const override
        {
            return std::make_unique<DrawEffect>(m_amount->clone());
        }
        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

    private:
        std::unique_ptr<numbers::INumber> m_amount{
            std::make_unique<numbers::ExactNumber>(1)};
    };

} // namespace dandan::effects

#endif
