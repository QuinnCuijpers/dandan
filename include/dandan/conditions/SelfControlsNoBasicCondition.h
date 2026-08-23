#ifndef DANDAN_SELFCONTROLSNObasicCONDITION_H
#define DANDAN_SELFCONTROLSNObasicCONDITION_H

#include "dandan/conditions/ICondition.h"
#include "dandan/core/Game.h"
#include "dandan/core/IMindBendable.h"
#include <memory>

namespace dandan::conditions
{
    /**
     * @brief A condition that checks if the player controls no island.
     * @class ControlsNoIslandCondition
     *
     * @implements ICondition
     */
    class SelfControlsNoBasicCondition : public ICondition, core::IMindBendable
    {
    public:
        explicit SelfControlsNoBasicCondition(core::SubType basic_land_type);

        [[nodiscard]] core::SubType type() const;

        [[nodiscard]] bool isSatisfied(
            const core::Game &game,
            std::optional<effects::EffectContext> context) const override;

        [[nodiscard]] std::unique_ptr<ICondition> clone() const override;

        // NOLINTBEGIN(bugprone-easily-swappable-parameters)
        void replaceBasicWord(core::SubType from,
                              core::SubType new_basic) override;
        // NOLINTEND(bugprone-easily-swappable-parameters)

    private:
        core::SubType m_basic_type;
    };
} // namespace dandan::conditions

#endif
