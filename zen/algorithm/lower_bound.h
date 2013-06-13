/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    lower_bound.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_LOWER_BOUND_H
#define ZEN_GUARD_ALGORITHM_LOWER_BOUND_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <algorithm>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((lower_bound)(auto r, x)
    if (is_range<r>)
    (
        std::lower_bound(boost::begin(r), boost::end(r), x)
    )

)

}

#endif
