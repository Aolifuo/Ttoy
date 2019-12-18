#include <iostream>
#include <type_traits>
template <int... vals>
struct IntList;

template <typename>
struct ListPrinter;

template <typename, int>
struct push_back;

template <int, typename>
struct push_front;

template <typename, typename>
struct concat;

template <typename, int, bool>
struct CompareFilter;

template <typename, bool>
struct quicksort;

template <int... Vals, int N>
struct push_back<IntList<Vals...>, N>
{
    using type = IntList<Vals..., N>;
};

template <int N, int... Vals>
struct push_front<N, IntList<Vals...>>
{
    using type = IntList<N, Vals...>;
};

template <typename Prev, int Head, int... Tails>
struct concat<Prev, IntList<Head, Tails...>>
{
    using type = typename concat<
        typename push_back<Prev, Head>::type,
        IntList<Tails...>>::type;
};

template <typename Prev>
struct concat<Prev, IntList<>>
{
    using type = Prev;
};

template <int Head, int... Tails, int N, bool Flag>
struct CompareFilter<IntList<Head, Tails...>, N, Flag>
{
    static constexpr bool select = Flag ? Head < N : Head >= N;
    using type = std::conditional_t<select,
                                    typename push_front<Head, typename CompareFilter<IntList<Tails...>, N, Flag>::type>::type,
                                    typename CompareFilter<IntList<Tails...>, N, Flag>::type>;
};

template <int N, bool Flag>
struct CompareFilter<IntList<>, N, Flag>
{
    using type = IntList<>;
};

template <int Head, int... Tails, bool Flag>
struct quicksort<IntList<Head, Tails...>, Flag>
{
    using type = typename concat<
        typename push_back<
            typename quicksort<
                typename CompareFilter<IntList<Tails...>, Head, Flag>::type,
                Flag>::type,
            Head>::type,
        typename quicksort<
            typename CompareFilter<IntList<Tails...>, Head, !Flag>::type,
            Flag>::type>::type;
};

template <bool Flag>
struct quicksort<IntList<>, Flag>
{
    using type = IntList<>;
};

template <int Head, int... Tails>
struct ListPrinter<IntList<Head, Tails...>>
{
    static void print()
    {
        std::cout << Head << " ";
        ListPrinter<IntList<Tails...>>::print();
    }
};

template <>
struct ListPrinter<IntList<>>
{
    static void print()
    {
        std::cout << std::endl;
    }
};

int main()
{
    ListPrinter<typename quicksort<IntList<7, 3, 2, 5, 9, 2, 1>, true>::type>::print();
    return 0;
}