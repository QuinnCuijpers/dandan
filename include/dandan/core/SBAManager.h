#ifndef DANDAN_SBAMANAGER_H
#define DANDAN_SBAMANAGER_H

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
         */
        static void checkSBAs(Game &game);
    };
} // namespace dandan::core

#endif // DANDAN_SBAMANAGER_H