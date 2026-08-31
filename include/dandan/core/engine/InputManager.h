#ifndef DANDAN_INPUTMANAGER_H
#define DANDAN_INPUTMANAGER_H

#include <iostream>
#include <istream>
namespace dandan::core
{
    class InputManager
    {
    public:
        InputManager() = default;

        explicit InputManager(std::istream &stream) : m_stream(&stream)
        {
        }

        std::istream &stream()
        {
            return *m_stream;
        }

        void setInput(std::istream &stream)
        {
            m_stream = &stream;
        }

    private:
        // TODO: consider making this own the stream
        std::istream *m_stream{&std::cin};
    };
} // namespace dandan::core
#endif // !DANDAN_INPUTMANAGER_H
