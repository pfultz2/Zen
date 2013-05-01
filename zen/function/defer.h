/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    defer.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_DEFER_H
#define ZEN_GUARD_FUNCTION_DEFER_H

// @begin
// defer
// =====
// 
// Description
// -----------
// 
// The `defer` function adaptor implements the `result_of` protocol for functions
// by using type deduction. This can be useful to make functions(such as lambdas)
// compatible with old TR1-style `result_of` protocol.
// 
// Synopsis
// --------
// 
//     template<class F>
//     defer_adaptor<F> defer(F f);
// 
// @end

#include <zen/function/adaptor.h>
#include <zen/function/is_callable.h>
#include <zen/function/detail/nullary_tr1_result_of.h>

namespace zen {

template<class F>
struct defer_adaptor : F
{
    defer_adaptor()
    {};

    template<class X>
    defer_adaptor(X x) : F(x)
    {}

    typedef void zen_is_callable_by_result_tag;

    template<class X, class Enable = void>
    struct result;

    struct no_result
    {};

    template<class X>
    struct nullary_result
    {
        typedef ZEN_XTYPEOF_TPL(zen::declval<X>()()) type;
    };

    template<class X>
    struct result<X(), void>
    : boost::mpl::if_<is_callable<F()>, nullary_result<F>, no_result>
    {};

#ifndef ZEN_NO_VARIADIC_TEMPLATES
    template<class X, class T0, class... T>
    struct result<X(T0, T...), ZEN_CLASS_REQUIRES(zen::is_callable<F(T0, T...)>)>
    {
        typedef ZEN_XTYPEOF_TPL(zen::declval<F>()(zen::declval<T0>(), zen::declval<T>()...)) type;
    };
#else
    #define ZEN_DEFER_ADAPTOR(z, n, data) \
    template<class X, ZEN_PP_PARAMS_Z(z, n, class T)> \
    struct result<X(ZEN_PP_PARAMS_Z(z, n, T)), ZEN_CLASS_REQUIRES(zen::is_callable<F(ZEN_PP_PARAMS_Z(z, n, T))>)> \
    { \
        typedef ZEN_XTYPEOF_TPL(zen::declval<F>()(ZEN_PP_PARAMS_Z(z, n, zen::declval<T, >() BOOST_PP_INTERCEPT))) type; \
    };
    BOOST_PP_REPEAT_FROM_TO_1(1, ZEN_PARAMS_LIMIT, ZEN_DEFER_ADAPTOR, ~)

#endif

};


template<class F>
defer_adaptor<F> defer(F f)
{
    return defer_adaptor<F>(f);
}

}

ZEN_NULLARY_TR1_RESULT_OF_N(1, zen::defer_adaptor)


#endif
