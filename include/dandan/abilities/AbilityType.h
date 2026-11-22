#ifndef DANDAN_ABILITYTYPE_H
#define DANDAN_ABILITYTYPE_H

#include <cstdint>

namespace dandan::abilities
{
    class IAbility;

    /** @brief Classifies an ability by its effect on the game.
     * @class AbilityType
     */
    class AbilityType
    {
    public:
        /** @brief The supported categories of abilities. */
        enum class Type : uint8_t
        {
            /// An ability activated by a player.
            Activated,
            /// A mana ability of a basic land.
            BasicLand,
            /// An ability triggered by an event.
            EventTriggered,
            /// An ability that produces mana.
            Mana,
            /// A spell cast from a hand or other zone.
            Spell,
            /// An ability triggered by a change in game state.
            StateTriggered,
            /// A static ability that replaces an event.
            StaticReplacement,
            /// A static ability that prevents an event.
            StaticPrevention,
            /// A static ability that sets characteristics.
            StaticCharacteristicDefining,
            /// An ability that modifies another ability.
            AbilityDecorator,
            /// A keyword ability.
            Keyword,
        };

        /** Create a wrapper from its type.
         * @param type The type to wrap.
         */
        explicit AbilityType(Type type);

        /** Gets the wrapped ability type.
         * @return The ability type.
         */
        [[nodiscard]] Type getType() const;

        /** Determines the type of an ability at runtime.
         * @param ability The ability to classify.
         * @return The type of the ability.
         */
        static AbilityType from(const IAbility *ability);

    private:
        Type m_type;
    };
} // namespace dandan::abilities

#endif
