/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    is_nullable_pointer.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_TRAITS_IS_NULLABLE_POINTER_H
#define ZEN_GUARD_TRAITS_IS_NULLABLE_POINTER_H

#include <zen/traits/builder.h>

namespace zen {

ZEN_TRAIT(is_nullable_pointer)
{
    template<class T>
    auto requires(T x) -> ZEN_VALID_EXPR(
        zen::is_true<is_regular<T>>,
        zen::is_true<is_full_equality_comparable<T>>,
        T(nullptr),
        zen::returns<bool>(x == nullptr),
        zen::returns<bool>(nullptr == x),
        zen::returns<bool>(x != nullptr),
        zen::returns<bool>(nullptr != x)
    );
}

}

#endif