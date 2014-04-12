/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    is_less_than_comparable.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_TRAITS_IS_LESS_THAN_COMPARABLE_H
#define ZEN_GUARD_TRAITS_IS_LESS_THAN_COMPARABLE_H

#include <zen/traits/builder.h>

namespace zen {
namespace detail {
struct is_less_than_comparable_t
{
    template<class T, class U>
    auto requires(T&& x, U&& y) -> ZEN_VALID_EXPR(
        zen::returns<bool>(x < y)
    );
};
}
template<class T>
struct is_less_than_comparable
: zen::trait<detail::is_less_than_comparable_t(T, T)>
{};

}

#endif