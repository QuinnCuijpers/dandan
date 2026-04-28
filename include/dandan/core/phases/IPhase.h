#ifndef DANDAN_IPHASE_H
#define DANDAN_IPHASE_H

namespace dandan::core
{
    class Game;

    class IPhase
    {
    public:
        IPhase(Game *game) : m_game(game)
        {
        }
        IPhase(const IPhase &) = delete;
        IPhase(IPhase &&) = delete;
        IPhase &operator=(const IPhase &) = delete;
        IPhase &operator=(IPhase &&) = delete;
        virtual ~IPhase() = default;

        [[nodiscard]] Game *getGame() const
        {
            return m_game;
        }

    private:
        Game *m_game;
    };
} // namespace dandan::core

#endif