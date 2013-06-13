/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    replace.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_REPLACE_H
#define ZEN_GUARD_ALGORITHM_REPLACE_H

#include <zen/algorithm/transform.h>
#include <boost/bind.hpp>

namespace zen { 

namespace detail {

ZEN_FUNCTION_CLASS((replacer)(auto x, auto old_value, auto new_value)
    (
        x == old_value ? new_value : x
    ))

}

ZEN_FUNCTION_PIPE_OBJECT((replace)(auto r, auto old_value, auto new_value)
    if (is_range_or_sequence<r>)(zen::transform(r, boost::bind(detail::replacer(), _1, old_value, new_value)))

    )

}

#endif
