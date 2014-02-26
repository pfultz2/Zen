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

#include <zen/function/invoke.h>
#include <zen/function/detail/remove_rvalue_reference.h>

namespace zen { namespace detail {

template<template <class> class F, class Sequence>
struct implicit_invoke
{
    Sequence seq;

    implicit_invoke(Sequence seq) : seq(seq)
    {}

    // typedef void zen_has_conversion_op_tag;

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

template<template <class> class F, class Sequence>
implicit_invoke<F, Sequence> make_implicit_invoke(Sequence&& seq)
{
    return implicit_invoke<F, Sequence>(std::forward<Sequence>(seq));
}

}


template<template <class> class F>
struct implicit
{
    template<class... Ts>
    auto operator()(Ts&&... xs) const
    {
        return detail::make_implicit_invoke<F>(detail::make_ref_tuple(std::forward<Ts>(xs)...));
    }

};

}


#ifdef ZEN_TEST
#include <zen/test.h>


template<class T>
struct auto_caster
{
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
