/*=============================================================================
    Copyright (c) 2013 Paul Fultz II
    ax.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_AX_H
#define ZEN_GUARD_AX_H

#include <type_traits>

namespace zen {

template<template<class...> class Trait, class... Ts>
constexpr bool ax(Ts&&...)
{
    return Trait<typename std::remove_reference<Ts>::type...>::value;
}

struct local_ax
{
    template<template<class...> class Trait, class... Ts>
    static constexpr bool ax(Ts&&...)
    {
        return Trait<typename std::remove_reference<Ts>::type...>::value;
    }
};

}

#endif
