/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    lexicographical_compare.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_LEXICOGRAPHICAL_COMPARE_H
#define ZEN_GUARD_ALGORITHM_LEXICOGRAPHICAL_COMPARE_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <algorithm>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((lexicographical_compare)(auto r1, auto r2)
    if (is_range<r1>, is_range<r2>)
    (
        std::lexicographical_compare(boost::begin(r1), boost::end(r1), boost::begin(r2), boost::end(r2))
    )

)

}

#endif
