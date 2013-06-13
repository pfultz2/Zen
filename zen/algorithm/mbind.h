/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    mbind.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_MBIND_H
#define ZEN_GUARD_ALGORITHM_MBIND_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <zen/iterator/mbind_iterator.h>
#include <zen/range/iterator_range.h>
#include <algorithm>

// TODO: Rename to flat_transform

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((mbind)(r, f)
    if (is_range<r>)
    (
        make_iterator_range
        (
            make_bind_iterator(r, boost::begin(r), boost::end(r)),
            make_bind_iterator(r, boost::end(r), boost::end(r))
        )
    )

)

}

#endif
