/**
 *成员函数检测
 *检测类  是否有成员函数 func
 */

#include <iostream>
#include <vector>
#include <type_traits>

#define _IF_CLASS_HAS_FUNC_

#ifdef _IF_CLASS_HAS_FUNC_
#define HAS_FUNC(_CLASS_, _FUNC_) if_has_##_FUNC_<_CLASS_>::value
#define _IF_HAS_FUNC_(_NAME_)                                                     \
    template <typename CLASS_NAME>                                                \
    struct if_has_##_NAME_                                                        \
    {                                                                             \
        template <typename U>                                                     \
        static std::true_type get_return(decltype(std::declval<U>()._NAME_()) *); \
        template <typename U>                                                     \
        static std::false_type get_return(...);                                   \
        using type = decltype(get_return<CLASS_NAME>(nullptr));                   \
        static constexpr bool value = type::value;                                \
    }

#endif //if_has_func

_IF_HAS_FUNC_(size);

int main()
{
    std::cout << HAS_FUNC(std::vector<int>, size) << std::endl;
    return 0;
}