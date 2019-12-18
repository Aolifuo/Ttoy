#pragma once
#include <iostream>
#include <type_traits>

template <typename T, T... vals>
struct integral_sequence
{
    using value_type = T;
};

template <typename>
struct length;

template <typename T, T N, typename>
struct push_front;

template <typename T, typename, T N>
struct push_back;

template <typename, typename, typename>
struct concat;

template <typename, typename>
struct reverse;

template <typename T, template <typename U, U> class, typename>
struct map;

template <typename T, T, template <typename U, U, U> class, typename>
struct reduce;

template <typename T, template <typename U, U> class, typename>
struct filter;

template <typename T, T... vals>
struct length<integral_sequence<T, vals...>>
    : std::integral_constant<T, sizeof...(vals)>
{
};

template <typename, bool, typename>
struct quick_sort;

template <typename T, T N, T... tails>
struct push_front<T, N, integral_sequence<T, tails...>>
{
    using type = integral_sequence<T, N, tails...>;
};

template <typename T, T... tails, T N>
struct push_back<T, integral_sequence<T, tails...>, N>
{
    using type = integral_sequence<T, tails..., N>;
};

template <typename T, typename L1, T head, T... tails>
struct concat<T, L1, integral_sequence<T, head, tails...>>
{
    using type = typename concat<T, typename push_back<T, L1, head>::type, integral_sequence<T, tails...>>::type;
};

template <typename T, typename L1>
struct concat<T, L1, integral_sequence<T>>
{
    using type = L1;
};

template <typename T, T head, T... tails>
struct reverse<T, integral_sequence<T, head, tails...>>
{
    using type = typename push_back<T, typename reverse<T, integral_sequence<T, tails...>>::type, head>::type;
};

template <typename T>
struct reverse<T, integral_sequence<T>>
{
    using type = integral_sequence<T>;
};

template <typename T, template <typename U, U> class Mapper, T head, T... tails> //传进元函数
struct map<T, Mapper, integral_sequence<T, head, tails...>>
{
    using type = typename push_front<T, Mapper<T, head>::value,
                                     typename map<T, Mapper, integral_sequence<T, tails...>>::type>::type;
};

template <typename T, template <typename U, U> class Mapper>
struct map<T, Mapper, integral_sequence<T>>
{
    using type = integral_sequence<T>;
};

template <typename T, T N, template <typename U, U, U> class F, T head, T... tails>
struct reduce<T, N, F, integral_sequence<T, head, tails...>>
{
    static constexpr T value = F<T, head, reduce<T, N, F, integral_sequence<T, tails...>>::value>::value;
};

template <typename T, T N, template <typename U, U, U> class F>
struct reduce<T, N, F, integral_sequence<T>>
{
    static constexpr T value = N;
};

template <typename T, template <typename U, U> class Filter, T head, T... tails>
struct filter<T, Filter, integral_sequence<T, head, tails...>>
{
    using type = std::conditional_t<Filter<T, head>::value,
                                    typename push_front<T, head, typename filter<T, Filter, integral_sequence<T, tails...>>::type>::type,
                                    typename filter<T, Filter, integral_sequence<T, tails...>>::type>;
};

template <typename T, template <typename U, U> class Filter>
struct filter<T, Filter, integral_sequence<T>>
{
    using type = integral_sequence<T>;
};

/*template <typename T, bool Label, T head, T... tails>
struct quick_sort<T, Label, integral_sequence<T, head, tails...>>
{
    template <typename T, T N>
    struct less
    {
        static constexpr value = (N < head);
    };

    typename<typename T, T N> struct greater
    {
        static constexpr value = (N >= head);
    };

    struct Compare
    {
        using type = std::conditional_t<Label, less, greater>;
    };

    using type = typename concat<
        typename quick_sort<T, Label, typename filter<T, typename Compare::type, integral_sequence<T, tails...>>::type>::type,
        typename push_front<T, head, typename quick_sort<T, !Label, typename filter<T, typename Compare::type>::type>>::type>::type;
};*/

template <typename T>
constexpr typename T::value_type length_v = length<T>::value;

template <typename T, T N, typename U>
using push_front_t = typename push_front<T, N, U>::type;

template <typename T, typename L, T N>
using push_back_t = typename push_back<T, L, N>::type;

template <typename T, typename L1, typename L2>
using concat_t = typename concat<T, L1, L2>::type;

template <typename T, typename L>
using reverse_t = typename reverse<T, L>::type;

template <typename T, template <typename U, U> class Mapper, typename S>
using map_t = typename map<T, Mapper, S>::type;

template <typename T, template <typename U, U> class Filter, typename S>
using filter_t = typename filter<T, Filter, S>::type;

template <typename T, T N, template <typename U, U, U> class F, typename S>
constexpr T reduce_v = reduce<T, N, F, S>::value;

template <typename T, T N>
struct increment
{
    static constexpr T value = N + 1;
};

template <typename T, T A, T B>
struct add
{
    static constexpr T value = A + B;
};

template <typename T, T A, T B>
struct multiply
{
    static constexpr T value = A * B;
};

template <typename T, T A, T B>
struct max
{
    static constexpr T value = A > B ? A : B;
};

template <typename T, T A, T B>
struct min
{
    static constexpr T value = A < B ? A : B;
};

template <typename T, T N>
struct is_even
{
    static constexpr bool value = (N % 2 == 0);
};

template <typename T, T N>
struct is_odd
{
    static constexpr bool value = (N % 2 != 0);
};

template <typename T>
void print(integral_sequence<T>)
{
    std::cout << std::endl;
}

template <typename T, T head>
void print(integral_sequence<T, head>)
{
    std::cout << head << std::endl;
}

template <typename T, T head, T... tails>
void print(integral_sequence<T, head, tails...>)
{
    std::cout << head << " ";
    print(integral_sequence<T, tails...>());
}

template <int N>
constexpr int ConstInt_v = std::integral_constant<int, N>::value;

template <int... vals>
using ArrInt = integral_sequence<int, vals...>;