/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    lazy.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_LAZY_H
#define ZEN_GUARD_FUNCTION_LAZY_H

// @begin
// lazy
// ====
// 
// Description
// -----------
// 
// The `lazy` function adaptor returns a lazy phoenix function so it can accept
// phoenix actors as parameters.
// 
// Synopsis
// --------
// 
//     template<class F>
//     lazy_adaptor<F> lazy(F f);
// 
// Example
// -------
// 
//     struct sum
//     {
//         template<class T>
//         T sum(T x, T y)
//         {
//             return x+y;
//         }
//     };
// 
//     using zen::ph::_1;
//     using zen::ph::_2;
//     assert(3 == lazy(sum())(1, 2)());
//     assert(3 == lazy(sum())(_1, _2)(1, 2));
//     assert(3 == lazy(sum())(_1, 2)(1));
// 
// @end

#include <zen/function/adaptor.h>
#include <zen/function/detail/nullary_tr1_result_of.h>
#include <boost/phoenix/function/function.hpp>
#include <boost/phoenix/core/is_actor.hpp>
#include <zen/traits.h>

namespace zen { 

template<class F>
struct lazy_adaptor : boost::phoenix::function<F>
{
    lazy_adaptor() {}

    template<class X>
    lazy_adaptor(X x) : boost::phoenix::function<F>(x)
    {}

    // We add a result since the phoenix::function isn't implemented correctly
    template<class X, class Enable = void>
    struct result;

#ifndef ZEN_NO_VARIADIC_TEMPLATES
    template<class X, class... T>
    struct result<X(T...), ZEN_CLASS_REQUIRES(zen::is_callable<X(T...)>)>
    : zen::result_of<boost::phoenix::function<F>(const typename zen::purify<T>::type&...)>
    {};
#else
    #define ZEN_LAZY_ADAPTOR(z, n, data) \
    template<class X BOOST_PP_COMMA_IF(n) ZEN_PP_PARAMS_Z(z, n, class T)> \
    struct result<X(ZEN_PP_PARAMS_Z(z, n, T)), ZEN_CLASS_REQUIRES(zen::is_callable<X(ZEN_PP_PARAMS_Z(z, n, T))>)> \
    : zen::result_of<boost::phoenix::function<F>( ZEN_PP_PARAMS_Z(z, n, const typename zen::purify<T, >::type& BOOST_PP_INTERCEPT) )> \
    {};
    //
    BOOST_PP_REPEAT_1(ZEN_PARAMS_LIMIT, ZEN_LAZY_ADAPTOR, ~)
#endif
};

//lazy
//TODO: Use boost::phoenix::detail::expression::function_eval instead
template<class F>
lazy_adaptor<F> lazy(F f)
{
    return lazy_adaptor<F>(f);
}

}

ZEN_NULLARY_TR1_RESULT_OF_N(1, zen::lazy_adaptor)


#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/static.h>
#include <zen/function/placeholders.h>
#include <boost/phoenix/core/argument.hpp>

zen::static_<zen::lazy_adaptor<binary_class> > binary_lazy = {};

ZEN_TEST_CASE(lazy_test)
{
    using zen::ph::_1;
    using zen::ph::_2;
    ZEN_TEST_EQUAL(3, binary_lazy(1, 2)());
    ZEN_TEST_EQUAL(3, binary_lazy(_1, _2)(1, 2));
    ZEN_TEST_EQUAL(3, binary_lazy(_1, 2)(1));
}
#endif

#endif
