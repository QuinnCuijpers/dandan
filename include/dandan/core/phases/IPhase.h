#ifndef DANDAN_IPHASE_H
#define DANDAN_IPHASE_H

#include <memory>
namespace dandan::core
{
    class Game;

    class IPhase
    {
    public:
        explicit IPhase(Game *game) : m_game(game)
        {
        }
        IPhase(const IPhase &) = delete;
        IPhase(IPhase &&) = delete;
        IPhase &operator=(const IPhase &) = delete;
        IPhase &operator=(IPhase &&) = delete;
        virtual ~IPhase() = default;

        [[nodiscard]] virtual std::unique_ptr<IPhase> handle() = 0;

        [[nodiscard]] Game *getGame() const
        {
            return m_game;
        }

    private:
        Game *m_game;
    };
} // namespace dandan::core

#endif