/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    take.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_TAKE_H
#define ZEN_GUARD_ALGORITHM_TAKE_H

#include <zen/algorithm/at.h>
#include <zen/range/iterator_range.h>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((take)(r, n)
    if (is_range<r>)(make_iterator_range(boost::begin(r), detail::iterator_at(r)))

)

}

#endif
