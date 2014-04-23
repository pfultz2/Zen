/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    replace_args.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_MPL_REPLACE_ARGS_H
#define ZEN_GUARD_MPL_REPLACE_ARGS_H

#include <boost/mpl/vector.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/at.hpp>
#include <zen/mpl/placeholders.h>
#include <boost/mpl/size.hpp>
#include <zen/requires.h>

namespace zen { namespace mpl {

namespace detail {

template<class Vector>
struct vector_replace
{
    template<class Placeholder>
    struct apply
    : boost::mpl::at_c<Vector, Placeholder::value - 1>
    {
        static_assert(Placeholder::value <= boost::mpl::size<Vector>::value, "Invalid placeholder");
    };
};

template<class T>
struct single_replace
{
    template<class Placeholder>
    struct apply
    {
        static_assert(Placeholder::value == 1, "Invalid placeholder");
        typedef T type;
    };
};

template<class F, class Replacer>
struct replace_args_recursive
{
    typedef F type;
};
// TODO: Match for boost::mpl::protect
template<int N, class Replacer>
struct replace_args_recursive<boost::mpl::arg<N>, Replacer>
: Replacer::template apply<boost::mpl::int_<N>>
{};

template<template<class...> class F, class Replacer, class... Args>
struct replace_args_recursive<F<Args...>, Replacer>
{
    typedef F<typename replace_args_recursive<Args, Replacer>::type...> type;
};

template<class F, class Replacer>
struct replace_args_impl
: replace_args_recursive<F, Replacer>
{};

// Specialization for simple unnamed placeholders
template<template<class...> class F, class Replacer, class... Args>
struct replace_args_impl<F<boost::mpl::arg<-1>, Args...>, Replacer>
{
    typedef F<
        typename Replacer::template apply<boost::mpl::int_<1>>::type, 
        typename replace_args_recursive<Args, Replacer>::type...
    > type;
};

template<template<class...> class F, class Replacer, class Arg, class... Args>
struct replace_args_impl<F<Arg, boost::mpl::arg<-1>, Args...>, Replacer>
{
    typedef F<
        typename replace_args_recursive<Arg, Replacer>::type,
        typename Replacer::template apply<boost::mpl::int_<1>>::type, 
        typename replace_args_recursive<Args, Replacer>::type...
    > type;
};

}


template<class F, class... Ts>
struct replace_args
: detail::replace_args_impl<F, detail::vector_replace<boost::mpl::vector<Ts...>>>
{};

// Specializations for the most common use cases
template<template<class...> class F, class T, class... Args>
struct replace_args<F<Args...>, T>
: detail::replace_args_impl<F<Args...>, detail::single_replace<T>>
{};

}}

#ifdef ZEN_TEST
#include <zen/static_assert.h>

template<class... T>
struct zen_replace_args_test
{};
ZEN_STATIC_ASSERT_SAME(typename zen::mpl::replace_args<zen_replace_args_test<int>, long>::type, 
    zen_replace_args_test<int>);
ZEN_STATIC_ASSERT_SAME(typename zen::mpl::replace_args<zen_replace_args_test<zen::mpl::_>, long>::type, 
    zen_replace_args_test<long>);
ZEN_STATIC_ASSERT_SAME(typename zen::mpl::replace_args<zen_replace_args_test<zen::mpl::_1>, long>::type, 
    zen_replace_args_test<long>);
ZEN_STATIC_ASSERT_SAME(typename zen::mpl::replace_args<zen_replace_args_test<zen::mpl::_1, zen::mpl::_2>, long, float>::type, 
    zen_replace_args_test<long, float>);

#endif

#endif