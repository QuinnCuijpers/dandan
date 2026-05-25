#ifndef DANDAN_UNTAPEFFECT_H
#define DANDAN_UNTAPEFFECT_H

#include "dandan/core/Card.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>

namespace dandan::effects
{
    /**
     * @class UntapEffect
     * @brief A one-shot effect that untaps a card.
     *
     * This effect is used whenever a card should be untapped as part of an
     * effect, such as during the untap step or as a result of a spell or
     * ability. It sets the tapped state of the card to false and generates an
     * UntapEvent.
     *
     * @implements IOneShotEffect
     */
    class UntapEffect : public IOneShotEffect
    {
    public:
        /**
         * Constructs an UntapEffect for a specified card.
         * @param card The card to be untapped by this effect.
         */
        explicit UntapEffect(core::Card &card) : m_card{card}
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> clone() const override
        {
            return std::make_unique<UntapEffect>(m_card);
        }

        /**
         * Apply the untap effect and generate the corresponding event.
         * @param game The game state to apply the effect to.
         * @return The event generated from applying the effect.
         */
        std::unique_ptr<events::IEvent> apply(
            [[maybe_unused]] core::Game &game) const override;

    private:
        core::Card &m_card;
    };
} // namespace dandan::effects

#endif