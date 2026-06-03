#ifndef DANDAN_DESTROY_EFFECT_H
#define DANDAN_DESTROY_EFFECT_H

#include "dandan/core/Card.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>

namespace dandan::effects
{
    /** @brief A class that represents the effect of destroying a card.
     * @class DestroyEffect
     *
     * @implements IOneShotEffect
     */
    class DestroyEffect : public IOneShotEffect
    {
    public:
        /** @brief Constructs a new destroy effect with the specified card.
         * @param card The card to destroy.
         */
        explicit DestroyEffect(core::Card &card) : m_card{card}
        {
        }

        std::unique_ptr<events::IEvent> apply(core::Game &game) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> clone() const override
        {
            return std::make_unique<DestroyEffect>(m_card);
        }

    private:
        core::Card &m_card;
    };
} // namespace dandan::effects

#endif