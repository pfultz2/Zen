/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    empty.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_EMPTY_H
#define ZEN_GUARD_ALGORITHM_EMPTY_H

#include <zen/function/builder.h>
#include <zen/traits.h>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>

#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <algorithm>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((empty)(r)
        if (is_sequence<r>)(boost::fusion::empty(r)) 
        else if (is_range<r>)(boost::empty(r))
    )

}

#endif
