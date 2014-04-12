/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    is_regular.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_TRAITS_IS_REGULAR_H
#define ZEN_GUARD_TRAITS_IS_REGULAR_H

#include <zen/traits/builder.h>

namespace zen {


ZEN_TRAIT(is_semi_regular)
{
    template<class T>
    auto requires(T&& x) -> ZEN_VALID_EXPR(
        zen::is_true<std::is_copy_constructible<T>>,
        zen::is_true<std::is_copy_assignable<T>>,
        zen::is_true<std::is_destructible<T>>
    );
}

ZEN_TRAIT(is_regular)
{
    template<class T>
    auto requires(T&& x) -> ZEN_VALID_EXPR(
        zen::is_true<is_semi_regular<T>>,
        zen::is_true<std::is_default_constructible<T>>
    );
}

}

#endif