/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    find_first_of.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FIND_FIRST_OF_H
#define ZEN_GUARD_ALGORITHM_FIND_FIRST_OF_H

#include <zen/function/builder.h>
#include <zen/range/range_traits.h>

#include <algorithm>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((find_first_of)(auto&& r, auto&& x)
        if (_p<is_sub_range>(r, x))(std::find_end(zen::begin(r), zen::end(r), zen::begin(x), zen::end(x)))
    )   


}

#endif
