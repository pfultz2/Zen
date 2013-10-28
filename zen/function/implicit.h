/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    implicit.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_IMPLICIT_H
#define ZEN_GUARD_FUNCTION_IMPLICIT_H

// @begin
// implicit
// ========
// 
// Description
// -----------
// 
// The `implicit` adaptor is a static function adaptor that uses the type that
// return value can be converted to in order to determine the type of the
// template parameter. Since it is static function adaptor, the function must be
// default constructible.
// 
// Synopsis
// --------
// 
//     template<template <class> class F>
//     class implicit<F>;
// 
// Example
// -------
// 
//     template<class T>
//     struct auto_caster
//     {
//         template<class X>
//         struct result
//         {
//             typedef T type;
//         };
//         template<class U>
//         T operator()(U x)
//         {
//             return T(x);
//         }
//     };
// 
//     implicit<auto_caster> auto_cast = {};
// 
//     struct auto_caster_foo
//     {
//         int i;
//         explicit auto_caster_foo(int i) : i(i) {}
// 
//     };
// 
//     float f = 1.5;
//     int i = auto_cast(f);
//     auto_caster_foo x = auto_cast(1);
//     assert(1 == i);
//     assert(1 == x.i);
// 
// @end

#include <zen/function/variadic.h>
#include <zen/function/invoke.h>
#include <zen/function/static.h>

namespace zen { namespace detail {

template<template <class> class F, class Sequence>
struct implicit_invoke
{
    Sequence seq;

    implicit_invoke(Sequence seq) : seq(seq)
    {}

    typedef void zen_has_conversion_op_tag;

    // TODO: Add a default template parameter in c++11 to check if it is callable
    template<class X>
    operator X() const
    {
        return invoke(F<X>(), seq);
    }

    template<template <class> class F2, class Sequence2>
    operator implicit_invoke<F2, Sequence2>() const
    {
        return implicit_invoke<F2, Sequence2>(seq);
    }
};


template<template <class> class F>
struct implicit_base
{
    template<class>
    struct result;

    template<class X, class T>
    struct result<X(T)>
    {
        typedef implicit_invoke<F, typename boost::decay<T>::type> type;
    };

    template<class T>
    implicit_invoke<F, T> operator()(const T& x) const
    {
        return implicit_invoke<F, T>(x);
    }
};

}

#ifndef ZEN_NO_VARIADIC_TEMPLATES
template<template <class> class F>
struct implicit
{
    typedef variadic_adaptor<detail::implicit_base<F> > function;
    template<class S>
    struct result
    : zen::result_of<S, function>
    {};

    ZEN_PERFECT_FACADE(function, function())

};
#else

template<template <class> class F, class Enable=void>
struct implicit;

template<template <class> class F>
struct implicit<F, ZEN_CLASS_REQUIRES(exclude is_callable<variadic_adaptor<detail::implicit_base<F> >()>)>
{
    typedef variadic_adaptor<detail::implicit_base<F> > function;
    template<class S>
    struct result
    : zen::result_of<S, function>
    {};

    ZEN_PERFECT_FACADE(function, function())

};

template<template <class> class F>
struct implicit<F, ZEN_CLASS_REQUIRES(is_callable<variadic_adaptor<detail::implicit_base<F> >()>)>
{
    typedef variadic_adaptor<detail::implicit_base<F> > function;
    template<class S>
    struct result
    : zen::result_of<S, function>
    {};

    typename zen::result_of<function()>::type operator()() const
    {
        return function()();
    }

    ZEN_PERFECT_FACADE(function, function())

};
#endif



}


#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/detail/sequence.h>


template<class T>
struct auto_caster
{
    template<class X>
    struct result
    {
        typedef T type;
    };
    template<class U>
    T operator()(U x)
    {
        return T(x);
    }
};

struct auto_caster_foo
{
    int i;
    explicit auto_caster_foo(int i) : i(i) {}

};

static_assert(zen::typeof_detail::has_conversion_op
< 
    zen::detail::implicit_invoke<auto_caster, ZEN_FUNCTION_SEQUENCE<float> > 
>::value, "Can use in rvalue probe");
zen::implicit<auto_caster> auto_cast = {};

ZEN_TEST_CASE(implicit_test)
{
    float f = 1.5;
    int i = auto_cast(f);
    // auto_caster_foo x = 1;
    auto_caster_foo x = auto_cast(1);
    ZEN_TEST_EQUAL(1, i);
    ZEN_TEST_EQUAL(1, x.i);

}
#endif

#endif
