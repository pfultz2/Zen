/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    find_if_not.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FIND_IF_NOT_H
#define ZEN_GUARD_ALGORITHM_FIND_IF_NOT_H

#include <zen/function/builder.h>

#include <zen/algorithm/find_if.h>
#include <algorithm>


namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((find_if_not)(auto&& r, auto f)
        if (_p<is_range>(r))
        (
            find_if(r, [f](auto&& x){ return !f(x); })
        )
    )

}

#endif
