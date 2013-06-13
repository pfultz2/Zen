/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    replace_if.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_REPLACE_IF_H
#define ZEN_GUARD_ALGORITHM_REPLACE_IF_H

#include <zen/algorithm/transform.h>
#include <boost/bind.hpp>

namespace zen { 

namespace detail {

ZEN_FUNCTION_CLASS((replacer_if)(auto x, auto f, auto new_value)
    (
        f(x) ? new_value : x
    ))

}

ZEN_FUNCTION_PIPE_OBJECT((replace_if)(auto r, f, auto new_value)
    if (is_range_or_sequence<r>)(zen::transform(r, boost::bind(detail::replacer_if(), _1, f, new_value)))

    )

}

#endif
