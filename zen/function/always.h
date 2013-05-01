/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    always.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_ALWAYS_H
#define ZEN_GUARD_FUNCTION_ALWAYS_H

// @begin
// always
// ======
// 
// Description
// -----------
// 
// The `always` function returns a function object that will always return the
// value given to it, no matter what parameters are passed to the function
// object.
// 
// Synopsis
// --------
// 
//     template<class T>
//     /* unspecified */ always(T value);
// 
// Example
// -------
// 
//     int ten = 10;
//     assert( zen::always(ten)(1,2,3,4,5) == 10 );
// 
// @end

#include <zen/function/variadic.h>
#include <zen/function/static.h>

namespace zen { namespace detail {

template<class T>
struct always_base
{
    T x;
    
    always_base()
    {}
    
    template<class X>
    always_base(X x) : x(x)
    {}

    template<class>
    struct result;

    template<class X, class A>
    struct result<X(A)>
    {
        typedef T type;
    };

    template<class A>
    T operator()(A) const
    {
        return this->x;
    }
};

}

template<class T>
variadic_adaptor<detail::always_base<T> > always(T x)
{
    return variadic_adaptor<detail::always_base<T> >(x);
}

}

#ifdef ZEN_TEST
#include <zen/test.h>

ZEN_TEST_CASE(always_test)
{
    int ten = 10;
    ZEN_TEST_EQUAL( zen::always(ten)(1,2,3,4,5), 10 );
}

#endif

#endif
