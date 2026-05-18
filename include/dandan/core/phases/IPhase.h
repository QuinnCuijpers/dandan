#ifndef DANDAN_IPHASE_H
#define DANDAN_IPHASE_H

#include <memory>
#include <ostream>
#include <string>

namespace dandan::core
{
    class Game;

    class IPhase
    {
    public:
        explicit IPhase(Game &game) : m_game(game)
        {
        }
        IPhase(const IPhase &) = delete;
        IPhase(IPhase &&) = delete;
        IPhase &operator=(const IPhase &) = delete;
        IPhase &operator=(IPhase &&) = delete;
        virtual ~IPhase() = default;

        [[nodiscard]] virtual std::unique_ptr<IPhase> handle() = 0;

        [[nodiscard]] virtual std::string name() const = 0;

        [[nodiscard]] Game &game()
        {
            return m_game;
        }

        [[nodiscard]] const Game &game() const
        {
            return m_game;
        }

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