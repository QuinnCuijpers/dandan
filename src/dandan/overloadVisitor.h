#ifndef DANDAN_OVERLOADVISITOR_H
#define DANDAN_OVERLOADVISITOR_H

template <class... Ts> struct overloaded : Ts...
{
    using Ts::operator()...;
};
// explicit deduction guide (not needed as of C++20)
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

#endif