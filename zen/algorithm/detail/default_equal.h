/*=============================================================================
    Copyright (c) 2013 Paul Fultz II, Neil Groves
    default_equal.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_DETAIL_DEFAULT_EQUAL_H
#define ZEN_GUARD_ALGORITHM_DETAIL_DEFAULT_EQUAL_H

#include <zen/function/builder.h>

namespace zen { namespace detail {

ZEN_FUNCTION_CLASS((default_equal)(const auto& x, const auto& y)(x == y));

}}

#endif