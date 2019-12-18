#include <iostream>
using namespace std;

template <typename C, typename T, typename U>
struct replace_type;

template <typename C, typename U>
struct replace_type<C, C, U>
{
    using type = U;
};

template <typename C, typename T, typename U>
struct replace_type<C *, T, U>
{
    using type = typename replace_type<C, T, U>::type *;
};

template <typename C, typename T, typename U>
struct replace_type<C &, T, U>
{
    using type = typename replace_type<C, T, U>::type &;
};

template <typename C, typename T, typename U, std::size_t N>
struct replace_type<C[N], T, U>
{
    using type = typename replace_type<C, T, U>::type[N];
};

template <typename C, typename T, typename U>
struct replace_type<C(), T, U>
{
    using type = typename replace_type<C, T, U>::type();
};

template <typename C, typename T, typename U, typename... Args>
struct replace_type<C(Args...), T, U>
{
    using type =
        typename replace_type<C, T, U>::type(typename replace_type<Args, T, U>::type...);
};

int main()
{
    cout << is_same<replace_type<int ***&(int *, int(&)[6]), int, const double>::type,
                    const double ***&(const double *, const double(&)[6])>::value
         << endl;
    return 0;
}
