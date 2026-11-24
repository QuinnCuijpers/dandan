#ifndef DANDAN_IKEYWORDABILITY_H
#define DANDAN_IKEYWORDABILITY_H

#include "dandan/abilities/IAbility.h"
#include "dandan/abilities/keywords/Keyword.h"

namespace dandan::abilities
{
    /** @brief Interface for abilities identified by a keyword.
     * @class IKeyWordAbility
     */
    class IKeyWordAbility : public IAbility
    {
    public:
        /** Gets the keyword represented by this ability.
         * @return The keyword.
         */
        [[nodiscard]] virtual Keyword keyword() const = 0;

    private:
    };
} // namespace dandan::abilities

#endif // !DANDAN_IKEYWORDABILITY_H
