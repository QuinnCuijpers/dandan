#ifndef DANDAN_ICONDITION_H
#define DANDAN_ICONDITION_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/core/TextReplacement.h"
#include <memory>
#include <optional>
#include <vector>

namespace dandan::core
{
    class Game;
}

namespace dandan::conditions
{
    /**
     * @brief Base interface for conditions
     * @class ICondition
     */
    class ICondition
    {
    public:
        ICondition() = default;
        ICondition(const ICondition &) = delete;
        ICondition(ICondition &&) = delete;
        ICondition &operator=(const ICondition &) = delete;
        ICondition &operator=(ICondition &&) = delete;
        virtual ~ICondition() = default;

        /**
         * @param game The game for which to check whether the condition is
         * satisfied.
         * @returns true if the condition is satisfied, false otherwise.
         */
        [[nodiscard]] virtual bool isSatisfied(
            const core::Game &game,
            std::optional<abilities::AbilityContext> context =
                std::nullopt) const = 0;

        /**
         * Creates a copy of the condition.
         * @returns A unique pointer to a cloned condition.
         */
        [[nodiscard]] virtual std::unique_ptr<ICondition> clone() const = 0;
    };

} // namespace dandan::conditions
#endif
