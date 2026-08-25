#ifndef DANDAN_IPHASE_H
#define DANDAN_IPHASE_H

#include "dandan/core/ExecutionContext.h"
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
        explicit IPhase(ExecutionContext &exec_ctx) : m_ctx(exec_ctx)
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

        /** Returns the execution context for the phase
         * @return The execution context
         */
        [[nodiscard]] const ExecutionContext &context() const
        {
            return m_ctx;
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
        ExecutionContext &m_ctx;
    };
} // namespace dandan::core

#endif
