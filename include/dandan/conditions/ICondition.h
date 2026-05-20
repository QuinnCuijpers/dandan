#ifndef DANDAN_ICONDITION_H
#define DANDAN_ICONDITION_H

#include "dandan/core/Game.h"
namespace dandan::conditions
{
    /**
     * Base interface for conditions
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
        virtual bool isSatisfied(const core::Game &game) = 0;
    };

} // namespace dandan::conditions
#endif