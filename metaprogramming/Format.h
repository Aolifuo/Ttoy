#pragma once

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
void print(const T &t)
{
    cout << t << endl;
}

template <typename T, typename... Args>
void print(const T &t, const Args &... rest)
{
    cout << t;
    print(rest...);
}

const char *convert(const std::string s)
{
    return s.c_str();
}

template <typename T,
          typename = std::enable_if_t<!std::is_same<std::decay_t<T>, std::string>::value>>
decltype(auto) convert(T &&arg)
{
    return std::forward<T>(arg);
}

template <typename... Args>
std::string fmt(const char *ps, Args &&... rest)
{
    char buf[256] = {0};
    snprintf(buf, sizeof(buf), ps, convert(std::forward<Args>(rest))...);
    return buf;
}