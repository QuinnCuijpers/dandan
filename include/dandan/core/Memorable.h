#ifndef DANDAN_MEMORABLE_H
#define DANDAN_MEMORABLE_H

#include <string>
#include <variant>

namespace dandan::core
{
    using Memorable = std::variant<std::string>;
}

#endif