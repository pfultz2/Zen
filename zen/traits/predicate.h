/*=============================================================================
    Copyright (c) 2013 Paul Fultz II
    predicate.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_AX_H
#define ZEN_GUARD_AX_H

#include <type_traits>
#include <zen/requires.h>

namespace zen {

template<template<class...> class Trait, class... Ts>
constexpr auto predicate_trait(Ts&&...)
{
    return zen::predicate_clause::expression<Trait<typename std::remove_reference<Ts>::type...>>();
}

// Short version
template<template<class...> class Trait, class... Ts>
constexpr auto _p(Ts&&... xs)
{
    return predicate_trait<Trait>(std::forward<Ts>(xs)...);
}
}

#ifdef ZEN_TEST
#include <vector>

namespace test_zen_predicate_trait {

template<class T>
constexpr bool make_const()
{
    return T::value;
}

static_assert(zen::_p<std::is_integral>(1), "Its an integral");
static_assert(make_const<ZEN_PREDICATE_CLAUSE(zen::_p<std::is_integral>(1))>(), "Its an integral");
static_assert(make_const<ZEN_PREDICATE_CLAUSE(not zen::_p<std::is_integral>(std::vector<int>()))>(), "Its not an integral");

}


#endif

#endif
