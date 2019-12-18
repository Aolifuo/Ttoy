#include <bits/stdc++.h>
using namespace std;

template <typename T>
using Ptr = T *;

template <typename T, unsigned N>
struct Times
{
    using type = Ptr<typename Times<T, N - 1>::type>;
};

template <typename T>
struct Times<T, 1>
{
    using type = Ptr<T>;
};

template <unsigned N>
using CharPtr = typename Times<char, N>::type;

template <typename T, typename U>
struct is_equal
{
    static constexpr bool value = false;
};

template <typename T>
struct is_equal<T, T>
{
    static constexpr bool value = true;
};

int main()
{
    cout << is_equal<int, double>::value << endl;
    cout << is_equal<int, int>::value << endl;
    return 0;
}