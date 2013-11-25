/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    compose.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_COMPOSE_H
#define ZEN_GUARD_FUNCTION_COMPOSE_H

// @begin
// compose
// ======
// 
// Description
// -----------
// 
// The `compose` function adaptor provides funcion composition. It produces a
// function object that composes a set of functions, ie the output of one
// function becomes the input of the second function. So, `compose(f, g)(0)` is
// equivalent to `g(f(0))`.
// 
// Note: Functions used in the `compose_adaptor` are evaluated in the order they
// are given, rather than order they are written, which is way it represented
// mathematically. For example, mathematically, `g(f(x))` is written `g * f`,
// however, using the adaptor it is written `compose(f, g)` since `f` is
// evaluated first.
// 
// Synopsis
// --------
// 
//     template<class F1, class F2, ...>
//     compose_adaptor<F1, F2, ...> compose(F1 f1, F2 f2, ...);
// 
// Example
// -------
// 
//     struct increment
//     {
//         template<class T>
//         T operator()(T x) const
//         {
//             return x + 1;
//         }
//     };
// 
//     struct decrement
//     {
//         template<class T>
//         T operator()(T x) const
//         {
//             return x - 1;
//         }
//     };
// 
//     int r = compose(increment(), decrement(), increment())(3);
//     assert(r == 4);
// 
// @end

#include <zen/function/variadic.h>
#include <zen/function/fuse.h>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <zen/function/detail/nullary_tr1_result_of.h>

#ifndef ZEN_NO_VARIADIC_TEMPLATES
#include <tuple>
#include <boost/fusion/adapted/std_tuple.hpp>
#else
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#endif

#ifndef ZEN_COMPOSE_LIMIT
#define ZEN_COMPOSE_LIMIT 10
#endif

namespace zen { namespace detail {

struct compose_fold
{
    template<class>
    struct result;

    template<class X, class State, class F>
    struct result<X(State, F)>
    : zen::result_of<typename boost::decay<F>::type(State)>
    {};

    template<class State, class F>
    typename result<compose_fold(State, F)>::type 
    operator()(State s, F f) const
    {
        return f(s);
    }
};
template<class Sequence>
struct compose_base
{

    typedef typename boost::decay<typename boost::fusion::result_of::at_c<Sequence, 0>::type>::type first;
    Sequence seq;

    compose_base() {}

    compose_base(Sequence seq) : seq(seq)
    {}

    template<class, class Enable = void>
    struct result;

    // template<class X, class T>
    // struct result<X(T), ZEN_CLASS_REQUIRES(is_callable<first(T)>)>
    // : boost::fusion::result_of::fold<Sequence, T, compose_fold>
    // {};

    struct no_result {};

    template<class X, class T>
    struct result<X(T)>
    : boost::mpl::if_<is_callable<first(T)>, 
        boost::fusion::result_of::fold<Sequence, T, compose_fold>, 
        no_result>::type
    {};

    template<class T>
    typename result<compose_base(T)>::type 
    operator()(const T& x) const
    {
        return boost::fusion::fold(seq, x, compose_fold());
    }
};

}

#ifndef ZEN_NO_VARIADIC_TEMPLATES
template<class F, class... Fs>
struct compose_adaptor
: zen::variadic_adaptor<detail::compose_base< std::tuple<zen::fuse_adaptor<F>, Fs...> > >
{
    typedef zen::variadic_adaptor<detail::compose_base<std::tuple<zen::fuse_adaptor<F>, Fs...> > > base;
    compose_adaptor() {}

    compose_adaptor(F f, Fs... fs) : base(std::make_tuple(zen::fuse_adaptor<F>(f), fs...))
    {}
};

template<class... Fs>
compose_adaptor<Fs...> compose(Fs... fs)
{
    return compose_adaptor<Fs...>(fs...);
}
#else
template<class T = void, ZEN_PP_PARAMS_Z(1, ZEN_COMPOSE_LIMIT, class T, = void BOOST_PP_INTERCEPT)>
struct compose_adaptor;
#define ZEN_COMPOSE_ADAPTOR(z, n, data) \
template<class F, ZEN_PP_PARAMS_Z(z, n, class Fs)> \
struct compose_adaptor<F, ZEN_PP_PARAMS_Z(z, n, Fs)> \
: zen::variadic_adaptor<detail::compose_base< boost::fusion::vector<zen::fuse_adaptor<F>, ZEN_PP_PARAMS_Z(z, n, Fs)> > > \
{ \
    typedef zen::variadic_adaptor<detail::compose_base<boost::fusion::vector<zen::fuse_adaptor<F>, ZEN_PP_PARAMS_Z(z, n, Fs)> > > base; \
    compose_adaptor() {} \
 \
    compose_adaptor(const compose_adaptor& rhs) : base(static_cast<const base&>(rhs)) \
    {} \
    compose_adaptor(F f, ZEN_PP_PARAMS_Z(z, n, Fs, fs)) : base(boost::fusion::make_vector(zen::fuse_adaptor<F>(f), ZEN_PP_PARAMS_Z(z, n, fs))) \
    {} \
};
BOOST_PP_REPEAT_FROM_TO_1(1, ZEN_COMPOSE_LIMIT, ZEN_COMPOSE_ADAPTOR, ~)

#define ZEN_COMPOSE_FUN(z, n, data) \
template<ZEN_PP_PARAMS_Z(z, n, class Fs)> \
compose_adaptor<ZEN_PP_PARAMS_Z(z, n, Fs)> compose(ZEN_PP_PARAMS_Z(z, n, Fs, fs)) \
{ \
    return compose_adaptor<ZEN_PP_PARAMS_Z(z, n, Fs)>(ZEN_PP_PARAMS_Z(z, n, fs)); \
}
BOOST_PP_REPEAT_FROM_TO_1(1, ZEN_COMPOSE_LIMIT, ZEN_COMPOSE_FUN, ~)
#endif

}

ZEN_NULLARY_TR1_RESULT_OF_N(ZEN_COMPOSE_LIMIT, zen::compose_adaptor)


#ifdef ZEN_TEST
#include <zen/test.h>
#include <zen/function/static.h>
#include <zen/function/reveal.h>
#include <zen/function/placeholders.h>
#include <zen/function/lazy.h>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/statement/if.hpp>


ZEN_TEST_CASE(compose_test)
{
    using zen::ph::_1;
    // int r = (_1 + 1)()(3);
    int r = zen::compose(_1 + 1, _1 - 1, _1 + 1)(3);
    ZEN_TEST_EQUAL(r, 4);
}

#endif

#endif
