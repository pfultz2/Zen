/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    distance.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef ZEN_GUARD_RANGE_DISTANCE_H
#define ZEN_GUARD_RANGE_DISTANCE_H

#include <zen/iterator/distance.h>
#include <zen/range/range_traits.h>

namespace zen {

template<class Range>
auto distance(Range&& r) ZEN_RETURNS(detail::distance(zen::begin(r), zen::end(r)));

}

#endif