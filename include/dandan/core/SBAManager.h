#ifndef DANDAN_SBAMANAGER_H
#define DANDAN_SBAMANAGER_H

#include "dandan/core/ExecutionContext.h"
namespace dandan::core
{

    class Game;

    /** @brief A class that manages state-based actions.
     * @class SBAManager
     */
    class SBAManager
    {
    public:
        /** Checks for state-based actions and handles them.
         * @param game The game instance to check for state-based actions in.
         */
        static void checkSBAs(ExecutionContext exec_ctx);
    };
} // namespace dandan::core

#endif // DANDAN_SBAMANAGER_H
