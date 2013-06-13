/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    find_if_not.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_FIND_IF_NOT_H
#define ZEN_GUARD_ALGORITHM_FIND_IF_NOT_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <zen/algorithm/find_if_not.h>
#include <algorithm>

#include <boost/bind.hpp>
#include <functional>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((find_if_not)(r, f)
        if (is_range<r>)
        (
            find_if(r, boost::bind(std::logical_not<bool>(), boost::bind(f, _1)))
        )
    )

}

#endif
