#include <type_traits>
#include <iostream>

template <unsigned A, unsigned B>
struct GCD
{
    static constexpr unsigned value = GCD<B, A % B>::value;
};

template <unsigned A>
struct GCD<A, 0>
{
    static constexpr unsigned value = A;
};

int main()
{
    std::cout << GCD<9, 6>::value << std::endl;
    return 0;
}
