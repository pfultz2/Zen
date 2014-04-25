/*=============================================================================
    Copyright (c) 2013 Paul Fultz II
    returns.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RETURNS_H
#define ZEN_GUARD_RETURNS_H

#include <utility>

namespace zen {
namespace returns_detail {
struct void_ {};

template<class T> T&& operator,(T&& x, void_)
{
    return std::forward<T>(x);
}
#define ZEN_AVOID(...) ((__VA_ARGS__), zen::returns_detail::void_())

#if !defined(ZEN_NO_NOEXCEPT)
template<typename T>
typename std::remove_reference<T>::type&&
move(T&& x) noexcept;
void move(void_);
#endif
}
}

#if !defined(ZEN_NO_NOEXCEPT) && !defined(ZEN_NO_RVALUE_REFS)
#define ZEN_RETURNS(...) \
    noexcept(noexcept(decltype(__VA_ARGS__)(zen::returns_detail::move(ZEN_AVOID(__VA_ARGS__))))) \
    -> decltype(__VA_ARGS__) \
    { return (__VA_ARGS__); } static_assert(true, "")
#else
#define ZEN_RETURNS(...) -> decltype(__VA_ARGS__) { return __VA_ARGS__; } static_assert(true, "")
#endif

#define ZEN_AUTO_FORWARD(x) std::forward<decltype(x)>(x)

#endif