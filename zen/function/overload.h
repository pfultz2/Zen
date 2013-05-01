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

#include <zen/function/adaptor.h>
#include <zen/function/defer.h>
#include <zen/function/detail/nullary_tr1_result_of.h>

#ifndef ZEN_OVERLOAD_LIMIT
#define ZEN_OVERLOAD_LIMIT 16
#endif

namespace zen {

namespace detail {
#ifndef ZEN_NO_VARIADIC_TEMPLATES
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


#else
template<class F, ZEN_PP_PARAMS_Z(1, ZEN_OVERLOAD_LIMIT, class F, = void BOOST_PP_INTERCEPT)>
struct overload_adaptor_base;

#define ZEN_OVERLOAD_ADAPTOR_BASE(z, n, data) \
template<class F, ZEN_PP_PARAMS_Z(z, n, class F)> \
struct overload_adaptor_base<F, ZEN_PP_PARAMS_Z(z, n, F)> : F, overload_adaptor_base<ZEN_PP_PARAMS_Z(z, n, F)> \
{ \
    typedef overload_adaptor_base<ZEN_PP_PARAMS_Z(z, n, F)> base; \
    overload_adaptor_base() {} \
    \
    template<class T, ZEN_PP_PARAMS_Z(z, n, class T)> \
    overload_adaptor_base(T head, ZEN_PP_PARAMS_Z(z, n, T, tail)) \
    : F(head), base(ZEN_PP_PARAMS_Z(z, n, tail)) \
    {} \
    \
    using F::operator(); \
    using base::operator(); \
};
BOOST_PP_REPEAT_FROM_TO_1(1, ZEN_OVERLOAD_LIMIT, ZEN_OVERLOAD_ADAPTOR_BASE, ~)

#endif

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

#ifndef ZEN_NO_VARIADIC_TEMPLATES
template<class...Fs> 
struct overload_adaptor : defer_adaptor<detail::overload_adaptor_base<Fs...> >
{
    typedef detail::overload_adaptor_base<Fs...> core;
    typedef defer_adaptor<core> base;
    overload_adaptor()
    {}

    template<class... T>
    overload_adaptor(T... x) : base(core(x...))
    {}
};

template<class...Fs>
typename overload_adaptor<Fs...>::type overload(Fs...x)
{ 
    return overload_adaptor<Fs...>(x...); 
}
#else

template<ZEN_PP_PARAMS_Z(1, ZEN_OVERLOAD_LIMIT, class F, = void BOOST_PP_INTERCEPT)> 
struct overload_adaptor : defer_adaptor<detail::overload_adaptor_base<ZEN_PP_PARAMS_Z(1, ZEN_OVERLOAD_LIMIT, F)> >
{
    typedef detail::overload_adaptor_base<ZEN_PP_PARAMS_Z(1, ZEN_OVERLOAD_LIMIT, F)> core;
    typedef defer_adaptor<core> base;
    overload_adaptor()
    {}
#define ZEN_OVERLOAD_ADAPTOR_CONSTRUCTOR(z, n, data) \
    template<ZEN_PP_PARAMS_Z(z, n, class T)> \
    overload_adaptor(ZEN_PP_PARAMS_Z(z, n, T, x)) : base(core(ZEN_PP_PARAMS_Z(z, n, x))) \
    {}
BOOST_PP_REPEAT_FROM_TO_1(1, ZEN_OVERLOAD_LIMIT, ZEN_OVERLOAD_ADAPTOR_CONSTRUCTOR, ~)
};


#define ZEN_OVERLOAD_FUNCTION(z, n, data) \
template<ZEN_PP_PARAMS_Z(z, n, class F)> \
typename overload_adaptor<ZEN_PP_PARAMS_Z(z, n, F)>::type overload(ZEN_PP_PARAMS_Z(z, n, F, x)) \
{ \
    return overload_adaptor<ZEN_PP_PARAMS_Z(z, n, F)>(ZEN_PP_PARAMS_Z(z, n, x)); \
}
BOOST_PP_REPEAT_FROM_TO_1(1, ZEN_OVERLOAD_LIMIT, ZEN_OVERLOAD_FUNCTION, ~)
#endif



}

ZEN_NULLARY_TR1_RESULT_OF_N(ZEN_OVERLOAD_LIMIT, zen::overload_adaptor)



#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/reveal.h>
#include <zen/typeof.h>

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

typedef ZEN_TYPEOF(reveal(fun)(1)) fun_type;

void test()
{
reveal(fun)(1);
}

static_assert(boost::is_same<int, ZEN_TYPEOF(fun(1))>::value, "Failed overload");
static_assert(boost::is_same<foo, ZEN_TYPEOF(fun(foo()))>::value, "Failed overload");
}}

#endif

#endif
