/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    trait_check.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_TRAIT_CHECK_H
#define ZEN_GUARD_TRAIT_CHECK_H

#include <zen/traits/builder.h>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace zen {

template<class... T>
struct TRAIT_CHECK_FAILURE;

template<>
struct TRAIT_CHECK_FAILURE<>
{};

namespace detail {  

template<int... N>
struct trait_check_test
{};

template<class T, class TraitCheck>
struct trait_check_push_back;

template<class T, class... Ts>
struct trait_check_push_back<T, TRAIT_CHECK_FAILURE<Ts...>>
{
    typedef TRAIT_CHECK_FAILURE<T, Ts...> type;
};

struct trait_check_fold_each
{
    template<class TraitCheck, class T>
    struct apply
    : boost::mpl::eval_if<T,
        boost::mpl::identity<TraitCheck>, 
        trait_check_push_back<T, TraitCheck>
    >
    {};
};

template<class Set>
struct trait_check_fold
: boost::mpl::fold<Set, 
    TRAIT_CHECK_FAILURE<>, 
    trait_check_fold_each
>
{};

template<class Set>
struct trait_check_impl
{
    typedef trait_check_test<sizeof(typename trait_check_fold<Set>::type)> type;
};

template<class Set, class T>
struct trait_check_insert_trait
: trait_check_insert_trait<typename boost::mpl::insert<Set, T>::type, typename base_traits_type<T>::type>
{};

template<class Set, class... Ts>
struct trait_check_insert_trait<Set, base_traits<Ts...>>
: boost::mpl::fold<
    boost::mpl::vector<Ts...>,
    Set,
    trait_check_insert_trait<boost::mpl::_1, boost::mpl::_2 >
>
{};

template<class Set, class... Ts>
struct trait_check_insert_traits
: boost::mpl::fold<
    boost::mpl::vector<Ts...>,
    Set,
    trait_check_insert_trait< boost::mpl::_1, boost::mpl::_2 >
>
{};

}

template<class... Ts>
struct trait_check
: detail::trait_check_impl<typename detail::trait_check_insert_traits<boost::mpl::set0<>, Ts...>::type>
{};

}

#define ZEN_TRAIT_CHECK(...) typedef typename zen::trait_check<__VA_ARGS__>::type BOOST_PP_CAT(zen_trait_check_typedef_, __LINE__)


#endif