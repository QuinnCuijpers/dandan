#include "dandan/core/Stack.h"

namespace dandan::core
{
    void Stack::resolveNext()
    {
        if (m_stack.empty())
            return;

        auto ability = m_stack.back();
        m_stack.pop_back();

        ability->resolve();
    }
} // namespace dandan::core