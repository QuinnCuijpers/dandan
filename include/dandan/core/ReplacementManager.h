

#include "dandan/effects/continuous/replacement/IReplacementEffect.h"
#include <memory>
#include <vector>

namespace dandan::core
{
    class ReplacementManager
    {
    public:
        void subscribe(const effects::IReplacementEffect *effect);
        void unsubscribe(const effects::IReplacementEffect *effect);

    private:
        std::vector<std::unique_ptr<effects::IReplacementEffect>>
            m_replacement_effects;
    };
} // namespace dandan::core
