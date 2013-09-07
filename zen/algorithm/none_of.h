/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    none_of.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_NONE_OF_H
#define ZEN_GUARD_ALGORITHM_NONE_OF_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <zen/algorithm/any_of.h>


namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((none_of)(const r, f)
        if (is_range_or_sequence<r>)(not any_of(r, f))
    )

}

#endif
