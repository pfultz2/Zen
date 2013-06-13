/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    any_of.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_ANY_OF_H
#define ZEN_GUARD_ALGORITHM_ANY_OF_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/fusion/algorithm/query/any.hpp>
#include <algorithm>


namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((any_of)(r, f)
        if (is_sequence<r>)(boost::fusion::any(r, f))
        else if (is_range<r>)(std::find_if(boost::begin(r), boost::end(r), f) != boost::end(r))

    )

}

#endif
