/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    compose.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_COMPOSE_H
#define ZEN_GUARD_FUNCTION_COMPOSE_H

// TODO: Add a note about the base classes, and how it can use duplicate functions

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
// equivalent to `f(g(0))`.
// 
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

#include <zen/returns.h>


namespace zen { namespace detail {

template<long N>
struct compose_fold
{
    template<class T, class Tuple>
    static auto call(T&& x, const Tuple& t) ZEN_RETURNS
    (std::get<N-1>(t)(compose_fold<N-1>::call(std::forward<T>(x), t)));
};

template<>
struct compose_fold<0>
{
    template<class T, class Tuple>
    static auto call(T&& x, const Tuple&) ZEN_RETURNS
    (std::forward<T>(x));
};

}

template<class... Fs>
struct compose_adaptor
{
    std::tuple<Fs...> fs;
    static const long N = sizeof...(Fs);
    compose_adaptor() {}

    template<class... Xs>
    compose_adaptor(Xs... xs) : fs(std::make_tuple(xs...))
    {}

    template<class T>
    auto operator()(T&& x) const ZEN_RETURNS
    (detail::compose_fold<N>::call(std::forward<T>(x), fs));
};

template<class... Fs>
compose_adaptor<Fs...> compose(Fs... fs)
{
    return compose_adaptor<Fs...>(fs...);
}

}


#ifdef ZEN_TEST
#include <zen/test.h>
namespace zne_compose_test {
struct increment
{
    template<class T>
    T operator()(T x) const
    {
        return x + 1;
    }
};

struct decrement
{
    template<class T>
    T operator()(T x) const
    {
        return x - 1;
    }
};

ZEN_TEST_CASE(compose_test)
{
    int r = zen::compose(increment(), decrement(), increment())(3);
    printf("r: %i\n", r);
    ZEN_TEST_EQUAL(r, 4);
}
}

#endif

#endif
