#ifndef DANDAN_INPUTMANAGER_H
#define DANDAN_INPUTMANAGER_H

#include <iostream>
#include <istream>
namespace dandan::core
{
    /** @brief Provides access to the input stream used by the game.
     * @class InputManager
     */
    class InputManager
    {
    public:
        InputManager() = default;

        /** Constructs a manager that reads from the given stream.
         * @param stream The stream to read from.
         */
        explicit InputManager(std::istream &stream);

        /** Gets the input stream.
         * @return A reference to the input stream.
         */
        std::istream &stream();

        /** Sets the input stream.
         * @param stream The stream to read from.
         */
        void setInput(std::istream &stream);

    private:
        // TODO: consider making this own the stream
        std::istream *m_stream{&std::cin};
    };
} // namespace dandan::core
#endif // !DANDAN_INPUTMANAGER_H
