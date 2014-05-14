/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    empty.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_ALGORITHM_EMPTY_H
#define ZEN_GUARD_ALGORITHM_EMPTY_H

#include <zen/function/builder.h>
#include <zen/range/range_traits.h>

#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/support/is_sequence.hpp>

namespace zen { 

ZEN_FUNCTION_PIPE_OBJECT((empty)(auto&& r)
        if (_p<boost::fusion::traits::is_sequence>(r))(boost::fusion::empty(r)) 
        else if (_p<is_range>(r))(zen::begin(r) == zen::end(r))
    )

}

#endif
