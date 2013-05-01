/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    reveal.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_REVEAL_H
#define ZEN_GUARD_FUNCTION_REVEAL_H

// @begin
// reveal
// ======
// 
// Description
// -----------
// 
// The `reveal` function adaptor turns substitution failures into compile errors.
// Sometimes an error in a function that causes a substitution failure, will
// remove the function from valid overloads thus masking the error inside the
// function. The `reveal` adaptor reveals these errors by forcing a compile
// error, instead of a substitution failure.
// 
// Synopsis
// --------
// 
//     template<class F>
//     reveal_adaptor<F> reveal(F f);
// 
// @end

#include <zen/function/conditional.h>
#include <zen/function/detail/nullary_tr1_result_of.h>

namespace zen { 

namespace detail {

template<class F>
struct reveal_adaptor_base : function_adaptor_base<F>
{

    reveal_adaptor_base()
    {}

    template<class X>
    reveal_adaptor_base(X x) : function_adaptor_base<F>(x)
    {}

    struct fail
    {};

    template<class>
    struct result
    {
        typedef fail type;
    };

#ifndef ZEN_NO_VARIADIC_TEMPLATES
    template<class... T>
    fail operator()(T &&... x) const
    {
        this->get_function()(zen::forward<T>(x)...);
        return fail();
    }
#else
#define ZEN_REVEAL_ADAPTOR_BASE(z, n, data) \
    template<ZEN_PP_PARAMS_Z(z, n, class T)> \
    fail operator()(ZEN_PP_PARAMS_Z(z, n, T, ZEN_FORWARD_REF() BOOST_PP_INTERCEPT, x)) const \
    { \
        this->get_function()(ZEN_PP_PARAMS_Z(z, n, zen::forward<T, > BOOST_PP_INTERCEPT, (x))); \
        return fail(); \
    }
BOOST_PP_REPEAT_FROM_TO_1(1, ZEN_PARAMS_LIMIT, ZEN_REVEAL_ADAPTOR_BASE, ~)
#endif
};

}

template<class F>
struct reveal_adaptor
: zen::conditional_adaptor<F, detail::reveal_adaptor_base<F> >
{
    reveal_adaptor()
    {}

    template<class X>
    reveal_adaptor(X x) : zen::conditional_adaptor<F, detail::reveal_adaptor_base<F> >(x, x)
    {}
};

template<class F>
reveal_adaptor<F> reveal(F f)
{
    return reveal_adaptor<F>(f);
}

}

ZEN_NULLARY_TR1_RESULT_OF_N(1, zen::reveal_adaptor)

#if 0
#include <zen/test.h>

ZEN_TEST_CASE(reveal_test)
{
}

#endif

#endif
