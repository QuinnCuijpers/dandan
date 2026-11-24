#ifndef DANDAN_ADDMANAEFFECT_H
#define DANDAN_ADDMANAEFFECT_H

#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/events/IEvent.h"
#include "dandan/mana/ManaBag.h"
#include <memory>
#include <utility>
namespace dandan::effects
{
    /** @brief Represents an effect for adding mana
     *  @class AddManaEffect
     *
     *  @implements IOneShotEffect
     */
    class AddManaEffect : public IOneShotEffect
    {
    public:
        /** @brief Constructs an effect that adds mana to a player.
         * @param mana Mana to add.
         * @param context Effect execution context.
         */
        explicit AddManaEffect(mana::ManaBag mana, EffectContext context);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

        /** @brief Gets the mana bag this effect adds.
         * @return Mana to add.
         */
        [[nodiscard]] const mana::ManaBag &getMana() const;

    private:
        mana::ManaBag m_mana;
    };
} // namespace dandan::effects

#endif
