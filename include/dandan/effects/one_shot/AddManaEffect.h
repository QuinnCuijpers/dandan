#ifndef DANDAN_ADDMANAEFFECT_H
#define DANDAN_ADDMANAEFFECT_H

#include "dandan/core/Game.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/events/IEvent.h"
#include "dandan/mana/Mana.h"
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
        explicit AddManaEffect(mana::ManaMap mana, EffectContext context)
            : IOneShotEffect(std::move(context)), m_mana(std::move(mana))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<AddManaEffect>(m_mana, getEffectContext());
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

        [[nodiscard]] const mana::ManaMap &getMana() const
        {
            return m_mana;
        }

    private:
        mana::ManaMap m_mana;
    };
} // namespace dandan::effects

#endif
