#include <bits/stdc++.h>
using namespace std;

template <typename Type>
class range_type
{
public:
    range_type(Type lower, Type upper)
        : _lower(lower), _upper(upper) {}
    class iterator
    {
    public:
        iterator(Type v) : _value(v) {}
        Type &operator*() { return _value; }
        iterator operator++()
        {
            _value++;
            return *this;
        }
        iterator operator++(int)
        {
            iterator copy(*this);
            _value++;
            return copy;
        }
        bool operator==(const iterator &other) const { return _value == other._value; }
        bool operator!=(const iterator &other) const { return _value != other._value; }

    private:
        Type _value;
    };

    iterator begin() { return iterator(_lower); }
    iterator end() { return iterator(_upper); }

private:
    Type _lower, _upper;
};

template <typename Type>
range_type<Type> range(Type lower, Type upper)
{
    return range_type<Type>(lower, upper + 1);
}

int main()
{
    for (auto &e : range(1, 100))
        cout << e << ends;
    return 0;
}