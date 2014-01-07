/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    test.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_DETAIL_TEST_H
#define ZEN_GUARD_DETAIL_TEST_H

// #include <zen/function/defer.h>
// #include <zen/forward.h>
// #include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>

struct binary_class
{
    template<class T, class U>
    T operator()(T x, U y) const
    {
        // printf("%i + %i\n", x, y);
        return x+y;
    }

};

// typedef zen::defer_adaptor<binary_class_d> binary_class;

struct mutable_class
{
    template<class F>
    struct result;

    template<class F, class T, class U>
    struct result<F(T&, U)>
    {
        typedef T type;
    };

    template<class T, class U>
    T operator()(T & x, U y) const
    {
        return x+=y;
    }

};

struct unary_class
{
    template<class T>
    T&& operator()(T&& x) const
    {
        return std::forward<T>(x);
    }

};

struct void_class
{
    template<class T>
    void operator()(T) const
    {
    }
};

struct mono_class
{
    int operator()(int x) const
    {
        return x+1;
    }
};

struct tuple_class
{
    template<class T>
    int operator()(T t) const
    {
        return boost::fusion::at_c<0>(t) + 1;
    }
};

template<class R>
struct explicit_class
{
    template<class T>
    R operator()(T x)
    {
        return static_cast<R>(x);
    }
};

#endif
