/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    drop_while.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_DROP_WHILE_H
#define ZEN_GUARD_ALGORITHM_DROP_WHILE_H

#include <zen/algorithm/find_if.h>
#include <zen/range/iterator_range.h>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((drop_while)(r, f)
    if (is_range<r>)(make_iterator_range(find_if(r, f), boost::end(r)))

)

}

#endif
