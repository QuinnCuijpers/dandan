#include "dandan/core/engine/InputManager.h"

namespace dandan::core
{
    InputManager::InputManager(std::istream &stream) : m_stream(&stream)
    {
    }

    std::istream &InputManager::stream()
    {
        return *m_stream;
    }

    void InputManager::setInput(std::istream &stream)
    {
        m_stream = &stream;
    }
} // namespace dandan::core
