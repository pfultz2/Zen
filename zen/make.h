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
struct make_holder
{
    typedef void type;
};

template<class T, class Enable=void>
struct has_no_make
: std::false_type
{};

template<class T>
struct has_no_make<T, typename make_holder<
    typename T::zen_no_make
>::type>
: std::true_type
{};

template<class T, class Enable=void>
struct has_no_forward_as
: std::false_type
{};

template<class T>
struct has_no_forward_as<T, typename make_holder<
    typename T::zen_no_forward_as
>::type>
: std::true_type
{};

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
    // TODO: Mkae this remove reference instead
    bare<T>
>::type
{};

}

template<template<class...> class Template, class... Ts>
constexpr auto make(Ts&&... xs)
{
    typedef Template<typename detail::make_decay<Ts>::type...> type;
    static_assert(not detail::has_no_make<type>(), 
        "make cannot be used with this template. Try using forward_as instead.");
    return type(std::forward<Ts>(xs)...);
}

template<template<class...> class Template, class... Ts>
constexpr auto forward_as(Ts&&... xs)
{
    typedef Template<Ts&&...> type;
    static_assert(not detail::has_no_forward_as<type>(), 
        "forward_as cannot be used with this template. Try using make instead.");
    return type(std::forward<Ts>(xs)...);
}

#define ZEN_DISABLE_MAKE() struct zen_no_make {};
#define ZEN_DISABLE_FORWARD_AS() struct zen_no_forward_as {};

}

#endif