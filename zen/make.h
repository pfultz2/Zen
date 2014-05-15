/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    make.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_MAKE_H
#define ZEN_GUARD_MAKE_H

#include <type_traits>
#include <functional>
#include <zen/traits/is_template.h>
#include <zen/traits/bare.h>
#include <boost/mpl/if.hpp>

namespace zen {

namespace detail {

template<class T>
struct unwrap_ref;

template<class T>
struct unwrap_ref<std::reference_wrapper<T>>
{
    using type = T&;
};

template<class T>
struct make_decay
: boost::mpl::if_<is_template<bare_t<T>, std::reference_wrapper>, 
    unwrap_ref<bare_t<T>>, 
    bare<T>
>::type
{};

}

template<template<class...> class Template, class... Ts>
constexpr auto make(Ts&&... xs)
{
    return Template<typename detail::make_decay<Ts>::type...>(std::forward<Ts>(xs)...);
}

template<template<class...> class Template, class... Ts>
constexpr auto forward_as(Ts&&... xs)
{
    return Template<Ts&&...>(std::forward<Ts>(xs)...);
}

}

#endif