#ifndef DANDAN_OVERLOADVISITOR_H
#define DANDAN_OVERLOADVISITOR_H

namespace dandan::utils
{
    // helper for visiting variants with lambdas, from cppreference
    template <class... Ts> struct overloaded : Ts...
    {
        using Ts::operator()...;
    };
    // explicit deduction guide (not needed as of C++20)
    template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
} // namespace dandan::utils

#endif