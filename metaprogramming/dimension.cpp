#include <iostream>
using namespace std;

template <typename T, unsigned Count>
struct dimension_count
{
    static constexpr unsigned value = Count;
};

template <typename T, unsigned Count, unsigned N>
struct dimension_count<T[N], Count>
{
    static constexpr unsigned value = dimension_count<T, Count + 1>::value;
};

int main()
{
    cout << dimension_count<int[1][2][3], 0>::value << endl;
    return 0;
};