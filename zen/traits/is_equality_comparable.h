/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    is_equality_comparable.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_TRAITS_IS_EQUALITY_COMPARABLE_H
#define ZEN_GUARD_TRAITS_IS_EQUALITY_COMPARABLE_H

#include <zen/traits/builder.h>

namespace zen {

ZEN_TRAITS(is_equality_comparable)
{
    template<class T, class U>
    auto requires(T&& x) -> ZEN_VALID_EXPR(
        zen::returns<bool>(x == x),
        zen::returns<bool>(x != x),
    );

    template<class T, class U>
    auto requires(T&& x, U&& y) -> ZEN_VALID_EXPR(
        this->requires(x),
        this->requires(y),
        zen::returns<bool>(x == y),
        zen::returns<bool>(y == x),
        zen::returns<bool>(x != y),
        zen::returns<bool>(y != x)
    );
}

}

#endif