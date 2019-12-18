#include <iostream>
#include <type_traits>

template <unsigned... vals>
struct uint_list
{ };

template <unsigned N>
struct uint_const : std::integral_constant<unsigned, N>
{ };

template <unsigned, typename>
struct push_back;

template <unsigned N, unsigned... tails>
struct push_back<N, uint_list<tails...>>
{
    using type = uint_list<tails..., N>;
};

template <unsigned... tails>
struct push_back<0, uint_list<tails...>>
{
    using type = uint_list<tails...>;
};

template <unsigned N, unsigned Div = N / 2 + 1>
struct is_prime
{
    static constexpr unsigned value = N == 3 ? true : (N % Div == 0 ? false : is_prime<N, Div - 1>::value);
};

template <unsigned N>
struct is_prime<N, 2>
{
    static constexpr unsigned value = N == 2 ? true : !(N % 2 == 0);
};

template <unsigned Upper>
struct make_prime_list
{
    using type =
        typename push_back<is_prime<Upper>::value ? Upper : 0,
                           typename make_prime_list<Upper - 1>::type>::type;
};

template <>
struct make_prime_list<1>
{
    using type = uint_list<>;
};

void print(uint_list<>)
{
    std::cout << std::endl;
}

template <unsigned Last>
void print(uint_list<Last>)
{
    std::cout << Last << std::endl;
}

template <unsigned Head, unsigned... tails>
void print(uint_list<Head, tails...>)
{
    std::cout << Head << " ";
    print(uint_list<tails...>());
}

int main()
{
    print(make_prime_list<100>::type());
    return 0;
}