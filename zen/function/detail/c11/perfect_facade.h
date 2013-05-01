/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    perfect_facade.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_C11_PERFECT_FACADE_H
#define ZEN_GUARD_C11_PERFECT_FACADE_H

#include <zen/function/result_of.h>
#include <zen/forward.h>

#define ZEN_PERFECT_FACADE(F, f) \
template<class... T> \
typename zen::result_of<F(T&&...)>::type \
operator()(T && ... x) const \
{ \
    return f(zen::forward<T>(x)...); \
}

#define ZEN_PERFECT_FACADE_TPL(F, f, tpl) \
template<tpl T_ ## tpl, class... T> \
typename zen::result_of<F(T&&...)>::type \
operator()(T && ... x) const \
{ \
    return f(zen::forward<T>(x)...); \
}

#endif
