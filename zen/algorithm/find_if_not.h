/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    find_if_not.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FIND_IF_NOT_H
#define ZEN_GUARD_ALGORITHM_FIND_IF_NOT_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <zen/algorithm/find_if.h>
#include <algorithm>

#include <zen/function/compose.h>
#include <functional>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((find_if_not)(auto r, f)
        if (is_range<r>)
        (
            find_if(r, zen::compose(f, std::logical_not<bool>()))
        )
    )

}

#endif
