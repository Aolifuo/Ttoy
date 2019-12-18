#include <iostream>
#include <type_traits>
#include <ratio>

template <unsigned N>
struct factorial
{
    static constexpr unsigned value = N * factorial<N - 1>::value;
};

template <>
struct factorial<1>
{
    static constexpr unsigned value = 1;
};

template <unsigned N>
struct calc_e
{
    using type = std::ratio_add<std::ratio<1, factorial<N>::value>, typename calc_e<N - 1>::type>;
};

template <>
struct calc_e<0>
{
    using type = std::ratio<1>;
};

int main()
{
    std::cout << calc_e<9>::type::num << "/" << calc_e<9>::type::den << std::endl;

    return 0;
}