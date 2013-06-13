/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    join.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_JOIN_H
#define ZEN_GUARD_ALGORITHM_JOIN_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/range/join.hpp>
#include <zen/range/iterator_range.h>

#include <boost/fusion/algorithm/transformation/join.hpp>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((join)(auto x, auto y)
    if (is_range<x>, is_range<y>)(boost::range::join(x, y))
    else if (is_sequence<x>, is_sequence<y>)(boost::fusion::join(x, y))

    )


}

#endif
