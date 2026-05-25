#ifndef DANDAN_ADDMANAEFFECT_H
#define DANDAN_ADDMANAEFFECT_H

#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/events/IEvent.h"
#include "dandan/mana/Mana.h"
#include <memory>
namespace dandan::effects
{
    class AddManaEffect : public IOneShotEffect
    {
    public:
        explicit AddManaEffect(mana::ManaMap m_mana) : m_mana(std::move(m_mana))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> clone() const override
        {
            return std::make_unique<AddManaEffect>(m_mana);
        }

        std::unique_ptr<events::IEvent> apply(core::Game &game) const override;

    private:
        mana::ManaMap m_mana;
    };
} // namespace dandan::effects

#endif