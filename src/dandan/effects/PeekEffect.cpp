#include "dandan/effects/PeekEffect.h"
#include <iostream>

namespace dandan::effects
{

    void PeekEffect::apply()
    {
        std::cout << "Applying PeekEffect: peeking at the top " << m_peek_amount
                  << " cards of the library\n";
    }

} // namespace dandan::effects