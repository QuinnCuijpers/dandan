#ifndef DANDAN_PUTCARDONTOPEFFECT_H
#define DANDAN_PUTCARDONTOPEFFECT_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>

namespace dandan::effects
{

    class PutCardOnTopEffect : public IOneShotEffect
    {
    public:
        explicit PutCardOnTopEffect(int amount) : m_amount(amount)
        {
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> clone() const override;

        [[nodiscard]] int getAmount() const
        {
            return m_amount;
        }

    private:
        int m_amount{};
    };

} // namespace dandan::effects

#endif