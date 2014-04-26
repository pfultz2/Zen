/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    local_ops.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_TRAITS_LOCAL_OPS_H
#define ZEN_GUARD_TRAITS_LOCAL_OPS_H

#include <zen/traits/predicate.h>
#include <zen/traits/transform.h>


namespace zen { 

struct local_ops
{

    template<template<class...> class Trait, class... Ts>
    static constexpr auto _p(Ts&&... xs)
    {
        return predicate_trait<Trait>(std::forward<Ts>(xs)...);
    }

    template<class T>
    using _t = typename T::type;
};

}

#endif
