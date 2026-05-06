#include "dandan/core/Stack.h"
#include "dandan/core/Game.h"

namespace dandan::core
{
    void Stack::resolveNext(core::Game &game)
    {
        if (m_stack.empty())
        {
            return;
        }

        auto effect = std::move(m_stack.back());
        m_stack.pop_back();

        effect->apply(game);
    }
} // namespace dandan::core