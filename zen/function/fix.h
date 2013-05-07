/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    fix.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_FIX_H
#define ZEN_GUARD_FUNCTION_FIX_H

// @begin
// fix
// ===
// 
// Description
// -----------
// 
// The `fix` function adaptor implements a fixed-point combinator. This can be
// used to write recursive functions.
// 
// Synopsis
// --------
// 
//     template<class F>
//     fix_adaptor<F> fix(F f);
// 
// Example
// -------
// 
//     struct factorial
//     {
//         // This is used here to avoid incomplete types on older compilers.
//         // Instead of detecting whether the function is callable, it will just
//         // detect if result has a nested type.
//         typedef void zen_is_callable_by_result_tag;
//         template<class>
//         struct result;
// 
//         template<class X, class Self, class T>
//         struct result<X(Self, T)>
//         : boost::decay<T>
//         {};
// 
//         template<class Self, class T>
//         T operator()(Self s, T x) const
//         {
//             return x == 0 ? 1 : x * s(x-1);
//         }
//     };
// 
//     int r = fix(factorial())(5);
//     assert(r, 5*4*3*2*1);
// 
// @end

#include <zen/function/variadic.h>
#include <zen/function/partial.h>
#include <zen/function/detail/nullary_tr1_result_of.h>

#ifndef ZEN_NO_VARIADIC_TEMPLATES
#include <tuple>
#include <boost/fusion/adapted/std_tuple.hpp>
#define ZEN_FIX_SEQUENCE std::tuple
#else
#include <boost/fusion/container/vector.hpp>
#define ZEN_FIX_SEQUENCE boost::fusion::vector
#endif


namespace zen { namespace detail {

template<class F>
struct fix_point : function_adaptor_base<F>
{
    typedef void zen_is_callable_by_result_tag;
    fix_point() {};

    template<class X>
    fix_point(X x) : function_adaptor_base<F>(x)
    {};

    template<class X, class Enable = void>
    struct result;

    template<class X, class Fix, class T>
    struct result<X(Fix, T), ZEN_CLASS_REQUIRES(boost::fusion::traits::is_sequence<typename boost::decay<T>::type>)>
    : zen::invoke_result<F, typename boost::fusion::result_of::as_vector<typename boost::fusion::result_of::join
        <
            ZEN_FIX_SEQUENCE<typename boost::add_const<typename boost::decay<Fix>::type>::type&>,
            typename boost::decay<T>::type
        >::type>::type >
    {}; 

    template<class Fix, class T>
    typename result<F(const Fix&, const T&)>::type operator()(const Fix& f, const T & x) const
    {
        return zen::invoke(this->get_function(), boost::fusion::as_vector(boost::fusion::join
        (
            ZEN_FIX_SEQUENCE<const Fix&>(f),
            x
        )));
    }
};

template<class F>
struct fix_adaptor_base : function_adaptor_base<fix_point<F> >
{
    typedef void zen_is_callable_by_result_tag;
    fix_adaptor_base() {};

    template<class X>
    fix_adaptor_base(X x) : function_adaptor_base<fix_point<F> >(x)
    {};

    template<class>
    struct result;

    template<class X, class T>
    struct result<X(T)>
    : fix_point<F>::template result<fix_point<F>(variadic_adaptor<X>, T)>
    {};

    template<class T>
    typename result<fix_adaptor_base(const T&)>::type 
    operator()(const T& x) const
    {
        return this->get_function()(variadic(*this), x);
    }
};
}

template<class F>
struct fix_adaptor : zen::variadic_adaptor<detail::fix_adaptor_base<F> >
{
    typedef zen::variadic_adaptor<detail::fix_adaptor_base<F> > base;
    fix_adaptor()
    {}

    // MSVC Workarounds
    fix_adaptor(const fix_adaptor& rhs) : base(static_cast<const base&>(rhs))
    {}

    template<class X>
    fix_adaptor(X x) : base(x)
    {}
};

template<class F>
fix_adaptor<F> fix(F f)
{
    return fix_adaptor<F>(f);
}
}

ZEN_NULLARY_TR1_RESULT_OF_N(1, zen::fix_adaptor)


#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/static.h>
#include <zen/function/reveal.h>
#include <zen/function/placeholders.h>
#include <zen/function/lazy.h>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/statement/if.hpp>

struct factorial_t
{
    typedef void zen_is_callable_by_result_tag;
    template<class>
    struct result;

    template<class X, class Self, class T>
    struct result<X(Self, T)>
    : boost::decay<T>
    {};

    template<class Self, class T>
    T operator()(Self s, T x) const
    {
        return x == 0 ? 1 : x * s(x-1);
    }
};

// TODO: Add suport for type deduction with fix adaptor
// struct factorial_t
// {
//     typedef void zen_is_callable_by_result_tag;
//     template<class>
//     struct result;

//     template<class X, class Self, class T>
//     struct result<X(Self, T)>
//     {
//         static typename boost::decay<Self>::type& s;
//         static typename boost::decay<T>::type& x;
//         typedef ZEN_XTYPEOF_TPL(x == 0 ? 1 : x * s(x-1)) type;
//     };

//     template<class Self, class T>
//     typename result<factorial_t(Self, T)>::type 
//     operator()(Self s, T x) const
//     {
//         return x == 0 ? 1 : x * s(x-1);
//     }
// };

zen::static_<zen::fix_adaptor<factorial_t> > factorial = {};

ZEN_TEST_CASE(fix_test)
{
    using zen::ph::_1;
    using zen::ph::_2;
    using boost::phoenix::if_else;

    int r = factorial(5);
    // int r = zen::fix
    // (
    //     if_else
    //     (
    //         _2 == 0, 
    //         1, 
    //         _2 * _1(_2 - 1)
    //     )
    // )(5);
    // printf("%i\n", r);
    ZEN_TEST_EQUAL(r, 5*4*3*2*1);

}

#endif

#endif
