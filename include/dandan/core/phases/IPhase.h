#ifndef DANDAN_IPHASE_H
#define DANDAN_IPHASE_H

#include <memory>
#include <ostream>
#include <string>

namespace dandan::core
{
    class Game;

    /**
     * @brief Base interface for phases
     * @class IPhase
     */
    class IPhase
    {
    public:
        /** Constructor
         * @param game The game instance.
         */
        explicit IPhase(Game &game) : m_game(game)
        {
        }
        IPhase(const IPhase &) = delete;
        IPhase(IPhase &&) = delete;
        IPhase &operator=(const IPhase &) = delete;
        IPhase &operator=(IPhase &&) = delete;
        virtual ~IPhase() = default;

        /** Handles the current phase
         * @return The next phase to move to, returns nullptr if there is no
         * next phase and the game should switch active players
         */
        [[nodiscard]] virtual std::unique_ptr<IPhase> handle() = 0;

        /** Returns the name of the phase
         * @return The name of the phase
         */
        [[nodiscard]] virtual std::string name() const = 0;

        /** Returns the game instance mutable
         * @return The game instance
         */
        [[nodiscard]] Game &game()
        {
            return m_game;
        }

        /** Returns the game instance const
         * @return The game instance
         */
        [[nodiscard]] const Game &game() const
        {
            return m_game;
        }

        /** Outputs the phase name to the stream
         * @param ostream The output stream
         * @param phase The phase to output
         * @return The output stream
         */
        friend std::ostream &operator<<(std::ostream &ostream,
                                        const IPhase &phase)
        {
            ostream << "Phase{name: " << phase.name() << '}';
            return ostream;
        }

    private:
        Game &m_game;
    };
} // namespace dandan::core

#endif
