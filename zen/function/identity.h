/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    identity.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_IDENTITY_H
#define ZEN_GUARD_FUNCTION_IDENTITY_H

// @begin
// identity
// ========
// 
// Description
// -----------
// 
// The `identity` function is an unary function object that returns whats given to it. 
// 
// Synopsis
// --------
// 
//     struct
//     {
//         template<class T>
//         T&& operator()(T&& x) const
//         {
//             return zen::forward<T>(x);
//         }
//     } identity;
// 
// @end

#include <zen/function/static.h>

namespace zen { namespace detail {

struct identity_base
{
    template<class F>
    struct result;

    template<class F, class T>
    struct result<F(T)>
    : zen::add_forward_reference<T>
    {};

    template<class T>
    ZEN_FORWARD_REF(T) operator()(ZEN_FORWARD_REF(T) x) const
    {
        return zen::forward<T>(x);
    }
};

}

static_<detail::identity_base> identity = {};

}

#ifdef ZEN_TEST
#include <zen/test.h>

ZEN_TEST_CASE(identity_test)
{
    ZEN_TEST_EQUAL( zen::identity(10), 10 );
}

#endif

#endif
