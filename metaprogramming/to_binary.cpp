#include <type_traits>
#include <iostream>

template <unsigned... vals>
struct uint_list
{
};

template <typename>
struct length;

template <typename>
struct to_decimal;

template <unsigned, typename>
struct push_back
{
};

template <unsigned... vals>
struct length<uint_list<vals...>> : std::integral_constant<unsigned, sizeof...(vals)>
{
};

template <unsigned N, unsigned... tails>
struct push_back<N, uint_list<tails...>>
{
    using type = uint_list<tails..., N>;
};

template <unsigned N>
struct make_binary_list
{

    using type = typename push_back<
        N % 2, typename make_binary_list<N / 2>::type>::type;
};

template <>
struct make_binary_list<0>
{
    using type = uint_list<>;
};

/*template <unsigned head, unsigned... tails>
struct to_decimal<uint_list<head, tails...>>
{
    static constexpr unsigned value = (head + to_decimal<uint_list<tails...>>::value) * 2;
};

template <unsigned A, unsigned B>
struct to_decimal<uint_list<A, B>>
{
    static constexpr unsigned value = ;
};*/

struct Printer
{
    template <unsigned head, unsigned... tails>
    static void print(uint_list<head, tails...>)
    {
        std::cout << head << " ";
        print(uint_list<tails...>());
    }

    static void print(uint_list<>)
    {
        std::cout << std::endl;
    }

    template <typename T>
    static void print(T n)
    {
        std::cout << n << std::endl;
    }
};

int main()
{
    Printer::print(make_binary_list<123>::type());
    return 0;
}