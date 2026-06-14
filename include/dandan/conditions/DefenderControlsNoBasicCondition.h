#ifndef DANDAN_DEFENDERCONTROLSNOBASICCONDITION_H
#define DANDAN_DEFENDERCONTROLSNOBASICCONDITION_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/conditions/ICondition.h"
#include "dandan/core/Game.h"
#include "dandan/core/IMindBendable.h"
#include <memory>
#include <optional>
namespace dandan::conditions
{
    class DefenderControlsNoBasicCondition : public ICondition,
                                             public core::IMindBendable
    {

    public:
        explicit DefenderControlsNoBasicCondition(core::SubType type)
            : m_type(type)
        {
        }

        [[nodiscard]] core::SubType type() const
        {
            return m_type;
        }

        [[nodiscard]] bool isSatisfied(
            const core::Game &game,
            std::optional<abilities::AbilityContext> context =
                std::nullopt) const override;

        [[nodiscard]] std::unique_ptr<ICondition> clone() const override
        {
            return std::make_unique<DefenderControlsNoBasicCondition>(m_type);
        }

        // NOLINTBEGIN(bugprone-easily-swappable-parameters)
        void replaceBasicWord(core::SubType from,
                              core::SubType new_basic) override
        {
            if (m_type == from)
            {
                m_type = new_basic;
            }
        }
        // NOLINTEND(bugprone-easily-swappable-parameters)

    private:
        core::SubType m_type;
    };
} // namespace dandan::conditions

#endif