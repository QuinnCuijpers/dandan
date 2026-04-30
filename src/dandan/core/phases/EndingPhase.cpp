#include "dandan/core/phases/EndingPhase.h"

namespace dandan::core
{
    [[nodiscard]] std::unique_ptr<IPhase> EndingPhase::handle()
    {
        std::cout << "Handling ending phase\n";
        return nullptr;
    }
} // namespace dandan::core