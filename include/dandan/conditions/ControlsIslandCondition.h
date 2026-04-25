#ifndef DANDAN_CONTROLSISLANDCONDITION_H
#define DANDAN_CONTROLSISLANDCONDITION_H

#include "dandan/conditions/ICondition.h"
#include "dandan/core/Player.h"

namespace dandan::conditions
{
    class ControlsIslandCondition : public ICondition
    {
    public:
        ControlsIslandCondition(const core::Player &player) : m_player(player)
        {
        }
        bool isSatisfied() override;

    private:
        const core::Player &m_player;
    };
} // namespace dandan::conditions

#endif