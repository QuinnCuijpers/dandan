#ifndef REPLACEMENTABILITY_H
#define REPLACEMENTABILITY_H

#include "IAbility.h"
#include "dandan/effects/continuous/IContinuousEffect.h"
#include <cstdint>
#include <memory>

namespace dandan::abilities
{

    class StaticAbility final : public IAbility
    {
    public:
        enum Type : uint8_t
        {
            CharacteristicDefining,
            Prevention,
            Replacement,
        };
        StaticAbility(Type type,
                      std::unique_ptr<effects::IContinuousEffect> effect)
            : m_type(type), m_effect(std::move(effect))
        {
        }

        [[nodiscard]] Type getType() const
        {
            return m_type;
        }

        [[nodiscard]] const effects::IContinuousEffect *getEffect() const
        {
            return m_effect.get();
        }

        void resolve() const override;

    private:
        Type m_type{};
        std::unique_ptr<effects::IContinuousEffect> m_effect;
    };
} // namespace dandan::abilities

#endif // REPLACEMENTABILITY_H