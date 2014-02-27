/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    overload.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_OVERLOAD_H
#define ZEN_GUARD_FUNCTION_OVERLOAD_H

// @begin
// overload
// ========
// 
// Description
// -----------
// 
// The `overload` function adaptor combines several functions together and
// resolves which one should be called by using C++ overload resolution. This is
// different than than the `conditional` adaptor which resolves them based on
// order.
// 
// Synopsis
// --------
// 
//     template<class F1, class F2, ...>
//     overload_adaptor<F1, F2, ...> overload(F1 f1, F2 f2, ...);
// 
// Example
// -------
// 
//     struct int_class
//     {
//         int operator()(int) const
//         {
//             return 1;
//         }
//     };
// 
//     struct foo
//     {};
// 
//     struct foo_class
//     {
//         foo operator()(foo) const
//         {
//             return foo();
//         }
//     };
// 
//     typedef overload_adaptor<int_class, foo_class> fun;
// 
//     static_assert(boost::is_same<int, ZEN_TYPEOF(fun()(1))>::value, "Failed overload");
//     static_assert(boost::is_same<foo, ZEN_TYPEOF(fun()(foo()))>::value, "Failed overload");
// 
// @end


namespace zen {

namespace detail {
template<class...Fs> struct overload_adaptor_base;
 
template<class F, class...Fs>
struct overload_adaptor_base<F, Fs...> : F, overload_adaptor_base<Fs...>
{
    typedef overload_adaptor_base<Fs...> base;

    overload_adaptor_base()
    {}

    template<class T, class... Ts>
    overload_adaptor_base(T head, Ts... tail)
    : F(head), base(tail...)
    {}

    using F::operator();
    using base::operator();
};

template<class F>
struct overload_adaptor_base<F> : F
{
    typedef F base;
    using F::operator();

    overload_adaptor_base()
    {}

    template<class T>
    overload_adaptor_base(T f) : F(f)
    {}
};
}

template<class...Fs> 
struct overload_adaptor : detail::overload_adaptor_base<Fs...>
{
    typedef detail::overload_adaptor_base<Fs...> base;
    overload_adaptor()
    {}

    template<class... T>
    overload_adaptor(T... x) : base(x...)
    {}
};

template<class...Fs>
typename overload_adaptor<Fs...>::type overload(Fs...x)
{ 
    return overload_adaptor<Fs...>(x...); 
}

}

#ifdef ZEN_TEST
#include <zen/test.h>

namespace zen { namespace overload_test {
struct int_class
{
    int operator()(int) const
    {
        return 1;
    }
};

struct foo
{};

struct foo_class
{
    foo operator()(foo) const
    {
        return foo();
    }
};

zen::static_<zen::overload_adaptor<int_class, foo_class> > fun = {};

static_assert(boost::is_same<int, decltype(fun(1))>::value, "Failed overload");
static_assert(boost::is_same<foo, decltype(fun(foo()))>::value, "Failed overload");
}}

#endif

#endif
