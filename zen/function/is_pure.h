/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    is_pure.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_FUNCTION_IS_PURE_H
#define ZEN_GUARD_FUNCTION_IS_PURE_H

#include <type_traits>

namespace zen { 

template<class F>
struct is_pure : std::is_empty<F>
{};

}

#endif
