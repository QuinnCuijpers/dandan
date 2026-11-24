#ifndef DANDAN_MANAPRICE_H
#define DANDAN_MANAPRICE_H

#include "dandan/mana/ManaBag.h"
#include <cstddef>
namespace dandan::mana

{
    /** @brief A mana cost with specific and generic requirements.
     * @class ManaPrice
     */
    class ManaPrice
    {
    public:
        /** Constructs a mana cost.
         * @param specific The specific mana types required.
         * @param generic_amount The amount of generic mana required.
         */
        explicit ManaPrice(ManaBag specific = ManaBag{},
                           size_t generic_amount = {});

        /** Gets the specific mana required by the cost.
         * @return A const reference to the specific mana bag.
         */
        [[nodiscard]] const ManaBag &specific() const;

        /** Gets the generic mana required by the cost.
         * @return The amount of generic mana.
         */
        [[nodiscard]] size_t generic() const;

        /** Gets the total amount of mana required by the cost.
         * @return The sum of specific and generic mana.
         */
        [[nodiscard]] size_t totalRequired() const;

    private:
        ManaBag m_specific;
        size_t m_generic;
    };
} // namespace dandan::mana
#endif
