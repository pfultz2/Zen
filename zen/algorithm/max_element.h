/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    max_element.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_MAX_ELEMENT_H
#define ZEN_GUARD_ALGORITHM_MAX_ELEMENT_H

#include <zen/algorithm/fold.h>


namespace zen { 

namespace detail {

ZEN_FUNCTION_CLASS((max_element_fold)(auto x, auto y)(x > y ? x : y))

}

ZEN_FUNCTION_PIPE_OBJECT((max_element)(auto r)
        if(is_range_or_sequence<r>)(fold(r, detail::max_element_fold()))
    )

}

#endif
