#ifndef DANDAN_CASTEFFECT_H
#define DANDAN_CASTEFFECT_H

#include "dandan/abilities/SpellAbility.h"
#include "dandan/core/Card.h"
#include "dandan/core/CastContext.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/GameState.h"
#include "dandan/core/PriorityManager.h"
#include "dandan/core/Target.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "dandan/effects/one_shot/ModalEffect.h"
#include "dandan/events/IEvent.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

// TODO: add doc explaining how this is different from ETBEffect
namespace dandan::effects
{

    namespace impl
    {
        void choose_targets(core::Card *cardp,
                            const effects::IOneShotEffectDefinition &effect,
                            core::ExecutionContext exec_ctx);

        IOneShotEffectDefinition *choose_mode(
            core::Card *cardp, const ModalEffectDefinition &modal_effect,
            core::ExecutionContext exec_ctx);
    } // namespace impl

    /** @brief Represents the effect of playing a card.
     * @class PlayCardEffect
     *
     * @implements IOneShotEffect
     */
    class CastEffect : public IOneShotEffect
    {
    public:
        /** Constructor
         *@param card The card that would be played
         */
        explicit CastEffect(core::CastContext cast_ctx, EffectContext context);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

    private:
        core::CastContext m_cast_ctx;
    };
} // namespace dandan::effects
#endif
