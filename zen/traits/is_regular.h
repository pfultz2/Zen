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

ZEN_TRAIT(is_semi_regular, 
    std::is_copy_constructible<_>, 
    std::is_copy_assignable<_>,
    std::is_destructible<_>
)
{};

ZEN_TRAIT(is_regular,
    is_semi_regular<_>, 
    std::is_default_constructible<_>
)
{};

}

#ifdef ZEN_TEST
#include "zen/traits/trait_check.h"

ZEN_TRAIT_CHECK(zen::is_regular<int>);
ZEN_TRAIT_CHECK(zen::is_semi_regular<int>);
ZEN_TRAIT_CHECK(zen::is_semi_regular<int&>);

#endif

#endif