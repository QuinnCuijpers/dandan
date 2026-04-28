#ifndef DANDAN_IPHASE_H
#define DANDAN_IPHASE_H

#include <memory>

namespace dandan::core
{
    class Game;

    class IPhase
    {
    public:
        IPhase() = default;
        IPhase(const IPhase &) = delete;
        IPhase(IPhase &&) = delete;
        IPhase &operator=(const IPhase &) = delete;
        IPhase &operator=(IPhase &&) = delete;
        virtual ~IPhase() = default;

    private:
        std::unique_ptr<Game> m_game;
    };
} // namespace dandan::core

#endif