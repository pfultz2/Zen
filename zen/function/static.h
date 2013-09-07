/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    static.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_STATIC_H
#define ZEN_GUARD_FUNCTION_STATIC_H

// @begin
// static
// ======
// 
// Description
// -----------
// 
// The `static_` adaptor is a static function adaptor that allows any default-
// constructible function object to be static-initialized.
// 
// Synopsis
// --------
// 
//     template<class F>
//     class static_;
// 
// Example
// -------
// 
//     // In C++03 this class can't be static-initialized, because of the 
//     // default constructor.
//     struct times_function
//     {
//         double factor;
//         times2_function() : factor(2)
//         {}
//         template<class T>
//         T operator()(T x) const
//         {
//             return x*factor;
//         }
//     };
// 
//     static_<times_function> times2 = {};
// 
//     assert(6 == times2(3));
// 
// @end

#include <zen/function/adaptor.h>
#include <zen/function/result_of.h>
#include <zen/function/detail/nullary_tr1_result_of.h>

#if !defined(ZEN_NO_VARIADIC_TEMPLATES) && !defined(ZEN_NO_RVALUE_REFS)
#include <zen/function/detail/c11/perfect_facade.h>
#elif !defined(ZEN_NO_RVALUE_REFS)
#include <zen/function/detail/msvc/perfect_facade.h>
#else
#include <zen/function/detail/c03/perfect_facade.h>
#endif

namespace zen { 

// TODO: Add support for forwarding nullary functions as well
#ifndef ZEN_NO_VARIADIC_TEMPLATES
template<class F>
struct static_
{
    typedef F function;
    template<class S>
    struct result
    : zen::result_of<S, function>
    {};

    F get_function() const
    {
        return F();
    }

    ZEN_PERFECT_FACADE(function, function())
};

#else
template<class F, class Enable = void>
struct static_;

template<class F>
struct static_<F, ZEN_CLASS_REQUIRES(exclude is_callable<F()>)>
{
    typedef F function;
    template<class S>
    struct result
    : zen::result_of<S, function>
    {};

    F get_function() const
    {
        return F();
    }

    ZEN_PERFECT_FACADE(function, function())
};

template<class F>
struct static_<F, ZEN_CLASS_REQUIRES(is_callable<F()>)>
{
    typedef F function;
    template<class S>
    struct result
    : zen::result_of<S, function>
    {};

    typename zen::result_of<F()>::type operator()() const
    {
        return function()();
    }

    F get_function() const
    {
        return F();
    }

    ZEN_PERFECT_FACADE(function, function())
};

#endif

}

ZEN_NULLARY_TR1_RESULT_OF_N(1, zen::static_)

#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/detail/test.h>

zen::static_<binary_class> binary_static = {};

zen::static_<void_class> void_static = {};

zen::static_<mono_class> mono_static = {};

ZEN_TEST_CASE(static_test)
{
    void_static(1);
    ZEN_TEST_EQUAL(3, binary_static(1, 2));
    ZEN_TEST_EQUAL(3, mono_static(2));
}
#endif

#endif
