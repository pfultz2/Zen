/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    indirect.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_INDIRECT_H
#define ZEN_GUARD_ALGORITHM_INDIRECT_H

#include <zen/algorithm/transform.h>

namespace zen { namespace detail {

ZEN_FUNCTION_CLASS((indirect_selector)(x)(*x))

}

ZEN_FUNCTION_PIPE_OBJECT((indirect)(auto r)
    if (is_range_or_sequence<r>)(zen::transform(r, detail::indirect_selector()))
)


}

#endif
