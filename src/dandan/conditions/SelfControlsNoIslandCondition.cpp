#include "dandan/conditions/SelfControlsNoBasicCondition.h"
#include "dandan/core/Game.h"
#include "dandan/core/TextReplacement.h"
#include <vector>

namespace dandan::conditions
{
    bool SelfControlsNoBasicCondition::isSatisfied(
        [[maybe_unused]] const core::Game &game,
        [[maybe_unused]] std::optional<std::vector<core::TextReplacement>>
            text_replacements) const
    {
        return false;
    }
} // namespace dandan::conditions