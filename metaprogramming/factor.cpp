#include <type_traits>
#include <iostream>

template <unsigned... vals>
struct uint_list
{
};

template <unsigned N>
struct uint_const : std::integral_constant<unsigned, N>
{
};

template <unsigned, typename>
struct push_front;

template <unsigned N, unsigned... tails>
struct push_front<N, uint_list<tails...>>
{
    using type = uint_list<N, tails...>;
};

template <unsigned... tails>
struct push_front<0, uint_list<tails...>>
{
    using type = uint_list<tails...>;
};

template <unsigned N, unsigned Div = 2>
struct make_factor_of
{
    static constexpr bool Flag = (N % Div == 0);

    static constexpr unsigned Next = Flag ? N / Div : N;

    static constexpr unsigned NextDiv = Flag ? Div : Div + 1;

    using type = typename push_front<
        Flag ? Div : 0,
        typename make_factor_of<Next, NextDiv>::type>::type;
};

template <unsigned N>
struct make_factor_of<N, N>
{
    using type = uint_list<N>;
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
    print(make_factor_of<987>::type());
    return 0;
}