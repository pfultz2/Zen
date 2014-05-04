/*=============================================================================
    Copyright (c) 2013 Paul Fultz II
    predicate_check.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_PREDICATE_CHECK_H
#define ZEN_GUARD_PREDICATE_CHECK_H

#include <type_traits>
#include <zen/requires.h>
#include <zen/traits/trait_check.h>

namespace zen {

namespace detail {

template<class Expression, class TraitCheck>
struct predicate_check_impl;

template<class Trait, class... Ts>
struct predicate_check_impl<Trait, trait_check<Ts...>>
: trait_check<Trait, Ts...>
{};

template<class Trait, class... Ts>
struct predicate_check_impl<predicate_clause::expression<Trait>, trait_check<Ts...>>
: predicate_check_impl<Trait, trait_check<Ts...>>
{};

template<class Trait1, class Trait2, class Op, class... Ts>
struct predicate_check_impl<predicate_clause::node<Trait1, Trait2, Op>, trait_check<Ts...>>
: predicate_check_impl<Trait1, predicate_check_impl<Trait2, trait_check<Ts...>>>
{};

}

template<class T>
struct predicate_check
: detail::predicate_check_impl<T, trait_check<>>
{};

}

#endif