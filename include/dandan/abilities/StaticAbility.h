#ifndef REPLACEMENTABILITY_H
#define REPLACEMENTABILITY_H

#include "IAbility.h"
#include "dandan/core/Game.h"
#include "dandan/effects/continuous/IContinuousEffect.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <cstdint>
#include <memory>

namespace dandan::abilities
{

    /** @brief A static ability that modifies the game state
     * @class StaticAbility
     *
     * @implements IAbility
     */
    class StaticAbility final : public IAbility
    {
    public:
        /** The type of the static ability
         * @enum Type
         */
        enum class Type : uint8_t
        {
            /// A characteristic-defining ability modifies the characteristics
            /// of a card
            CharacteristicDefining,
            /// A static ability that modifies the rules of the game, such as
            /// "Players can't gain life"
            Prevention,
            /// A static ability that modifies effects
            Replacement,
        };

        /** Constructor *@param type The type of the static ability
         *@param effect The continuous effect of the static ability
         */
        StaticAbility(Type type,
                      std::unique_ptr<effects::IContinuousEffect> effect)
            : m_type(type), m_effect(std::move(effect))
        {
        }

        /** Get the type of the static ability
         * @return The type of the static ability
         */
        [[nodiscard]] Type getType() const
        {
            return m_type;
        }

        /** Get the effect of the static ability
         * @return The effect of the static ability
         */
        [[nodiscard]] const effects::IContinuousEffect *getEffect() const
        {
            return m_effect.get();
        }

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game, AbilityContext context) const override;

    private:
        Type m_type{};
        std::unique_ptr<effects::IContinuousEffect> m_effect;
    };
} // namespace dandan::abilities

#endif // REPLACEMENTABILITY_H
