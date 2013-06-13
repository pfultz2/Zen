/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    filter.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FILTER_H
#define ZEN_GUARD_ALGORITHM_FILTER_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/iterator/filter_iterator.hpp>
#include <zen/range/iterator_range.h>

#include <algorithm>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((filter)(auto r, f)
    if (is_range<r>)
    (
        zen::make_iterator_range
        (
            boost::make_filter_iterator(f, boost::begin(r)),
            boost::make_filter_iterator(f, boost::end(r))
        )
    )

    )

}

#endif
