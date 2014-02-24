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
//     int r = zen::fix([](auto s, auto x) -> decltype(x) { return x == 0 ? 1 : x * s(x-1); })(5);
//     assert(r, 5*4*3*2*1);
// 
// @end

#include <zen/function/variadic.h>
#include <zen/function/fuse.h>

namespace zen { namespace detail {

template<class Derived, class F>
struct fix_adaptor_base : fuse_adaptor<F>
{
    fix_adaptor_base() {}

    template<class X>
    fix_adaptor_base(X x) : fuse_adaptor<F>(x)
    {}

    const fuse_adaptor<F>& get_function() const
    {
        return *this;
    }

    std::tuple<const Derived&> get_derived_function_tuple() const
    {
        return std::tuple<const Derived&>(*this);
    }

    template<class T>
    auto operator()(const T& x) const ZEN_RETURNS
    (this->get_function()(std::tuple_cat(this->get_derived_function_tuple(), x)));
};
}

template<class F>
struct fix_adaptor : zen::variadic_adaptor<detail::fix_adaptor_base<fix_adaptor<F>, F> >
{
    typedef zen::variadic_adaptor<detail::fix_adaptor_base<fix_adaptor<F>, F> > base;
    fix_adaptor()
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


#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/static.h>

struct factorial_t
{
    template<class Self, class T>
    T operator()(Self s, T x) const
    {
        return x == 0 ? 1 : x * s(x-1);
    }
};

zen::static_<zen::fix_adaptor<factorial_t> > factorial = {};

ZEN_TEST_CASE(fix_test)
{
    int r1 = factorial(5);
    ZEN_TEST_EQUAL(r1, 5*4*3*2*1);
    int r2 = zen::fix([](auto s, auto x) -> decltype(x) { return x == 0 ? 1 : x * s(x-1); })(5);
    ZEN_TEST_EQUAL(r2, 5*4*3*2*1);
}

#endif

#endif
