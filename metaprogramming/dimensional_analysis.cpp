#include <type_traits>
#include <iostream>

template <typename _Type, _Type...>
struct basic_unit;

using scalar = basic_unit<int, 0, 0, 0, 0, 0, 0, 0>;
using length = basic_unit<int, 1, 0, 0, 0, 0, 0, 0>;
using mass = basic_unit<int, 0, 1, 0, 0, 0, 0, 0>;
using time = basic_unit<int, 0, 0, 1, 0, 0, 0, 0>;
using charge = basic_unit<int, 0, 0, 0, 1, 0, 0, 0>;
using temperature = basic_unit<int, 0, 0, 0, 0, 1, 0, 0>;
using amount_of_substance = basic_unit<int, 0, 0, 0, 0, 0, 1, 0>;
using luminous_intensity = basic_unit<int, 0, 0, 0, 0, 0, 0, 1>;

template <typename _Type, typename _Unit>
class SI_units
{
public:
    SI_units() = default;
    SI_units(_Type x) : _value(x) {}
    _Type value() const { return _value; }

    operator _Type() { return _value; }

private:
    _Type _value = 0;
};

template <typename Unit1, typename Unit2>
struct multi_type;

template <typename Unit1, typename Unit2>
struct div_type;

template <int... Arg1, int... Arg2>
struct multi_type<basic_unit<int, Arg1...>, basic_unit<int, Arg2...>>
{
    using type = basic_unit<int, (Arg1 + Arg2)...>;
};

template <int... Arg1, int... Arg2>
struct div_type<basic_unit<int, Arg1...>, basic_unit<int, Arg2...>>
{
    using type = basic_unit<int, (Arg1 - Arg2)...>;
};

template <typename Type1, typename Type2, typename Unit>
decltype(auto) operator+(const SI_units<Type1, Unit> &left, const SI_units<Type2, Unit> &right)
{
    return SI_units<decltype(left.value() + right.value()), Unit>(left.value() + right.value());
}

template <typename Type1, typename Type2, typename Unit>
decltype(auto) operator-(const SI_units<Type1, Unit> &left, const SI_units<Type2, Unit> &right)
{
    return SI_units<decltype(left.value() - right.value()), Unit>(left.value() - right.value());
}

template <typename Type1, typename Type2, typename Unit1, typename Unit2>
decltype(auto) operator*(const SI_units<Type1, Unit1> &left, const SI_units<Type2, Unit2> &right)
{
    return SI_units<decltype(left.value() * right.value()), typename multi_type<Unit1, Unit2>::type>(left.value() * right.value());
}

template <typename Type1, typename Type2, typename Unit1, typename Unit2>
decltype(auto) operator/(const SI_units<Type1, Unit1> &left, const SI_units<Type2, Unit2> &right)
{
    return SI_units<decltype(left.value() / right.value()), typename div_type<Unit1, Unit2>::type>(left.value() / right.value());
}

int main()
{
    SI_units<double, length> s(2.33);
    SI_units<double, time> t(5);
    auto v = s / t;
    auto a = v / t;
    std::cout << v << std::endl;
    return 0;
};