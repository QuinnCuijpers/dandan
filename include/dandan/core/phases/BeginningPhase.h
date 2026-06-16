#ifndef DANDAN_BEGINNINGPHASE_H
#define DANDAN_BEGINNINGPHASE_H

#include "dandan/core/phases/IPhase.h"
#include "dandan/core/phases/MainPhase.h"
#include <cstdint>
#include <memory>

// 501. Beginning Phase
// 502. Untap Step
// 503. Upkeep Step
// 504. Draw Step

namespace dandan::core
{
    /**
     * @brief Beginning Phase
     * @class BeginningPhase
     *
     * @implements IPhase
     */
    class BeginningPhase : public IPhase
    {
    public:
        /**
         * The steps of the beginning phase
         * @enum Step
         */
        enum class Step : uint8_t
        {
            /// The untap step, in which the active player untaps their
            /// permanents
            Untap,
            /// The upkeep step, in which "at the beginning of upkeep" triggers
            Upkeep,
            /// The draw step, in which the active player draws a card, unless
            /// they are the starting player on the first turn, in which case
            /// they skip the draw
            Draw,
            /// Indicates that there are no more steps and we should proceed to
            /// the next phase
            Done
        };

        /**
         * Constructor
         * @param game The game instance.
         */
        explicit BeginningPhase(Game &game) : IPhase(game) {};

        std::unique_ptr<IPhase> handle() override;

        [[nodiscard]] std::string name() const override
        {
            return "Beginning Phase";
        }

    private:
        Step m_step{Step::Untap};
        std::unique_ptr<IPhase> m_next_phase{
            std::make_unique<MainPhase>(game())};

        void handleNextStep();
        void handleUntapStep();
        // void handleUpkeepStep();
        // void handleDrawStep();
    };
} // namespace dandan::core
#endif
