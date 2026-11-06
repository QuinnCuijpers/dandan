#include "dandan/core/phases/IPhase.h"

namespace dandan::core
{
    IPhase::IPhase(ExecutionContext exec_ctx) : m_ctx(exec_ctx)
    {
    }

    const ExecutionContext &IPhase::context() const
    {
        return m_ctx;
    }

    std::ostream &operator<<(std::ostream &ostream, const IPhase &phase)
    {
        ostream << "Phase{name: " << phase.name() << '}';
        return ostream;
    }
} // namespace dandan::core
