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
        /** Constructor
         * @param mana the mana that this effect will add.
         */
        explicit AddManaEffect(mana::ManaBag mana, EffectContext context)
            : IOneShotEffect(std::move(context)), m_mana(std::move(mana))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<AddManaEffect>(m_mana, getEffectContext());
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override;

        [[nodiscard]] const mana::ManaBag &getMana() const
        {
            return m_mana;
        }

    private:
        mana::ManaBag m_mana;
    };
} // namespace dandan::effects

#endif
