 /*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    drop.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_DROP_H
#define ZEN_GUARD_ALGORITHM_DROP_H

#include <zen/algorithm/at.h>
#include <zen/range/iterator_range.h>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((drop)(r, n)
    if (is_range<r>)(make_iterator_range(detail::iterator_at(r), boost::end(r)))

)

}

#endif
